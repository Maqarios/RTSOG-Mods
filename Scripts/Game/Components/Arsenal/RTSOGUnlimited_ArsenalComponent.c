class RTSOGUnlimited_ArsenalComponentClass: SCR_ArsenalComponentClass {}
class RTSOGUnlimited_ArsenalComponent: SCR_ArsenalComponent {
	override bool GetFilteredArsenalItems(out notnull array<SCR_ArsenalItem> filteredArsenalItems, EArsenalItemDisplayType requiresDisplayType = -1) {
		//~ Clear any previously added items
    	filteredArsenalItems.Clear();

		//~ Cannot get items if no entity catalog manager
		SCR_EntityCatalogManagerComponent catalogManager = SCR_EntityCatalogManagerComponent.GetInstance();
		if (!catalogManager) {
			PrintFormat("RTSOGUnlimited_ArsenalComponent | Entity Catalog Manager is not loaded!", level: LogLevel.ERROR);
			return false;
		}

		FactionManager factionManager = GetGame().GetFactionManager();
		if (!factionManager) {
			PrintFormat("RTSOGUnlimited_ArsenalComponent | Faction Manager is not loaded!", level: LogLevel.ERROR);
			return false;
		}

		array<Faction> factions = {};
		factionManager.GetFactionsList(factions);

		array<SCR_ArsenalItem> tempArsenalItems = {};
		set<ResourceName> tempResourceNames = new set<ResourceName>();

		foreach (Faction faction : factions) {
			SCR_Faction scrFaction = SCR_Faction.Cast(faction);
			if (!scrFaction) {
				PrintFormat("RTSOGUnlimited_ArsenalComponent | Faction %1 is not of SCR_Faction type!", faction, level: LogLevel.WARNING);
				continue;
			}

			tempArsenalItems = catalogManager.GetFilteredArsenalItems(m_eSupportedArsenalItemTypes, m_eSupportedArsenalItemModes, SCR_ArsenalManagerComponent.GetArsenalGameModeType_Static(), scrFaction, requiresDisplayType);

			foreach (SCR_ArsenalItem arsenalItem : tempArsenalItems) {
				if (tempResourceNames.Contains(arsenalItem.GetItemResourceName())) {
					continue;
				}
				
				tempResourceNames.Insert(arsenalItem.GetItemResourceName());
				filteredArsenalItems.Insert(arsenalItem);
			}
		}

		return true;
	}
}
