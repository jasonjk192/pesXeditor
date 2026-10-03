#pragma once

#include "rapidcsv.h"
#include "dll.h"
#include "cache.h"

#ifdef _WIN32
#define EDITOR_EXPORT __declspec(dllexport)
#else
#define EDITOR_EXPORT __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

EDITOR_EXPORT EditorOpResult editor_export_player_csv(const uint32_t id, const editor_player_entry* players, const editor_cache* cache, const char* filePath);
EDITOR_EXPORT EditorOpResult editor_export_players_csv(const uint32_t *ids, const editor_player_entry* players, uint32_t numPlayers, const editor_cache* cache, const char* filePath);

EDITOR_EXPORT EditorOpResult editor_export_team_csv(const uint32_t id, const editor_team_entry* teams, const editor_cache* cache, const char* filePath);
EDITOR_EXPORT EditorOpResult editor_export_teams_csv(const uint32_t *ids, const editor_team_entry* teams, uint32_t numTeams, const editor_cache* cache, const char* filePath);
EDITOR_EXPORT EditorOpResult editor_export_team_players_csv(const uint32_t id, const editor_team_entry* teams, const editor_player_entry* players, const editor_cache* cache, const char* filePath);
EDITOR_EXPORT EditorOpResult editor_export_team_starting11_csv(const uint32_t id, const editor_team_entry* teams, const editor_player_entry* players, const editor_cache* cache, const char* filePath);

//EDITOR_EXPORT EditorOpResult editor_export_savefile_csv(const editor_player_entry* players, uint32_t numPlayers, const editor_team_entry* teams, uint32_t numTeams, const char* filePath);

// imports and automatically replace existing players. If a player ID doesn't exist, they will be skipped
EDITOR_EXPORT EditorOpResult editor_import_players_csv_auto_merge(editor_player_entry* players, const editor_cache* cache, const char* filePath);
// imports and automatically replace existing teams. If a team ID doesn't exist, they will be skipped
EDITOR_EXPORT EditorOpResult editor_import_teams_csv_auto_merge(editor_team_entry* teams, const editor_cache* cache, const char* filePath);

// imports new players without affecting the original existing players
EDITOR_EXPORT EditorOpResult editor_import_players_csv(const char* filePath, editor_player_entry** outPlayers, uint32_t* outNumPlayers);
// imports new teams without affecting the original existing teams
EDITOR_EXPORT EditorOpResult editor_import_teams_csv(const char* filePath, editor_team_entry** outTeams, uint32_t* outNumTeams);

// Use this to free your imported players (that are not automatically merged)
EDITOR_EXPORT void free_imported_players(const editor_player_entry* importedPlayers);
// Use this to free your imported teams (that are not automatically merged)
EDITOR_EXPORT void free_imported_teams(const editor_team_entry* importedTeams);

#ifdef __cplusplus
}
#endif