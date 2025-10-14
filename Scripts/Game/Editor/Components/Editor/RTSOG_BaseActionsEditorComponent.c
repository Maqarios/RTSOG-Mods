modded class SCR_BaseActionsEditorComponent
{
	override protected void ActionPerform(SCR_BaseEditorAction action, SCR_EditableEntityComponent hoveredEntityComponent, set<SCR_EditableEntityComponent> selectedEntityComponents, vector cursorWorldPosition, int flags, int param)
	{
		// Case 1: No Target
		if (!hoveredEntityComponent && selectedEntityComponents.IsEmpty())
		{
			// Logging Mechanism
			string actionType = "Context";
			string actionName = "N/A";
			string instigator = "N/A";
			string target = "N/A";
			
			// Logging Mechanism: Get Action
			actionName = action.GetInfo().GetName();
			
			// Logging Mechanism: Get Instigator
			SCR_EditorManagerEntity manager = GetManager();
			if (manager && manager.GetPlayerID()) {
				instigator = RTSOGMods.GetPlayerEID(manager.GetPlayerID());
			}
			
			// Logging Mechanism: Printing
			PrintFormat("RTSOGMods | GM_MONITOR | type: %1, instigator: %2, action: %3, target: %4", actionType, instigator, actionName, target, level: LogLevel.NORMAL);
		}
		
		// Case 2: Hovered but not Selected
		if (hoveredEntityComponent && !selectedEntityComponents.Contains(hoveredEntityComponent))
		{
			// Logging Mechanism
			string actionType = "Context";
			string actionName = "N/A";
			string instigator = "N/A";
			string target = "N/A";
			
			// Logging Mechanism: Get Action
			actionName = action.GetInfo().GetName();
			
			// Logging Mechanism: Get Instigator
			SCR_EditorManagerEntity manager = GetManager();
			if (manager && manager.GetPlayerID()) {
				instigator = RTSOGMods.GetPlayerEID(manager.GetPlayerID());
			}
			
			// Logging Mechanism: Get Target
			if (hoveredEntityComponent) {
				if (hoveredEntityComponent.GetPlayerID() == 0) {
					target = hoveredEntityComponent.GetDisplayName();
				} else {
					target = RTSOGMods.GetPlayerEID(hoveredEntityComponent.GetPlayerID());
				}
			}	
			
			// Logging Mechanism: Printing
			PrintFormat("RTSOGMods | GM_MONITOR | type: %1, instigator: %2, action: %3, target: %4", actionType, instigator, actionName, target, level: LogLevel.NORMAL);
		}
		
		// Case 3: Selected
		foreach (SCR_EditableEntityComponent selectedEntityComponent : selectedEntityComponents)
		{
			// Logging Mechanism
			string actionType = "Context";
			string actionName = "N/A";
			string instigator = "N/A";
			string target = "N/A";
			
			
			// Logging Mechanism: Get Action
			actionName = action.GetInfo().GetName();
			
			// Logging Mechanism: Get Instigator
			SCR_EditorManagerEntity manager = GetManager();
			if (manager && manager.GetPlayerID())
			{
				instigator = RTSOGMods.GetPlayerEID(manager.GetPlayerID());
			}
			
			// Logging Mechanism: Get Target
			if (selectedEntityComponent.GetPlayerID() == 0)
				target = selectedEntityComponent.GetDisplayName();
			else
				target = RTSOGMods.GetPlayerEID(selectedEntityComponent.GetPlayerID());
			
			// Logging Mechanism: Printing
			PrintFormat("RTSOGMods | GM_MONITOR | type: %1, instigator: %2, action: %3, target: %4", actionType, instigator, actionName, target, level: LogLevel.NORMAL);
		}
		
		super.ActionPerform(action, hoveredEntityComponent, selectedEntityComponents, cursorWorldPosition, flags, param);
	}
}