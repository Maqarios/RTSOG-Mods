//------------------------------------------------------------------------------------------------
class RTSOG_OrderSurrenderUserAction : ScriptedUserAction
{
	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		if (!super.CanBeShownScript(user))
			return false;
		
		int playerID = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(GetOwner());
		if (playerID > 0)
			return false;
		
		SCR_ChimeraCharacter scrCharacter = SCR_ChimeraCharacter.Cast(GetOwner());
	    if (!scrCharacter)
	        return false;
	        
	    SCR_CharacterControllerComponent controller = SCR_CharacterControllerComponent.Cast(scrCharacter.GetCharacterController());
		if (!controller)
			return false;
		
		if (controller.GetLifeState() != ECharacterLifeState.ALIVE || controller.IsUnconscious() || controller.ACE_Captives_HasSurrendered())
			return false;
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		if (!super.CanBePerformedScript(user))
			return false;
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		SCR_ChimeraCharacter scrCharacter = SCR_ChimeraCharacter.Cast(pOwnerEntity);
	    if (!scrCharacter)
	        return;
	        
	    SCR_CharacterControllerComponent controller = SCR_CharacterControllerComponent.Cast(scrCharacter.GetCharacterController());
		if (!controller)
			return;
		
		controller.Rpc_OrderSurrender();
	}
}
