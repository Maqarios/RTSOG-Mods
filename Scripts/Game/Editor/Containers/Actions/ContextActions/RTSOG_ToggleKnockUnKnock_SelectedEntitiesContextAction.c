//------------------------------------------------------------------------------------------------
[BaseContainerProps(), SCR_BaseContainerCustomTitleUIInfo("m_Info")]
class RTSOG_ToggleKnockUnKnock_SelectedEntitiesContextAction : SCR_SelectedEntitiesContextAction
{	
	//------------------------------------------------------------------------------------------------
	override bool CanBeShown(SCR_EditableEntityComponent selectedEntity, vector cursorWorldPosition, int flags)
	{
		return SCR_EditableCharacterComponent.Cast(selectedEntity);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanBePerformed(SCR_EditableEntityComponent selectedEntity, vector cursorWorldPosition, int flags)
	{
	    SCR_ChimeraCharacter scrCharacter = SCR_ChimeraCharacter.Cast(selectedEntity.GetOwner());
	    if (!scrCharacter)
	        return false;
		    
	    ChimeraCharacter character = ChimeraCharacter.Cast(scrCharacter);
	    if (!character)
	        return false;
	        
	    CharacterControllerComponent controller = character.GetCharacterController();
	    if (!controller)
	        return false;
				
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override void Perform(SCR_EditableEntityComponent selectedEntity, vector cursorWorldPosition)
	{
		SCR_ChimeraCharacter scrCharacter = SCR_ChimeraCharacter.Cast(selectedEntity.GetOwner());
	    if (!scrCharacter)
	        return;
		    
	    ChimeraCharacter character = ChimeraCharacter.Cast(scrCharacter);
	    if (!character)
	        return;
	        
	    CharacterControllerComponent controller = character.GetCharacterController();
	    if (!controller)
	        return;
	    
	    RTSOG_ConsumableEffectHealthItems KUKInjector = new RTSOG_ConsumableEffectHealthItems();
		KUKInjector.ApplyEffect(selectedEntity.GetOwner(), selectedEntity.GetOwner(), null, null);
	}
}
