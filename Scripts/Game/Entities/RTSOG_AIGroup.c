modded class SCR_AIGroup {
	override string GetCustomName() {
		return m_sCustomName;
	}
	
	override void RemovePlayer(int playerID)
	{
		if (!m_aPlayerIDs.Contains(playerID))
			return;
		
		RPC_DoRemovePlayer(playerID);
		Rpc(RPC_DoRemovePlayer, playerID);
		CheckForLeader(-1, false);
		RemovePlayerAgent(playerID);
		SCR_NotificationsComponent.SendToGroup(m_iGroupID, ENotification.GROUPS_PLAYER_LEFT, playerID);
	}
}