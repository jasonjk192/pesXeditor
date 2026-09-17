#include "cache.h"

#pragma region Cache

struct editor_cache
{
	std::unordered_map<uint32_t, uint32_t> playerIndexByID;
	std::unordered_map<uint32_t, uint32_t> teamIndexByID;
};

EDITOR_EXPORT EditorOpResult editor_buildCache(const editor_player_entry* players, uint32_t numPlayers, const editor_team_entry* teams, uint32_t numTeams, editor_cache** outCache)
{
	if (!outCache || !players || !teams)
		return EditorOpResult::INVALID_ARGUMENT;
	*outCache = NULL;

	try
	{
		editor_cache* cache = new editor_cache();
		cache->playerIndexByID.reserve(numPlayers);
		cache->teamIndexByID.reserve(numTeams);

		for (uint32_t i = 0; i < numPlayers; ++i)
		{
			cache->playerIndexByID[players[i].id] = i;
		}

		for (uint32_t i = 0; i < numTeams; ++i)
		{
			cache->teamIndexByID[teams[i].id] = i;
		}

		*outCache = cache;
		return EditorOpResult::OK;
	}
	catch (const std::bad_alloc&)
	{
		return EditorOpResult::ALLOC_FAILED;
	}
	catch (...)
	{
		return EditorOpResult::UNKNOWN;
	}
}

EDITOR_EXPORT void editor_freeCache(editor_cache* cache)
{
	if(cache) delete cache;
}

EDITOR_EXPORT EditorOpResult editor_playerIndexByID(const editor_cache* cache, uint32_t playerID, uint32_t* outIndex)
{
	if (!cache || !outIndex)
		return EditorOpResult::INVALID_ARGUMENT;

	const auto it = cache->playerIndexByID.find(playerID);
	if (it == cache->playerIndexByID.end())
		return EditorOpResult::NOT_FOUND;

	*outIndex = it->second;
	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_teamIndexByID(const editor_cache* cache, uint32_t teamID, uint32_t* outIndex)
{
	if (!cache || !outIndex)
		return EditorOpResult::INVALID_ARGUMENT;

	const auto it = cache->teamIndexByID.find(teamID);
	if (it == cache->teamIndexByID.end())
		return EditorOpResult::NOT_FOUND;

	*outIndex = it->second;
	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_playerIndicesByIDs(const editor_cache* cache, const uint32_t* playerIDs, uint32_t count, uint32_t* outIndices)
{
	if (!cache || !outIndices || !playerIDs)
		return EditorOpResult::INVALID_ARGUMENT;

	for (uint32_t i = 0; i < count; ++i)
	{
		const auto it = cache->playerIndexByID.find(playerIDs[i]);
		if (it == cache->playerIndexByID.end())
			return EditorOpResult::NOT_FOUND;
		outIndices[i] = it->second;
	}

	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_teamIndicesByIDs(const editor_cache* cache, const uint32_t* teamIDs, uint32_t count, uint32_t* outIndices)
{
	if (!cache || !outIndices || !teamIDs)
		return EditorOpResult::INVALID_ARGUMENT;

	for (uint32_t i = 0; i < count; ++i)
	{
		const auto it = cache->teamIndexByID.find(teamIDs[i]);
		if (it == cache->teamIndexByID.end())
			return EditorOpResult::NOT_FOUND;
		outIndices[i] = it->second;
	}

	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_getTeamPlayerIndices(const editor_cache* cache, const editor_team_entry* team, uint32_t* outIndices, uint32_t* outCount)
{
	if (!cache || !team || !outIndices || !outCount)
		return EditorOpResult::INVALID_ARGUMENT;

	uint32_t count = 0;
	for (uint32_t i = 0; i < 40; ++i)
	{
		const uint32_t playerID = team->players[i];
		if (playerID == 0)
			continue;

		const auto it = cache->playerIndexByID.find(playerID);
		if (it == cache->playerIndexByID.end())
		{
			return EditorOpResult::NOT_FOUND;
		}

		outIndices[count++] = it->second;
	}

	*outCount = count;
	return EditorOpResult::OK;
}

EDITOR_EXPORT EditorOpResult editor_getTeamStarting11PlayerIndices(const editor_cache* cache, const editor_team_entry* team, uint32_t* outIndices, uint32_t* outCount)
{
	if (!cache || !team || !outIndices || !outCount)
		return EditorOpResult::INVALID_ARGUMENT;

	uint32_t count = 0;
	for (uint32_t i = 0; i < 11; ++i)
	{
		const int32_t playerSlot = team->starting11[i];
		if (playerSlot < 0)
			continue;
		if (playerSlot >= 40)
			return EditorOpResult::OUT_OF_RANGE;

		const uint32_t playerID = team->players[playerSlot];
		const auto it = cache->playerIndexByID.find(static_cast<uint32_t>(playerID));

		if (it == cache->playerIndexByID.end())
			return EditorOpResult::NOT_FOUND;

		outIndices[count++] = it->second;
	}

	*outCount = count;
	return EditorOpResult::OK;
}

#pragma endregion
