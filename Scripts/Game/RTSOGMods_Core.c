class RTSOGMods {
	static string limitedArsenalBlacklistPath = "$profile:RTSOGMods_LimitedArsenalBlacklist.json";
	static ref array<string> blacklistedArsenalFactions;
	static ref array<string> blacklistedArsenalItems;
	
	static string groupsPlayersPath = "$profile:RTSOGMods_GroupsPlayers.json";
	static ref array<string> whitelistedPlayers;
	
	static string damageMultipliersPath = "$profile:RTSOGMods_DamageMultiplier.json";
	static ref RTSOGMods_DamageMultipliers damageMultipliers;
	
	static string GetPlayerEID(int playerId) {		
		BackendApi api = GetGame().GetBackendApi();
		
		if (!api)
		{
			Print("RTSOGMods | Backend API is down!", LogLevel.ERROR);
			
			return "";
		};
		
		return api.GetPlayerIdentityId(playerId);
	};
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	static RTSOGLimited_ArnsenalBlacklist LoadArsenalBlacklist() {
		RTSOGLimited_ArnsenalBlacklist blacklist = new RTSOGLimited_ArnsenalBlacklist();
		blacklist.LoadFromFile(limitedArsenalBlacklistPath);
		
		return blacklist;
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	static RTSOGMods_GroupsPlayersWhitelist LoadGroupsPlayersWhitelist() {
		RTSOGMods_GroupsPlayersWhitelist whitelist = new RTSOGMods_GroupsPlayersWhitelist();
		whitelist.LoadFromFile(groupsPlayersPath);
		
		return whitelist;
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
	static void LoadDamageMultipliers() {
		damageMultipliers = new RTSOGMods_DamageMultipliers();
		damageMultipliers.LoadFromFile(damageMultipliersPath);
		
		PrintFormat("RTSOGMods | Loaded Damage Multiplier! %1", damageMultipliers.playerKineticDamageMultiplier, level: LogLevel.NORMAL);
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	static void GetGroupsPlayersLists(out array<string> certifiedGMs, out array<string> chalkTeam, out array<string> redSection, out array<string> greySection, out array<string> blackSection) {
		if(!Replication.IsServer()) return;

	    RTSOGMods_GroupsPlayersWhitelist whitelist = LoadGroupsPlayersWhitelist();
		
		certifiedGMs = whitelist.certifiedGMs;
		chalkTeam = whitelist.chalkTeam;
		redSection = whitelist.redSection;
		greySection = whitelist.greySection;
		blackSection = whitelist.blackSection;
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
	ref array<string> certifiedGMs;
	ref array<string> chalkTeam;
	ref array<string> redSection;
	ref array<string> greySection;
	ref array<string> blackSection;
		
	void RTSOGMods_GroupsPlayersWhitelist() {
		certifiedGMs = new array<string>();
		chalkTeam = new array<string>();
		redSection = new array<string>();
		greySection = new array<string>();
		blackSection = new array<string>();
		
		RegV("certifiedGMs");
		RegV("chalkTeam");
		RegV("redSection");
		RegV("greySection");
		RegV("blackSection");
	}
}

class RTSOGMods_DamageMultipliers : JsonApiStruct {
	float playerKineticDamageMultiplier;
	float AIKineticDamageMultiplier;
	
	void RTSOGMods_DamageMultipliers() {
		playerKineticDamageMultiplier = 1.0;
		AIKineticDamageMultiplier = 1.0;
		
		RegV("playerKineticDamageMultiplier");
		RegV("AIKineticDamageMultiplier");
	}
}