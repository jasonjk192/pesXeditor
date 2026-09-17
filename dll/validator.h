#pragma once

#include "dll.h"

#ifdef _WIN32
#define EDITOR_EXPORT __declspec(dllexport)
#else
#define EDITOR_EXPORT __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

EDITOR_EXPORT EditorOpResult editor_validateSinglePlayerEntry(editor_player_entry* player, uint8_t* version);
EDITOR_EXPORT EditorOpResult editor_validateSingleTeamEntry(editor_team_entry* teams, uint8_t* version);
EDITOR_EXPORT EditorOpResult editor_validateData(editor_player_entry* players, int numPlayers, editor_team_entry* teams, int numTeams, uint8_t* version);

#ifdef __cplusplus
}
#endif