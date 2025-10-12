modded class SCR_AttributesManagerEditorComponent
{	
	override protected void ConfirmEditingServer(notnull array<int> attributesIds, notnull array<ref SCR_BaseEditorAttributeVar> attributesVars, int PlayerID)
	{
		if (!m_PrefabData)
			return;
		
		foreach (int i, int attributeId: attributesIds)
		{
			SCR_BaseEditorAttribute attribute = m_PrefabData.GetAttribute(attributeId);
			SCR_BaseEditorAttributeVar var = attributesVars[i];
			foreach (Managed item: m_aEditedItems)
			{
				if (attribute.ReadVariable(item, this))
				{
					// Logging Mechanism
					string actionType = "Attribute";
					string actionName = "N/A";
					string instigator = "N/A";
					string selected = "N/A";
					string attributeStr = "N/A";
					string before = "N/A";
					string after = "N/A";
					
					// Logging Mechanism: Get Action
					actionName = attribute.GetUIInfo().GetName();
					
					// Logging Mechanism: Get Instigator
					SCR_EditorManagerEntity manager = GetManager();
					if (manager && manager.GetPlayerID()) {
						instigator = RTSOGMods.GetPlayerEID(manager.GetPlayerID());
					}
					
					// Logging Mechanism: Get Selected
					SCR_EditableEntityComponent editableEntity = SCR_EditableEntityComponent.Cast(item);
					if (PlayerID == 0) {
						selected = editableEntity.GetDisplayName();
					} else {
						selected = RTSOGMods.GetPlayerEID(PlayerID);
					}
					
					// Logging Mechanism: Get Attribute
					attributeStr = attribute.GetUIInfo().GetName();
					
					// Logging Mechanism: Get Before
					before = attribute.ReadVariable(item, this).GetFloat().ToString();
					
					// Logging Mechanism: Get After
					after = var.GetFloat().ToString();
					
					// Logging Mechanism: Printing
					PrintFormat("RTSOGMods | GM_MONITOR | type: %1, instigator: %2, action: %3, selected: %4, attribute: %5, before: %6, after: %7", actionType, instigator, actionName, selected, attributeStr, before, after, level: LogLevel.NORMAL);
				}
			}
		}
		
		super.ConfirmEditingServer(attributesIds, attributesVars, PlayerID);
	}
}
