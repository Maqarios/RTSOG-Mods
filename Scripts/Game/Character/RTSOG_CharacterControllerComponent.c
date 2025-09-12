modded class SCR_CharacterControllerComponent
{
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
    void Rpc_OrderSurrender()
    {
		if (this.ACE_Captives_HasSurrendered())
            return;
		
        this.ACE_Captives_SetSurrender(true);
    }
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
    void Rpc_OrderRelease()
    {
		if (!this.ACE_Captives_HasSurrendered())
            return;
		
        this.ACE_Captives_SetSurrender(false);
    }
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	void Rpc_KnockOut()
	{
		if (this.IsUnconscious())
			return;
		
		ChimeraCharacter char = GetCharacter();
		if (!char)
			return;
		
		SCR_CharacterDamageManagerComponent damageMan = SCR_CharacterDamageManagerComponent.Cast(char.GetDamageManager());
		if (!damageMan)
			return;
		
		damageMan.ForceUnconsciousness();
	}
}