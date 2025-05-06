class RTSOGForAll_ArsenalComponentClass: SCR_ArsenalComponentClass {}

class RTSOGForAll_ArsenalComponent: SCR_ArsenalComponent {
	[RplProp()]
	ref array<string> blacklistedFactions;
	
	[RplProp()]
	ref array<string> blacklistedItems;
	
	//override void EOnInit(IEntity owner)
	//{				
	//	super.EOnInit(owner);
	//}
	
	override bool GetFilteredArsenalItems(out notnull array<SCR_ArsenalItem> filteredArsenalItems, EArsenalItemDisplayType requiresDisplayType = -1) {
		UpdateBlacklist(GetGame().GetPlayerController().GetPlayerId());
		
		//~ Cannot get items if no entity catalog manager
		SCR_EntityCatalogManagerComponent catalogManager = SCR_EntityCatalogManagerComponent.GetInstance();
		if (!catalogManager) {
			PrintFormat("RTSOGForAll_ArsenalComponent | Entity Catalog Manager is not loaded!", level: LogLevel.ERROR);
			return false;
		}

		FactionManager factionManager = GetGame().GetFactionManager();
		if (!factionManager) {
			PrintFormat("RTSOGForAll_ArsenalComponent | Faction Manager is not loaded!", level: LogLevel.ERROR);
			
			return false;
		}

		array<Faction> factions = {};
		factionManager.GetFactionsList(factions);

		array<SCR_ArsenalItem> tempArsenalItems = {};
		set<ResourceName> tempResourceNames = new set<ResourceName>();

		foreach (Faction faction : factions) {
			string factionName = faction.GetFactionName();
			if (blacklistedFactions.Contains(factionName)) {
				PrintFormat("RTSOGForAll_ArsenalComponent | Removing Faction: %1", factionName, level: LogLevel.NORMAL);
				continue;
			} else {
				PrintFormat("RTSOGForAll_ArsenalComponent | Adding Faction: %1", factionName, level: LogLevel.NORMAL);
			}
			
			SCR_Faction scrFaction = SCR_Faction.Cast(faction);
			if (!scrFaction) {
				PrintFormat("RTSOGForAll_ArsenalComponent | Faction %1 is not of SCR_Faction type!", faction, level: LogLevel.WARNING);
				
				continue;
			}

			tempArsenalItems = catalogManager.GetFilteredArsenalItems(m_eSupportedArsenalItemTypes, m_eSupportedArsenalItemModes, SCR_ArsenalManagerComponent.GetArsenalGameModeType_Static(), scrFaction, requiresDisplayType);

			foreach (SCR_ArsenalItem arsenalItem : tempArsenalItems) {
				if (tempResourceNames.Contains(arsenalItem.GetItemResourceName())) {
					continue;
				}
				
				bool isRemoved = false;
				foreach (string blacklistedItem : blacklistedItems) {
					if (FilePath.MatchesPattern(arsenalItem.GetItemResourceName(), "*" + blacklistedItem + "*"))  {
						isRemoved = true;
						break;
					}
				}
				
				if (!isRemoved) {
					PrintFormat("RTSOGForAll_ArsenalComponent | Adding Item: %1", arsenalItem.GetItemResourceName(), level: LogLevel.NORMAL);
					tempResourceNames.Insert(arsenalItem.GetItemResourceName());
					filteredArsenalItems.Insert(arsenalItem);
				} else {
					PrintFormat("RTSOGForAll_ArsenalComponent | Removing Item: %1", arsenalItem.GetItemResourceName(), level: LogLevel.NORMAL);
				}
			}
		}
		
		return true;
	}

    [RplRpc(RplChannel.Reliable, RplRcver.Server)]
    void UpdateBlacklist(int playerId) {
        if(!Replication.IsServer()) return;

		RTSOGLimited_ArnsenalBlacklist blacklist = RTSOGMods.LoadArsenalBlacklist();
		
        blacklistedFactions = new array<string>();
        blacklistedItems = new array<string>();
		
		// Check if owner is RTSOG
		string playerEID = RTSOGMods.GetPlayerEID(playerId);
		array<string> chalkTeam;
		array<string> redSection;
		array<string> greySection;
		array<string> blackSection;
		array<string> redTalon;
		RTSOGMods.GetGroupsPlayersLists(chalkTeam, redSection, greySection, blackSection, redTalon);
		
		PrintFormat("RTSOGForAll_ArsenalComponent | Player is updating the blacklists: %1", playerEID, level: LogLevel.NORMAL);
		
		if (redTalon.Contains(playerEID)) return;

        foreach (string faction : blacklist.factions) 
            blacklistedFactions.Insert(faction);
        foreach (string item : blacklist.items) 
            blacklistedItems.Insert(item);

        Replication.BumpMe();
    }
}