class RTSOG_RhinoAttachmentComponentClass : RHS_RhinoAttachmentComponentClass
{
}

class RTSOG_RhinoAttachmentComponent : RHS_RhinoAttachmentComponent
{
	//------------------------------------------------------------------------------------------------
	//! Method called when wearer Aims Down the Sight
	override void OnADSIn()
	{
		if (m_bActivated)
		{
			if (m_CharacterOwner && m_CharacterOwner.IsInVehicle())
			{
				if (!m_bIsADS)
				{//to not do this each frame we cache vehicle sight the first time that user goes ADS
					CompartmentAccessComponent compartmentAccessComp = m_CharacterOwner.GetCompartmentAccessComponent();
					if (compartmentAccessComp)
					{
						BaseCompartmentSlot comparmentSlot = compartmentAccessComp.GetCompartment();
						if (comparmentSlot)
						{
							BaseWeaponManagerComponent vehicleWeaponManager = BaseWeaponManagerComponent.Cast(comparmentSlot.GetOwner().FindComponent(BaseWeaponManagerComponent));
							if (vehicleWeaponManager)
								m_CurrentlyUsedSightComponent = vehicleWeaponManager.GetCurrentSights();
						}
					}
				}
			}
			else
			{
				m_CurrentlyUsedSightComponent = m_WeaponManager.GetCurrentSights();
			}

			if (m_bIsAvialbleInADS)
			{
				bool canSightBeUsedWithNVG = true;

				if (!m_bUseThermal)
				{
					if (m_CurrentlyUsedSightComponent && m_CurrentlyUsedSightComponent.RHS_IsSightConfiguredForRHSNVG())
					{
						canSightBeUsedWithNVG = m_CurrentlyUsedSightComponent.RHS_IsNVGCompatible();
					}
					else
					{
						SightsFOVInfo currentSightInfo = m_CharacterController.GetSightsFOVInfo();
						if (currentSightInfo && currentSightInfo.GetFOV() < SCR_2DOpticsComponent.CalculateZoomFOV(m_fMaxZoomLevel))
							canSightBeUsedWithNVG = false;
					}
				}

				if (!canSightBeUsedWithNVG)
					ActivateAction();
			}
			else
			{
				ActivateAction();
			}

			m_bIsADS = true;
		}

		SetNVGLightState(m_bActivated && false);
	}
}
