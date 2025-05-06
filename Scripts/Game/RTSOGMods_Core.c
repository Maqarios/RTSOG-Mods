class RTSOGMods {
	static string limitedArsenalBlacklistPath = "$profile:RTSOGMods_LimitedArsenalBlacklist.json";
	static ref array<string> blacklistedArsenalFactions;
	static ref array<string> blacklistedArsenalItems;
	
	static string groupsPlayersPath = "$profile:RTSOGMods_GroupsPlayers.json";
	static ref array<string> whitelistedPlayers;
	
	static RTSOGLimited_ArnsenalBlacklist LoadArsenalBlacklist() {
		RTSOGLimited_ArnsenalBlacklist blacklist = new RTSOGLimited_ArnsenalBlacklist();
		blacklist.LoadFromFile(limitedArsenalBlacklistPath);
		
		return blacklist;
	}
	
	static RTSOGMods_GroupsPlayersWhitelist LoadGroupsPlayersWhitelist() {
		RTSOGMods_GroupsPlayersWhitelist whitelist = new RTSOGMods_GroupsPlayersWhitelist();
		whitelist.LoadFromFile(groupsPlayersPath);
		
		return whitelist;
	}
	
	static string GetPlayerEID(int playerId)
	{		
		BackendApi api = GetGame().GetBackendApi();
		
		if (!api)
		{
			Print("RTSOGMods | Backend API is down!", LogLevel.ERROR);
			
			return "";
		};
		
		return api.GetPlayerIdentityId(playerId);
	};
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	static void GetGroupsPlayersLists(out array<string> chalkTeam, out array<string> redSection, out array<string> greySection, out array<string> blackSection, out array<string> redTalon) {
		if(!Replication.IsServer()) return;

	    RTSOGMods_GroupsPlayersWhitelist whitelist = LoadGroupsPlayersWhitelist();
		
		chalkTeam = whitelist.chalkTeam;
		redSection = whitelist.redSection;
		greySection = whitelist.greySection;
		blackSection = whitelist.blackSection;
		redTalon = whitelist.redTalon;
	}
}

class RTSOGLimited_ArnsenalBlacklist : JsonApiStruct {
	ref array<string> factions;
	ref array<string> items;
		
	void RTSOGLimited_ArnsenalBlacklist() {
		factions = new array<string>();
		items = new array<string>();
		
		RegV("factions");
		RegV("items");
	}
}

class RTSOGMods_GroupsPlayersWhitelist : JsonApiStruct {
	ref array<string> chalkTeam;
	ref array<string> redSection;
	ref array<string> greySection;
	ref array<string> blackSection;
	ref array<string> redTalon;
		
	void RTSOGMods_GroupsPlayersWhitelist() {
		chalkTeam = new array<string>();
		redSection = new array<string>();
		greySection = new array<string>();
		blackSection = new array<string>();
		redTalon = new array<string>();
		
		RegV("chalkTeam");
		RegV("redSection");
		RegV("greySection");
		RegV("blackSection");
		RegV("redTalon");
	}
}