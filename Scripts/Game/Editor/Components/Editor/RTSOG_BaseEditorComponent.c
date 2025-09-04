class RTSOG_BaseEditorComponentClass: SCR_BaseEditorComponentClass {
	
};

class RTSOG_BaseEditorComponent: SCR_BaseEditorComponent {
	override void OnPostInit(IEntity owner) {
		RTSOGMods.damageMultipliers = new RTSOGMods_DamageMultipliers();
		RTSOGMods.LoadDamageMultipliers();
		
		bool isDebugger = RplSession.Mode() == RplMode.None;
		bool isServer = RplSession.Mode() == RplMode.Dedicated;
		if (isDebugger || isServer) {
			GetGame().GetCallqueue().CallLater(RTSOGMods.LoadDamageMultipliers, 30000, true);
		}
		
		PrintFormat("RTSOG_BaseEditorComponent | Loaded!", level: LogLevel.NORMAL);
	}
}