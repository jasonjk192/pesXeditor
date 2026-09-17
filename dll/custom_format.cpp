#include "custom_format.h"
#include <locale>
#include <codecvt>

#pragma region Custom Formats

static std::string csv_escape(const std::string& value)
{
	bool needsQuotes = false;
	for (char c : value)
	{
		if (c == ',' || c == '"' || c == '\n' || c == '\r')
		{
			needsQuotes = true;
			break;
		}
	}
	if (!needsQuotes)
		return std::string(value);

	std::string result;
	result.reserve(value.size() + 2);

	result.push_back('"');

	for (std::string::const_iterator it = value.begin(); it != value.end(); ++it)
	{
		if (*it == '"')
			result += "\"\"";
		else
			result.push_back(*it);
	}

	result.push_back('"');
	return result;
}

static void csv_write_separator(std::ofstream& file, bool& first)
{
	if (!first)
		file << ',';
	first = false;
}

static std::string utf16_to_utf8(const uint16_t* str, size_t maxLength)
{
	std::u16string value;
	for (size_t i = 0; i < maxLength; ++i)
	{
		if (str[i] == 0)
			break;
		value.push_back(static_cast<char16_t>(str[i]));
	}

	/*
	 * codecvt is deprecated in newer C++, but it is available in C++14
	 * and is perfectly adequate if C++14 compatibility is required.
	 */
	std::wstring_convert<		std::codecvt_utf8_utf16<char16_t>, char16_t	> converter;
	return converter.to_bytes(value);
}

static void csv_write_uint(std::ofstream& file, bool& first, uint32_t value)
{
	csv_write_separator(file, first);
	file << value;
}

static void csv_write_int(std::ofstream& file, bool& first, int32_t value)
{
	csv_write_separator(file, first);
	file << value;
}

static void csv_write_int8(std::ofstream& file, bool& first, int8_t value)
{
	csv_write_separator(file, first);
	file << static_cast<int>(value);
}

static void csv_write_uint8(std::ofstream& file, bool& first, uint8_t value)
{
	csv_write_separator(file, first);
	file << static_cast<unsigned int>(value);
}

static void csv_write_string(std::ofstream& file, bool first, std::string str)
{
	csv_write_separator(file, first);
	file << csv_escape(str);
}

static void write_player_csv_header(std::ofstream& file)
{
	bool first = true;
	auto header = [&](const char* name)
		{
			csv_write_string(file, first, name);
		};

	header("id");
	header("app_id");
	header("b_changed");
	header("b_show");
	header("team_ind");
	header("team_lineup_ind");

	header("data_nation");
	header("data_height");
	header("data_weight");

	header("data_gc1");
	header("data_gc2");

	header("data_atk");
	header("data_def");
	header("data_gk");
	header("data_drib");

	header("data_mo_fk");
	header("data_finish");
	header("data_lowpass");
	header("data_loftpass");
	header("data_header");
	header("data_form");

	header("data_b_edit_player");

	header("data_swerve");
	header("data_catching");
	header("data_clearing");
	header("data_reflex");
	header("data_injury");

	header("data_b_edit_basicset");

	header("data_body_ctrl");
	header("data_phys_cont");
	header("data_kick_pwr");
	header("data_exp_pwr");

	header("data_mo_armd");

	header("data_b_edit_regpos");

	header("data_age");
	header("data_reg_pos");
	header("data_play_style");
	header("data_ball_ctrl");
	header("data_ball_win");
	header("data_weak_acc");
	header("data_jump");

	header("data_mo_armr");
	header("data_mo_ck");
	header("data_cover");
	header("data_weak_use");

	for (int i = 0; i < 13; ++i)
	{
		char name[32];
		std::snprintf(name, sizeof(name), "data_play_pos_%d", i);
		header(name);
	}

	header("data_mo_hunchd");
	header("data_mo_hunchr");
	header("data_mo_pk");
	header("data_place_kick");

	header("data_star");
	header("data_mo_drib");
	header("data_tight_pos");
	header("data_aggres");
	header("data_play_attit");

	header("data_b_edit_playpos");
	header("data_b_edit_ability");
	header("data_b_edit_skill");

	header("data_stamina");
	header("data_speed");

	header("data_b_edit_style");
	header("data_b_edit_com");
	header("data_b_edit_motion");
	header("data_b_base_copy");

	header("data_strong_foot");
	header("data_strong_hand");

	for (int i = 0; i < 7; ++i)
	{
		char name[32];
		std::snprintf(name, sizeof(name), "data_com_style_%d", i);
		header(name);
	}

	for (int i = 0; i < 41; ++i)
	{
		char name[32];
		std::snprintf(name, sizeof(name), "data_play_skill_%d", i);
		header(name);
	}

	header("data_name");
	header("data_shirt_name");

	header("data_b_edit_face");
	header("data_b_edit_hair");
	header("data_b_edit_phys");
	header("data_b_edit_strip");

	header("data_boot_id");
	header("data_glove_id");
	header("data_copy_id");

	header("data_neck_len");
	header("data_neck_size");
	header("data_shldr_hi");
	header("data_shldr_wid");
	header("data_chest");
	header("data_waist");
	header("data_arm_size");
	header("data_arm_len");
	header("data_thigh");
	header("data_calf");
	header("data_leg_len");
	header("data_head_len");
	header("data_head_wid");
	header("data_head_dep");

	header("data_wrist_col_l");
	header("data_wrist_col_r");
	header("data_wrist_tape");
	header("data_spec_col");
	header("data_spec_style");
	header("data_sleeve");
	header("data_inners");
	header("data_socks");
	header("data_undershorts");

	header("data_untucked");
	header("data_ankle_tape");
	header("data_gloves");

	header("data_gloves_col");
	header("data_skin_col");
	header("data_iris_col");

	file << '\n';
}

static void write_player_csv_row(std::ofstream& file, const editor_player_entry& player)
{
	bool first = true;
	const editor_player_export& data = player.data;

	/* editor_player_entry */

	csv_write_uint(file, first, player.id);
	csv_write_uint(file, first, player.app_id);
	csv_write_uint8(file, first, player.b_changed);
	csv_write_uint8(file, first, player.b_show);
	csv_write_int(file, first, player.team_ind);
	csv_write_int(file, first, player.team_lineup_ind);

	/* editor_player_export */

	csv_write_uint(file, first, data.nation);

	csv_write_uint8(file, first, data.height);
	csv_write_uint8(file, first, data.weight);

	csv_write_uint8(file, first, data.gc1);
	csv_write_uint8(file, first, data.gc2);

	csv_write_uint8(file, first, data.atk);
	csv_write_uint8(file, first, data.def);
	csv_write_uint8(file, first, data.gk);
	csv_write_uint8(file, first, data.drib);

	csv_write_uint8(file, first, data.mo_fk);
	csv_write_uint8(file, first, data.finish);
	csv_write_uint8(file, first, data.lowpass);
	csv_write_uint8(file, first, data.loftpass);
	csv_write_uint8(file, first, data.header);
	csv_write_uint8(file, first, data.form);

	csv_write_uint8(file, first, data.b_edit_player);

	csv_write_uint8(file, first, data.swerve);
	csv_write_uint8(file, first, data.catching);
	csv_write_uint8(file, first, data.clearing);
	csv_write_uint8(file, first, data.reflex);
	csv_write_uint8(file, first, data.injury);

	csv_write_uint8(file, first, data.b_edit_basicset);

	csv_write_uint8(file, first, data.body_ctrl);
	csv_write_uint8(file, first, data.phys_cont);
	csv_write_uint8(file, first, data.kick_pwr);
	csv_write_uint8(file, first, data.exp_pwr);

	csv_write_uint8(file, first, data.mo_armd);

	csv_write_uint8(file, first, data.b_edit_regpos);

	csv_write_uint8(file, first, data.age);
	csv_write_uint8(file, first, data.reg_pos);
	csv_write_uint8(file, first, data.play_style);
	csv_write_uint8(file, first, data.ball_ctrl);
	csv_write_uint8(file, first, data.ball_win);
	csv_write_uint8(file, first, data.weak_acc);
	csv_write_uint8(file, first, data.jump);

	csv_write_uint8(file, first, data.mo_armr);
	csv_write_uint8(file, first, data.mo_ck);
	csv_write_uint8(file, first, data.cover);
	csv_write_uint8(file, first, data.weak_use);

	for (int i = 0; i < 13; ++i)
	{
		csv_write_uint8(file, first, data.play_pos[i]);
	}

	csv_write_uint8(file, first, data.mo_hunchd);
	csv_write_uint8(file, first, data.mo_hunchr);
	csv_write_uint8(file, first, data.mo_pk);
	csv_write_uint8(file, first, data.place_kick);

	csv_write_uint8(file, first, data.star);
	csv_write_uint8(file, first, data.mo_drib);
	csv_write_uint8(file, first, data.tight_pos);
	csv_write_uint8(file, first, data.aggres);
	csv_write_uint8(file, first, data.play_attit);

	csv_write_uint8(file, first, data.b_edit_playpos);
	csv_write_uint8(file, first, data.b_edit_ability);
	csv_write_uint8(file, first, data.b_edit_skill);

	csv_write_uint8(file, first, data.stamina);
	csv_write_uint8(file, first, data.speed);

	csv_write_uint8(file, first, data.b_edit_style);
	csv_write_uint8(file, first, data.b_edit_com);
	csv_write_uint8(file, first, data.b_edit_motion);
	csv_write_uint8(file, first, data.b_base_copy);

	csv_write_uint8(file, first, data.strong_foot);
	csv_write_uint8(file, first, data.strong_hand);

	for (int i = 0; i < 7; ++i)
	{
		csv_write_uint8(file, first, data.com_style[i]);
	}

	for (int i = 0; i < 41; ++i)
	{
		csv_write_uint8(file, first, data.play_skill[i]);
	}

	/* UTF-16 player name -> UTF-8 CSV field.*/
	const std::string name = utf16_to_utf8(data.name, 61);
	csv_write_string(file, first, name);

	/* shirt_name is already a char array. Ensure it doesn't accidentally run beyond its fixed buffer. */
	size_t shirtNameLength = 0;

	while (shirtNameLength < sizeof(data.shirt_name) &&
		data.shirt_name[shirtNameLength] != '\0')
	{
		++shirtNameLength;
	}

	std::string shirt_name_str = std::string(data.shirt_name, shirtNameLength);
	csv_write_string(file, first, shirt_name_str);

	csv_write_uint8(file, first, data.b_edit_face);
	csv_write_uint8(file, first, data.b_edit_hair);
	csv_write_uint8(file, first, data.b_edit_phys);
	csv_write_uint8(file, first, data.b_edit_strip);

	csv_write_uint(file, first, data.boot_id);
	csv_write_uint(file, first, data.glove_id);
	csv_write_uint(file, first, data.copy_id);

	csv_write_int(file, first, data.neck_len);
	csv_write_int(file, first, data.neck_size);
	csv_write_int(file, first, data.shldr_hi);
	csv_write_int(file, first, data.shldr_wid);
	csv_write_int(file, first, data.chest);
	csv_write_int(file, first, data.waist);
	csv_write_int(file, first, data.arm_size);
	csv_write_int(file, first, data.arm_len);
	csv_write_int(file, first, data.thigh);
	csv_write_int(file, first, data.calf);
	csv_write_int(file, first, data.leg_len);
	csv_write_int(file, first, data.head_len);
	csv_write_int(file, first, data.head_wid);
	csv_write_int(file, first, data.head_dep);

	csv_write_uint8(file, first, data.wrist_col_l);
	csv_write_uint8(file, first, data.wrist_col_r);
	csv_write_uint8(file, first, data.wrist_tape);
	csv_write_uint8(file, first, data.spec_col);
	csv_write_uint8(file, first, data.spec_style);
	csv_write_uint8(file, first, data.sleeve);
	csv_write_uint8(file, first, data.inners);
	csv_write_uint8(file, first, data.socks);
	csv_write_uint8(file, first, data.undershorts);

	csv_write_uint8(file, first, data.untucked);
	csv_write_uint8(file, first, data.ankle_tape);
	csv_write_uint8(file, first, data.gloves);

	csv_write_uint8(file, first, data.gloves_col);
	csv_write_uint8(file, first, data.skin_col);
	csv_write_uint8(file, first, data.iris_col);

	file << '\n';
}

EDITOR_EXPORT EditorOpResult editor_export_player_csv(uint32_t id, const editor_player_entry* players, uint32_t numPlayers, const editor_cache* cache, const char* filePath)
{
	if (!players || !cache || !filePath)
		return EditorOpResult::INVALID_ARGUMENT;
	uint32_t playerIndex = 0;

	EditorOpResult result = editor_playerIndexByID(cache, id, &playerIndex);
	if (result != EditorOpResult::OK)
		return result;

	if (playerIndex >= numPlayers)
		return EditorOpResult::UNKNOWN; // player not found

	editor_player_entry player = players[playerIndex];

	std::ofstream outStream(filePath);
	if (outStream.is_open())
	{
		write_player_csv_row(outStream, player);
		outStream.close();

		return EditorOpResult::OK;
	}
	else
	{
		return EditorOpResult::OPEN_FAILED;
	}
}

#pragma endregion
