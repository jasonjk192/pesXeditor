#include "validator.h"

static inline EditorOpResult validate_bool(uint8_t v)
{
	return (v <= 1) ? EditorOpResult::OK : EditorOpResult::VALIDATION_ERROR_BOOLEAN;
}

static inline EditorOpResult validate_stat(uint8_t v)
{
	return (v >= 40 && v <= 99) ? EditorOpResult::OK : EditorOpResult::VALIDATION_ERROR_RANGE;
}

static inline EditorOpResult validate_stat(uint8_t v, uint8_t inclusive_min, uint8_t inclusive_max)
{
	return (v >= inclusive_min && v <= inclusive_max) ? EditorOpResult::OK : EditorOpResult::VALIDATION_ERROR_RANGE;
}

static inline EditorOpResult validate_stat_0_99(uint8_t v)
{
	// Useful for fields where 0 may represent "unset"/default.
	return (v <= 99) ? EditorOpResult::OK : EditorOpResult::VALIDATION_ERROR_RANGE;
}

static inline EditorOpResult validate_non_negative(int32_t v)
{
	return (v >= 0) ? EditorOpResult::OK : EditorOpResult::VALIDATION_ERROR_NEGATIVE;
}

static inline EditorOpResult validate_string(uint16_t* v, uint8_t l)
{
	bool name_terminated = false;
	for (size_t i = 0; i < l; ++i)
	{
		if (v[i] == 0)
		{
			name_terminated = true;
			break;
		}
	}
	if (!name_terminated)
		return EditorOpResult::VALIDATION_ERROR_STRING;
	return EditorOpResult::OK;
}

static inline EditorOpResult validate_string(char* v, uint8_t l)
{
	bool name_terminated = false;
	for (size_t i = 0; i < l; ++i)
	{
		if (v[i] == 0)
		{
			name_terminated = true;
			break;
		}
	}
	if (!name_terminated)
		return EditorOpResult::VALIDATION_ERROR_STRING;
	return EditorOpResult::OK;
}

static inline EditorOpResult validate_array_0_99(const uint8_t* values, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		if (values[i] > 99)
			return EditorOpResult::VALIDATION_ERROR_RANGE;
	}
	return EditorOpResult::OK;
}

static EditorOpResult validate_height_weight(uint8_t* height, uint8_t* weight, uint8_t* version)
{
	switch (*version)
	{
	case 15: // unsure 
		break;
	case 16:
	case 17:
		if (*height < 155 || *height > 210)
			return EditorOpResult::VALIDATION_ERROR_RANGE;
		if (*weight < max(30, *height - 129) || *weight > *height - 81)
			return EditorOpResult::VALIDATION_ERROR_RANGE;
		break;
	case 18:
		if (*height < 138 || *height > 210)
			return EditorOpResult::VALIDATION_ERROR_RANGE;
		if (*weight < max(30, *height - 129) || *weight > *height - 81)
			return EditorOpResult::VALIDATION_ERROR_RANGE;
		break;
	case 19:
	case 20:
	case 21:
		if (*height < 155 || *height > 210)
			return EditorOpResult::VALIDATION_ERROR_RANGE;
		if (*weight < max(30, *height - 129) || *weight > *height - 81)
			return EditorOpResult::VALIDATION_ERROR_RANGE;
		break;
	}
	return EditorOpResult::OK;
}

static EditorOpResult validate_age(uint8_t* age, uint8_t* version)
{
	uint8_t value = *age;
	if (value < 15 || value > 50)
		return EditorOpResult::VALIDATION_ERROR_RANGE;
	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_validateSinglePlayerEntry(editor_player_entry* player, uint8_t* version)
{
	if (!player)
		return EditorOpResult::VALIDATION_ERROR_NULL;

	editor_player_export p = player->data;
	//if (player->id == 0)
	//	return EditorOpResult::VALIDATION_ERROR_ID;

	//if (player->app_id == 0)
	//	return EditorOpResult::VALIDATION_ERROR_ID;

	if (player->b_changed > 1)
		return EditorOpResult::VALIDATION_ERROR_BOOLEAN;

	if (player->b_show > 1)
		return EditorOpResult::VALIDATION_ERROR_BOOLEAN;

	if (player->team_ind < 0 || player->team_lineup_ind < 0)
		return EditorOpResult::VALIDATION_ERROR_NEGATIVE;

	if (validate_height_weight(&p.height, &p.weight, version) != EditorOpResult::OK)
		return EditorOpResult::VALIDATION_ERROR_RANGE;

	if (validate_age(&p.age, version) != EditorOpResult::OK)
		return EditorOpResult::VALIDATION_ERROR_RANGE;

	// ------------------------------------------------------------
	// Player abilities

#define VALIDATE_STAT(field)                                      \
    do {                                                          \
        EditorOpResult r = validate_stat(p.field);                     \
        if (r != EditorOpResult::OK)                                    \
            return r;                                             \
    } while (0)

#define VALIDATE_STAT_RANGE(field, i_min, i_max)                  \
    do {                                                          \
        EditorOpResult r = validate_stat(p.field, i_min, i_max);        \
        if (r != EditorOpResult::OK)                                    \
            return r;                                             \
    } while (0)

	VALIDATE_STAT(atk);
	VALIDATE_STAT(def);
	VALIDATE_STAT(gk);
	VALIDATE_STAT(drib);
	VALIDATE_STAT(mo_fk);
	VALIDATE_STAT(finish);
	VALIDATE_STAT(lowpass);
	VALIDATE_STAT(loftpass);
	VALIDATE_STAT(header);
	VALIDATE_STAT(form);

	VALIDATE_STAT(swerve);
	VALIDATE_STAT(catching);
	VALIDATE_STAT(clearing);
	VALIDATE_STAT(reflex);
	VALIDATE_STAT(injury);

	VALIDATE_STAT(body_ctrl);
	VALIDATE_STAT(phys_cont);
	VALIDATE_STAT(kick_pwr);
	VALIDATE_STAT(exp_pwr);

	VALIDATE_STAT(ball_ctrl);
	VALIDATE_STAT(ball_win);
	VALIDATE_STAT_RANGE(weak_acc, 0, 3);
	VALIDATE_STAT(jump);

	VALIDATE_STAT_RANGE(mo_armr, 0, 7);
	VALIDATE_STAT_RANGE(mo_ck, 0, 5);
	VALIDATE_STAT(cover);
	VALIDATE_STAT_RANGE(weak_use, 0, 3);

	VALIDATE_STAT(place_kick);

	VALIDATE_STAT(stamina);
	VALIDATE_STAT(speed);

	VALIDATE_STAT(tight_pos);
	VALIDATE_STAT(aggres);
	VALIDATE_STAT(play_attit);

#undef VALIDATE_STAT


	// ------------------------------------------------------------
	// Boolean/edit flags

#define VALIDATE_BOOL(field)                                     \
    do {                                                          \
        EditorOpResult r = validate_bool(p.field);                     \
        if (r != EditorOpResult::OK)                                    \
            return r;                                             \
    } while (0)

	VALIDATE_BOOL(b_edit_player);
	VALIDATE_BOOL(b_edit_basicset);
	VALIDATE_BOOL(b_edit_regpos);
	VALIDATE_BOOL(b_edit_playpos);
	VALIDATE_BOOL(b_edit_ability);
	VALIDATE_BOOL(b_edit_skill);
	VALIDATE_BOOL(b_edit_style);
	VALIDATE_BOOL(b_edit_com);
	VALIDATE_BOOL(b_edit_motion);
	VALIDATE_BOOL(b_base_copy);
	VALIDATE_BOOL(b_edit_face);
	VALIDATE_BOOL(b_edit_hair);
	VALIDATE_BOOL(b_edit_phys);
	VALIDATE_BOOL(b_edit_strip);

#undef VALIDATE_BOOL


	// ------------------------------------------------------------
	// Arrays

	for (size_t i = 0; i < 13; ++i)
	{
		if (p.play_pos[i] > 99)
			return EditorOpResult::VALIDATION_ERROR_ENUM;
	}

	for (size_t i = 0; i < 7; ++i)
	{
		if (p.com_style[i] > 99)
			return EditorOpResult::VALIDATION_ERROR_ENUM;
	}

	for (size_t i = 0; i < 41; ++i)
	{
		if (p.play_skill[i] > 99)
			return EditorOpResult::VALIDATION_ERROR_ENUM;
	}


	// ------------------------------------------------------------
	// Signed physique values

#define VALIDATE_NON_NEGATIVE(field)                             \
    do {                                                          \
        EditorOpResult r = validate_non_negative(p.field);             \
        if (r != EditorOpResult::OK)                                    \
            return r;                                             \
    } while (0)

	VALIDATE_NON_NEGATIVE(neck_len);
	VALIDATE_NON_NEGATIVE(neck_size);
	VALIDATE_NON_NEGATIVE(shldr_hi);
	VALIDATE_NON_NEGATIVE(shldr_wid);
	VALIDATE_NON_NEGATIVE(chest);
	VALIDATE_NON_NEGATIVE(waist);
	VALIDATE_NON_NEGATIVE(arm_size);
	VALIDATE_NON_NEGATIVE(arm_len);
	VALIDATE_NON_NEGATIVE(thigh);
	VALIDATE_NON_NEGATIVE(calf);
	VALIDATE_NON_NEGATIVE(leg_len);
	VALIDATE_NON_NEGATIVE(head_len);
	VALIDATE_NON_NEGATIVE(head_wid);
	VALIDATE_NON_NEGATIVE(head_dep);

#undef VALIDATE_NON_NEGATIVE


	// ------------------------------------------------------------
	// Names

#define VALIDATE_STRING(field, length)                   \
    do {                                                 \
        EditorOpResult r = validate_string(field, length);   \
        if (r != EditorOpResult::OK)                           \
            return r;                                    \
    } while (0)


	VALIDATE_STRING(p.name, 61);
	VALIDATE_STRING(p.shirt_name, 21);

#undef VALIDATE_STRING

	//if (p.b_base_copy && p.copy_id == 0)
	//	return EditorOpResult::VALIDATION_ERROR_INCONSISTENT;

	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_validateSingleTeamEntry(editor_team_entry* team, uint8_t* version)
{
	if (!team)
		return EditorOpResult::VALIDATION_ERROR_NULL;

	// ------------------------------------------------------------
	// Names

#define VALIDATE_STRING(field, length)                   \
    do {                                                 \
        EditorOpResult r = validate_string(field, length);     \
        if (r != EditorOpResult::OK)                           \
            return r;                                    \
    } while (0)


	VALIDATE_STRING(team->name, 70);
	VALIDATE_STRING(team->short_name, 4);

#undef VALIDATE_STRING

	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_validateData(editor_player_entry* players, int numPlayers, editor_team_entry* teams, int numTeams, uint8_t* version)
{
	EditorOpResult result = EditorOpResult::OK;
	for (int pi = 0; pi < numPlayers; pi++)
	{
		editor_player_entry* player = &players[pi];
		result = editor_validateSinglePlayerEntry(player, version);
		if (result != EditorOpResult::OK)
			return result;
	}

	for (int ti = 0; ti < numTeams; ti++)
	{
		editor_team_entry* team = &teams[ti];
		result = editor_validateSingleTeamEntry(team, version);
		if (result != EditorOpResult::OK)
			return result;
	}

	return result;
}