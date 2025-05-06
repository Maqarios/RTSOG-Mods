modded class SCR_VotingManagerComponent {
	void Vote2(int playerID, EVotingType type, int value) {}

	void RemoveVote2(int playerID, EVotingType type, int value) {}
	
	bool StartVoting2(EVotingType type, int startingPlayerID, int value = SCR_VotingBase.DEFAULT_VALUE) {}

	void EndVoting2(EVotingType type, int value = SCR_VotingBase.DEFAULT_VALUE, EVotingOutcome outcome = EVotingOutcome.EVALUATE) {}

	bool IsVotingAvailable2(EVotingType type, int value = SCR_VotingBase.DEFAULT_VALUE) {
		return false;
	}

	bool IsVoting2(EVotingType type, int value = SCR_VotingBase.DEFAULT_VALUE) {
		return false;
	}

	protected void EOnFrame2(IEntity owner, float timeSlice) {}
	
	
	// Server Side
	override protected void EndVoting(SCR_VotingBase voting, EVotingOutcome outcome = EVotingOutcome.EVALUATE) {
		EVotingType type = voting.GetType();
		int value = voting.GetValue();
		
		if (type == EVotingType.EDITOR_IN || type == EVotingType.EDITOR_OUT || type == EVotingType.EDITOR_WITHDRAW) {
			// Get allowed groups
			array<string> chalkTeam;
			array<string> redSection;
			array<string> greySection;
			array<string> blackSection;
			array<string> redTalon;
			RTSOGMods.GetGroupsPlayersLists(chalkTeam, redSection, greySection, blackSection, redTalon);
			
			// Get player BI identifier
			string playerEID = RTSOGMods.GetPlayerEID(value);
			
			// Check if player is allowed in the group
			bool isChalkTeam = chalkTeam.Contains(playerEID);
			bool isRedSection = redSection.Contains(playerEID);
			bool isGreySection = greySection.Contains(playerEID);
			bool isBlackSection = blackSection.Contains(playerEID);
			bool isRedTalon = redTalon.Contains(playerEID);
			
			if  (isRedTalon) {
				super.EndVoting(voting, outcome);
			}
		} else {
			super.EndVoting(voting, EVotingOutcome.FORCE_FAIL);
		}
	}
}
