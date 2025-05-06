//------------------------------------------------------------------------------------------------
modded class SCR_CharacterDamageManagerComponent {
	void AddRandomInjury(ECharacterDamageState intensityEnum, float intensityFloat)
	{
		SCR_CharacterHitZone targetHitZone = GetRandomPhysicalHitZone();

		if (!targetHitZone || targetHitZone.IsProxy())
			return;
		
		if (intensityEnum == ECharacterDamageState.UNDAMAGED)
			return;
		
		targetHitZone.SetHealthScaled(intensityFloat);

		AddBleedingEffectOnHitZone(targetHitZone, 1);
	}
}