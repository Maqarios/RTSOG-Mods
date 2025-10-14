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
					string instigator = "N/A";
					string target = "N/A";
					string attributeStr = "N/A";
					string before = "N/A";
					string after = "N/A";
					
					// Logging Mechanism: Get Instigator
					SCR_EditorManagerEntity manager = GetManager();
					if (manager && manager.GetPlayerID()) {
						instigator = RTSOGMods.GetPlayerEID(manager.GetPlayerID());
					}
					
					// Logging Mechanism: Get Target
					SCR_EditableEntityComponent editableEntity = SCR_EditableEntityComponent.Cast(item);
					if (editableEntity.GetPlayerID() == 0)
						target = editableEntity.GetDisplayName();
					else
						target = RTSOGMods.GetPlayerEID(editableEntity.GetPlayerID());
					
					// Logging Mechanism: Get Attribute
					attributeStr = attribute.GetUIInfo().GetName();
					
					// Logging Mechanism: Get Before
					before = attribute.ReadVariable(item, this).GetFloat().ToString();
					
					// Logging Mechanism: Get After
					after = var.GetFloat().ToString();
					
					// Logging Mechanism: Printing
					PrintFormat("RTSOGMods | GM_MONITOR | type: %1, instigator: %2, target: %3, attribute: %4, before: %5, after: %6", actionType, instigator, target, attributeStr, before, after, level: LogLevel.NORMAL);
				}
			}
		}
		
		super.ConfirmEditingServer(attributesIds, attributesVars, PlayerID);
	}
}
