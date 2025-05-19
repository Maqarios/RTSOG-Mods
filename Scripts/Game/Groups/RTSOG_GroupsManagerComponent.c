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
		array<string> certifiedGMs;
		array<string> chalkTeam;
		array<string> redSection;
		array<string> greySection;
		array<string> blackSection;
		array<string> redTalon;
		RTSOGMods.GetGroupsPlayersLists(certifiedGMs, chalkTeam, redSection, greySection, blackSection, redTalon);
		
		if (group.IsFull() || !isPlayerAllowedInGroup(groupName, playerEID, certifiedGMs, chalkTeam, redSection, greySection, blackSection, redTalon))
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
			array<string> certifiedGMs;
			array<string> chalkTeam;
			array<string> redSection;
			array<string> greySection;
			array<string> blackSection;
			array<string> redTalon;
			RTSOGMods.GetGroupsPlayersLists(certifiedGMs, chalkTeam, redSection, greySection, blackSection, redTalon);
			
			if (newGroup.IsFull() || !isPlayerAllowedInGroup(groupName, playerEID, certifiedGMs, chalkTeam, redSection, greySection, blackSection, redTalon))
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
	
	bool isPlayerAllowedInGroup(string groupName, string playerEID, array<string> certifiedGMs, array<string> chalkTeam, array<string> redSection, array<string> greySection, array<string> blackSection, array<string> redTalon) {
		// Check if player is allowed in the group
		bool isCertifiedGM = certifiedGMs.Contains(playerEID);
		bool isChalkTeam = chalkTeam.Contains(playerEID);
		bool isRedSection = redSection.Contains(playerEID);
		bool isGreySection = greySection.Contains(playerEID);
		bool isBlackSection = blackSection.Contains(playerEID);
		bool isRedTalon = redTalon.Contains(playerEID);
		
		if (isRedTalon)
			return true;
		
		if(groupName == "Green Team")
			return true;
		
		if(groupName == "Chalk Team" && isChalkTeam)
			return true;
		
		if(groupName == "Red Section" && isRedSection)
			return true;
		
		if(groupName == "Grey Section" && isGreySection)
			return true;
		
		if(groupName == "Black Section" && isBlackSection)
			return true;
		
		if(groupName == "Watch Tower" && isCertifiedGM)
			return true;
		
		array<string> predefinedGroups = new array<string>();
		predefinedGroups = {"Green Team", "Chalk Team", "Red Section", "Grey Section", "Black Section", "Red Talon", "Watch Tower"};
		if(!predefinedGroups.Contains(groupName))
			return true;
		
		return false;
	}
}