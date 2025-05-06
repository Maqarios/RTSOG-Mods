modded class SCR_CharacterHitZone {
	override float ComputeEffectiveDamage(notnull BaseDamageContext damageContext, bool isDOT)
	{
		SCR_CharacterControllerComponent characterController = SCR_CharacterControllerComponent.Cast(GetOwner().FindComponent(SCR_CharacterControllerComponent));
		if (GetName() == "Head" && damageContext.damageType == EDamageType.MELEE && !characterController.IsUnconscious()) {
			SCR_CharacterDamageManagerComponent damageManager = SCR_CharacterDamageManagerComponent.Cast(GetOwner().FindComponent(SCR_CharacterDamageManagerComponent));
			damageManager.ForceUnconsciousness();
			return 0;
		}
		
		return super.ComputeEffectiveDamage(damageContext, isDOT);
	}
}
