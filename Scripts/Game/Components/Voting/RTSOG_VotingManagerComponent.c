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
			// Get player bohemia id
			string playerEID = RTSOGMods.GetPlayerEID(value);
			
			// Get groups whitelist
			RTSOGMods_GroupsPlayersWhitelist whitelist = RTSOGMods.GetGroupsPlayersLists();
			if (!whitelist)
			{
				super.EndVoting(voting, outcome);
				return;
			}
			
			if  (whitelist.certifiedGMs.Contains(playerEID)) {
				super.EndVoting(voting, outcome);
			}
		} else {
			super.EndVoting(voting, EVotingOutcome.FORCE_FAIL);
		}
	}
}
