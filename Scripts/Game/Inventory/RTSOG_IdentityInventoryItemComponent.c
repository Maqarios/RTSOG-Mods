modded class SCR_IdentityInventoryItemComponent
{
	protected void DelayedInit(IEntity owner)
	{
		if (!owner)
			return;
		
		ChimeraCharacter character;
		IEntity parent = owner.GetParent();
		
		while (parent)
		{
			character = ChimeraCharacter.Cast(parent);
			if (character)
				break;
			
			parent = parent.GetParent();
		}
		
		if (!character)
			return;

		SCR_ExtendedCharacterIdentityComponent rootExtendedIdentity = SCR_ExtendedCharacterIdentityComponent.Cast(character.FindComponent(SCR_ExtendedCharacterIdentityComponent));
		if (!rootExtendedIdentity)
			return;
		
		//-----------------------------------------------------------------------------
		// Added by RTSOG Mods to make weight zero for Red Talon Members
		//-----------------------------------------------------------------------------
		int playerID = rootExtendedIdentity.GetPlayerID();
		if (playerID && playerID > 0) {
			string playerEID = RTSOGMods.GetPlayerEID(playerID);
			
			array<string> redTalon;
			RTSOGMods.GetGroupsPlayersLists(null, null, null, null, null, redTalon);
			
			if (redTalon.Contains(playerEID)) {
				SetAdditionalWeight(-999.000);
			}
		}
		//-----------------------------------------------------------------------------
		
		RplComponent rplComp = RplComponent.Cast(rootExtendedIdentity.GetOwner().FindComponent(RplComponent));
		if (!rplComp)
			return;
		
		m_RplIdLinkedIdentity = Replication.FindId(rplComp);
		
		//~ This identity holds valuable intel. So make sure that is shown
		m_iValuableIntelFaction = rootExtendedIdentity.OnIdentityItemAdded_S(this, SCR_IdentityManagerComponent.Static_IsGenerateValuableIntelEnabled());
		
		if (m_iValuableIntelFaction >= 0)
			OnIntelFactionSet();

		Replication.BumpMe();
	}
}
