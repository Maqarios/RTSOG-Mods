modded class SCR_ArsenalManagerComponent {
	override protected bool CanSaveLoadout(int playerId, notnull GameEntity characterEntity, FactionAffiliationComponent playerFactionAffiliation, SCR_ArsenalComponent arsenalComponent, bool sendNotificationOnFailed) {
		// Get groups whitelist
		array<string> chalkTeam;
		array<string> redSection;
		array<string> greySection;
		array<string> blackSection;
		array<string> redTalon;
		GetGroupsPlayersLists(chalkTeam, redSection, greySection, blackSection, redTalon);
		
		// Get Player Enfusion ID
		string playerEID = RTSOGMods.GetPlayerEID(playerId);
		
		bool isChalkTeam = chalkTeam.Contains(playerEID);
		bool isRedSection = redSection.Contains(playerEID);
		bool isGreySection = greySection.Contains(playerEID);
		bool isBlackSection = blackSection.Contains(playerEID);
		bool isRedTalon = redTalon.Contains(playerEID);
		if (isChalkTeam || isRedSection || isGreySection || isBlackSection || isRedTalon) {
			return true;
		}
		
		return super.CanSaveLoadout(playerId, characterEntity, playerFactionAffiliation, arsenalComponent, sendNotificationOnFailed);
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	void GetGroupsPlayersLists(out array<string> chalkTeam, out array<string> redSection, out array<string> greySection, out array<string> blackSection, out array<string> redTalon) {
		if(!Replication.IsServer()) return;

	    RTSOGMods_GroupsPlayersWhitelist whitelist = RTSOGMods.LoadGroupsPlayersWhitelist();
		
		chalkTeam = whitelist.chalkTeam;
		redSection = whitelist.redSection;
		greySection = whitelist.greySection;
		blackSection = whitelist.blackSection;
		redTalon = whitelist.redTalon;
	}
}