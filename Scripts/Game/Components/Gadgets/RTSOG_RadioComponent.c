modded class SCR_RadioComponent
{
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);

		GetGame().GetCallqueue().CallLater(SetFixedChannels, 100, param1: owner);
	}
	
	// Hard setting radio transcievers
	void SetFixedChannels(IEntity owner)
	{
		PrintFormat("RTSOGMods | RTSOG_RadioComponent | SetFixedChannels", level: LogLevel.NORMAL);
		
		if (GetRadioComponent().GetTransceiver(0))
			GetRadioComponent().GetTransceiver(0).SetFrequency(32000);
		
		if (GetRadioComponent().GetTransceiver(1))
			GetRadioComponent().GetTransceiver(1).SetFrequency(48000);
		
		if (GetRadioComponent().GetTransceiver(2))
			GetRadioComponent().GetTransceiver(2).SetFrequency(38000);
	}
}
