#pragma once

#include <stdint.h>

#ifdef _WIN32
#define EDITOR_EXPORT __declspec(dllexport)
#else
#define EDITOR_EXPORT __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma region Structs

	typedef struct editor_player_export
	{
		uint32_t nation;

		uint8_t height;
		uint8_t weight;

		uint8_t gc1;
		uint8_t gc2;

		uint8_t atk;          // Attacking Prowess
		uint8_t def;          // Defensive Prowess
		uint8_t gk;           // Goalkeeping
		uint8_t drib;         // Dribbling

		uint8_t mo_fk;        // Motion: Free Kick
		uint8_t finish;       // Finishing
		uint8_t lowpass;      // Low Pass
		uint8_t loftpass;     // Lofted Pass
		uint8_t header;       // Header
		uint8_t form;         // Form

		uint8_t b_edit_player;    // Edited/Created player

		uint8_t swerve;           // Swerve
		uint8_t catching;         // Catching (Saving in 15)
		uint8_t clearing;         // Clearing (16+)
		uint8_t reflex;           // Reflexes (16+)
		uint8_t injury;           // Injury Resistance

		uint8_t b_edit_basicset;  // Whether the player's basic settings are changed

		uint8_t body_ctrl;        // Body Control
		uint8_t phys_cont;        // Physical Contact (17+)
		uint8_t kick_pwr;         // Kicking Power
		uint8_t exp_pwr;          // Explosive Power

		uint8_t mo_armd;          // Motion: Arm Movement (dribbling)

		uint8_t b_edit_regpos;    // Registered Position edit

		uint8_t age;              // Age
		uint8_t reg_pos;          // Registered Position
		uint8_t play_style;       // Playing Styles
		uint8_t ball_ctrl;        // Ball Control
		uint8_t ball_win;         // Ball Winning
		uint8_t weak_acc;         // Weak Foot Accuracy
		uint8_t jump;             // Jump

		uint8_t mo_armr;          // Motion: Arm Movement (running)
		uint8_t mo_ck;            // Motion: Corner Kick
		uint8_t cover;            // Coverage (16+)
		uint8_t weak_use;         // Weak Foot Usage

		uint8_t play_pos[13];     // Playable Position

		uint8_t mo_hunchd;        // Motion: Hunching (dribbling)
		uint8_t mo_hunchr;        // Motion: Hunching (running)
		uint8_t mo_pk;            // Motion: Penalty Kick
		uint8_t place_kick;       // Place Kicking

		uint8_t star;             // Star rating (19+)
		uint8_t mo_drib;          // Motion: Dribbling (20+)
		uint8_t tight_pos;        // Tight Possession (20+)
		uint8_t aggres;           // Aggression (20+)
		uint8_t play_attit;       // Playing Attitude (20+)

		uint8_t b_edit_playpos;   // Playable Position edit
		uint8_t b_edit_ability;   // Ability edit
		uint8_t b_edit_skill;     // Player Skills edit

		uint8_t stamina;          // Stamina
		uint8_t speed;            // Speed

		uint8_t b_edit_style;     // Playing Styles edit
		uint8_t b_edit_com;       // COM Playing Styles edit
		uint8_t b_edit_motion;    // Motion edit
		uint8_t b_base_copy;      // Is Base Copy?

		uint8_t strong_foot;       // Stronger Foot
		uint8_t strong_hand;       // Stronger hand (20+)

		uint8_t com_style[7];      // COM Playing Styles
		uint8_t play_skill[41];    // Player Skills

		uint16_t name[61];         // Player Name (UTF-16)
		char shirt_name[21];       // Shirt Name

		uint8_t b_edit_face;       // Edited Face
		uint8_t b_edit_hair;       // Edited Hairstyle
		uint8_t b_edit_phys;       // Edited Physique
		uint8_t b_edit_strip;      // Edited Strip Style

		uint32_t boot_id;          // Boots
		uint32_t glove_id;         // Goalkeeper gloves

		uint32_t copy_id;          // Base Copy Player

		int32_t neck_len;           // Neck Length
		int32_t neck_size;          // Neck Size
		int32_t shldr_hi;           // Shoulder Height
		int32_t shldr_wid;          // Shoulder Width
		int32_t chest;              // Chest Measurement
		int32_t waist;              // Waist Size
		int32_t arm_size;           // Arm Size
		int32_t arm_len;            // Arm Length
		int32_t thigh;              // Thigh Size
		int32_t calf;               // Calf Size
		int32_t leg_len;            // Leg Length
		int32_t head_len;            // Head Length
		int32_t head_wid;            // Head Width
		int32_t head_dep;            // Head Depth

		uint8_t wrist_col_l;        // Wrist Tape: Color left
		uint8_t wrist_col_r;        // Wrist Tape: Color right
		uint8_t wrist_tape;         // Wrist Taping
		uint8_t spec_col;           // Spectacles frame color
		uint8_t spec_style;          // Spectacles style
		uint8_t sleeve;              // Sleeves
		uint8_t inners;              // Long-Sleeved Inners
		uint8_t socks;               // Sock Length
		uint8_t undershorts;         // Undershorts

		uint8_t untucked;            // Shirttail
		uint8_t ankle_tape;           // Ankle Taping
		uint8_t gloves;               // Player Gloves

		uint8_t gloves_col;          // Player Gloves color
		uint8_t skin_col;             // Skin color
		uint8_t iris_col;             // Iris color

		editor_player_export& operator=(const player_export& src);
		player_export to_player_export() const;

	} editor_player_export;

	typedef struct editor_player_entry
	{
		editor_player_export data;

		uint32_t id;
		uint32_t app_id;

		uint8_t b_changed;
		uint8_t b_show;

		int32_t team_ind;
		int32_t team_lineup_ind;

		editor_player_entry& operator=(const player_entry& src);
		player_entry to_player_entry() const;

	} editor_player_entry;

	typedef struct editor_strip_set
	{
		uint8_t stripNumber; // Number of kit. 0x80 = goalkeeper
		uint32_t stripTeamId; // Team ID * 0x40. Explicitly represented as 32-bit for DLL ABI compatibility.

	} editor_strip_set;

	typedef struct editor_team_entry
	{
		uint32_t id;
		uint32_t manager_id;
		int32_t stadium_id;
		uint16_t name[0x46]; // wchar_t name[0x46]. On Windows, wchar_t is 16-bit, so uint16_t is used here. This represents a UTF-16 string.
		char short_name[0x4]; // 4-byte null-terminated short name
		uint32_t players[40];
		uint16_t numbers[40];

		uint8_t b_edit_name;
		uint8_t b_edit_shortname;
		uint8_t b_edit_stadium;
		uint8_t b_edit_strip;

		int32_t num_on_team;
		int32_t starting11[11];
		int8_t captain_ind;

		int8_t color1_red;
		int8_t color1_blue;
		int8_t color1_green;

		int8_t color2_red;
		int8_t color2_blue;
		int8_t color2_green;

		editor_strip_set stripBlock[10];

		uint8_t b_changed;
		uint8_t b_show;

		editor_team_entry& operator=(const team_entry& src);
		team_entry to_team_entry() const;

	} editor_team_entry;

#pragma endregion

#pragma region General

	EDITOR_EXPORT OpResult editor_readFile(const char* path, uint8_t** outData, uint32_t* sizePtr);
	EDITOR_EXPORT void editor_freeData(editor_player_entry* players, editor_team_entry* teams);
	EDITOR_EXPORT void editor_freeDescriptorNew(FileDescriptorNew* descriptor);
	EDITOR_EXPORT void editor_freeDescriptorOld(FileDescriptorOld* descriptor);
	EDITOR_EXPORT void editor_freeDescriptor15(FileDescriptor15* descriptor);

#pragma endregion

#pragma region PES15

	//EDITOR_EXPORT void editor_build_appearance_map15(appearance_map&, int&, void*);
	//EDITOR_EXPORT int editor_read_player_entry15(editor_player_entry* player, int* current_byte, void* descriptor);
	//EDITOR_EXPORT void editor_read_appearance_entry15(player_entry&, appearance_map&, void*);
	//EDITOR_EXPORT void editor_read_team_ids15(team_entry&, int&, void*);
	//EDITOR_EXPORT void editor_read_team_rosters15(int&, void*, team_entry*, int);
	//EDITOR_EXPORT void editor_read_team_tactics15(int&, void*, team_entry*, int);
	//EDITOR_EXPORT void editor_write_player_entry15(player_entry, int&, appearance_map&, void*);
	//EDITOR_EXPORT void editor_write_team_info15(team_entry, int&, void*);
	//EDITOR_EXPORT void editor_write_teamplayer_info15(team_entry, int&, void*);
	//EDITOR_EXPORT void editor_write_team_tactics15(team_entry, int&, void*);

#pragma endregion

#pragma region PES17

	EDITOR_EXPORT OpResult editor_readFile17(const char* path, FileDescriptorOld** outDescriptor);
	EDITOR_EXPORT OpResult editor_loadData17(const char* path, FileDescriptorOld** descriptor, editor_player_entry** outPlayers, uint32_t* outNumPlayers, editor_team_entry** outTeams, uint32_t* outNumTeams);
	EDITOR_EXPORT OpResult editor_saveData17(const char* path, FileDescriptorOld* descriptor, editor_player_entry* players, editor_team_entry* teams);

	EDITOR_EXPORT int editor_fill_player_entry17(editor_player_entry* player, void* descriptor);
	EDITOR_EXPORT int editor_fill_team_ids17(editor_team_entry* team, void* descriptor);
	EDITOR_EXPORT int editor_fill_team_rosters17(void* descriptor, editor_team_entry* teams, int team_count);
	EDITOR_EXPORT int editor_fill_team_tactics17(void* descriptor, editor_team_entry* teams, int team_count);
	EDITOR_EXPORT int editor_extract_player_entry17(const editor_player_entry* player, void* descriptor);
	EDITOR_EXPORT int editor_extract_team_info17(editor_team_entry* team, void* descriptor);
	EDITOR_EXPORT int editor_extract_teamplayer_info17(editor_team_entry* team, void* descriptor);
	EDITOR_EXPORT int editor_extract_team_tactics17(editor_team_entry* team, void* descriptor);

#pragma endregion

#ifdef __cplusplus
}
#endif
