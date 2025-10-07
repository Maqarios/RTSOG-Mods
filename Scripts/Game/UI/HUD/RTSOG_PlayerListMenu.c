//------------------------------------------------------------------------------------------------
modded class SCR_PlayerListMenu : SCR_SuperMenuBase
{
	override void CreateEntry(int id, SCR_PlayerDelegateEditorComponent editorDelegateManager)
	{
		// Get Player Enfusion ID
		string playerEID = RTSOGMods.GetPlayerEID(id);
		
		// Get groups whitelist
		RTSOGMods_GroupsPlayersWhitelist whitelist = RTSOGMods.LoadGroupsPlayersWhitelist();
		if (!whitelist || !whitelist.extra.Contains(playerEID))
		{
			super.CreateEntry(id, editorDelegateManager);
			return;
		}
		
		super.CreateEntry(id, null);
			
	}
}
