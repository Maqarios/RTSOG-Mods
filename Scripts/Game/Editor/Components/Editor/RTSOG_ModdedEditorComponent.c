modded class SCR_BaseActionsEditorComponent
{
	override protected void ActionPerform(SCR_BaseEditorAction action, SCR_EditableEntityComponent hoveredEntityComponent, set<SCR_EditableEntityComponent> selectedEntityComponents, vector cursorWorldPosition, int flags, int param)
	{
		// Logging Mechanism
		string actionType = "Context";
		string actionName = "UNKNOWN";
		string instigator = "UNKNOWN";
		string hovered = "UNKNOWN";
		string selected = "UNKNOWN";
		
		
		// Logging Mechanism: Get Action
		actionName = action.GetInfo().GetName();
		
		// Logging Mechanism: Get Instigator
		SCR_EditorManagerEntity manager = GetManager();
		if (manager && manager.GetPlayerID()) {
			instigator = RTSOGMods.GetPlayerEID(manager.GetPlayerID());
		}
		
		// Logging Mechanism: Get Hovered
		if (hoveredEntityComponent) {
			if (hoveredEntityComponent.GetPlayerID() == 0) {
				hovered = hoveredEntityComponent.GetDisplayName();
			} else {
				hovered = RTSOGMods.GetPlayerEID(hoveredEntityComponent.GetPlayerID());
			}
		}
		
		// Logging Mechanism: Get Selected
		if(selectedEntityComponents && !selectedEntityComponents.IsEmpty()) {
			selected = "";
			foreach (SCR_EditableEntityComponent selectedEntityComponent : selectedEntityComponents) {
				if (selectedEntityComponent.GetPlayerID() == 0) {
					selected += selectedEntityComponent.GetDisplayName() + ",";
				} else {
					selected += RTSOGMods.GetPlayerEID(selectedEntityComponent.GetPlayerID()) + ",";
				}
			}
			selected = selected.Substring(0, selected.Length() - 1);
		}
				
		
		// Logging Mechanism: Printing
		PrintFormat("RTSOG_GM_MONITOR | type=%1 | instigator=%2 | action=%3 | hovered=%4 | selected=%5", actionType, instigator, actionName, hovered, selected);
		
		super.ActionPerform(action, hoveredEntityComponent, selectedEntityComponents, cursorWorldPosition, flags, param);
	}
}

modded class SCR_PlacingEditorComponent
{
	override protected void OnBeforeEntityCreatedServer(ResourceName prefab)
	{
		// Logging Mechanism
		string actionType = "Spawn";
		string instigator = "UNKNOWN";
		string entity = prefab;
		
		// Logging Mechanism: Get Instigator
		SCR_EditorManagerEntity manager = GetManager();
		if (manager && manager.GetPlayerID()) {
			instigator = RTSOGMods.GetPlayerEID(manager.GetPlayerID());
		}
		
		// Logging Mechanism: Printing
		PrintFormat("RTSOG_GM_MONITOR | type=%1 | instigator=%2 | entity=%3", actionType, instigator, entity);
	}
}
