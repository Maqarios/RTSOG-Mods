//----------------------------------------------------------------------------------------
[EnumLinear()]
enum RTSOG_InjuryHelperID
{
	MINOR,
	MODERATE,
	SERIOUS,
}

//------------------------------------------------------------------------------------------------
[BaseContainerProps(), SCR_BaseContainerCustomTitleUIInfo("m_Info")]
class RTSOG_RandomInjuryCharacterContextAction : SCR_SelectedEntitiesContextAction
{
	[Attribute(uiwidget: UIWidgets.SearchComboBox, desc: "ID of the injury helper",  enums: ParamEnumArray.FromEnum(RTSOG_InjuryHelperID))]
	protected RTSOG_InjuryHelperID m_injuryHelperID;
	
	override bool CanBeShown(SCR_EditableEntityComponent selectedEntity, vector cursorWorldPosition, int flags)
	{
		return selectedEntity.GetEntityType() == EEditableEntityType.CHARACTER;
	}

	override bool CanBePerformed(SCR_EditableEntityComponent selectedEntity, vector cursorWorldPosition, int flags)
	{
		SCR_CharacterDamageManagerComponent characterDamageManager = SCR_CharacterDamageManagerComponent.Cast(selectedEntity.GetOwner().FindComponent(SCR_CharacterDamageManagerComponent));
		if (!characterDamageManager)
			return false;

		return true;
	}

	//------------------------------------------------------------------------------------------------
	override void Perform(SCR_EditableEntityComponent selectedEntity, vector cursorWorldPosition)
	{
		SCR_CharacterDamageManagerComponent characterDamageManager = SCR_CharacterDamageManagerComponent.Cast(selectedEntity.GetOwner().FindComponent(SCR_CharacterDamageManagerComponent));
		if (!characterDamageManager)
			return;
		
		if (m_injuryHelperID == RTSOG_InjuryHelperID.MINOR) {
			characterDamageManager.AddRandomInjury(ECharacterDamageState.WOUNDED, 0.8);
		} else if (m_injuryHelperID == RTSOG_InjuryHelperID.MODERATE) {
			characterDamageManager.AddRandomInjury(ECharacterDamageState.WOUNDED, 0.5);
		} else if (m_injuryHelperID == RTSOG_InjuryHelperID.SERIOUS) {
			characterDamageManager.AddRandomInjury(ECharacterDamageState.WOUNDED, 0.1);
		}
	}
};