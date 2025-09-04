modded class SCR_HitZone
{
	override float ComputeEffectiveDamage(notnull BaseDamageContext damageContext, bool isDOT) {
		float oldDamageValue = damageContext.damageValue;
		if (damageContext.damageType == EDamageType.KINETIC) {
			if (damageContext.instigator.GetInstigatorPlayerID() > 0) {
				damageContext.damageValue = RTSOGMods.damageMultipliers.playerKineticDamageMultiplier * damageContext.damageValue;
			}
				
			if (damageContext.instigator.GetInstigatorPlayerID() == 0) {
				damageContext.damageValue = RTSOGMods.damageMultipliers.AIKineticDamageMultiplier * damageContext.damageValue;
			}
		}
		
		return super.ComputeEffectiveDamage(damageContext, isDOT);
	}
}
