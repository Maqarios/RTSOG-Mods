modded class SCR_ArsenalManagerComponent {
	override protected bool CanSaveLoadout(int playerId, notnull GameEntity characterEntity, FactionAffiliationComponent playerFactionAffiliation, SCR_ArsenalComponent arsenalComponent, bool sendNotificationOnFailed) {
		// Get Player Enfusion ID
		string playerEID = RTSOGMods.GetPlayerEID(playerId);
		
		// Get groups whitelist
		RTSOGMods_GroupsPlayersWhitelist whitelist = RTSOGMods.LoadGroupsPlayersWhitelist();
		if (!whitelist)
			return true;
		
		bool isChalkTeam = whitelist.chalkTeam.Contains(playerEID);
		bool isRedSection = whitelist.redSection.Contains(playerEID);
		bool isGreySection = whitelist.greySection.Contains(playerEID);
		bool isBlackSection = whitelist.blackSection.Contains(playerEID);
		if (isChalkTeam || isRedSection || isGreySection || isBlackSection) {
			return true;
		}
		
		return super.CanSaveLoadout(playerId, characterEntity, playerFactionAffiliation, arsenalComponent, sendNotificationOnFailed);
	}
}