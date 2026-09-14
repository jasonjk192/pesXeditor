#include "masterkey.h"
#include "crypt.h"
#include "../src/editor.h"
#include "dll.h"

#pragma region Structs

editor_player_export& editor_player_export::operator=(const player_export& src)
{
	nation = src.nation;

	height = src.height;
	weight = src.weight;

	gc1 = src.gc1;
	gc2 = src.gc2;

	atk = src.atk;
	def = src.def;
	gk = src.gk;
	drib = src.drib;

	mo_fk = src.mo_fk;
	finish = src.finish;
	lowpass = src.lowpass;
	loftpass = src.loftpass;
	header = src.header;
	form = src.form;

	b_edit_player = src.b_edit_player ? 1 : 0;

	swerve = src.swerve;
	catching = src.catching;
	clearing = src.clearing;
	reflex = src.reflex;
	injury = src.injury;

	b_edit_basicset = src.b_edit_basicset ? 1 : 0;

	body_ctrl = src.body_ctrl;
	phys_cont = src.phys_cont;
	kick_pwr = src.kick_pwr;
	exp_pwr = src.exp_pwr;

	mo_armd = src.mo_armd;

	b_edit_regpos = src.b_edit_regpos ? 1 : 0;

	age = src.age;
	reg_pos = src.reg_pos;
	play_style = src.play_style;
	ball_ctrl = src.ball_ctrl;
	ball_win = src.ball_win;
	weak_acc = src.weak_acc;
	jump = src.jump;

	mo_armr = src.mo_armr;
	mo_ck = src.mo_ck;
	cover = src.cover;
	weak_use = src.weak_use;

	for (int i = 0; i < 13; ++i)
		play_pos[i] = src.play_pos[i];

	mo_hunchd = src.mo_hunchd;
	mo_hunchr = src.mo_hunchr;
	mo_pk = src.mo_pk;
	place_kick = src.place_kick;

	star = src.star;
	mo_drib = src.mo_drib;
	tight_pos = src.tight_pos;
	aggres = src.aggres;
	play_attit = src.play_attit;

	b_edit_playpos = src.b_edit_playpos ? 1 : 0;
	b_edit_ability = src.b_edit_ability ? 1 : 0;
	b_edit_skill = src.b_edit_skill ? 1 : 0;

	stamina = src.stamina;
	speed = src.speed;

	b_edit_style = src.b_edit_style ? 1 : 0;
	b_edit_com = src.b_edit_com ? 1 : 0;
	b_edit_motion = src.b_edit_motion ? 1 : 0;
	b_base_copy = src.b_base_copy ? 1 : 0;

	strong_foot = src.strong_foot;
	strong_hand = src.strong_hand;

	for (int i = 0; i < 7; ++i)
		com_style[i] = src.com_style[i] ? 1 : 0;

	for (int i = 0; i < 41; ++i)
		play_skill[i] = src.play_skill[i] ? 1 : 0;

	for (int i = 0; i < 61; ++i)
		name[i] = static_cast<uint16_t>(src.name[i]);

	for (int i = 0; i < 21; ++i)
		shirt_name[i] = src.shirt_name[i];

	b_edit_face = src.b_edit_face ? 1 : 0;
	b_edit_hair = src.b_edit_hair ? 1 : 0;
	b_edit_phys = src.b_edit_phys ? 1 : 0;
	b_edit_strip = src.b_edit_strip ? 1 : 0;

	boot_id = src.boot_id;
	glove_id = src.glove_id;
	copy_id = static_cast<uint32_t>(src.copy_id);

	neck_len = src.neck_len;
	neck_size = src.neck_size;
	shldr_hi = src.shldr_hi;
	shldr_wid = src.shldr_wid;
	chest = src.chest;
	waist = src.waist;
	arm_size = src.arm_size;
	arm_len = src.arm_len;
	thigh = src.thigh;
	calf = src.calf;
	leg_len = src.leg_len;
	head_len = src.head_len;
	head_wid = src.head_wid;
	head_dep = src.head_dep;

	wrist_col_l = src.wrist_col_l;
	wrist_col_r = src.wrist_col_r;
	wrist_tape = src.wrist_tape;
	spec_col = src.spec_col;
	spec_style = src.spec_style;
	sleeve = src.sleeve;
	inners = src.inners;
	socks = src.socks;
	undershorts = src.undershorts;

	untucked = src.untucked ? 1 : 0;
	ankle_tape = src.ankle_tape ? 1 : 0;
	gloves = src.gloves ? 1 : 0;

	gloves_col = src.gloves_col;
	skin_col = src.skin_col;
	iris_col = src.iris_col;

	return *this;
}

player_export editor_player_export::to_player_export() const
{
	player_export dst;

	dst.nation = nation;

	dst.height = height;
	dst.weight = weight;

	dst.gc1 = gc1;
	dst.gc2 = gc2;

	dst.atk = atk;
	dst.def = def;
	dst.gk = gk;
	dst.drib = drib;

	dst.mo_fk = mo_fk;
	dst.finish = finish;
	dst.lowpass = lowpass;
	dst.loftpass = loftpass;
	dst.header = header;
	dst.form = form;

	dst.b_edit_player = (b_edit_player != 0);

	dst.swerve = swerve;
	dst.catching = catching;
	dst.clearing = clearing;
	dst.reflex = reflex;
	dst.injury = injury;

	dst.b_edit_basicset = (b_edit_basicset != 0);

	dst.body_ctrl = body_ctrl;
	dst.phys_cont = phys_cont;
	dst.kick_pwr = kick_pwr;
	dst.exp_pwr = exp_pwr;

	dst.mo_armd = mo_armd;

	dst.b_edit_regpos = (b_edit_regpos != 0);

	dst.age = age;
	dst.reg_pos = reg_pos;
	dst.play_style = play_style;
	dst.ball_ctrl = ball_ctrl;
	dst.ball_win = ball_win;
	dst.weak_acc = weak_acc;
	dst.jump = jump;

	dst.mo_armr = mo_armr;
	dst.mo_ck = mo_ck;
	dst.cover = cover;
	dst.weak_use = weak_use;

	for (int i = 0; i < 13; ++i)
		dst.play_pos[i] = play_pos[i];

	dst.mo_hunchd = mo_hunchd;
	dst.mo_hunchr = mo_hunchr;
	dst.mo_pk = mo_pk;
	dst.place_kick = place_kick;

	dst.star = star;
	dst.mo_drib = mo_drib;
	dst.tight_pos = tight_pos;
	dst.aggres = aggres;
	dst.play_attit = play_attit;

	dst.b_edit_playpos = (b_edit_playpos != 0);
	dst.b_edit_ability = (b_edit_ability != 0);
	dst.b_edit_skill = (b_edit_skill != 0);

	dst.stamina = stamina;
	dst.speed = speed;

	dst.b_edit_style = (b_edit_style != 0);
	dst.b_edit_com = (b_edit_com != 0);
	dst.b_edit_motion = (b_edit_motion != 0);
	dst.b_base_copy = (b_base_copy != 0);

	dst.strong_foot = strong_foot;
	dst.strong_hand = strong_hand;

	for (int i = 0; i < 7; ++i)
		dst.com_style[i] = (com_style[i] != 0);

	for (int i = 0; i < 41; ++i)
		dst.play_skill[i] = (play_skill[i] != 0);

	for (int i = 0; i < 61; ++i)
		dst.name[i] = static_cast<wchar_t>(name[i]);

	for (int i = 0; i < 21; ++i)
		dst.shirt_name[i] = shirt_name[i];

	dst.b_edit_face = (b_edit_face != 0);
	dst.b_edit_hair = (b_edit_hair != 0);
	dst.b_edit_phys = (b_edit_phys != 0);
	dst.b_edit_strip = (b_edit_strip != 0);

	dst.boot_id = boot_id;
	dst.glove_id = glove_id;
	dst.copy_id = static_cast<unsigned long>(copy_id);

	dst.neck_len = neck_len;
	dst.neck_size = neck_size;
	dst.shldr_hi = shldr_hi;
	dst.shldr_wid = shldr_wid;
	dst.chest = chest;
	dst.waist = waist;
	dst.arm_size = arm_size;
	dst.arm_len = arm_len;
	dst.thigh = thigh;
	dst.calf = calf;
	dst.leg_len = leg_len;
	dst.head_len = head_len;
	dst.head_wid = head_wid;
	dst.head_dep = head_dep;

	dst.wrist_col_l = wrist_col_l;
	dst.wrist_col_r = wrist_col_r;
	dst.wrist_tape = wrist_tape;
	dst.spec_col = spec_col;
	dst.spec_style = spec_style;
	dst.sleeve = sleeve;
	dst.inners = inners;
	dst.socks = socks;
	dst.undershorts = undershorts;

	dst.untucked = (untucked != 0);
	dst.ankle_tape = (ankle_tape != 0);
	dst.gloves = (gloves != 0);

	dst.gloves_col = gloves_col;
	dst.skin_col = skin_col;
	dst.iris_col = iris_col;

	return dst;
}

editor_player_entry& editor_player_entry::operator=(const player_entry& src)
{
	data = static_cast<const player_export&>(src);

	id = static_cast<uint32_t>(src.id);
	app_id = static_cast<uint32_t>(src.app_id);
	b_changed = src.b_changed ? 1 : 0;
	b_show = src.b_show ? 1 : 0;
	team_ind = static_cast<int32_t>(src.team_ind);
	team_lineup_ind = static_cast<int32_t>(src.team_lineup_ind);

	return *this;
}

player_entry editor_player_entry::to_player_entry() const
{
	player_entry dst;

	// Convert the player_export portion.
	player_export export_data = data.to_player_export();

	static_cast<player_export&>(dst) = export_data;

	// player_entry-specific fields.
	dst.id = static_cast<unsigned long>(id);
	dst.app_id = static_cast<unsigned long>(app_id);
	dst.b_changed = (b_changed != 0);
	dst.b_show = (b_show != 0);
	dst.team_ind = team_ind;
	dst.team_lineup_ind = team_lineup_ind;

	return dst;
}

editor_team_entry& editor_team_entry::operator=(const team_entry& src)
{
	id = static_cast<uint32_t>(src.id);
	manager_id = static_cast<uint32_t>(src.manager_id);
	stadium_id = static_cast<int32_t>(src.stadium_id);

	// wchar_t -> UTF-16 uint16_t
	// This assumes Windows, where wchar_t is 16-bit.
	memcpy(name, src.name, sizeof(name));
	memcpy(short_name, src.short_name, sizeof(short_name));

	// Players
	for (int i = 0; i < 40; ++i)
	{
		players[i] = static_cast<uint32_t>(src.players[i]);
		numbers[i] = static_cast<uint16_t>(src.numbers[i]);
	}

	// Edit flags
	b_edit_name = src.b_edit_name ? 1 : 0;
	b_edit_shortname = src.b_edit_shortname ? 1 : 0;
	b_edit_stadium = src.b_edit_stadium ? 1 : 0;
	b_edit_strip = src.b_edit_strip ? 1 : 0;
	num_on_team = static_cast<int32_t>(src.num_on_team);

	// Starting 11
	for (int i = 0; i < 11; ++i)
	{
		starting11[i] = static_cast<int32_t>(src.starting11[i]);
	}
	captain_ind = static_cast<uint8_t>(src.captain_ind);

	// Colors
	color1_red = static_cast<uint8_t>(src.color1_red);
	color1_blue = static_cast<uint8_t>(src.color1_blue);
	color1_green = static_cast<uint8_t>(src.color1_green);
	color2_red = static_cast<uint8_t>(src.color2_red);
	color2_blue = static_cast<uint8_t>(src.color2_blue);
	color2_green = static_cast<uint8_t>(src.color2_green);

	// Strip block
	//stripBlock = new editor_strip_set[10];
	for (int i = 0; i < 10; ++i)
	{
		stripBlock[i].stripNumber = static_cast<uint8_t>(src.stripBlock[i].stripNumber);
		stripBlock[i].stripTeamId = static_cast<uint32_t>(src.stripBlock[i].stripTeamId);
	}

	// State flags
	b_changed = src.b_changed ? 1 : 0;
	b_show = src.b_show ? 1 : 0;
	return *this;
}

team_entry editor_team_entry::to_team_entry() const
{
	team_entry dst;

	dst.id = static_cast<unsigned long>(id);
	dst.manager_id = static_cast<unsigned long>(manager_id);
	dst.stadium_id = static_cast<int>(stadium_id);

	// UTF-16 uint16_t -> Windows wchar_t
	memcpy(dst.name, name, sizeof(dst.name));
	memcpy(dst.short_name, short_name, sizeof(dst.short_name));

	// Players
	for (int i = 0; i < 40; ++i)
	{
		dst.players[i] = static_cast<unsigned long>(players[i]);
		dst.numbers[i] = static_cast<uint16_t>(numbers[i]);
	}

	// Edit flags
	dst.b_edit_name = b_edit_name != 0;
	dst.b_edit_shortname = b_edit_shortname != 0;
	dst.b_edit_stadium = b_edit_stadium != 0;
	dst.b_edit_strip = b_edit_strip != 0;
	dst.num_on_team = static_cast<int>(num_on_team);

	// Starting 11
	for (int i = 0; i < 11; ++i)
	{
		dst.starting11[i] = static_cast<int>(starting11[i]);
	}
	dst.captain_ind = static_cast<char>(captain_ind);

	// Colors
	dst.color1_red = static_cast<char>(color1_red);
	dst.color1_blue = static_cast<char>(color1_blue);
	dst.color1_green = static_cast<char>(color1_green);
	dst.color2_red = static_cast<char>(color2_red);
	dst.color2_blue = static_cast<char>(color2_blue);
	dst.color2_green = static_cast<char>(color2_green);

	// Strip block
	for (int i = 0; i < 10; ++i)
	{
		dst.stripBlock[i].stripNumber = static_cast<unsigned char>(stripBlock[i].stripNumber);
		dst.stripBlock[i].stripTeamId = static_cast<unsigned long>(stripBlock[i].stripTeamId);
	}

	dst.b_changed = b_changed != 0;
	dst.b_show = b_show != 0;

	return dst;
}

#pragma endregion

#pragma region General

EDITOR_EXPORT OpResult editor_readFile(const char* path, uint8_t** outData, uint32_t* sizePtr)
{
	return readFile(path, outData, sizePtr);
}

EDITOR_EXPORT void editor_freeData(editor_player_entry* players, editor_team_entry* teams)
{
	if (players) delete[] players;
	if (teams) delete[] teams;
}

EDITOR_EXPORT void editor_freeDescriptorNew(FileDescriptorNew* descriptor)
{
	destroyFileDescriptorNew(descriptor);
}

EDITOR_EXPORT void editor_freeDescriptorOld(FileDescriptorOld* descriptor)
{
	destroyFileDescriptorOld(descriptor);
}

EDITOR_EXPORT void editor_freeDescriptor15(FileDescriptor15* descriptor)
{
	destroyFileDescriptor15(descriptor);
}

#pragma endregion

#pragma region PES15

EDITOR_EXPORT int read_player_entry15_export(editor_player_entry* out, int* current_byte, void* descriptor)
{
	if (!out || !current_byte)
		return 0;
	player_entry p;
	read_player_entry15(p, *current_byte, descriptor);
	*out = p;
	return 1;
}

#pragma endregion

#pragma region PES17

EDITOR_EXPORT OpResult editor_readFile17(const char* path, FileDescriptorOld** outDescriptor)
{
	uint8_t* pfin = NULL;
	OpResult result = readFile(path, &pfin, NULL);
	if (result != OpResult::OK)
		return result;

	const uint8_t* masterKey17 = MasterKeyPes17;
	FileDescriptorOld* descriptor = createFileDescriptorOld();
	decryptWithKeyOld(descriptor, pfin, reinterpret_cast<const char*>(masterKey17));
	*outDescriptor = descriptor;
	return OpResult::OK;
}

EDITOR_EXPORT OpResult editor_loadData17(const char* path, FileDescriptorOld** outDescriptor, editor_player_entry** outPlayers, uint32_t* outNumPlayers, editor_team_entry** outTeams, uint32_t* outNumTeams)
{
	FileDescriptorOld* descriptor = NULL;
	OpResult result = editor_readFile17(path, &descriptor);
	if (result != OpResult::OK)
		return result;

	int num_players = descriptor->data[0x5C];
	num_players += (descriptor->data[0x5D]) * 256;
	int num_teams = descriptor->data[0x60];
	num_teams += (descriptor->data[0x61]) * 256;

	int current_byte = 0x78;
	player_entry* players = new player_entry[num_players];
	*outPlayers = new editor_player_entry[num_players];
	for (int pi = 0; pi < num_players; pi++)
	{
		fill_player_entry17(players[pi], current_byte, descriptor);
		(*outPlayers)[pi] = players[pi];
	}

	current_byte = 0x3C3E58;
	team_entry* teams = new team_entry[num_teams];
	for (int ti = 0; ti < num_teams; ti++)
	{
		fill_team_ids17(teams[ti], current_byte, descriptor);
	}

	current_byte = 0x475A90;
	for (int ti = 0; ti < num_teams; ti++)
	{
		fill_team_rosters17(current_byte, descriptor, teams, num_teams);
	}

	current_byte = 0x490640;
	for (int ti = 0; ti < num_teams; ti++)
	{
		fill_team_tactics17(current_byte, descriptor, teams, num_teams);
	}

	*outTeams = new editor_team_entry[num_teams];
	for (int ti = 0; ti < num_teams; ti++)
	{
		(*outTeams)[ti] = teams[ti];
	}

	delete[] players;
	delete[] teams;

	*outNumPlayers = num_players;
	*outNumTeams = num_teams;
	*outDescriptor = descriptor;

	return OpResult::OK;
}

EDITOR_EXPORT OpResult editor_saveData17(const char* path, FileDescriptorOld* descriptor, editor_player_entry* players, editor_team_entry* teams)
{
	if (!path || !descriptor || !players || !teams)
		return OpResult::INVALID_ARGUMENT;

	int num_players = descriptor->data[0x5C];
	num_players += (descriptor->data[0x5D]) * 256;
	int num_teams = descriptor->data[0x60];
	num_teams += (descriptor->data[0x61]) * 256;

	int current_byte = 0x78;
	player_entry internal_player;
	for (int pi = 0; pi < num_players; pi++)
	{
		internal_player = players[pi].to_player_entry();
		extract_player_entry17(internal_player, current_byte, descriptor);
	}

	team_entry internal_team;
	current_byte = 0x3C3E58;
	for (int ti = 0; ti < num_teams; ti++)
	{
		internal_team = teams[ti].to_team_entry();
		extract_team_info17(internal_team, current_byte, descriptor);
	}
	current_byte = 0x475A90;
	for (int ti = 0; ti < num_teams; ti++)
	{
		internal_team = teams[ti].to_team_entry();
		extract_teamplayer_info17(internal_team, current_byte, descriptor);
	}
	current_byte = 0x490640;
	for (int ti = 0; ti < num_teams; ti++)
	{
		internal_team = teams[ti].to_team_entry();
		extract_team_tactics17(internal_team, current_byte, descriptor);
	}

	int outputSize;
	uint8_t* output;
	const uint8_t* masterKey17 = MasterKeyPes17;
	output = encryptWithKeyOld(descriptor, &outputSize, reinterpret_cast<const char*>(masterKey17));
	if (!output)
		return OpResult::UNKNOWN;

	return writeFile(path, output, outputSize);
}

EDITOR_EXPORT int editor_fill_player_entry17(editor_player_entry* player, void* descriptor)
{
	if (!descriptor)
		return 0;
	int current_byte = 0x78;
	player_entry internal_player;
	fill_player_entry17(internal_player, current_byte, descriptor);
	*player = internal_player;
	return 1;
}

EDITOR_EXPORT int editor_fill_team_ids17(editor_team_entry* team, void* descriptor)
{
	if (!descriptor)
		return 0;
	int current_byte = 0x3C3E58;
	team_entry internal_team;
	fill_team_ids17(internal_team, current_byte, descriptor);
	*team = internal_team;
	return 1;
}

EDITOR_EXPORT int editor_fill_team_rosters17(void* descriptor, editor_team_entry* teams, int team_count)
{
	if (!descriptor || team_count <= 0)
		return 0;
	int current_byte = 0x475A90;
	team_entry* internal_teams = new team_entry[team_count];
	fill_team_rosters17(current_byte, descriptor, internal_teams, team_count);
	for (int i = 0; i < team_count; ++i)
	{
		teams[i] = internal_teams[i];
	}
	delete[] internal_teams;
	return 1;
}

EDITOR_EXPORT int editor_fill_team_tactics17(void* descriptor, editor_team_entry* teams, int team_count)
{
	if (!descriptor || team_count <= 0)
		return 0;
	int current_byte = 0x490640;
	team_entry* internal_teams = new team_entry[team_count];
	fill_team_tactics17(current_byte, descriptor, internal_teams, team_count);
	for (int i = 0; i < team_count; ++i)
	{
		teams[i] = internal_teams[i];
	}
	delete[] internal_teams;
	return 1;
}

EDITOR_EXPORT int editor_extract_player_entry17(const editor_player_entry* player, void* descriptor)
{
	if (!descriptor || !player)
		return 0;
	int current_byte = 0x78;
	player_entry internal_player = player->to_player_entry();
	extract_player_entry17(internal_player, current_byte, descriptor);
	return 1;
}

EDITOR_EXPORT int editor_extract_team_info17(editor_team_entry* team, void* descriptor)
{
	if (!descriptor || !team)
		return 0;
	int current_byte = 0x3C3E58;
	team_entry internal_team = team->to_team_entry();
	extract_team_info17(internal_team, current_byte, descriptor);
	*team = internal_team;
	return 1;
}

EDITOR_EXPORT int editor_extract_teamplayer_info17(editor_team_entry* team, void* descriptor)
{
	if (!descriptor || !team)
		return 0;
	int current_byte = 0x475A90;
	team_entry internal_team = team->to_team_entry();
	extract_teamplayer_info17(internal_team, current_byte, descriptor);
	*team = internal_team;
	return 1;
}

EDITOR_EXPORT int editor_extract_team_tactics17(editor_team_entry* team, void* descriptor)
{
	if (!descriptor || !team)
		return 0;
	int current_byte = 0x490640;
	team_entry internal_team = team->to_team_entry();
	extract_team_tactics17(internal_team, current_byte, descriptor);
	*team = internal_team;
	return 1;
}

#pragma endregion