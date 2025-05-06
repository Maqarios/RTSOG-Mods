modded enum SCR_EConsumableType {
	RTSOG_KnockUnKnock
}

[BaseContainerProps()]
class RTSOG_ConsumableEffectHealthItems : SCR_ConsumableEffectHealthItems
{
	//------------------------------------------------------------------------------------------------
	// constructor
	void RTSOG_ConsumableEffectHealthItems()
	{
		m_eConsumableType = SCR_EConsumableType.RTSOG_KnockUnKnock;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanApplyEffect(notnull IEntity target, notnull IEntity user, out SCR_EConsumableFailReason failReason)
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanApplyEffectToHZ(notnull IEntity target, notnull IEntity user, ECharacterHitZoneGroup group, out SCR_EConsumableFailReason failReason = SCR_EConsumableFailReason.NONE)
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------	
	override void ApplyEffect(notnull IEntity target, notnull IEntity user, IEntity item, ItemUseParameters animParams)
	{
		if (!Replication.IsServer())
			return;
		    
	    ChimeraCharacter character = ChimeraCharacter.Cast(target);
	    if (!character)
	        return;
	        
	    CharacterControllerComponent controller = character.GetCharacterController();
	    if (!controller)
	        return;
	        
	    // Direct state change on server
	    if (!controller.IsUnconscious()) {
	        controller.SetUnconscious(true);
	        controller.EnableReviveCharacter(false);
	    } else {
	        controller.SetUnconscious(false);
	        controller.EnableReviveCharacter(true);
	    }
	}
}