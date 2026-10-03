#include "csv.h"
#include <locale>
#include <codecvt>

struct named_index
{
	const char* name;
	int index;
};

static constexpr named_index play_pos_names[] =
{
	{ "GK",  12 },
	{ "CB",   9 },
	{ "LB",  10 },
	{ "RB",  11 },
	{ "DMF",  5 },
	{ "CMF",  6 },
	{ "LMF",  7 },
	{ "RMF",  8 },
	{ "AMF",  4 },
	{ "LWF",  2 },
	{ "RWF",  3 },
	{ "SS",   1 },
	{ "CF",   0 },
};

static constexpr named_index com_style_names[] =
{
	{ "trickster",       0 },
	{ "mazing_run",      1 },
	{ "speeding_bullet", 2 },
	{ "incisive_run",    3 },
	{ "long_ball_expert",4 },
	{ "early_cross",     5 },
	{ "long_ranger",     6 },
};

static constexpr named_index play_skill_names[] =
{
	{ "scissors_feint",          0 },
	{ "flip_flap",               1 },
	{ "marseille_turn",           2 },
	{ "sombrero",                 3 },
	{ "cut_behind_turn",          4 },
	{ "scotch_move",              5 },
	{ "heading",                  6 },
	{ "long_range_drive",         7 },
	{ "knuckle_shot",              8 },
	{ "acro_finishing",            9 },
	{ "heel_trick",               10 },
	{ "first_time_shot",           11 },
	{ "one_touch_pass",             12 },
	{ "weighted_pass",              13 },
	{ "pinpoint_crossing",           14 },
	{ "outside_curler",              15 },
	{ "rabona",                      16 },
	{ "low_lofted_pass",             17 },
	{ "low_punt_trajectory",         18 },
	{ "long_throw",                  19 },
	{ "gk_long_throw",               20 },
	{ "malicia",                     21 },
	{ "man_marking",                 22 },
	{ "track_back",                  23 },
	{ "acro_clear",                  24 },
	{ "captaincy",                   25 },
	{ "super_sub",                   26 },
	{ "fighting_spirit",             27 },
	{ "double_touch",                28 },
	{ "crossover_turn",              29 },
	{ "step_on_skill",               30 },
	{ "chip_shot",                   31 },
	{ "dipping_shots",               32 },
	{ "rising_shots",                33 },
	{ "no_look_pass",                34 },
	{ "gk_high_punt_trajectory",     35 },
	{ "penalty_specialist",          36 },
	{ "gk_penalty_specialist",       37 },
	{ "interception",                38 },
	{ "long_range_shooting",         39 },
	{ "through_passing",             40 },
};


static std::string utf16_to_utf8(const uint16_t* utf16_str, size_t max_len)
{
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	size_t len = 0;
	while (len < max_len && utf16_str[len] != 0)
	{
		len++;
	}
	try
	{
		return convert.to_bytes(reinterpret_cast<const char16_t*>(utf16_str), reinterpret_cast<const char16_t*>(utf16_str + len));
	}
	catch (...)
	{
		return "";
	}
}

static std::u16string utf16_string(const uint16_t* utf16_str, size_t max_len)
{
	if (!utf16_str || max_len == 0) return {};
	size_t actual_len = 0;
	while (actual_len < max_len && utf16_str[actual_len] != 0)
	{
		actual_len++;
	}
	return std::u16string(reinterpret_cast<const char16_t*>(utf16_str), actual_len);
}

static bool utf8_to_utf16(const std::string& src, uint16_t* dst, size_t dst_count)
{
	if (!dst || dst_count == 0)
		return false;

	std::fill(dst, dst + dst_count, uint16_t(0));

	if (src.empty())
		return true;

	int required = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, src.data(), static_cast<int>(src.size()), nullptr, 0);
	if (required <= 0)
		return false;

	const int max_chars = static_cast<int>(dst_count - 1);
	const int chars_to_copy = min(required, max_chars);

	if (MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, src.data(), static_cast<int>(src.size()), reinterpret_cast<wchar_t*>(dst), chars_to_copy) <= 0)
	{
		return false;
	}

	dst[chars_to_copy] = 0;
	return true;
}

static std::unordered_map<std::string, size_t> make_csv_header_map(const rapidcsv::Document& doc)
{
	std::unordered_map<std::string, size_t> result;
	const auto headers = doc.GetColumnNames();
	for (size_t i = 0; i < headers.size(); ++i)
		result.emplace(headers[i], i);
	return result;
}

static bool validate_players_csv_headers(const std::vector<std::string>& headers)
{
	// TODO: check headers
	return true;
}

static bool validate_teams_csv_headers(const std::vector<std::string>& headers)
{
	// TODO: check headers
	return true;
}

static void write_headers(rapidcsv::Document& doc, const std::vector<std::string>& headers)
{
	for (size_t i = 0; i < headers.size(); ++i)
		doc.SetColumnName(i, headers[i]);
}

static bool write_schema_version_comment(const char* filePath, std::ofstream& outStream)
{
	/*if (!filePath || filePath[0] == '\0' || !outStream) 
		return false;
	
	outStream << "# csv_schema: 1.0\n";
	if (!outStream)
		return false;*/

	return true;
}

#pragma region EXPORT

static void write_player_data_header_csv(std::vector<std::string>& headers)
{
#define ADD_HEADER(fieldName) headers.push_back(#fieldName);

	ADD_HEADER(id);
	//ADD_HEADER(app_id);
	//ADD_HEADER(b_changed);
	//ADD_HEADER(b_show);
	//ADD_HEADER(team_ind);
	//ADD_HEADER(team_lineup_ind);

	ADD_HEADER(nation);
	ADD_HEADER(height);
	ADD_HEADER(weight);
	ADD_HEADER(gc1);
	ADD_HEADER(gc2);
	ADD_HEADER(atk);
	ADD_HEADER(def);
	ADD_HEADER(gk);
	ADD_HEADER(drib);
	ADD_HEADER(mo_fk);
	ADD_HEADER(finish);
	ADD_HEADER(lowpass);
	ADD_HEADER(loftpass);
	ADD_HEADER(header);
	ADD_HEADER(form);
	ADD_HEADER(b_edit_player);
	ADD_HEADER(swerve);
	ADD_HEADER(catching);
	ADD_HEADER(clearing);
	ADD_HEADER(reflex);
	ADD_HEADER(injury);
	ADD_HEADER(b_edit_basicset);
	ADD_HEADER(body_ctrl);
	ADD_HEADER(phys_cont);
	ADD_HEADER(kick_pwr);
	ADD_HEADER(exp_pwr);
	ADD_HEADER(mo_armd);
	ADD_HEADER(b_edit_regpos);
	ADD_HEADER(age);
	ADD_HEADER(reg_pos);
	ADD_HEADER(play_style);
	ADD_HEADER(ball_ctrl);
	ADD_HEADER(ball_win);
	ADD_HEADER(weak_acc);
	ADD_HEADER(jump);
	ADD_HEADER(mo_armr);
	ADD_HEADER(mo_ck);
	ADD_HEADER(cover);
	ADD_HEADER(weak_use);

	for (const auto& pos : play_pos_names)
	{
		headers.push_back("play_pos_" + std::string(pos.name));
	}

	ADD_HEADER(mo_hunchd);
	ADD_HEADER(mo_hunchr);
	ADD_HEADER(mo_pk);
	ADD_HEADER(place_kick);
	ADD_HEADER(star);
	ADD_HEADER(mo_drib);
	ADD_HEADER(tight_pos);
	ADD_HEADER(aggres);
	ADD_HEADER(play_attit);
	ADD_HEADER(b_edit_playpos);
	ADD_HEADER(b_edit_ability);
	ADD_HEADER(b_edit_skill);
	ADD_HEADER(stamina);
	ADD_HEADER(speed);
	ADD_HEADER(b_edit_style);
	ADD_HEADER(b_edit_com);
	ADD_HEADER(b_edit_motion);
	ADD_HEADER(b_base_copy);
	ADD_HEADER(strong_foot);
	ADD_HEADER(strong_hand);

	for (const auto& style : com_style_names)
	{
		headers.push_back("com_style_" + std::string(style.name));
	}

	for (const auto& skill : play_skill_names)
	{
		headers.push_back("play_skill_" + std::string(skill.name));
	}

	ADD_HEADER(name);
	ADD_HEADER(shirt_name);
	ADD_HEADER(b_edit_face);
	ADD_HEADER(b_edit_hair);
	ADD_HEADER(b_edit_phys);
	ADD_HEADER(b_edit_strip);
	ADD_HEADER(boot_id);
	ADD_HEADER(glove_id);
	ADD_HEADER(copy_id);
	ADD_HEADER(neck_len);
	ADD_HEADER(neck_size);
	ADD_HEADER(shldr_hi);
	ADD_HEADER(shldr_wid);
	ADD_HEADER(chest);
	ADD_HEADER(waist);
	ADD_HEADER(arm_size);
	ADD_HEADER(arm_len);
	ADD_HEADER(thigh);
	ADD_HEADER(calf);
	ADD_HEADER(leg_len);
	ADD_HEADER(head_len);
	ADD_HEADER(head_wid);
	ADD_HEADER(head_dep);
	ADD_HEADER(wrist_col_l);
	ADD_HEADER(wrist_col_r);
	ADD_HEADER(wrist_tape);
	ADD_HEADER(spec_col);
	ADD_HEADER(spec_style);
	ADD_HEADER(sleeve);
	ADD_HEADER(inners);
	ADD_HEADER(socks);
	ADD_HEADER(undershorts);
	ADD_HEADER(untucked);
	ADD_HEADER(ankle_tape);
	ADD_HEADER(gloves);
	ADD_HEADER(gloves_col);
	ADD_HEADER(skin_col);
	ADD_HEADER(iris_col);

#undef ADD_HEADER
}

static void write_player_data_csv(std::vector<std::string>& row, const editor_player_entry& player)
{
	const editor_player_export& data = player.data;

#define ADD_VALUE(fieldName) row.push_back(std::to_string(data.fieldName));

	row.push_back(std::to_string(player.id));
	//row.push_back(std::to_string(player.app_id));
	//row.push_back(std::to_string(player.b_changed));
	//row.push_back(std::to_string(player.b_show));
	//row.push_back(std::to_string(player.team_ind));
	//row.push_back(std::to_string(player.team_lineup_ind));

	ADD_VALUE(nation);
	ADD_VALUE(height);
	ADD_VALUE(weight);
	ADD_VALUE(gc1);
	ADD_VALUE(gc2);
	ADD_VALUE(atk);
	ADD_VALUE(def);
	ADD_VALUE(gk);
	ADD_VALUE(drib);
	ADD_VALUE(mo_fk);
	ADD_VALUE(finish);
	ADD_VALUE(lowpass);
	ADD_VALUE(loftpass);
	ADD_VALUE(header);
	ADD_VALUE(form);
	ADD_VALUE(b_edit_player);
	ADD_VALUE(swerve);
	ADD_VALUE(catching);
	ADD_VALUE(clearing);
	ADD_VALUE(reflex);
	ADD_VALUE(injury);
	ADD_VALUE(b_edit_basicset);
	ADD_VALUE(body_ctrl);
	ADD_VALUE(phys_cont);
	ADD_VALUE(kick_pwr);
	ADD_VALUE(exp_pwr);
	ADD_VALUE(mo_armd);
	ADD_VALUE(b_edit_regpos);
	ADD_VALUE(age);
	ADD_VALUE(reg_pos);
	ADD_VALUE(play_style);
	ADD_VALUE(ball_ctrl);
	ADD_VALUE(ball_win);
	ADD_VALUE(weak_acc);
	ADD_VALUE(jump);
	ADD_VALUE(mo_armr);
	ADD_VALUE(mo_ck);
	ADD_VALUE(cover);
	ADD_VALUE(weak_use);

	for (const auto& pos : play_pos_names)
	{
		row.push_back(std::to_string(data.play_pos[pos.index]));
	}

	ADD_VALUE(mo_hunchd);
	ADD_VALUE(mo_hunchr);
	ADD_VALUE(mo_pk);
	ADD_VALUE(place_kick);
	ADD_VALUE(star);
	ADD_VALUE(mo_drib);
	ADD_VALUE(tight_pos);
	ADD_VALUE(aggres);
	ADD_VALUE(play_attit);
	ADD_VALUE(b_edit_playpos);
	ADD_VALUE(b_edit_ability);
	ADD_VALUE(b_edit_skill);
	ADD_VALUE(stamina);
	ADD_VALUE(speed);
	ADD_VALUE(b_edit_style);
	ADD_VALUE(b_edit_com);
	ADD_VALUE(b_edit_motion);
	ADD_VALUE(b_base_copy);
	ADD_VALUE(strong_foot);
	ADD_VALUE(strong_hand);

	for (const auto& style : com_style_names)
	{
		row.push_back(std::to_string(data.com_style[style.index]));
	}

	for (const auto& skill : play_skill_names)
	{
		row.push_back(std::to_string(data.play_skill[skill.index]));
	}

	row.push_back(utf16_to_utf8(data.name, 61));
	row.push_back(std::string(data.shirt_name));

	ADD_VALUE(b_edit_face);
	ADD_VALUE(b_edit_hair);
	ADD_VALUE(b_edit_phys);
	ADD_VALUE(b_edit_strip);
	ADD_VALUE(boot_id);
	ADD_VALUE(glove_id);
	ADD_VALUE(copy_id);
	ADD_VALUE(neck_len);
	ADD_VALUE(neck_size);
	ADD_VALUE(shldr_hi);
	ADD_VALUE(shldr_wid);
	ADD_VALUE(chest);
	ADD_VALUE(waist);
	ADD_VALUE(arm_size);
	ADD_VALUE(arm_len);
	ADD_VALUE(thigh);
	ADD_VALUE(calf);
	ADD_VALUE(leg_len);
	ADD_VALUE(head_len);
	ADD_VALUE(head_wid);
	ADD_VALUE(head_dep);
	ADD_VALUE(wrist_col_l);
	ADD_VALUE(wrist_col_r);
	ADD_VALUE(wrist_tape);
	ADD_VALUE(spec_col);
	ADD_VALUE(spec_style);
	ADD_VALUE(sleeve);
	ADD_VALUE(inners);
	ADD_VALUE(socks);
	ADD_VALUE(undershorts);
	ADD_VALUE(untucked);
	ADD_VALUE(ankle_tape);
	ADD_VALUE(gloves);
	ADD_VALUE(gloves_col);
	ADD_VALUE(skin_col);
	ADD_VALUE(iris_col);

#undef ADD_VALUE
}

static void write_team_data_header_csv(std::vector<std::string>& headers)
{
#define ADD_HEADER(fieldName) headers.push_back(#fieldName);

	ADD_HEADER(id);
	ADD_HEADER(manager_id);
	ADD_HEADER(stadium_id);

	ADD_HEADER(name);
	ADD_HEADER(short_name);

	for (int i = 0; i < 40; ++i)
	{
		headers.push_back("players_" + std::to_string(i));
	}

	for (int i = 0; i < 40; ++i)
	{
		headers.push_back("numbers_" + std::to_string(i));
	}

	//ADD_HEADER(b_edit_name);
	//ADD_HEADER(b_edit_shortname);
	//ADD_HEADER(b_edit_stadium);
	//ADD_HEADER(b_edit_strip);

	ADD_HEADER(num_on_team);

	for (int i = 0; i < 11; ++i)
	{
		headers.push_back("starting11_" + std::to_string(i));
	}

	ADD_HEADER(captain_ind);

	ADD_HEADER(color1_red);
	ADD_HEADER(color1_blue);
	ADD_HEADER(color1_green);

	ADD_HEADER(color2_red);
	ADD_HEADER(color2_blue);
	ADD_HEADER(color2_green);

	for (int i = 0; i < 10; ++i)
	{
		headers.push_back("stripNumber_" + std::to_string(i));
		headers.push_back("stripTeamId_" + std::to_string(i));
	}

	//ADD_HEADER(b_changed);
	//ADD_HEADER(b_show);

#undef ADD_HEADER
}

static void write_team_data_csv(std::vector<std::string>& row, const editor_team_entry& team)
{
#define ADD_VALUE(fieldName) row.push_back(std::to_string(team.fieldName));

	ADD_VALUE(id);
	ADD_VALUE(manager_id);
	ADD_VALUE(stadium_id);

	row.push_back(utf16_to_utf8(team.name, 0x46));
	row.push_back(std::string(team.short_name));

	for (int i = 0; i < 40; ++i)
	{
		row.push_back(std::to_string(team.players[i]));
	}

	for (int i = 0; i < 40; ++i)
	{
		row.push_back(std::to_string(team.numbers[i]));
	}

	//ADD_VALUE(b_edit_name);
	//ADD_VALUE(b_edit_shortname);
	//ADD_VALUE(b_edit_stadium);
	//ADD_VALUE(b_edit_strip);

	ADD_VALUE(num_on_team);

	for (int i = 0; i < 11; ++i)
	{
		row.push_back(std::to_string(team.starting11[i]));
	}

	ADD_VALUE(captain_ind);

	ADD_VALUE(color1_red);
	ADD_VALUE(color1_blue);
	ADD_VALUE(color1_green);

	ADD_VALUE(color2_red);
	ADD_VALUE(color2_blue);
	ADD_VALUE(color2_green);

	for (int i = 0; i < 10; ++i)
	{
		row.push_back(std::to_string(team.stripBlock[i].stripNumber));
		row.push_back(std::to_string(team.stripBlock[i].stripTeamId));
	}

	//ADD_VALUE(b_changed);
	//ADD_VALUE(b_show);

#undef ADD_VALUE
}


EDITOR_EXPORT EditorOpResult editor_export_player_csv(const uint32_t id, const editor_player_entry* players, const editor_cache* cache, const char* filePath)
{
	if (!players || !cache || !filePath)
		return EditorOpResult::INVALID_ARGUMENT;

	uint32_t playerIndex = -1;
	EditorOpResult result = editor_playerIndexByID(cache, id, &playerIndex);
	if (result != EditorOpResult::OK)
		return result;

	const editor_player_entry& player = players[playerIndex];
	rapidcsv::Document doc("", rapidcsv::LabelParams(0, -1));
	std::vector<std::string> headers;
	std::vector<std::string> row;

	write_player_data_header_csv(headers);
	write_player_data_csv(row, player);

	try
	{
		std::ofstream outFile;
		outFile.open(filePath);
		if (!outFile.is_open())
		{
			return EditorOpResult::UNKNOWN;
		}
		if (!write_schema_version_comment(filePath, outFile))
		{
			outFile.close();
			return EditorOpResult::UNKNOWN;
		}

		doc.SetRow(0, row);
		write_headers(doc, headers);
		doc.Save(outFile);
		outFile.close();
	}
	catch (...)
	{
		return EditorOpResult::UNKNOWN;
	}

	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_export_players_csv(const uint32_t* ids, const editor_player_entry* players, uint32_t numPlayers, const editor_cache* cache, const char* filePath)
{
	if (!ids || !players || !cache || !filePath)
		return EditorOpResult::INVALID_ARGUMENT;

	uint32_t* playerIndices = new uint32_t[numPlayers];
	EditorOpResult result = editor_playerIndicesByIDs(cache, ids, numPlayers, playerIndices);
	if (result != EditorOpResult::OK)
		return result;

	rapidcsv::Document doc("", rapidcsv::LabelParams(0, -1));
	std::vector<std::string> headers;
	std::vector<std::string> row;
	write_player_data_header_csv(headers);

	try
	{
		doc.SetRow(0, headers);
		write_headers(doc, headers);
	}
	catch (...)
	{
		delete[] playerIndices;
		return EditorOpResult::UNKNOWN;
	}

	for (int pi = 0; pi < numPlayers; pi++)
	{
		uint32_t playerIndex = playerIndices[pi];
		editor_player_entry player = players[playerIndex];

		write_player_data_csv(row, player);
		try
		{
			doc.SetRow(pi, row);
		}
		catch (...)
		{
			delete[] playerIndices;
			return EditorOpResult::UNKNOWN;
		}
		row.clear();
	}

	delete[] playerIndices;
	try
	{
		std::ofstream outFile;
		outFile.open(filePath);
		if (!outFile.is_open())
		{
			return EditorOpResult::UNKNOWN;
		}
		if (!write_schema_version_comment(filePath, outFile))
		{
			outFile.close();
			return EditorOpResult::UNKNOWN;
		}

		doc.Save(outFile);
		outFile.close();
	}
	catch (...)
	{
		return EditorOpResult::UNKNOWN;
	}
	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_export_team_csv(const uint32_t id, const editor_team_entry* teams, const editor_cache* cache, const char* filePath)
{
	if (!teams || !cache || !filePath)
		return EditorOpResult::INVALID_ARGUMENT;

	uint32_t teamIndex = -1;
	EditorOpResult result = editor_teamIndexByID(cache, id, &teamIndex);
	if (result != EditorOpResult::OK)
		return result;

	const editor_team_entry& team = teams[teamIndex];
	rapidcsv::Document doc("", rapidcsv::LabelParams(0, -1));
	std::vector<std::string> headers;
	std::vector<std::string> row;

	write_team_data_header_csv(headers);
	write_team_data_csv(row, team);

	try
	{
		std::ofstream outFile;
		outFile.open(filePath);
		if (!outFile.is_open())
		{
			return EditorOpResult::UNKNOWN;
		}
		if (!write_schema_version_comment(filePath, outFile))
		{
			outFile.close();
			return EditorOpResult::UNKNOWN;
		}

		doc.InsertRow(0, headers);
		doc.InsertRow(1, row);
		doc.Save(outFile);
		outFile.close();
	}
	catch (...)
	{
		return EditorOpResult::UNKNOWN;
	}

	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_export_teams_csv(const uint32_t* ids, const editor_team_entry* teams, uint32_t numTeams, const editor_cache* cache, const char* filePath)
{
	if (!ids || !teams || !cache || !filePath)
		return EditorOpResult::INVALID_ARGUMENT;

	uint32_t* teamIndices = new uint32_t[numTeams];
	EditorOpResult result = editor_teamIndicesByIDs(cache, ids, numTeams, teamIndices);
	if (result != EditorOpResult::OK)
		return result;

	rapidcsv::Document doc("", rapidcsv::LabelParams(0, -1));
	std::vector<std::string> headers;
	std::vector<std::string> row;
	write_team_data_header_csv(headers);

	try
	{
		doc.SetRow(0, headers);
		write_headers(doc, headers);
	}
	catch (...)
	{
		delete[] teamIndices;
		return EditorOpResult::UNKNOWN;
	}

	for (int ti = 0; ti < numTeams; ti++)
	{
		uint32_t teamIndex = teamIndices[ti];
		editor_team_entry team = teams[teamIndex];

		write_team_data_csv(row, team);
		try
		{
			doc.SetRow(ti, row);
		}
		catch (...)
		{
			delete[] teamIndices;
			return EditorOpResult::UNKNOWN;
		}
		row.clear();
	}

	delete[] teamIndices;
	try
	{
		std::ofstream outFile;
		outFile.open(filePath);
		if (!outFile.is_open())
		{
			return EditorOpResult::UNKNOWN;
		}
		if (!write_schema_version_comment(filePath, outFile))
		{
			outFile.close();
			return EditorOpResult::UNKNOWN;
		}

		doc.Save(outFile);
		outFile.close();
	}
	catch (...)
	{
		return EditorOpResult::UNKNOWN;
	}
	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_export_team_players_csv(const uint32_t id, const editor_team_entry* teams, const editor_player_entry* players, const editor_cache* cache, const char* filePath)
{
	if (!teams || !cache || !filePath)
		return EditorOpResult::INVALID_ARGUMENT;

	uint32_t teamIndex = -1;
	EditorOpResult result = editor_teamIndexByID(cache, id, &teamIndex);
	if (result != EditorOpResult::OK)
		return result;

	const editor_team_entry& team = teams[teamIndex];
	const uint32_t* ids = team.players;
	result = editor_export_players_csv(ids, players, team.num_on_team, cache, filePath);
	return result;
}

EDITOR_EXPORT EditorOpResult editor_export_team_starting11_csv(const uint32_t id, const editor_team_entry* teams, const editor_player_entry* players, const editor_cache* cache, const char* filePath)
{
	if (!teams || !cache || !filePath)
		return EditorOpResult::INVALID_ARGUMENT;

	uint32_t teamIndex = -1;
	EditorOpResult result = editor_teamIndexByID(cache, id, &teamIndex);
	if (result != EditorOpResult::OK)
		return result;

	const editor_team_entry& team = teams[teamIndex];
	uint32_t* ids = team.get_starting11_ids();
	result = editor_export_players_csv(ids, players, 11, cache, filePath);

	delete[] ids;
	return result;
}

#pragma endregion

#pragma region IMPORT

EDITOR_EXPORT EditorOpResult editor_import_players_csv_auto_merge(editor_player_entry* players, const editor_cache* cache, const char* filePath)
{
	editor_player_entry* importedPlayers = nullptr;
	uint32_t outNumPlayers = 0;
	EditorOpResult result = editor_import_players_csv(filePath, &importedPlayers, &outNumPlayers);
	if (result != EditorOpResult::OK)
	{
		free_imported_players(importedPlayers);
		return result;
	}
		
	result = editor_replace_players(players, importedPlayers, outNumPlayers, cache);
	free_imported_players(importedPlayers);

	if (result != EditorOpResult::OK)
		return result;

	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_import_teams_csv_auto_merge(editor_team_entry* teams, const editor_cache* cache, const char* filePath)
{
	editor_team_entry* importedTeams = nullptr;
	uint32_t outNumTeams = 0;
	EditorOpResult result = editor_import_teams_csv(filePath, &importedTeams, &outNumTeams);
	if (result != EditorOpResult::OK)
	{
		free_imported_teams(importedTeams);
		return result;
	}

	result = editor_replace_teams(teams, importedTeams, outNumTeams, cache);
	free_imported_teams(importedTeams);

	if (result != EditorOpResult::OK)
		return result;

	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_import_players_csv(const char* filePath, editor_player_entry** outPlayers, uint32_t* outNumPlayers)
{
	if (!filePath || !outPlayers || !outNumPlayers)
		return EditorOpResult::INVALID_ARGUMENT;

	rapidcsv::Document doc(filePath);

	const auto headers = doc.GetColumnNames();
	if (!validate_players_csv_headers(headers))
		return EditorOpResult::UNKNOWN;

	std::unordered_map<std::string, size_t> column_by_name;
	column_by_name.reserve(headers.size());

	for (size_t i = 0; i < headers.size(); ++i)
		column_by_name.emplace(headers[i], i);

	auto find_column = [&](const std::string& name) -> int
		{
			auto it = column_by_name.find(name);
			if (it == column_by_name.end())
				return -1;
			return static_cast<int>(it->second);
		};

	auto get_string = [&](size_t row, const std::string& name) -> std::string
		{
			const int col = find_column(name);
			if (col < 0)
				return {};
			return doc.GetCell<std::string>(col, row);
		};

	auto get_u8 = [&](size_t row, const std::string& name, uint8_t& dst) -> bool
		{
			const int col = find_column(name);
			if (col < 0)
				return false;
			dst = static_cast<uint8_t>(doc.GetCell<unsigned int>(col, row));
			return true;
		};

	auto get_u32 = [&](size_t row, const std::string& name, uint32_t& dst) -> bool
		{
			const int col = find_column(name);
			if (col < 0)
				return false;
			dst = doc.GetCell<uint32_t>(col, row);
			return true;
		};

	auto get_i32 = [&](size_t row, const std::string& name, int32_t& dst) -> bool
		{
			const int col = find_column(name);
			if (col < 0)
				return false;
			dst = doc.GetCell<int32_t>(col, row);
			return true;
		};

	const size_t row_count = doc.GetRowCount();
	std::vector<editor_player_entry> imported;

	for (size_t row = 0; row < row_count; ++row)
	{
		uint32_t id = 0;
		if (!get_u32(row, "id", id))
			continue;

		editor_player_entry player{};
		player.id = id;
		editor_player_export& data = player.data;

#define IMPORT_U8(field) get_u8(row, #field, data.field)
#define IMPORT_U32(field) get_u32(row, #field, data.field)
#define IMPORT_I32(field) get_i32(row, #field, data.field)

		IMPORT_U32(nation);

		IMPORT_U8(height);
		IMPORT_U8(weight);

		IMPORT_U8(gc1);
		IMPORT_U8(gc2);

		IMPORT_U8(atk);
		IMPORT_U8(def);
		IMPORT_U8(gk);
		IMPORT_U8(drib);

		IMPORT_U8(mo_fk);
		IMPORT_U8(finish);
		IMPORT_U8(lowpass);
		IMPORT_U8(loftpass);
		IMPORT_U8(header);
		IMPORT_U8(form);

		IMPORT_U8(b_edit_player);

		IMPORT_U8(swerve);
		IMPORT_U8(catching);
		IMPORT_U8(clearing);
		IMPORT_U8(reflex);
		IMPORT_U8(injury);

		IMPORT_U8(b_edit_basicset);

		IMPORT_U8(body_ctrl);
		IMPORT_U8(phys_cont);
		IMPORT_U8(kick_pwr);
		IMPORT_U8(exp_pwr);

		IMPORT_U8(mo_armd);

		IMPORT_U8(b_edit_regpos);

		IMPORT_U8(age);
		IMPORT_U8(reg_pos);
		IMPORT_U8(play_style);
		IMPORT_U8(ball_ctrl);
		IMPORT_U8(ball_win);
		IMPORT_U8(weak_acc);
		IMPORT_U8(jump);

		IMPORT_U8(mo_armr);
		IMPORT_U8(mo_ck);
		IMPORT_U8(cover);
		IMPORT_U8(weak_use);

		IMPORT_U8(mo_hunchd);
		IMPORT_U8(mo_hunchr);
		IMPORT_U8(mo_pk);
		IMPORT_U8(place_kick);

		IMPORT_U8(star);
		IMPORT_U8(mo_drib);
		IMPORT_U8(tight_pos);
		IMPORT_U8(aggres);
		IMPORT_U8(play_attit);

		IMPORT_U8(b_edit_playpos);
		IMPORT_U8(b_edit_ability);
		IMPORT_U8(b_edit_skill);

		IMPORT_U8(stamina);
		IMPORT_U8(speed);

		IMPORT_U8(b_edit_style);
		IMPORT_U8(b_edit_com);
		IMPORT_U8(b_edit_motion);
		IMPORT_U8(b_base_copy);

		IMPORT_U8(strong_foot);
		IMPORT_U8(strong_hand);

		IMPORT_U32(boot_id);
		IMPORT_U32(glove_id);
		IMPORT_U32(copy_id);

		IMPORT_I32(neck_len);
		IMPORT_I32(neck_size);
		IMPORT_I32(shldr_hi);
		IMPORT_I32(shldr_wid);
		IMPORT_I32(chest);
		IMPORT_I32(waist);
		IMPORT_I32(arm_size);
		IMPORT_I32(arm_len);
		IMPORT_I32(thigh);
		IMPORT_I32(calf);
		IMPORT_I32(leg_len);
		IMPORT_I32(head_len);
		IMPORT_I32(head_wid);
		IMPORT_I32(head_dep);

		IMPORT_U8(wrist_col_l);
		IMPORT_U8(wrist_col_r);
		IMPORT_U8(wrist_tape);
		IMPORT_U8(spec_col);
		IMPORT_U8(spec_style);
		IMPORT_U8(sleeve);
		IMPORT_U8(inners);
		IMPORT_U8(socks);
		IMPORT_U8(undershorts);

		IMPORT_U8(untucked);
		IMPORT_U8(ankle_tape);
		IMPORT_U8(gloves);

		IMPORT_U8(gloves_col);
		IMPORT_U8(skin_col);
		IMPORT_U8(iris_col);

#undef IMPORT_U8
#undef IMPORT_U32
#undef IMPORT_I32

		for (const auto& pos : play_pos_names)
		{
			const std::string column = "play_pos_" + std::string(pos.name);
			get_u8(row, column, data.play_pos[pos.index]);
		}

		for (const auto& style : com_style_names)
		{
			const std::string column = "com_style_" + std::string(style.name);
			get_u8(row, column, data.com_style[style.index]);
		}

		for (const auto& skill : play_skill_names)
		{
			const std::string column = "play_skill_" + std::string(skill.name);
			get_u8(row, column, data.play_skill[skill.index]);
		}

		const std::string name = get_string(row, "name");
		if (!utf8_to_utf16(name, data.name, std::size(data.name)))
		{
			return EditorOpResult::UNKNOWN;
		}

		const std::string shirt_name = get_string(row, "shirt_name");
		std::memset(data.shirt_name, 0, sizeof(data.shirt_name));
		strncpy_s(data.shirt_name, shirt_name.c_str(), sizeof(data.shirt_name) - 1);

		player.b_changed = 1;
		imported.push_back(player);
	}

	auto* players = new editor_player_entry[imported.size()];
	std::copy(imported.begin(), imported.end(), players);
	*outPlayers = players;
	*outNumPlayers = static_cast<uint32_t>(imported.size());
	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_import_teams_csv(const char* filePath, editor_team_entry** outTeams, uint32_t* outNumTeams)
{
	if (!filePath || !outTeams || !outNumTeams)
		return EditorOpResult::INVALID_ARGUMENT;

	rapidcsv::Document doc(filePath);

	const auto headers = doc.GetColumnNames();
	if (!validate_teams_csv_headers(headers))
		return EditorOpResult::UNKNOWN;

	std::unordered_map<std::string, size_t> column_by_name;
	column_by_name.reserve(headers.size());

	for (size_t i = 0; i < headers.size(); ++i)
		column_by_name.emplace(headers[i], i);

	auto find_column = [&](const std::string& name) -> int
		{
			auto it = column_by_name.find(name);
			if (it == column_by_name.end())
				return -1;
			return static_cast<int>(it->second);
		};

	auto get_string = [&](size_t row, const std::string& name) -> std::string
		{
			const int col = find_column(name);
			if (col < 0)
				return {};
			return doc.GetCell<std::string>(col, row);
		};

	auto get_u8 = [&](size_t row, const std::string& name, uint8_t& dst) -> bool
		{
			const int col = find_column(name);
			if (col < 0)
				return false;
			dst = static_cast<uint8_t>(doc.GetCell<unsigned int>(col, row));
			return true;
		};

	auto get_u32 = [&](size_t row, const std::string& name, uint32_t& dst) -> bool
		{
			const int col = find_column(name);
			if (col < 0)
				return false;
			dst = doc.GetCell<uint32_t>(col, row);
			return true;
		};

	auto get_i32 = [&](size_t row, const std::string& name, int32_t& dst) -> bool
		{
			const int col = find_column(name);
			if (col < 0)
				return false;
			dst = doc.GetCell<int32_t>(col, row);
			return true;
		};

	auto get_i8 = [&](size_t row, const std::string& name, int8_t& dst) -> bool
		{
			const int col = find_column(name);
			if (col < 0)
				return false;
			try
			{
				dst = static_cast<int8_t>(doc.GetCell<int>(col, row));
			}
			catch (...)
			{
				return false;
			}
			return true;
		};

	auto get_u16 = [&](size_t row, const std::string& name, uint16_t& dst) -> bool
		{
			const int col = find_column(name);
			if (col < 0)
				return false;
			try
			{
				dst = static_cast<uint16_t>(doc.GetCell<unsigned int>(col, row));
			}
			catch (...)
			{
				return false;
			}
			return true;
		};

	const size_t row_count = doc.GetRowCount();
	std::vector<editor_team_entry> imported;

	for (size_t row = 0; row < row_count; ++row)
	{
		uint32_t id = 0;
		if (!get_u32(row, "id", id))
			continue;

		editor_team_entry team{};
		team.id = id;

#define IMPORT_U8(field) get_u8(row, #field, team.field)
#define IMPORT_I8(field) get_i8(row, #field, team.field)
#define IMPORT_U32(field) get_u32(row, #field, team.field)
#define IMPORT_I32(field) get_i32(row, #field, team.field)

		IMPORT_U32(manager_id);
		IMPORT_I32(stadium_id);

		IMPORT_I32(num_on_team);

		IMPORT_I8(captain_ind);

		IMPORT_I8(color1_red);
		IMPORT_I8(color1_blue);
		IMPORT_I8(color1_green);

		IMPORT_I8(color2_red);
		IMPORT_I8(color2_blue);
		IMPORT_I8(color2_green);

		const std::string name = get_string(row, "name");
		if (!utf8_to_utf16(name, team.name, std::size(team.name)))
		{
			return EditorOpResult::UNKNOWN;
		}

		const std::string short_name = get_string(row, "short_name");
		std::memset(team.short_name, 0, sizeof(team.short_name));
		strncpy_s(team.short_name, short_name.c_str(), sizeof(team.short_name) - 1);

		for (size_t i = 0; i < 40; ++i)
		{
			get_u32(row, "players_" + std::to_string(i), team.players[i]);
		}
		for (size_t i = 0; i < 40; ++i)
		{
			get_u16(row, "numbers_" + std::to_string(i), team.numbers[i]);
		}

		for (size_t i = 0; i < 11; ++i)
		{
			get_i32(row, "starting11_" + std::to_string(i), team.starting11[i]);
		}
		for (size_t i = 0; i < 10; ++i)
		{
			get_u8(row, "stripNumber_" + std::to_string(i), team.stripBlock[i].stripNumber);
			get_u32(row, "stripTeamId_" + std::to_string(i), team.stripBlock[i].stripTeamId);
		}

#undef IMPORT_U8
#undef IMPORT_I8
#undef IMPORT_U32
#undef IMPORT_I32

		team.b_changed = 1;
		imported.push_back(team);
	}

	auto* teams = new editor_team_entry[imported.size()];
	std::copy(imported.begin(), imported.end(), teams);
	*outTeams = teams;
	*outNumTeams = static_cast<uint32_t>(imported.size());
	return EditorOpResult::OK;
}

EDITOR_EXPORT void free_imported_players(const editor_player_entry* importedPlayers)
{
	if(importedPlayers) delete[] importedPlayers;
}

EDITOR_EXPORT void free_imported_teams(const editor_team_entry* importedTeams)
{
	if (importedTeams) delete[] importedTeams;
}

#pragma endregion