#pragma once

#include "color.h"

#define default_tick_interval (0.015)
#define minimum_tick_interval (0.001)
#define maximum_tick_interval (0.1)
#define absolute_player_limit 255
#define absolute_player_limit_dw ((absolute_player_limit/32) + 1)
#define max_player_name_length 128
#define max_players_per_client 1
#define max_map_name 96
#define max_map_name_save 32
#define max_display_map_name 32
#define	max_networked_length 64
#define sp_model_index_bits 13
#define	max_edict_bits 11
#define	max_edicts (1<<max_edict_bits)
#define max_server_class_bits 9
#define max_server_classes (1<<max_server_class_bits)
#define signed_guid_len 32
#define num_ententry_bits (max_edict_bits + 1)
#define num_ent_entries (1 << num_ententry_bits)
#define ent_entry_mask (num_ent_entries - 1)
#define invalid_ehandle_index 0xFFFFFFFF
#define num_serial_num_bits (32 - num_ententry_bits)
#define num_networked_ehandle_serial_number_bits 10
#define num_networked_ehandle_bits (max_edict_bits + num_networked_ehandle_serial_number_bits)
#define invalid_networked_ehandle_value ((1 << num_networked_ehandle_bits) - 1)
#define max_packedentity_data (16384)
#define max_packedentity_props (4096)
#define max_custom_files 4
#define max_custom_file_size 524288

#define wl_feet 1

#define	fl_onground		(1 << 0)
#define fl_ducking		(1 << 1)
#define	fl_waterjump	(1 << 2)
#define fl_ontrain		(1 << 3)
#define fl_intrain		(1 << 4)
#define fl_frozen		(1 << 5)
#define fl_atcontrols	(1 << 6)
#define	fl_client		(1 << 7)
#define fl_fakeclient	(1 << 8)
#define	fl_inwater		(1 << 9)

#define in_attack       (1 << 0)
#define in_jump         (1 << 1)
#define in_moveleft     (1 << 9)
#define in_moveright    (1 << 10)
#define in_forward      (1 << 3)
#define in_back         (1 << 4)

#define color_red		color(255, 64, 64)
#define color_blue		color(153, 204, 255)
#define color_yellow	color(255, 178, 0)
#define color_green		color(153, 255, 153)
#define color_grey		color(204, 204, 204)
#define color_white		color(255, 255, 255)
#define color_black		color(0, 0, 0)

#define	hitgroup_generic	0
#define	hitgroup_head		1
#define	hitgroup_chest		2
#define	hitgroup_stomach	3
#define hitgroup_leftarm	4	
#define hitgroup_rightarm	5
#define hitgroup_leftleg	6
#define hitgroup_rightleg	7
#define hitgroup_gear		10

#define	life_alive 0
#define	life_dying 1
#define	lide_dead 2
#define life_respawnable 3
#define life_discardbody 4

#define EF_PARITY_BITS 3
#define EF_PARITY_MASK ((1<<EF_PARITY_BITS)-1)
#define EF_MUZZLEFLASH_BITS 2
#define	PLAT_LOW_TRIGGER 1
#define	SF_TRAIN_WAIT_RETRIGGER	1
#define SF_TRAIN_PASSABLE 8
#define FIXANGLE_NONE 0
#define FIXANGLE_ABSOLUTE 1
#define FIXANGLE_RELATIVE 2
#define BREAK_GLASS 0x01
#define BREAK_METAL 0x02
#define BREAK_FLESH 0x04
#define BREAK_WOOD 0x08
#define BREAK_SMOKE 0x10
#define BREAK_TRANS 0x20
#define BREAK_CONCRETE 0x40
#define BREAK_SLAVE 0x80
#define BOUNCE_GLASS BREAK_GLASS
#define	BOUNCE_METAL BREAK_METAL
#define BOUNCE_FLESH BREAK_FLESH
#define BOUNCE_WOOD	 BREAK_WOOD
#define BOUNCE_SHRAP 0x10
#define BOUNCE_SHELL 0x20
#define	BOUNCE_CONCRETE BREAK_CONCRETE
#define BOUNCE_SHOTSHELL 0x80
#define TE_BOUNCE_NULL 0
#define TE_BOUNCE_SHELL 1
#define TE_BOUNCE_SHOTSHELL	2

#define SOUND_NORMAL_CLIP_DIST	1000.0f
#define MAX_AREA_STATE_BYTES 32
#define MAX_AREA_PORTAL_STATE_BYTES 24
#define MAX_USER_MSG_DATA 255
#define MAX_ENTITY_MSG_DATA 255

#define STUDIO_NONE 0x00000000
#define STUDIO_RENDER 0x00000001
#define STUDIO_VIEWXFORMATTACHMENTS 0x00000002
#define STUDIO_DRAWTRANSLUCENTSUBMODELS 0x00000004
#define STUDIO_TWOPASS 0x00000008
#define STUDIO_STATIC_LIGHTING 0x00000010
#define STUDIO_WIREFRAME 0x00000020
#define STUDIO_ITEM_BLINK 0x00000040
#define STUDIO_NOSHADOWS 0x00000080
#define STUDIO_WIREFRAME_VCOLLIDE 0x00000100
#define STUDIO_NO_OVERRIDE_FOR_ATTACH 0x00000200
#define STUDIO_GENERATE_STATS 0x01000000
#define STUDIO_SSAODEPTHTEXTURE 0x08000000
#define STUDIO_SHADOWDEPTHTEXTURE 0x40000000
#define STUDIO_TRANSPARENCY 0x80000000

enum solid_type_t {
	solid_none = 0,
	solid_bsp = 1,
	solid_bbox = 2,
	solid_obb = 3,
	solid_obb_yaw = 4,
	solid_custom = 5,
	solid_vphysics = 6,
	solid_last
};

enum SolidFlags_t {
	FSOLID_CUSTOMRAYTEST = 0x0001,
	FSOLID_CUSTOMBOXTEST = 0x0002,
	FSOLID_NOT_SOLID = 0x0004,
	FSOLID_TRIGGER = 0x0008,
	FSOLID_NOT_STANDABLE = 0x0010,
	FSOLID_VOLUME_CONTENTS = 0x0020,
	FSOLID_FORCE_WORLD_ALIGNED = 0x0040,
	FSOLID_USE_TRIGGER_BOUNDS = 0x0080,
	FSOLID_ROOT_PARENT_ALIGNED = 0x0100,
	FSOLID_TRIGGER_TOUCH_DEBRIS = 0x0200,
	FSOLID_MAX_BITS = 10
};

enum {
	EF_BONEMERGE = 0x001,
	EF_BRIGHTLIGHT = 0x002,
	EF_DIMLIGHT = 0x004,
	EF_NOINTERP = 0x008,
	EF_NOSHADOW = 0x010,
	EF_NODRAW = 0x020,
	EF_NORECEIVESHADOW = 0x040,
	EF_BONEMERGE_FASTCULL = 0x080,
	EF_ITEM_BLINK = 0x100,
	EF_PARENT_ANIMATES = 0x200,
	EF_MAX_BITS = 10
};

enum RenderMode_t {
	kRenderNormal = 0,
	kRenderTransColor,
	kRenderTransTexture,
	kRenderGlow,
	kRenderTransAlpha,
	kRenderTransAdd,
	kRenderEnvironmental,
	kRenderTransAddFrameBlend,
	kRenderTransAlphaAdd,
	kRenderWorldGlow,
	kRenderNone,
	kRenderModeCount
};

enum RenderFx_t {
	kRenderFxNone = 0,
	kRenderFxPulseSlow,
	kRenderFxPulseFast,
	kRenderFxPulseSlowWide,
	kRenderFxPulseFastWide,
	kRenderFxFadeSlow,
	kRenderFxFadeFast,
	kRenderFxSolidSlow,
	kRenderFxSolidFast,
	kRenderFxStrobeSlow,
	kRenderFxStrobeFast,
	kRenderFxStrobeFaster,
	kRenderFxFlickerSlow,
	kRenderFxFlickerFast,
	kRenderFxNoDissipation,
	kRenderFxDistort,
	kRenderFxHologram,
	kRenderFxExplode,
	kRenderFxGlowShell,
	kRenderFxClampMinScale,
	kRenderFxEnvRain,
	kRenderFxEnvSnow,
	kRenderFxSpotlight,
	kRenderFxRagdoll,
	kRenderFxPulseFastWider,
	kRenderFxMax
};

enum Collision_Group_t {
	COLLISION_GROUP_NONE = 0,
	COLLISION_GROUP_DEBRIS,
	COLLISION_GROUP_DEBRIS_TRIGGER,
	COLLISION_GROUP_INTERACTIVE_DEBRIS,
	COLLISION_GROUP_INTERACTIVE,
	COLLISION_GROUP_PLAYER,
	COLLISION_GROUP_BREAKABLE_GLASS,
	COLLISION_GROUP_VEHICLE,
	COLLISION_GROUP_PLAYER_MOVEMENT,
	COLLISION_GROUP_NPC,
	COLLISION_GROUP_IN_VEHICLE,
	COLLISION_GROUP_WEAPON,
	COLLISION_GROUP_VEHICLE_CLIP,
	COLLISION_GROUP_PROJECTILE,
	COLLISION_GROUP_DOOR_BLOCKER,
	COLLISION_GROUP_PASSABLE_DOOR,
	COLLISION_GROUP_DISSOLVING,
	COLLISION_GROUP_PUSHAWAY,
	COLLISION_GROUP_NPC_ACTOR,
	COLLISION_GROUP_NPC_SCRIPTED,
	LAST_SHARED_COLLISION_GROUP
};

enum hitboxes_t {
	hitbox_pelvis = 0,
	hitbox_stomach = 7,
	hitbox_chest = 8,
	hitbox_neck,
	hitbox_head,
	hitbox_max = 16
};

//17.7.2022
enum client_class_t
{
	ctesttraceline = 195,
	cteworlddecal = 198,
	ctespritespray = 193,
	ctesprite = 192,
	ctesparks = 191,
	ctesmoke = 190,
	cteshowline = 188,
	cteprojecteddecal = 185,
	cteplayerdecal = 184,
	ctephysicsprop = 182,
	cteparticlesystem = 181,
	ctemuzzleflash = 180,
	ctelargefunnel = 178,
	ctekillplayerattachments = 177,
	cteimpact = 176,
	cteglowsprite = 175,
	cteshattersurface = 187,
	ctefootprintdecal = 172,
	ctefizz = 170,
	cteexplosion = 168,
	cteenergysplash = 167,
	cteeffectdispatch = 166,
	ctedynamiclight = 165,
	ctedecal = 163,
	cteclientprojectile = 160,
	ctebubbletrail = 159,
	ctebubbles = 158,
	ctebspdecal = 157,
	ctebreakmodel = 156,
	ctebloodstream = 155,
	ctebloodsprite = 154,
	ctebeamspline = 152,
	ctebeamringpoint = 151,
	ctebeamring = 150,
	ctebeampoints = 149,
	ctebeamlaser = 148,
	ctebeamfollow = 147,
	ctebeaments = 146,
	ctebeamentpoint = 145,
	ctebasebeam = 144,
	ctearmorricochet = 142,
	ctemetalsparks = 179,
	csteamjet = 136,
	csmokestack = 129,
	dusttrail = 254,
	cfiretrail = 70,
	sporetrail = 264,
	sporeexplosion = 263,
	rockettrail = 261,
	smoketrail = 262,
	cpropvehicledriveable = 120,
	particlesmokegrenade = 259,
	cparticlefire = 101,
	movieexplosion = 257,
	ctegaussexplosion = 174,
	cenvquadraticbeam = 64,
	cembers = 54,
	cenvwind = 68,
	cprecipitation = 115,
	cprecipitationblocker = 116,
	cbasetempentity = 21,
	nextbotcombatcharacter = 258,
	cweapontrigger = 250,
	cweapontrex = 249,
	cweapontrenchknife = 248,
	cweapontokarev = 247,
	cweaponthompson = 246,
	cweapontesla = 245,
	ctankmineprojectile = 139,
	cweapontankmine = 244,
	cweaponstyracosaur = 243,
	cweaponstygimoloch = 242,
	cweaponsticky = 241,
	cweaponstickgrenade = 240,
	cweaponsten = 239,
	cweaponsniper = 238,
	cweaponsmokegrenade = 237,
	cweaponshotgun = 236,
	csatchelprojectile = 125,
	cweaponsatchel = 235,
	cweaponredbaron = 234,
	cweaponproximitymine = 233,
	cweaponpistol = 232,
	cweaponpiat = 231,
	cweaponp38 = 230,
	cweaponnagant = 229,
	cweaponmp44 = 228,
	cweaponmp40 = 227,
	cweaponmosin = 226,
	cweaponmicroraptor = 225,
	cweaponmg42 = 224,
	cweaponluger = 223,
	cweaponkabar = 222,
	cweaponk98sniper = 221,
	cweaponk98 = 220,
	cweaponjackrabbit = 219,
	cweaponhealthkit = 218,
	cweapongrenade = 217,
	cweapongreasegun = 216,
	cweapongarand = 215,
	cweaponflechette = 214,
	cdddflamethrower = 39,
	cweaponflak30 = 213,
	cweaponfistsregular = 212,
	cweaponfists = 211,
	cweapondilophosaurus = 210,
	cddddesmaflame = 38,
	cweapondddbase = 208,
	cweaponcompy = 207,
	cweaponclaws = 206,
	cweaponcarbine = 205,
	cdddbaserocket = 37,
	cbasedddgrenade = 9,
	cweaponbar = 204,
	cweaponammorecharge = 203,
	cweapondddmelee = 209,
	cbasesmokegrenadeprojectile = 20,
	cbasejackrabbitprojectile = 16,
	cbasehealthkitprojectile = 15,
	cbasegrenadeprojectile = 14,
	cbaseammorechargeprojectile = 3,
	cdddprojectile_redbaronrocket = 44,
	cdddprojectile_rocket = 45,
	cdddgamerulesproxy = 40,
	cdddteam_red = 49,
	cdddteam_blue = 48,
	cdddteam_unassigned = 50,
	cdddteam = 47,
	cdddplayerresource = 42,
	cdddragdoll = 46,
	cdddplayer = 41,
	cteplayeranimevent = 183,
	genericgerman = 0,
	genericdinosaur = 255,
	styracbot = 266,
	trexbot = 267,
	microbot = 256,
	dilobot = 253,
	desmabot = 252,
	axisbot = 1,
	alliesbot = 0,
	compybot = 100,
	stygibot = 265,
	raptorbot = 260,
	citemgold = 93,
	cfuncsimpleladder = 84,
	cdddviewmodel = 51,
	cdddprojectile_dart = 43,
	cdddbaseprojectile = 36,
	cweaponcubemap = 0,
	cweaponcycler = 0,
	ctefirebullets = 169,
	cobjectiveprop = 99,
	cctfgoalprop = 34,
	citemgoldcrate = 94,
	cmortarshell = 97,
	cfuncteamclip = 86,
	cddd_game_stats = 35,
	cgamedirector = 88,
	cteteslablast = 197,
	cte_pathhelper = 140,
	ctebigblast = 153,
	ctecompyexplosion = 161,
	ctestyracgunexplosion = 196,
	ctepterosaurexplosion = 186,
	cteflak30explosion = 171,
	cteartilleryexplosion = 143,
	ctedddexplosion = 162,
	ccontrolpoint = 33,
	chandletest = 90,
	cteamplayroundbasedrulesproxy = 0,
	cspritetrail = 134,
	cspriteoriented = 133,
	csprite = 132,
	cragdollpropattached = 123,
	cragdollprop = 122,
	cpredictedviewmodel = 117,
	cposecontroller = 113,
	cgamerulesproxy = 89,
	cinfoladderdismount = 91,
	cfuncladder = 78,
	ctefoundryhelpers = 173,
	cenvdetailcontroller = 60,
	cworld = 251,
	cwaterlodcontrol = 202,
	cwaterbullet = 201,
	cvguiscreen = 200,
	cpropjeep = 0,
	cpropvehiclechoreogeneric = 0,
	cbasevphysicstrigger = 25,
	ctriggerplayermovement = 199,
	cbasetrigger = 23,
	ctest_proxytoggle_networkable = 194,
	ctesla = 189,
	cteam = 141,
	csunlightshadowcontrol = 138,
	csun = 137,
	cparticleperformancemonitor = 102,
	cspotlightend = 131,
	cspatialentity = 130,
	cslideshowdisplay = 128,
	cshadowcontrol = 127,
	csceneentity = 126,
	cropekeyframe = 124,
	cragdollmanager = 121,
	cphysicspropmultiplayer = 107,
	cphysboxmultiplayer = 105,
	cpropdoorrotating = 119,
	cbasepropdoor = 19,
	cdynamicprop = 53,
	cprop_hallucination = 118,
	cpostprocesscontroller = 114,
	cpointcommentarynode = 112,
	cpointcamera = 111,
	cplayerresource = 110,
	cplasma = 109,
	cphysmagnet = 108,
	cphysicsprop = 106,
	cstatueprop = 135,
	cphysbox = 104,
	cparticlesystem = 103,
	cmoviedisplay = 98,
	cmaterialmodifycontrol = 96,
	clightglow = 95,
	cinfooverlayaccessor = 92,
	cfunctracktrain = 87,
	cfuncsmokevolume = 85,
	cfuncrotating = 83,
	cfuncreflectiveglass = 82,
	cfuncoccluder = 81,
	cfuncmovelinear = 80,
	cfuncmonitor = 79,
	cfunc_lod = 74,
	ctedust = 164,
	cfunc_dust = 73,
	cfuncconveyor = 77,
	cfuncbrush = 76,
	cbreakablesurface = 30,
	cfuncareaportalwindow = 75,
	cfish = 71,
	cfiresmoke = 69,
	cenvtonemapcontroller = 67,
	cenvscreeneffect = 65,
	cenvscreenoverlay = 66,
	cenvprojectedtexture = 63,
	cenvparticlescript = 62,
	cfogcontroller = 72,
	cenvdofcontroller = 61,
	cenvambientlight = 59,
	centityparticletrail = 58,
	centityfreezing = 57,
	centityflame = 56,
	centitydissolve = 55,
	cdynamiclight = 52,
	ccolorcorrectionvolume = 32,
	ccolorcorrection = 31,
	cbreakableprop = 29,
	cbeamspotlight = 27,
	cbasebutton = 6,
	cbasetoggle = 22,
	cbaseplayer = 18,
	cbaseflex = 12,
	cbaseentity = 11,
	cbasedoor = 10,
	cbasecombatcharacter = 7,
	cbaseanimatingoverlay = 5,
	cbonefollower = 28,
	cbaseanimating = 4,
	cai_basenpc = 2,
	cbeam = 26,
	cbaseviewmodel = 24,
	cbaseparticleentity = 17,
	cbasegrenade = 13,
	cbasecombatweapon = 8
};

template<typename t>
__inline t dword_swap_asm(t dw) {
	__asm {
		mov eax, dw
		bswap eax
	}
}