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
}