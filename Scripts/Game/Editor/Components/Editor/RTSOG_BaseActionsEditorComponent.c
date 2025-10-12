modded class SCR_BaseActionsEditorComponent
{
	override protected void ActionPerform(SCR_BaseEditorAction action, SCR_EditableEntityComponent hoveredEntityComponent, set<SCR_EditableEntityComponent> selectedEntityComponents, vector cursorWorldPosition, int flags, int param)
	{
		if (hoveredEntityComponent && !selectedEntityComponents.Contains(hoveredEntityComponent))
		{
			// Logging Mechanism
			string actionType = "Context";
			string actionName = "N/A";
			string instigator = "N/A";
			string hovered = "N/A";
			
			
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
					
			
			// Logging Mechanism: Printing
			PrintFormat("RTSOGMods | GM_MONITOR | type: %1, instigator: %2, action: %3, hovered: %4", actionType, instigator, actionName, hovered, level: LogLevel.NORMAL);
		}
		
		foreach (SCR_EditableEntityComponent selectedEntityComponent : selectedEntityComponents)
		{
			// Logging Mechanism
			string actionType = "Context";
			string actionName = "N/A";
			string instigator = "N/A";
			string selected = "N/A";
			
			
			// Logging Mechanism: Get Action
			actionName = action.GetInfo().GetName();
			
			// Logging Mechanism: Get Instigator
			SCR_EditorManagerEntity manager = GetManager();
			if (manager && manager.GetPlayerID())
			{
				instigator = RTSOGMods.GetPlayerEID(manager.GetPlayerID());
			}
			
			// Logging Mechanism: Get Selected
			if (selectedEntityComponent.GetPlayerID() == 0)
			{
				selected = selectedEntityComponent.GetDisplayName();
			}
			else
			{
				selected = RTSOGMods.GetPlayerEID(selectedEntityComponent.GetPlayerID());
			}
			
			// Logging Mechanism: Printing
			PrintFormat("RTSOGMods | GM_MONITOR | type: %1, instigator: %2, action: %3 selected: %4", actionType, instigator, actionName, selected, level: LogLevel.NORMAL);
		}
		
		super.ActionPerform(action, hoveredEntityComponent, selectedEntityComponents, cursorWorldPosition, flags, param);
	}
}