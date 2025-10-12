modded class SCR_PlacingEditorComponent
{
	override protected void OnBeforeEntityCreatedServer(ResourceName prefab)
	{
		// Logging Mechanism
		string actionType = "Spawn";
		string instigator = "N/A";
		string entity = prefab;
		
		// Logging Mechanism: Get Instigator
		SCR_EditorManagerEntity manager = GetManager();
		if (manager && manager.GetPlayerID()) {
			instigator = RTSOGMods.GetPlayerEID(manager.GetPlayerID());
		}
		
		// Logging Mechanism: Printing
		PrintFormat("RTSOGMods | GM_MONITOR | type: %1, instigator: %2, entity: %3", actionType, instigator, entity, level: LogLevel.NORMAL);
	}
}