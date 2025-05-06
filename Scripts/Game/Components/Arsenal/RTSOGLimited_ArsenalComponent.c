class RTSOGLimited_ArsenalComponentClass: SCR_ArsenalComponentClass {}

class RTSOGLimited_ArsenalComponent: SCR_ArsenalComponent {
	[RplProp()]
	ref array<string> blacklistedFactions;
	
	[RplProp()]
	ref array<string> blacklistedItems;
	
	override bool GetFilteredArsenalItems(out notnull array<SCR_ArsenalItem> filteredArsenalItems, EArsenalItemDisplayType requiresDisplayType = -1) {
		// Get Blacklist from server
		UpdateBlacklist();
		
		//~ Cannot get items if no entity catalog manager
		SCR_EntityCatalogManagerComponent catalogManager = SCR_EntityCatalogManagerComponent.GetInstance();
		if (!catalogManager) {
			PrintFormat("RTSOGLimited_ArsenalComponent | Entity Catalog Manager is not loaded!", level: LogLevel.ERROR);
			return false;
		}

		FactionManager factionManager = GetGame().GetFactionManager();
		if (!factionManager) {
			PrintFormat("RTSOGLimited_ArsenalComponent | Faction Manager is not loaded!", level: LogLevel.ERROR);
			
			return false;
		}

		array<Faction> factions = {};
		factionManager.GetFactionsList(factions);

		array<SCR_ArsenalItem> tempArsenalItems = {};
		set<ResourceName> tempResourceNames = new set<ResourceName>();

		foreach (Faction faction : factions) {
			string factionName = faction.GetFactionName();
			if (blacklistedFactions.Contains(factionName)) {
				PrintFormat("RTSOGLimited_ArsenalComponent | Removing Faction: %1", factionName, level: LogLevel.NORMAL);
				continue;
			} else {
				PrintFormat("RTSOGLimited_ArsenalComponent | Adding Faction: %1", factionName, level: LogLevel.NORMAL);
			}
			
			SCR_Faction scrFaction = SCR_Faction.Cast(faction);
			if (!scrFaction) {
				PrintFormat("RTSOGLimited_ArsenalComponent | Faction %1 is not of SCR_Faction type!", faction, level: LogLevel.WARNING);
				
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
					PrintFormat("RTSOGLimited_ArsenalComponent | Adding Item: %1", arsenalItem.GetItemResourceName(), level: LogLevel.NORMAL);
					tempResourceNames.Insert(arsenalItem.GetItemResourceName());
					filteredArsenalItems.Insert(arsenalItem);
				} else {
					PrintFormat("RTSOGLimited_ArsenalComponent | Removing Item: %1", arsenalItem.GetItemResourceName(), level: LogLevel.NORMAL);
				}
			}
		}
		
		return true;
	}
	
	
	// Client-side RPC to request filtered items
    [RplRpc(RplChannel.Reliable, RplRcver.Server)]
    void Rpc_RequestFilteredItems() 
    {
        // Only execute on server
        if (!Replication.IsServer()) return;    
        
        // Make sure blacklists are up to date before sending
        UpdateBlacklist();
            
        // Send data back to the requesting client
        Rpc_ReceiveFilteredItems(blacklistedFactions, blacklistedItems);
    }
    
    // Server-to-client RPC to receive filtered items
    [RplRpc(RplChannel.Reliable, RplRcver.Owner)]
    void Rpc_ReceiveFilteredItems(array<string> factions, array<string> items)
    {
        // Update client-side arrays
        if (!blacklistedFactions)
            blacklistedFactions = new array<string>();
        else
            blacklistedFactions.Clear();
            
        if (!blacklistedItems)
            blacklistedItems = new array<string>();
        else
            blacklistedItems.Clear();
            
        // Copy received data to local arrays
        foreach (string faction : factions)
            blacklistedFactions.Insert(faction);
            
        foreach (string item : items)
            blacklistedItems.Insert(item);
    }

    [RplRpc(RplChannel.Reliable, RplRcver.Server)]
    void UpdateBlacklist() {
        if(!Replication.IsServer()) return;

		RTSOGLimited_ArnsenalBlacklist blacklist = RTSOGMods.LoadArsenalBlacklist();
		
        blacklistedFactions = new array<string>();
        blacklistedItems = new array<string>();

        foreach (string faction : blacklist.factions) 
            blacklistedFactions.Insert(faction);
        foreach (string item : blacklist.items) 
            blacklistedItems.Insert(item);

        Replication.BumpMe();
    }
}