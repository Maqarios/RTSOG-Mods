modded class SCR_GroupTileButton {
	override void InitiateGroupTile()
	{
		m_GroupManager = SCR_GroupsManagerComponent.GetInstance();
		if (!m_GroupManager)
			return;

		m_GroupComponent = SCR_PlayerControllerGroupComponent.GetLocalPlayerControllerGroupComponent();
		if (!m_GroupComponent)
			return;

		SCR_PlayerController playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
		if (!playerController)
			return;
		
		SocialComponent  socialComp = SocialComponent.Cast(playerController.FindComponent(SocialComponent));
		if (!socialComp)
			return;


		SCR_AIGroup group = m_GroupManager.FindGroup(m_iGroupID);
		if (!group)
			return;

		group.GetOnPlayerLeaderChanged().Insert(SetupJoinGroupButton);
		group.GetOnJoinPrivateGroupRequest().Insert(SetupJoinGroupButton);
		
		//workaround for issues with playerControllerGroupsComponent, needs to be reworked with this whole script mess
		SCR_GroupSubMenu.Init();
		SCR_GroupSubMenu.GetOnJoingGroupRequestSent().Insert(SetupJoinGroupButton);

		m_BaseTaskManager = GetTaskManager();
		if (m_BaseTaskManager)
			m_BaseTaskManager.s_OnTaskUpdate.Insert(RefreshPlayers);

		group.GetOnMemberStateChange().Insert(RefreshPlayers);

		RichTextWidget squadName = RichTextWidget.Cast(GetRootWidget().FindAnyWidget("Callsign"));
		if (squadName)
		{
			string groupName = group.GetCustomNameWithOriginal();
			string company, platoon, squad, character, format;
			group.GetCallsigns(company, platoon, squad, character, format);

			if (groupName.IsEmpty() || group.GetNameAuthorID() != 0 && socialComp.IsRestricted(group.GetNameAuthorID(), EUserInteraction.UserGeneratedContent))
			{
				squadName.SetTextFormat(format, company, platoon, squad, character);
			}
			else
			{
				company = WidgetManager.Translate(company);
				groupName = group.GetCustomName();
				squadName.SetText(groupName);
			}
		}

		RichTextWidget frequency = RichTextWidget.Cast(GetRootWidget().FindAnyWidget("Frequency"));
		if (frequency)
			frequency.SetText(""+group.GetRadioFrequency()*0.001 + " #AR-VON_FrequencyUnits_MHz");

		RichTextWidget playerCount = RichTextWidget.Cast(GetRootWidget().FindAnyWidget("PlayerCount"));
		if (playerCount)
			playerCount.SetText(group.GetPlayerCount().ToString() + "/" + group.GetMaxMembers());

		if (group.IsFull())
			SetGroupInfoColor(m_GroupFullColor);

		ImageWidget background = ImageWidget.Cast(GetRootWidget().FindAnyWidget("Background"));

		if (background)
			background.SetVisible(m_GroupComponent.GetSelectedGroupID() == m_iGroupID);

		if (group.IsPlayerInGroup(playerController.GetPlayerId()))
			squadName.SetColor(m_PlayerNameSelfColor);

		ImageWidget privateIcon = ImageWidget.Cast(GetRootWidget().FindAnyWidget("PrivateIcon"));
		if (privateIcon)
			privateIcon.SetVisible(group.IsPrivate());

		if (!m_ParentSubMenu)
			FindParentMenu();
	}
	
	override void RefreshPlayers()
	{
		PlayerManager playerManager = GetGame().GetPlayerManager();
		if (!m_GroupFaction || !m_GroupManager || !playerManager)
			return;

		SCR_PlayerController playerController = SCR_PlayerController.Cast(GetGame().GetPlayerController());
		if (!playerController)
			return;

		SCR_AIGroup group = m_GroupManager.FindGroup(m_iGroupID);
		if (!group)
			return;

		SetupSelectGroupFlagButton(group);

		if (m_ParentSubMenu == null)
			FindParentMenu();

		m_aPlayerComponentsList.Clear();

		VerticalLayoutWidget playerList = VerticalLayoutWidget.Cast(m_ParentSubMenu.GetRootWidget().FindAnyWidget("PlayerList"));
		if (!playerList)
			return;

		VerticalLayoutWidget leaderList = VerticalLayoutWidget.Cast(m_ParentSubMenu.GetRootWidget().FindAnyWidget("Leader"));
		if (!leaderList)
			return;

		RichTextWidget squadName = RichTextWidget.Cast(m_ParentSubMenu.GetRootWidget().FindAnyWidget("GroupDetailCallsign"));
		if (!squadName)
			return;

		RichTextWidget description = RichTextWidget.Cast(m_ParentSubMenu.GetRootWidget().FindAnyWidget("Description"));
		if (!description)
			return;

		RichTextWidget frequency = RichTextWidget.Cast(m_ParentSubMenu.GetRootWidget().FindAnyWidget("GroupDetailFrequency"));
		if (!frequency)
			return;


		SCR_PlayerControllerGroupComponent s_PlayerGroupController = SCR_PlayerControllerGroupComponent.GetLocalPlayerControllerGroupComponent();
		if (!s_PlayerGroupController)
			return;
		
		SocialComponent socialComp = SocialComponent.Cast(playerController.FindComponent(SocialComponent));
		if (!socialComp)
			return;
		
		if (!s_PlayerGroupController.CanPlayerJoinGroup(playerController.GetPlayerId(), m_GroupManager.FindGroup(m_iGroupID)))
			m_JoinGroupButton.SetEnabled(false);
		else
			m_JoinGroupButton.SetEnabled(true);

		string groupName = group.GetCustomName();
		string company, platoon, squad, character, format;
		group.GetCallsigns(company, platoon, squad, character, format);
		
		if (groupName.IsEmpty() || group.GetNameAuthorID() != 0 && socialComp.IsRestricted(group.GetNameAuthorID(), EUserInteraction.UserGeneratedContent))
		{
			squadName.SetTextFormat(format, company, platoon, squad, character);
		}
		else
		{
			company = WidgetManager.Translate(company);
			groupName = group.GetCustomName();
			squadName.SetText(groupName);
		}

		if (!group.GetCustomDescription().IsEmpty())
			description.SetText(group.GetCustomDescription());
		else
			description.SetText(string.Empty);

		CheckLeaderOptions();

		frequency.SetText(""+group.GetRadioFrequency()*0.001 + " #AR-VON_FrequencyUnits_MHz");

		Widget children = playerList.GetChildren();
		while (children)
		{
			playerList.RemoveChild(children);
			children = playerList.GetChildren();
		}

		children = leaderList.GetChildren();
		while (children)
		{
			leaderList.RemoveChild(children);
			children = leaderList.GetChildren();
		}

		array<int> playerIDs = group.GetPlayerIDs();
		Widget playerTile;

		int leaderID = group.GetLeaderID();
		if (leaderID >= 0)
		{
			playerTile = GetGame().GetWorkspace().CreateWidgets(m_textLayout, leaderList);
			SetupPlayerTile(playerTile, leaderID);
		}

		foreach (int playerID : playerIDs)
		{
			if (playerID == leaderID)
				continue;

			playerTile = GetGame().GetWorkspace().CreateWidgets(m_textLayout, playerList);
			SetupPlayerTile(playerTile, playerID);
		}

		//disable this for now as it has issues with replication of aigroups
		//ShowAIsInGroup();

		SetupJoinGroupButton();

		GetGame().GetWorkspace().SetFocusedWidget(GetRootWidget());
	}
}