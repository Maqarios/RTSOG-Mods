modded class SCR_GroupsManagerComponent {
	override int AddPlayerToGroup(int groupID, int playerID) {
		// Get group name
		SCR_AIGroup group = FindGroup(groupID);
		if (!group)
			return -1;
		string groupName = group.GetCustomName();
		
		// Get Player Enfusion ID
		string playerEID = RTSOGMods.GetPlayerEID(playerID);

		// Get groups whitelist
		array<string> chalkTeam;
		array<string> redSection;
		array<string> greySection;
		array<string> blackSection;
		array<string> redTalon;
		GetGroupsPlayersLists(chalkTeam, redSection, greySection, blackSection, redTalon);
		
		if (group.IsFull() || !isPlayerAllowedInGroup(groupName, playerEID, chalkTeam, redSection, greySection, blackSection, redTalon))
			return -1;
		
		group.AddPlayer(playerID);
		return groupID;
	}
	
	override int MovePlayerToGroup(int playerID, int previousGroupID, int newGroupID)
	{
		m_iMovingPlayerToGroupID = newGroupID;
		SCR_AIGroup previousGroup = FindGroup(previousGroupID);
		if (previousGroup)
			previousGroup.RemovePlayer(playerID);
		
		SCR_AIGroup newGroup = FindGroup(newGroupID);
		if (newGroup)
		{
			// Get Player Enfusion ID
			string playerEID = RTSOGMods.GetPlayerEID(playerID);
			
			// Get group name
			string groupName = newGroup.GetCustomName();
			
			// Get groups whitelist
			array<string> chalkTeam;
			array<string> redSection;
			array<string> greySection;
			array<string> blackSection;
			array<string> redTalon;
			
			GetGroupsPlayersLists(chalkTeam, redSection, greySection, blackSection, redTalon);
			if (newGroup.IsFull() || !isPlayerAllowedInGroup(groupName, playerEID, chalkTeam, redSection, greySection, blackSection, redTalon))
			{
				m_iMovingPlayerToGroupID = -1;
				return -1;
			}
			
			newGroup.AddPlayer(playerID);
			m_iMovingPlayerToGroupID = -1;
			return newGroupID;
		}
		else
		{
			m_iMovingPlayerToGroupID = -1;
			return -1;
		}
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	void GetGroupsPlayersLists(out array<string> chalkTeam, out array<string> redSection, out array<string> greySection, out array<string> blackSection, out array<string> redTalon) {
		if(!Replication.IsServer()) return;

	    RTSOGMods_GroupsPlayersWhitelist whitelist = RTSOGMods.LoadGroupsPlayersWhitelist();
		
		chalkTeam = whitelist.chalkTeam;
		redSection = whitelist.redSection;
		greySection = whitelist.greySection;
		blackSection = whitelist.blackSection;
		redTalon = whitelist.redTalon;
	}
	
	bool isPlayerAllowedInGroup(string groupName, string playerEID, array<string> chalkTeam, array<string> redSection, array<string> greySection, array<string> blackSection, array<string> redTalon) {
		PrintFormat("RTSOG_GroupsManagerComponent | Player EID: %1", playerEID, level: LogLevel.DEBUG);
		PrintFormat("RTSOG_GroupsManagerComponent | Group Name: %1", groupName, level: LogLevel.DEBUG);
		PrintFormat("RTSOG_GroupsManagerComponent | Chalk Team: %1", chalkTeam.ToString(), level: LogLevel.DEBUG);
		PrintFormat("RTSOG_GroupsManagerComponent | Red Section: %1", redSection.ToString(), level: LogLevel.DEBUG);
		PrintFormat("RTSOG_GroupsManagerComponent | Grey Section: %1", greySection.ToString(), level: LogLevel.DEBUG);
		PrintFormat("RTSOG_GroupsManagerComponent | Black Section: %1", blackSection.ToString(), level: LogLevel.DEBUG);
		PrintFormat("RTSOG_GroupsManagerComponent | Red Talon: %1", redTalon.ToString(), level: LogLevel.DEBUG);
		
		// Check if player is allowed in the group
		bool isChalkTeam = chalkTeam.Contains(playerEID);
		bool isRedSection = redSection.Contains(playerEID);
		bool isGreySection = greySection.Contains(playerEID);
		bool isBlackSection = blackSection.Contains(playerEID);
		bool isRedTalon = redTalon.Contains(playerEID);
		
		if (isRedTalon)
			return true;
		
		// To be removed
		if (groupName == "Red Talon")
			return false;
		return true;
		
		if(groupName == "Green Team")
			return true;
		
		if(groupName == "Chalk Team" && (isChalkTeam || isRedSection || isGreySection || isBlackSection))
			return true;
		
		if(groupName == "Red Section" && isRedSection)
			return true;
		
		if(groupName == "Grey Section" && isGreySection)
			return true;
		
		if(groupName == "Black Section" && isBlackSection)
			return true;
		
		return false;
	}
}