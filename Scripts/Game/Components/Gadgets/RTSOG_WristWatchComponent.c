modded class RHS_WristWatchComponent
{
	override void EOnInit(IEntity owner)
	{
		m_eGarminMode = ERHS_GarminModes.COMPASS;
		super.EOnInit(owner);
	}
	
	override void UpdateCompass()
	{
		float azim = GetOwner().GetYawPitchRoll()[0] + 90.0;
		m_wCompassDial.SetRotation(-azim);

		if (azim < 0)
			azim += 360;

		m_wAzimuth.SetText(azim.ToString(3, 0));
		GetGame().GetCallqueue().CallLater(UpdateCompass, 50);

		if (azim > 337.5)
			m_wAzDir.SetText("N");
		else if (azim > 292.5)
			m_wAzDir.SetText("NW");
		else if (azim > 247.5)
			m_wAzDir.SetText("W");
		else if (azim > 202.5)
			m_wAzDir.SetText("SW");
		else if (azim > 157.5)
			m_wAzDir.SetText("S");
		else if (azim > 112.5)
			m_wAzDir.SetText("SE");
		else if (azim > 67.5)
			m_wAzDir.SetText("E");
		else if (azim > 25.5)
			m_wAzDir.SetText("NE");
		else
			m_wAzDir.SetText("N");
	}
}
