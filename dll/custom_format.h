#pragma once

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

#pragma region CSV

EDITOR_EXPORT EditorOpResult editor_export_player_csv(uint32_t id, const editor_player_entry* players, uint32_t numPlayers, const editor_cache* cache, const char* filePath);
EDITOR_EXPORT EditorOpResult editor_export_savefile_csv(uint32_t id, const editor_player_entry* players, uint32_t numPlayers, const char* filePath);

#pragma endregion

#pragma region JSON

EDITOR_EXPORT EditorOpResult editor_export_savefile_json(uint32_t id, const editor_player_entry* players, uint32_t numPlayers, const char* filePath);

#pragma endregion

#ifdef __cplusplus
}
#endif