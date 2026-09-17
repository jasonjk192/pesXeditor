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

typedef struct editor_cache editor_cache;
EDITOR_EXPORT EditorOpResult editor_buildCache(const editor_player_entry* players, uint32_t numPlayers, const editor_team_entry* teams, uint32_t numTeams, editor_cache** outCache);
EDITOR_EXPORT void editor_freeCache(editor_cache* cache);
EDITOR_EXPORT EditorOpResult editor_playerIndexByID(const editor_cache* cache, uint32_t playerID, uint32_t* outIndex);
EDITOR_EXPORT EditorOpResult editor_teamIndexByID(const editor_cache* cache, uint32_t teamID, uint32_t* outIndex);
EDITOR_EXPORT EditorOpResult editor_playerIndicesByIDs(const editor_cache* cache, const uint32_t* playerIDs, uint32_t count, uint32_t* outIndices);
EDITOR_EXPORT EditorOpResult editor_teamIndicesByIDs(const editor_cache* cache, const uint32_t* teamIDs, uint32_t count, uint32_t* outIndices);
EDITOR_EXPORT EditorOpResult editor_getTeamPlayerIndices(const editor_cache* cache, const editor_team_entry* team, uint32_t* outIndices, uint32_t* outCount);
EDITOR_EXPORT EditorOpResult editor_getTeamStarting11PlayerIndices(const editor_cache* cache, const editor_team_entry* team, uint32_t* outIndices, uint32_t* outCount);

#ifdef __cplusplus
}
#endif