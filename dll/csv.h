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

EDITOR_EXPORT EditorOpResult editor_import_players_csv(editor_player_entry* players, const editor_cache* cache, const char* filePath);
EDITOR_EXPORT EditorOpResult editor_import_teams_csv(editor_team_entry* teams, const editor_cache* cache, const char* filePath);

#ifdef __cplusplus
}
#endif