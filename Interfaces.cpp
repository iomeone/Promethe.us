#include "Interfaces.h"
#include "Utilities.h"

void InitialiseInterfaces()
{

	auto EnginePointer = get_module_factory(GetModuleHandleW(L"engine.dll"));
	auto ClientPointer = get_module_factory(GetModuleHandleW(L"client.dll"));
	auto VGUISurfacePointer = get_module_factory(GetModuleHandleW(L"vguimatsurface.dll"));
	auto VGUI2Pointer = get_module_factory(GetModuleHandleW(L"vgui2.dll"));
	auto MaterialPointer = get_module_factory(GetModuleHandleW(L"materialsystem.dll"));
	auto PhysicsPointer = get_module_factory(GetModuleHandleW(L"vphysics.dll"));
	auto StdPointer = get_module_factory(GetModuleHandleW(L"vstdlib.dll"));
	auto CachePointer = get_module_factory(GetModuleHandleW(L"datacache.dll"));
	auto DX9API = GetModuleHandleW(L"shaderapidx9.dll");

	g_CHLClient = (IBaseClientDLL*)ClientPointer("VClient018", nullptr);
	g_Engine = (IVEngineClient*)EnginePointer("VEngineClient014", nullptr);
	g_Panel = (IPanel*)VGUI2Pointer("VGUI_Panel009", nullptr);
	g_Surface = (ISurface*)VGUISurfacePointer("VGUI_Surface031", nullptr);
	g_EntityList = (C_BaseEntityList*)ClientPointer("VClientEntityList003", nullptr);
	g_DebugOverlay = (IVDebugOverlay*)EnginePointer("VDebugOverlay004", nullptr);
	g_Prediction = (IPrediction*)ClientPointer("VClientPrediction001", nullptr);
	g_MaterialSystem = (CMaterialSystem*)MaterialPointer("VMaterialSystem080", nullptr);
	g_RenderView = (CVRenderView*)EnginePointer("VEngineRenderView014", nullptr);
	g_ModelRender = (IVModelRender*)EnginePointer("VEngineModel016", nullptr);
	g_ModelInfo = (CModelInfo*)EnginePointer("VModelInfoClient004", nullptr);
	g_EngineTrace = (IEngineTrace*)EnginePointer("EngineTraceClient004", nullptr);
	g_PhysProps = (IPhysicsSurfaceProps*)PhysicsPointer("VPhysicsSurfaceProps001", nullptr);
	g_CVar = (ICVar*)StdPointer("VEngineCvar007", nullptr);
	g_Dlight = (IVEffects*)EnginePointer("VEngineEffects001", nullptr);
	g_GameMovement = (IGameMovement*)ClientPointer("GameMovement001", nullptr);
	g_MoveHelper = **(IMoveHelper***)(U::FindPattern("client.dll", (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B\x46\x08\x68", "xx????xxxx") + 2);
	g_EventManager = (IGameEventManager2*)EnginePointer("GAMEEVENTSMANAGER002", nullptr);
	g_GameConsole = (IGameConsole*)ClientPointer("GameConsole004", nullptr);
	g_Input = *(CInput**)(U::FindPatternIDA("client.dll", "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10") + 1);
	g_ViewRender = *(IViewRender**)(U::FindPattern("client.dll", (PBYTE)"\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xFF\x10", "x????x????xx????????xx") + 1);
	g_PlayerResource = **(C_CSPlayerResource***)(U::FindPattern("client.dll", (PBYTE)"\x8B\x3D\x00\x00\x00\x00\x85\xFF\x0F\x84\x00\x00\x00\x00\x81\xC7", "xx????xxxx????xx") + 2);
	g_GameRules = **(C_CSGameRules***)(U::FindPattern("client.dll", (PBYTE)"\xA1\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x6A\x00\x68\x00\x00\x00\x00\xC6\x80", "x????xx????xxx????xx") + 1);
	g_MdlCache = (IMDLCache*)CachePointer("MDLCache004", nullptr);
	g_ChatElement = FindHudElement<CHudChat>("CHudChat");
	g_ClientMode = **(IClientMode***)((*(DWORD**)g_CHLClient)[10] + 0x5);
	g_ClientState = *reinterpret_cast<CBaseClientState***>(call_vfunc<std::uintptr_t>(g_Engine, 12) + 0x10);
	g_Globals = **(CGlobalVarsBase***)((*(DWORD**)g_CHLClient)[0] + 0x1B);
	g_pViewRenderBeams = *reinterpret_cast< IViewRenderBeams** > (U::FindSig(("client.dll"), ("A1 ? ? ? ? 56 8B F1 B9 ? ? ? ? FF 50 08")) + 0x1);
	g_pMemAlloc = *(IMemAlloc**)(GetProcAddress(GetModuleHandle("tier0.dll"), "g_pMemAlloc"));
	g_D3DDevice9 = **(IDirect3DDevice9***)(U::pattern_scan(DX9API, "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);
	g_GlowObjManager = *(CGlowObjectManager**)(U::pattern_scan(GetModuleHandleW(L"client.dll"), "0F 11 05 ? ? ? ? 83 C8 01 C7 05 ? ? ? ? 00 00 00 00") + 3);
	g_ClientStringTableContainer = (CNetworkStringTableContainer*)EnginePointer("VEngineClientStringTable001", NULL);
}



IDirect3DDevice9* g_D3DDevice9 = nullptr;
IBaseClientDLL* g_CHLClient;
IVEngineClient* g_Engine;
IPanel* g_Panel;
C_BaseEntityList* g_EntityList;
ISurface* g_Surface;
IVDebugOverlay* g_DebugOverlay;
IClientMode* g_ClientMode;
CGlobalVarsBase* g_Globals;
IPrediction *g_Prediction;
CMaterialSystem* g_MaterialSystem;
CVRenderView* g_RenderView;
IVModelRender* g_ModelRender;
CModelInfo* g_ModelInfo;
IEngineTrace* g_EngineTrace;
IPhysicsSurfaceProps* g_PhysProps;
ICVar* g_CVar;
IVEffects* g_Dlight;
IMoveHelper* g_MoveHelper;
IGameMovement* g_GameMovement;
CInput* g_Input;
IGameEventManager2* g_EventManager;
C_CSPlayerResource* g_PlayerResource;
C_CSGameRules* g_GameRules;
IViewRender* g_ViewRender;
IGameConsole* g_GameConsole;
IMDLCache* g_MdlCache;
CHudChat* g_ChatElement;
CGlowObjectManager* g_GlowObjManager;
IViewRenderBeams* g_pViewRenderBeams;
IMemAlloc* g_pMemAlloc;
CNetworkStringTableContainer* g_ClientStringTableContainer;
CBaseClientState** g_ClientState;