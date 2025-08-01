modded class SCR_ArsenalManagerComponent {
	override protected bool CanSaveLoadout(int playerId, notnull GameEntity characterEntity, FactionAffiliationComponent playerFactionAffiliation, SCR_ArsenalComponent arsenalComponent, bool sendNotificationOnFailed) {
		// Get groups whitelist
		array<string> chalkTeam;
		array<string> redSection;
		array<string> greySection;
		array<string> blackSection;
		RTSOGMods.GetGroupsPlayersLists(null, chalkTeam, redSection, greySection, blackSection);
		
		// Get Player Enfusion ID
		string playerEID = RTSOGMods.GetPlayerEID(playerId);
		
		bool isChalkTeam = chalkTeam.Contains(playerEID);
		bool isRedSection = redSection.Contains(playerEID);
		bool isGreySection = greySection.Contains(playerEID);
		bool isBlackSection = blackSection.Contains(playerEID);
		if (isChalkTeam || isRedSection || isGreySection || isBlackSection) {
			return true;
		}
		
		return super.CanSaveLoadout(playerId, characterEntity, playerFactionAffiliation, arsenalComponent, sendNotificationOnFailed);
	}
}