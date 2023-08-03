#pragma once
#include"../scanner/scanner.hpp"

namespace offsets_modules 
{
	inline DWORD64 module_base = (DWORD64)m_pMemory->pNTModules->NtGetModuleHandleExW(__("EasyAntiCheat_launcher.exe"));
}

namespace offsets
{
	inline DWORD64 client_render_targets = 0x20d4e18;
	inline DWORD64 ibase_client_dll = 0x1de5590;
	inline DWORD64 iclient_entity_list = 0x1e54dc7;
	inline DWORD64 cprediction = 0x0;
	inline DWORD64 iv_model_render = 0x0;
	inline DWORD64 vgui_system = 0x0;
	inline DWORD64 iv_render_view = 0x0;
	inline DWORD64 iv_debug_overlay = 0x0;
	inline DWORD64 iv_model_info_client = 0x0;
	inline DWORD64 iv_engine_client = 0x0;
	inline DWORD64 iv_engine_trace = 0x0;
	inline DWORD64 inetwork_string_table = 0x0;
	inline DWORD64 cinput = 0x0;
	inline DWORD64 cengine = 0x0;
	inline DWORD64 iswapchain = 0x0;
	inline DWORD64 cl_entitylist = 0x1e54dc8;
	inline DWORD64 local_entity_handle = 0x0;
	inline DWORD64 local_player = 0x750b140;
	inline DWORD64 global_vars = 0x16053c8;
	inline DWORD64 name_list = 0xbe95d60;
	inline DWORD64 view_render = 0x5d2c13;
	inline DWORD64 view_matrix = 0x0;
	inline DWORD64 client_state = 0x16fb080;
	inline DWORD64 sign_on_state = 0x16fb118;
	inline DWORD64 level_name = 0x16fb240;
	inline DWORD64 glow_enable = 0xcc0;
	inline DWORD64 glow_type = 0x2c0;
	inline DWORD64 glow_color = 0x1d0;

	inline  DWORD64 thirdperson_override = 0x01b1c8b0;
	inline  DWORD64 m_thirdPersonShoulderView = 0x36c8; // Int
	inline  DWORD64 cl_phys_timescale = 0x01d19480 + 0x6C; // Default 1.0
	inline  DWORD64 mat_disable_bloom = 0x01d19b60 + 0x6C; // Default 0
	inline  DWORD64 cl_mouseenable = 0x01d10cc0; // Default 1
	inline  DWORD64 host_timescale = 0x0138a640; // Default 1.0
	inline  DWORD64 ss_viewmodelfov = 0x01ec29c0; // 0x01ec29c0
}

namespace Classes
{
	// Inheritance: 

	namespace CRopeKeyframe
	{
		constexpr auto m_localOrigin = 0x4; // Vector
		constexpr auto m_parentAttachment = 0x20; // Integer
		constexpr auto m_clrRender = 0x50; // Integer
		constexpr auto m_visibilityFlags = 0x444; // Integer
		constexpr auto m_hOwnerEntity = 0x4a8; // Integer
		constexpr auto m_nRenderMode = 0x4b9; // Integer
		constexpr auto m_parentAttachmentModel = 0x858; // Integer
		constexpr auto m_fadeDist = 0x864; // Float
		constexpr auto m_ropeZiplineAutoDetachDistance = 0xa60; // Float
		constexpr auto m_ziplineSagEnable = 0xa64; // Integer
		constexpr auto m_ziplineSagHeight = 0xa68; // Float
		constexpr auto m_ziplineMoveSpeedScale = 0xb60; // Float
		constexpr auto m_startOffset = 0xb64; // Vector
		constexpr auto m_endOffset = 0xb70; // Vector
		constexpr auto m_wiggleMaxLen = 0xb84; // Float
		constexpr auto m_wiggleMagnitude = 0xb88; // Float
		constexpr auto m_wiggleSpeed = 0xb8c; // Float
		constexpr auto m_flScrollSpeed = 0xbc4; // Float
		constexpr auto m_RopeFlags = 0xbc8; // Integer
		constexpr auto m_iRopeMaterialModelIndex = 0xbcc; // Integer
		constexpr auto m_nSegments = 0xe50; // Integer
		constexpr auto m_hStartPoint = 0xe54; // Integer
		constexpr auto m_hEndPoint = 0xe58; // Integer
		constexpr auto m_hPrevPoint = 0xe5c; // Integer
		constexpr auto m_iStartAttachment = 0xe60; // Integer
		constexpr auto m_iEndAttachment = 0xe61; // Integer
		constexpr auto m_subdivStackCount = 0xe8c; // Integer
		constexpr auto m_subdivSliceCount = 0xe90; // Integer
		constexpr auto m_ropeLength = 0xe94; // Integer
		constexpr auto m_constraintIterations = 0xe9c; // Integer
		constexpr auto m_ropeDampening = 0xea0; // Float
		constexpr auto m_Slack = 0xea4; // Integer
		constexpr auto m_TextureScale = 0xea8; // Float
		constexpr auto m_fLockedPoints = 0xeac; // Integer
		constexpr auto m_lockDirectionCutoffLength = 0xeb0; // Integer
		constexpr auto m_lockDirectionStrength = 0xeb4; // Float
		constexpr auto m_nChangeCount = 0xeb8; // Integer
		constexpr auto m_Width = 0xebc; // Float
		constexpr auto m_bConstrainBetweenEndpoints = 0xf50; // Integer
	}

	namespace CBaseEntity
	{
		constexpr auto m_parentAttachment = 0x20; // Integer
		constexpr auto m_fEffects = 0x40; // Integer
		constexpr auto m_usableType = 0x44; // Integer
		constexpr auto m_cellX = 0x48; // Integer
		constexpr auto m_cellY = 0x4c; // Integer
		constexpr auto m_cellZ = 0x50; // Integer
		constexpr auto m_clrRender = 0x50; // Integer
		constexpr auto m_localOrigin = 0x54; // Vector
		constexpr auto m_clIntensity = 0x54; // Integer
		constexpr auto m_nModelIndex = 0x60; // Integer
		constexpr auto m_bossPlayer = 0x124; // Integer
		constexpr auto m_shieldHealth = 0x170; // Integer
		constexpr auto m_shieldHealthMax = 0x174; // Integer
		constexpr auto m_wantsScopeHighlight = 0x3ec; // Integer
		constexpr auto m_networkedFlags = 0x3f0; // Integer
		constexpr auto m_visibilityFlags = 0x444; // Integer
		constexpr auto m_iTeamNum = 0x44c; // Integer
		constexpr auto m_teamMemberIndex = 0x454; // Integer
		constexpr auto m_squadID = 0x458; // Integer
		constexpr auto m_grade = 0x45c; // Integer
		constexpr auto m_ignorePredictedTriggerFlags = 0x460; // Integer
		constexpr auto m_passThroughFlags = 0x468; // Integer
		constexpr auto m_passThroughThickness = 0x46c; // Integer
		constexpr auto m_passThroughDirection = 0x470; // Float
		constexpr auto m_bIsSoundCodeControllerValueSet = 0x480; // Integer
		constexpr auto m_flSoundCodeControllerValue = 0x484; // Float
		constexpr auto m_localAngles = 0x494; // Vector
		constexpr auto m_hOwnerEntity = 0x4a8; // Integer
		constexpr auto m_bRenderWithViewModels = 0x4ac; // Integer
		constexpr auto m_nRenderFX = 0x4ad; // Integer
		constexpr auto m_nRenderMode = 0x4b9; // Integer
		constexpr auto m_vecMins = 0x4d0; // Vector
		constexpr auto m_vecMaxs = 0x4dc; // Vector
		constexpr auto m_usSolidFlags = 0x4e8; // Integer
		constexpr auto m_nSolidType = 0x4ec; // Integer
		constexpr auto m_triggerBloat = 0x4ed; // Integer
		constexpr auto m_collisionDetailLevel = 0x4ee; // Integer
		constexpr auto m_nSurroundType = 0x4fc; // Integer
		constexpr auto m_vecSpecifiedSurroundingMins = 0x508; // Vector
		constexpr auto m_vecSpecifiedSurroundingMaxs = 0x514; // Vector
		constexpr auto m_CollisionGroup = 0x540; // Integer
		constexpr auto m_contents = 0x544; // Integer
		constexpr auto m_collideWithOwner = 0x548; // Integer
		constexpr auto m_iSignifierName = 0x580; // String
		constexpr auto m_iName = 0x589; // String
		constexpr auto m_scriptNameIndex = 0x690; // Integer
		constexpr auto m_instanceNameIndex = 0x694; // Integer
		constexpr auto m_holdUsePrompt = 0x718; // String
		constexpr auto m_pressUsePrompt = 0x720; // String
		constexpr auto m_phaseShiftFlags = 0x7b8; // Integer
		constexpr auto m_baseTakeDamage = 0x7bc; // Integer
		constexpr auto m_invulnerableToDamageCount = 0x7c0; // Integer
		constexpr auto m_attachmentLerpStartOrigin = 0x83c; // Vector
		constexpr auto m_attachmentLerpStartAngles = 0x848; // Vector
		constexpr auto m_parentAttachmentModel = 0x858; // Integer
		constexpr auto m_fadeDist = 0x864; // Float
		constexpr auto m_dissolveEffectEntityHandle = 0x914; // Integer
		constexpr auto m_usablePriority = 0x924; // Integer
		constexpr auto m_usableDistanceOverride = 0x928; // Float
		constexpr auto m_usableFOV = 0x92c; // Float
		constexpr auto m_usePromptSize = 0x930; // Float
		constexpr auto m_firstChildEntityLink = 0xa40; // Integer
		constexpr auto m_firstParentEntityLink = 0xa44; // Integer
		constexpr auto m_realmsBitMask = 0xa48; // Integer64
	}
	
	namespace CPropSurvival
		{
			constexpr auto m_parentAttachment = 0x20; // Integer
			constexpr auto m_fEffects = 0x40; // Integer
			constexpr auto m_usableType = 0x44; // Integer
			constexpr auto m_cellX = 0x48; // Integer
			constexpr auto m_cellY = 0x4c; // Integer
			constexpr auto m_cellZ = 0x50; // Integer
			constexpr auto m_localOrigin = 0x54; // Vector
			constexpr auto m_nModelIndex = 0x60; // Integer
			constexpr auto m_networkedFlags = 0x3f0; // Integer
			constexpr auto m_visibilityFlags = 0x444; // Integer
			constexpr auto m_localAngles = 0x494; // Vector
			constexpr auto m_vecMins = 0x4d0; // Vector
			constexpr auto m_vecMaxs = 0x4dc; // Vector
			constexpr auto m_usSolidFlags = 0x4e8; // Integer
			constexpr auto m_nSolidType = 0x4ec; // Integer
			constexpr auto m_triggerBloat = 0x4ed; // Integer
			constexpr auto m_collisionDetailLevel = 0x4ee; // Integer
			constexpr auto m_nSurroundType = 0x4fc; // Integer
			constexpr auto m_vecSpecifiedSurroundingMins = 0x508; // Vector
			constexpr auto m_vecSpecifiedSurroundingMaxs = 0x514; // Vector
			constexpr auto m_CollisionGroup = 0x540; // Integer
			constexpr auto m_iSignifierName = 0x580; // String
			constexpr auto m_parentAttachmentModel = 0x858; // Integer
			constexpr auto m_usablePriority = 0x924; // Integer
			constexpr auto m_usableDistanceOverride = 0x928; // Float
			constexpr auto m_usableFOV = 0x92c; // Float
			constexpr auto m_usePromptSize = 0x930; // Float
			constexpr auto m_realmsBitMask = 0xa48; // Integer64
			constexpr auto m_itemFlavorGUID = 0xe4c; // Integer
			constexpr auto m_nSkin = 0xe54; // Integer
			constexpr auto m_skinMod = 0xe58; // Integer
			constexpr auto m_nBody = 0xe5c; // Integer
			constexpr auto m_camoIndex = 0xe60; // Integer
			constexpr auto m_ammoInClip = 0x1634; // Integer
			constexpr auto m_customScriptInt = 0x1638; // Integer
			constexpr auto m_survivalProperty = 0x163c; // Integer
			constexpr auto m_weaponNameIndex = 0x1644; // Integer
			constexpr auto m_modBitField = 0x1648; // Integer
			constexpr auto m_survivalPropFadeDist = 0x1650; // Float
		}

	namespace CAI_BaseNPC
	{
		constexpr auto m_localOrigin = 0x4; // Vector
		constexpr auto m_hGroundEntity = 0x438; // Integer
		constexpr auto m_iHealth = 0x43c; // Integer
		constexpr auto m_localAngles = 0x494; // Vector
		constexpr auto m_iMaxHealth = 0x578; // Integer
		constexpr auto m_lifeState = 0x798; // Integer
		constexpr auto m_fireteamSlotIndex = 0x1c50; // Integer
		constexpr auto m_aiSprinting = 0x1dba; // Integer
		constexpr auto m_aiNetworkFlags = 0x1ddc; // Integer
		constexpr auto m_isHologram = 0x1de0; // Integer
		constexpr auto m_title = 0x1de1; // String
		constexpr auto m_aiSettingsIndex = 0x1e04; // Integer
		constexpr auto m_subclass = 0x1e08; // Integer
	}

	namespace CPlayer
	{
		constexpr auto m_passives = 0x0; // Array
		constexpr auto m_vecAbsOrigin = 0x4; // Vector
		constexpr auto m_fFlags = 0x98; // Integer
		constexpr auto m_hGroundEntity = 0x438; // Integer
		constexpr auto m_iHealth = 0x43c; // Integer
		constexpr auto m_flMaxspeed = 0x440; // Float
		constexpr auto m_iMaxHealth = 0x578; // Integer
		constexpr auto m_lifeState = 0x798; // Integer
		constexpr auto m_titanSoul = 0x1aa4; // Integer
		constexpr auto m_bZooming = 0x1c51; // Integer
		constexpr auto m_zoomBaseFrac = 0x1c58; // Float
		constexpr auto m_flHullHeight = 0x211c; // Float
		constexpr auto m_angEyeAnglesx = 0x2120; // Float
		constexpr auto m_angEyeAnglesy = 0x2124; // Float
		constexpr auto m_traversalAnimProgress = 0x212c; // Float
		constexpr auto m_sprintTiltFrac = 0x2130; // Float
		constexpr auto m_ziprailBankTiltFrac = 0x2134; // Float
		constexpr auto m_ammoPoolCapacity = 0x25b4; // Integer
		constexpr auto m_hasBadReputation = 0x25b8; // Integer
		constexpr auto m_hardware = 0x25c0; // Integer
		constexpr auto m_progressionHardware = 0x25c1; // Integer
		constexpr auto m_unspoofedHardware = 0x25c2; // Integer
		constexpr auto m_platformUserId = 0x25c8; // Integer64
		constexpr auto m_progressionUserId = 0x25d0; // Integer64
		constexpr auto m_unSpoofedPlatformUserId = 0x25d8; // Integer64
		constexpr auto m_EadpUserId = 0x25e0; // Integer64
		constexpr auto m_crossPlayChat = 0x25e8; // Integer
		constexpr auto m_crossPlayChatFriends = 0x25e9; // Integer
		constexpr auto m_laserSightColorCustomized = 0x25ea; // Integer
		constexpr auto m_laserSightColor = 0x25ec; // Vector
		constexpr auto m_classModsActive = 0x25f8; // Integer64
		constexpr auto m_passives0 = 0x2730; // Integer64
		constexpr auto m_bleedoutState = 0x2750; // Integer
		constexpr auto m_bleedoutStartTime = 0x2754; // Float
		constexpr auto m_damageComboStartHealth = 0x2900; // Integer
		constexpr auto m_gestureAutoKillBitfield = 0x29b4; // Integer
		constexpr auto m_autoSprintForced = 0x29f8; // Integer
		constexpr auto m_fIsSprinting = 0x29fc; // Integer
		constexpr auto m_playerSettingForStickySprintForward = 0x2a0a; // Integer
		constexpr auto m_playerVehicleCount = 0x2a40; // Integer
		constexpr auto m_playerVehicleDriven = 0x2a44; // Integer
		constexpr auto m_duckState = 0x2a4c; // Integer
		constexpr auto m_leanState = 0x2a50; // Integer
		constexpr auto m_canStand = 0x2a55; // Integer
		constexpr auto m_StandHullMin = 0x2a58; // Vector
		constexpr auto m_StandHullMax = 0x2a64; // Vector
		constexpr auto m_DuckHullMin = 0x2a70; // Vector
		constexpr auto m_DuckHullMax = 0x2a7c; // Vector
		constexpr auto m_entitySyncingWithMe = 0x2a88; // Integer
		constexpr auto m_upDir = 0x2a8c; // Vector
		constexpr auto m_traversalState = 0x2b14; // Integer
		constexpr auto m_traversalType = 0x2b18; // Integer
		constexpr auto m_traversalForwardDir = 0x2b44; // Vector
		constexpr auto m_traversalRefPos = 0x2b50; // Vector
		constexpr auto m_traversalYawDelta = 0x2b7c; // Float
		constexpr auto m_traversalYawPoseParameter = 0x2b80; // Integer
		constexpr auto m_wallClimbSetUp = 0x2b98; // Integer
		constexpr auto m_wallHanging = 0x2b99; // Integer
		constexpr auto m_grapplePoints = 0x2ca8; // Array
		constexpr auto m_grappleVel = 0x2cb0; // Vector
		constexpr auto m_grapplePoints0 = 0x2cbc; // Vector
		constexpr auto m_grapplePointCount = 0x2cec; // Integer
		constexpr auto m_grappleAttached = 0x2cf0; // Integer
		constexpr auto m_grapplePulling = 0x2cf1; // Integer
		constexpr auto m_grappleSwinging = 0x2cf2; // Integer
		constexpr auto m_grappleRetracting = 0x2cf3; // Integer
		constexpr auto m_grappleForcedRetracting = 0x2cf4; // Integer
		constexpr auto m_grappleGracePeriodFinished = 0x2cf5; // Integer
		constexpr auto m_grappleUsedPower = 0x2cf8; // Float
		constexpr auto m_grappleMeleeTarget = 0x2d0c; // Integer
		constexpr auto m_grappleAutoAimTarget = 0x2d10; // Integer
		constexpr auto m_grappleHasGoodVelocity = 0x2d14; // Integer
		constexpr auto m_grappleSwingDetachLowSpeed = 0x2d1c; // Float
		constexpr auto m_grappleActive = 0x2d38; // Integer
		constexpr auto m_turret = 0x2d7c; // Integer
		constexpr auto m_activeZipline = 0x2ec0; // Integer
		constexpr auto m_ziplineValid3pWeaponLayerAnim = 0x2ecc; // Integer
		constexpr auto m_ziplineState = 0x2ed0; // Integer
		constexpr auto m_ziplineGrenadeBeginStationEntity = 0x2f6c; // Integer
		constexpr auto m_ziplineGrenadeBeginStationAttachmentId = 0x2f70; // Integer
		constexpr auto m_isPerformingBoostAction = 0x2fad; // Integer
		constexpr auto m_lastJumpPadTouched = 0x30a8; // Integer
		constexpr auto m_launchCount = 0x30b0; // Integer
		constexpr auto m_useCredit = 0x3218; // Integer
		constexpr auto m_playerFlags = 0x3228; // Integer
		constexpr auto m_hasMic = 0x3230; // Integer
		constexpr auto m_inPartyChat = 0x3231; // Integer
		constexpr auto m_communicationsAutoBlocked = 0x3232; // Integer
		constexpr auto m_playerMoveSpeedScale = 0x3234; // Float
		constexpr auto m_bShouldDrawPlayerWhileUsingViewEntity = 0x3480; // Integer
		constexpr auto m_iSpawnParity = 0x34ec; // Integer
		constexpr auto m_grappleHook = 0x3698; // Integer
		constexpr auto m_petTitan = 0x369c; // Integer
		constexpr auto m_xp = 0x36c4; // Integer
		constexpr auto m_skill_mu = 0x36cc; // Float
		constexpr auto m_bHasMatchAdminRole = 0x36d0; // Integer
		constexpr auto m_ubEFNoInterpParity = 0x4010; // Integer
		constexpr auto m_hColorCorrectionCtrl = 0x4014; // Integer
		constexpr auto m_title = 0x4038; // String
		constexpr auto m_nPlayerCond = 0x4370; // Integer
		constexpr auto m_pilotClassIndex = 0x43bc; // Integer
		constexpr auto m_playerScriptNetDataGlobal = 0x4648; // Integer
		constexpr auto m_helmetType = 0x4650; // Integer
		constexpr auto m_armorType = 0x4654; // Integer
		constexpr auto m_controllerModeActive = 0x465c; // Integer
		constexpr auto m_skydiveForwardPoseValueTarget = 0x4678; // Float
		constexpr auto m_skydiveSidePoseValueTarget = 0x4684; // Float
		constexpr auto m_skydiveState = 0x46ac; // Integer
		constexpr auto m_skydiveDiveAngle = 0x46c4; // Float
		constexpr auto m_skydiveIsDiving = 0x46c8; // Integer
		constexpr auto m_skydiveSpeed = 0x46cc; // Float
		constexpr auto m_skydiveStrafeAngle = 0x46d0; // Float
		constexpr auto m_skydivePlayerPitch = 0x46e4; // Float
		constexpr auto m_skydivePlayerYaw = 0x46e8; // Float
		constexpr auto m_skydiveFromSkywardLaunch = 0x4725; // Integer
		constexpr auto m_skywardLaunchState = 0x4728; // Integer
		constexpr auto m_skywardLaunchSlowStartTime = 0x473c; // Float
		constexpr auto m_skywardLaunchSlowEndTime = 0x4740; // Float
		constexpr auto m_skywardLaunchFastEndTime = 0x4744; // Float
		constexpr auto m_skywardLaunchEndTime = 0x474c; // Float
		constexpr auto m_skywardLaunchSlowSpeed = 0x4754; // Float
		constexpr auto m_skywardLaunchFastSpeed = 0x4758; // Float
		constexpr auto m_skywardOffset = 0x475c; // Vector
		constexpr auto m_skywardLaunchInterrupted = 0x476c; // Integer
		constexpr auto m_skywardLaunchFollowing = 0x476d; // Integer
		constexpr auto m_skywardObstacleAvoidanceEndPos = 0x4770; // Vector
		constexpr auto m_armoredLeapAirPos = 0x4780; // Vector
		constexpr auto m_armoredLeapEndPos = 0x478c; // Vector
		constexpr auto m_armoredLeapType = 0x4798; // Integer
		constexpr auto m_armoredLeapPhase = 0x479c; // Integer
		constexpr auto m_dragReviveState = 0x4810; // Integer
		constexpr auto m_dragReviveOutroStartTime = 0x4814; // Float
		constexpr auto m_reviveTarget = 0x4818; // Integer

		constexpr auto m_view_angles = m_ammoPoolCapacity - 0x14;
		constexpr auto m_breath_angles = m_view_angles - 0x10;
		constexpr auto m_vecPunchWeapon_Angle = 0x0040;
		constexpr auto m_iObserverMode = 0x34d4;
		constexpr auto m_hObserverTarget = 0x34e0;

	}

	namespace CPointCamera
	{
		constexpr auto m_FOV = 0xac0; // Float
		constexpr auto m_bFogEnable = 0xae8; // Integer
		constexpr auto m_bActive = 0xae9; // Integer
	}

	namespace CTeam
	{
		constexpr auto m_score = 0xa60; // Integer
		constexpr auto m_score2 = 0xa64; // Integer
		constexpr auto m_kills = 0xa68; // Integer
		constexpr auto m_deaths = 0xa6c; // Integer
		constexpr auto m_iRoundsWon = 0xa70; // Integer
		constexpr auto m_iTeamTeamNum = 0xa74; // Integer
		constexpr auto m_szTeamname = 0xa98; // String
	}

	namespace CWorld
	{
		constexpr auto m_WorldMins = 0xa60; // Vector
		constexpr auto m_WorldMaxs = 0xa6c; // Vector
		constexpr auto m_bStartDark = 0xa78; // Integer
		constexpr auto m_statusEffectsGenerationNV = 0xa8c; // Integer
		constexpr auto m_worldFlags = 0xa94; // Integer
		constexpr auto m_timeshiftArmDeviceSkin = 0xa98; // Integer
		constexpr auto m_spTitanLoadoutUnlocks = 0xa9c; // Integer
		constexpr auto m_teamRelationRulesForPVE = 0x11e0; // Integer
	}

	namespace CWeaponX
	{
		constexpr auto m_networkedFlags = 0x3f0; // Integer
		constexpr auto m_bClientSideAnimation = 0x1006; // Integer
		constexpr auto m_weaponOwner = 0x1630; // Integer
		constexpr auto m_worldModelIndexOverride = 0x1644; // Integer
		constexpr auto m_iWorldModelIndex = 0x1648; // Integer
		constexpr auto m_holsterModelIndex = 0x164c; // Integer
		constexpr auto m_droppedModelIndex = 0x1650; // Integer
		constexpr auto m_idealSequence = 0x1654; // Integer
		constexpr auto m_idealActivity = 0x1656; // Integer
		constexpr auto m_weaponActivity = 0x1658; // Integer
		constexpr auto m_ActiveState = 0x165c; // Integer
		constexpr auto m_weapState = 0x1670; // Integer
		constexpr auto m_allowedToUse = 0x1674; // Integer
		constexpr auto m_discarded = 0x1675; // Integer
		constexpr auto m_forcedADS = 0x1678; // Integer
		constexpr auto m_tossRelease = 0x167c; // Integer
		constexpr auto m_offhandSwitchSlot = 0x1680; // Integer
		constexpr auto m_energizeState = 0x1684; // Integer
		constexpr auto m_heatValue = 0x1690; // Float
		constexpr auto m_heatValueOnLastFire = 0x1694; // Float
		constexpr auto m_fullyHeated = 0x1698; // Integer
		constexpr auto m_customActivity = 0x169a; // Integer
		constexpr auto m_customActivitySequence = 0x169c; // Integer
		constexpr auto m_customActivityOwner = 0x16a0; // Integer
		constexpr auto m_customActivityFlags = 0x16a8; // Integer
		constexpr auto m_moveSpread = 0x16b8; // Float
		constexpr auto m_spreadStartFracHip = 0x16c0; // Float
		constexpr auto m_spreadStartFracADS = 0x16c4; // Float
		constexpr auto m_kickSpreadHipfire = 0x16c8; // Float
		constexpr auto m_kickSpreadADS = 0x16cc; // Float
		constexpr auto m_kickScaleBasePitch = 0x16d4; // Float
		constexpr auto m_kickScaleBaseYaw = 0x16d8; // Float
		constexpr auto m_kickPatternScaleBase = 0x16dc; // Float
		constexpr auto m_kickSpringHeatBaseValue = 0x16e4; // Float
		constexpr auto m_semiAutoTriggerDown = 0x16ec; // Integer
		constexpr auto m_pendingTriggerPull = 0x16ed; // Integer
		constexpr auto m_semiAutoNeedsRechamber = 0x16ee; // Integer
		constexpr auto m_pendingReloadAttempt = 0x16ef; // Integer
		constexpr auto m_offhandHybridNormalMode = 0x16f0; // Integer
		constexpr auto m_pendingoffhandHybridToss = 0x16f1; // Integer
		constexpr auto m_fastHolster = 0x16f2; // Integer
		constexpr auto m_didFirstDeploy = 0x16f3; // Integer
		constexpr auto m_shouldCatch = 0x16f4; // Integer
		constexpr auto m_clipModelIsHidden = 0x16f5; // Integer
		constexpr auto m_segmentedReloadEndSeqRequired = 0x16f6; // Integer
		constexpr auto m_reloadStartedEmpty = 0x16f7; // Integer
		constexpr auto m_segmentedAnimStartedOneHanded = 0x16f8; // Integer
		constexpr auto m_segmentedReloadCanRestartLoop = 0x16f9; // Integer
		constexpr auto m_segmentedReloadLoopFireLocked = 0x16fa; // Integer
		constexpr auto m_realtimeModCmdHead = 0x1703; // Integer
		constexpr auto m_realtimeModCmdCount = 0x1704; // Integer
		constexpr auto m_realtimeModCanADS = 0x1705; // Integer
		constexpr auto m_customActivityAttachedModelIndex = 0x1708; // Integer
		constexpr auto m_customActivityAttachedModelAttachmentId = 0x170c; // Integer
		constexpr auto m_fireRateLerp_startFraction = 0x1714; // Float
		constexpr auto m_fireRateLerp_stopFraction = 0x171c; // Float
		constexpr auto m_chargeAnimIndex = 0x1720; // Integer
		constexpr auto m_chargeAnimIndexOld = 0x1724; // Integer
		constexpr auto m_proScreen_owner = 0x1728; // Integer
		constexpr auto m_proScreen_int0 = 0x172c; // Integer
		constexpr auto m_proScreen_int1 = 0x1730; // Integer
		constexpr auto m_proScreen_int2 = 0x1734; // Integer
		constexpr auto m_proScreen_float0 = 0x1738; // Float
		constexpr auto m_proScreen_float1 = 0x173c; // Float
		constexpr auto m_proScreen_float2 = 0x1740; // Float
		constexpr auto m_reloadMilestone = 0x1744; // Integer
		constexpr auto m_rechamberMilestone = 0x1748; // Integer
		constexpr auto m_cooldownMilestone = 0x174c; // Integer
		constexpr auto m_prevSeqWeight = 0x1750; // Integer
		constexpr auto m_scriptFlags0 = 0x1760; // Integer
		constexpr auto m_scriptInt0 = 0x1764; // Integer
		constexpr auto m_scriptInt1 = 0x1766; // Integer
		constexpr auto m_curZoomFOV = 0x1768; // Float
		constexpr auto m_targetZoomFOV = 0x176c; // Float
		constexpr auto m_zoomFOVLerpTime = 0x1770; // Float
		constexpr auto m_currentAltFireAnimIndex = 0x1780; // Integer
		constexpr auto m_legendaryModelIndex = 0x1784; // Integer
		constexpr auto m_charmModelIndex = 0x1788; // Integer
		constexpr auto m_charmAttachment = 0x178c; // Integer
		constexpr auto m_charmItemFlavorGUID = 0x1790; // Integer
		constexpr auto m_lastTossedGrenade = 0x1798; // Integer
		constexpr auto m_targetingLaserEnabledScript = 0x179c; // Integer
		constexpr auto m_needsReloadCheck = 0x179d; // Integer
		constexpr auto m_needsEmptyCycleCheck = 0x179e; // Integer
		constexpr auto m_skinOverride = 0x17a0; // Integer
		constexpr auto m_skinOverrideIsValid = 0x17a4; // Integer
		constexpr auto m_lastChargeFrac = 0x17b0; // Float
		constexpr auto m_sustainedLaserCurrentSpread = 0x17dc; // Float
		constexpr auto m_sustainedDischargeIsInPrimaryAttack = 0x17e0; // Integer
		constexpr auto m_sustainedLaserNextRandomSeed = 0x17e1; // Integer
		constexpr auto m_modBitfieldFromPlayer = 0x17e4; // Integer
		constexpr auto m_modBitfieldInternal = 0x17e8; // Integer
		constexpr auto m_modBitfieldCurrent = 0x17ec; // Integer
		constexpr auto m_curSharedEnergyCost = 0x17f0; // Integer
		constexpr auto m_grappleWeaponNeedsDryfire = 0x17f4; // Integer
		constexpr auto m_scriptFloat0 = 0x17f8; // Float
		constexpr auto m_scriptVectorTransitionDuration = 0x17fc; // Float
		constexpr auto m_scriptVectorTransitionStartTime = 0x1800; // Float
		constexpr auto m_scriptVectorTransitionStart = 0x1804; // Vector
		constexpr auto m_scriptVectorTransitionEnd = 0x1810; // Vector
		constexpr auto m_scriptVector = 0x181c; // Vector
		constexpr auto m_shouldPlayIdleAnims = 0x1828; // Integer
		constexpr auto m_scriptActivated = 0x1829; // Integer
		constexpr auto m_curReactiveSkinKillCount = 0x182a; // Integer
		constexpr auto m_curReactiveSkinKnockdownCount = 0x182b; // Integer
		constexpr auto m_lockedSet = 0x1848; // Integer
		constexpr auto m_isLoadoutPickup = 0x184c; // Integer
		constexpr auto m_utilityEnt = 0x1850; // Integer
		constexpr auto m_weaponNameIndex = 0x1858; // Integer
		constexpr auto m_oaActiveOverride = 0x1864; // Integer
		constexpr auto m_parentTurret = 0x1868; // Integer
	}

	namespace CBaseViewModel
	{
		constexpr auto m_animStartCycle = 0xc; // Float
		constexpr auto m_animPlaybackRate = 0x10; // Float
		constexpr auto m_animModelIndex = 0x14; // Integer
		constexpr auto m_nNewSequenceParity = 0x18; // Integer
		constexpr auto m_animSequence = 0x20; // Integer
		constexpr auto m_animFrozen = 0x22; // Integer
		constexpr auto m_fEffects = 0x40; // Integer
		constexpr auto m_clrRender = 0x50; // Integer
		constexpr auto m_nModelIndex = 0x60; // Integer
		constexpr auto m_nRenderMode = 0x4b9; // Integer
		constexpr auto m_nBody = 0xe5c; // Integer
		constexpr auto m_nResetEventsParity = 0xe6c; // Integer
		constexpr auto m_bSequenceFinished = 0xefc; // Integer
		constexpr auto m_flModelScale = 0xf08; // Float
		constexpr auto m_viewModelOwner = 0x19c4; // Integer
		constexpr auto m_projectileIsVisible = 0x19c8; // Integer
		constexpr auto m_bBlockEventLayer = 0x1dc0; // Integer
		constexpr auto m_isAdsTransition = 0x1dc1; // Integer
		constexpr auto m_hWeapon = 0x1dc4; // Integer
	}
}