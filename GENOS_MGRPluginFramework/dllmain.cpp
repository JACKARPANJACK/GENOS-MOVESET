#include "Events.h"
#include <cWeaponSelectMenu.h>
#include <PlayerManagerImplement.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <Trigger.h>
#include <GameMenuStatus.h>
#include <Pl0000.h>
#include <cGameUIManager.h>
#include "cSlowRateManager.h"
#include <AnimationMapManagerImplement.h>
#include <Windows.h>
#include <WinUser.h>
#include "pch.h"
#include <EntitySystem.h>
#include <EntityHandle.h>
#include <Entity.h>
#include <Behavior.h>
#include <BehaviorEmBase.h>
#include <cObj.h>

//FSM-finite scalable state machine
struct DatHolder
{
    char* m_data;

    void* getFile(const char* name)
    {
        return ((void* (__thiscall*)(DatHolder*, const char*))(shared::base + 0x9E4500))(this, name);
    }
};

void sub_808430(Behavior* a1)
{
    ((void* (__thiscall*)(Behavior * a1))(shared::base + 0x808430))(a1);
}
void sub_47C660(Behavior* a1)
{
    ((void* (__thiscall*)(Behavior * a1))(shared::base + 0x47C660))(a1);
}
void sub_7884C0(Pl0000* player)
{
    ((void(__thiscall*)(Pl0000 * player))(shared::base + 0x788590))(player);
}
void sub_794FC0(Pl0000* player)
{
    ((void(__thiscall*)(Pl0000 * player))(shared::base + 0x794FC0))(player);
}
BOOL sub_A36060(int* v349, int a2)
{
    return ((BOOL(__thiscall*)(int* v349, int a2))(shared::base + 0xA36060))(v349, a2);
}
void setIdle(Pl0000* player, int a2)
{
    CallVMTFunc<226, Pl0000*, int>(player, a2);
}

void bladeModeFadeOut(Pl0000* player)
{
    ((void(__thiscall*)(Pl0000 * player))(shared::base + 0x77AA80))(player);
}

void FocusToEnemy(Pl0000* player, float a2, float a3, float a4, float a5)
{
    return ((void(__thiscall*)(Pl0000 * player, float, float, float, float))(shared::base + 0x77B270))(player, a2, a3, a4, a5);
}
void sub_786010(Pl0000* player, int a2)
{
    ((void(__thiscall*)(Pl0000 * player, int a2))(shared::base + 0x786010))(player, a2);
}

void sub_4CEA50(Behavior* a1)
{
    ((void* (__thiscall*)(Behavior * a1))(shared::base + 0x4CEA50))(a1);
}
BOOL CheckFlag(Behavior* a1, int a2)
{
    return a2 / 32 < 2 && (*(&a1->field_790 + a2 / 32) & (1 << (a2 % 32))) != 0;
}
BOOL sub_786410(float* a1)
{
    return ((BOOL(__thiscall*)(float* a1))(shared::base + 0x786410))(a1);
}
D3DXVECTOR3* sub_68E880(BehaviorAppBase* player, cVec4* a2)
{
    return ((D3DXVECTOR3 * (*__thiscall)(BehaviorAppBase * player, cVec4 * a2))(shared::base + 0x68E880))(player, a2);
}

void AnimationPlayer(Behavior* behavior, float a2, float a3) {
    ((void(__thiscall*)(Behavior*, float, float))(shared::base + 0x794790))(behavior, a2, a3);
}

void AnimationStop(Behavior* behavior, int a2, float a3) {
    ((void(__thiscall*)(Behavior*, int, float))(shared::base + 0x694BC0))(behavior, a2, a3);
}

int MGR_PlaySound(const char* se, int a2) {
    return ((int(__cdecl*)(const char*, int))(shared::base + 0xA5E050))(se, a2);
}

int setAnimation(Behavior* behavior, void* animationFile, const char* animName, int a4, float fInterpolation, float a6, int nFlags, float fStartFrame, float a9) {
    return ((int(__thiscall*)(Behavior*, void*, const char*, int, float, float, int, float, float))(shared::base + 0xA3FD90))(behavior, animationFile, animName, a4, fInterpolation, a6, nFlags, fStartFrame, a9);
}

const char* getAnimationNameById(Behavior* bh, int animId) {
    return ((const char* (__thiscall*)(Behavior*, int))(shared::base + 0x4D7D70))(bh, animId);
}

void SetFunctionToAddress(unsigned int addr1, unsigned int addr2) {
    if (injector::ReadMemory<unsigned int>(addr1, true) != addr2) injector::WriteMemory<unsigned int>(addr1, addr2, true);
}

//PC Default Button                /////////////////
//6-Left mouse click               player->field_E20
//7-Right mouse click              player->field_E24
//8-Crtl EnableBladeMode           player->field_E50
//9-Shift                          player->field_E48 player->field_B94
//10-Press F                       player->field_E38
//11-RipperMode Press R            /////////////////
//12-Press E                       player->field_E08
//13-Press C                       player->field_E38
//14-Press Z                       player->field_E58
//15-Press num1 
//20-FinishedQTEButton  X(Ori PC)

int getIsHotkeyPressed(int a1)
{
    return ((int(__cdecl*)(int a1))(shared::base + 0x61D280))(a1);
}

void AddNewAction(Pl0000* player, std::string AnimationString)
{
    int v341 = player->m_nCurrentActionId;
    if (v341)
    {
        if (v341 != 1)
            return;
    }
    else
    {
        player->field_940 = 0;
        bladeModeFadeOut(player);
        player->m_fEntityTickRate = 1.0f;
        sub_794FC0(player);
        player->requestAnimationByName(AnimationString.c_str(), 0, 1.f / 60.f, 1.f, 0x8000000, -1.f, 1.f);
        ++player->m_nCurrentActionId;
        player->field_26D4 = 0;
        player->m_bSwordHidden = 0;
    }
    player->field_11A4 = 1;
    player->field_B78 = 0;
    AnimationPlayer(player, 1.0f, 1.0f);
    player->field_B78 = 1;
    Animation* v349 = player->m_pAnimation;
    if (!(v349->field_B8 + v349->field_C4 + v349->field_D0) || sub_A36060(&v349->field_F4, 0))
    {
        setIdle(player, 0);
    }
    return;
}

bool CurrentAnimationCurrentlyCancelable(Pl0000* player) {
    if (CheckFlag(player, 17) == 1 //Dodge cancel?
        || CheckFlag(player, 29) == 1 //Any cancel? (walk flag)
        || CheckFlag(player, 23) == 1 //Blade Mode cancel?
        || CheckFlag(player, 28) == 1 // Jump cancel?
        || CheckFlag(player, 49) == 1) // Dodge cancel again?
    {
        return true;
    }
    else
        return false;
}

class GameManager {
public:
    static bool IS_GENOS;

    static void TurnOnGenos() {
        IS_GENOS = true;
    }

    static void TurnOffGenos() {
        IS_GENOS = false;
    }

    static bool IsGenosOn() {
        return IS_GENOS;
    }

    static void ToggleGenos() {
        IS_GENOS = !IS_GENOS;
    }
};

bool GameManager::IS_GENOS = false;

void HandleWeaponToggle(Pl0000* player) {
    if (player) {
        auto pl = PlayerManagerImplement::pInstance;
        int  currentCustomWeapon = pl->GetCustomWeaponEquipped();
        bool isKeyPressed = shared::IsKeyPressed(0x47, false);
        if (isKeyPressed) {
            Behavior* bSheath = nullptr;
            Entity* entity = player->m_SheathHandle.getEntity();
            bSheath = (Behavior*)entity->m_pInstance;
            if (currentCustomWeapon != 5) {
                GameManager::ToggleGenos();
                player->setSwordLost(1);
                player->m_nSwordState = 1;
                **(int**)(shared::base + 0x17E9FCC) = 0x32040;
                ((void(__thiscall*)(Pl0000*))(shared::base + 0x7948D0))(player);
                pl->SetCustomWeaponEquipped(5);
                bSheath->toggleAnyMesh("equip_sheath", false);
                bSheath->toggleAnyMesh("connect", false);
                player->toggleAnyMesh("saya_arm", false);  // Sheath
                setIdle(player, 0);
                //if (!genosE)
                //{

                //    static float timer = 0.f;
                //    //timer += cSlowRateManager::Instance.m_fTickRate;
                //    //if (timer >= 30.f) {
                //    //    player->shutdownEffects();
                //    //    effControler.FadeUnits(0.f, 0.f);// 0.5 seconds
                //    //}
                //}
            }
            if (currentCustomWeapon == 5) {
                GameManager::ToggleGenos();
                player->setSwordLost(0);
                player->m_nSwordState = 0;
                ((void(__thiscall*)(Pl0000*))(shared::base + 0x7948D0))(player);
                pl->SetCustomWeaponEquipped(0);
                bSheath->toggleAnyMesh("equip_sheath", true);
                player->toggleAnyMesh("saya_arm", true);  // Sheath
                bSheath->toggleAnyMesh("connect", true);
                setIdle(player, 0);
            }
        }
    }
}

struct PlayerInputState {
    bool rButtonHeld = false;
    bool rButton = false;
    bool lButton = false;
    bool lButtonW = false;
    bool xKey = false;
    bool adKeys = false;
    bool wKey = false;
    float launcherHoldDuration = 0.0f;
};

PlayerInputState input;                // Holds the very latest frame’s inputs

static float comboTimer = 0;

// === ComboNode Definition for Chain Branching ===
struct ComboNode {
    const char* animation;
    ComboNode* lightBranch = nullptr;
    ComboNode* AlightBranch = nullptr;
    ComboNode* heavyBranch = nullptr;
    ComboNode* airBranch = nullptr;
};

// Combo tree nodes (global scope)
ComboNode c1, c2, c3, c4, c5, c6 ,c7 ,c8, c9;      // Ground‐chain nodes
ComboNode air1, air2, air3, air4, air5, air6, air7, air8, air9;                  // Air‐chain nodes
ComboNode launcher_primary, launcher_secondary, spec1, spec2, spec3, c_alt1, c_alt2, c_alt3;           // Launcher node (branches into air1)
ComboNode* currentCombo = &c1;         // Pointer to the current node in the chain



// FSM timing & state
enum class ComboState { Idle, Executing, Buffering };
static ComboState comboState = ComboState::Idle;

static int   totalAnimIndex = 0;       // Which step in the current chain
static float lastComboTime = 0.0f;     // When the last combo step fired
static const float comboWindow = 800;  // ms before chain resets

// Buffer window
static bool  bufferWindowActive = false;
static float bufferStartTime = 0.0f;
static const float bufferWindow = 500; // ms grace period

// “now” tick
float now = 0.0f;                      // cSlowRateManager::Instance.m_fTickRate each tick

// Dynamic combo tree initialization
void InitComboTree() {
    // Define your combo stages
    static ComboNode* groundHits[]   = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9 };
    static ComboNode* altGround[]    = { &c_alt1, &c_alt2, &c_alt3 };
    static ComboNode* airHits[]      = { &air1, &air2, &air3, &air4, &air5, &air6, &air7, &air8, &air9 };
    static ComboNode* launchers[]    = { &launcher_primary, &launcher_secondary };
    static ComboNode* specials[]     = { &spec1, &spec2, &spec3 };

    // Helper to link a linear chain, optionally terminating into another node
    auto linkChain = [](ComboNode* nodes[], size_t count, ComboNode* terminal = nullptr) {
        for (size_t i = 0; i + 1 < count; ++i) {
            nodes[i]->lightBranch = nodes[i + 1];
        }
        nodes[count - 1]->lightBranch = terminal;
    };

    // 1. Ground hits chain -> alternate ground entry
    linkChain(groundHits,   sizeof(groundHits)/sizeof(groundHits[0]),   altGround[0]);
    // 2. Alternate ground chain -> primary launcher
    linkChain(altGround,    sizeof(altGround)/sizeof(altGround[0]),     launchers[0]);
    // 3. Air hits chain -> secondary launcher
    linkChain(airHits,      sizeof(airHits)/sizeof(airHits[0]),         launchers[1]);
    // 4. Launcher chain -> first special
    linkChain(launchers,    sizeof(launchers)/sizeof(launchers[0]),     specials[0]);
    // 5. Specials chain terminates to nullptr (end of combo)
    linkChain(specials,     sizeof(specials)/sizeof(specials[0]),       nullptr);

    // Assign air transitions: each ground hit can branch into corresponding air hit
    size_t groundCount = sizeof(groundHits)/sizeof(groundHits[0]);
    size_t airCount    = sizeof(airHits)   /sizeof(airHits[0]);
    for (size_t i = 0; i < groundCount; ++i) {
        groundHits[i]->airBranch = (i < airCount ? airHits[i] : nullptr);
    }

    // Reset combo state
    currentCombo       = nullptr;
    totalAnimIndex     = 0;
    bufferWindowActive = false;
    lastComboTime      = 0.0f;
}




// --- Edit ResetComboState ---
void ResetComboState(PlayerInputState& input) {
    totalAnimIndex = 0;
    comboTimer = 0;
    lastComboTime = 0;

    input = PlayerInputState{};
}

// Simple buffer window handler: returns true when we're clear to fire the next
// combo link, or false if we're still in the “cannot cancel → buffering” window.
bool HandleComboBufferWindow(Pl0000* player,
    float now,
    PlayerInputState& input)
{
    if (!CurrentAnimationCurrentlyCancelable(player)) {
        // start or continue the buffer countdown
        if (!bufferWindowActive) {
            bufferWindowActive = true;
            bufferStartTime = now;
        }
        else if (now - bufferStartTime >= bufferWindow) {
            // buffer expired — clear combo
            ResetComboState(input);
            bufferWindowActive = false;
        }
        return false;
    }

    // cancelable again → clear buffer flag, allow next link
    bufferWindowActive = false;
    return true;
}

// --- Edit HasInitialInput ---
bool HasInitialInput(const PlayerInputState& input) {
    ePrintf("[Input Check] r: %d l: %d lw: %d x: %d ad: %d w: %d\n",
        input.rButton, input.lButton, input.lButtonW,
        input.xKey, input.adKeys, input.wKey);

    return input.rButton || input.lButton || input.lButtonW || input.xKey || input.adKeys || input.wKey;
}


// --- Fix UpdatePlayerInputState to use GetAsyncKeyState ---
bool IsKeyDown(int key) {
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}

PlayerInputState UpdatePlayerInputState(Pl0000* player) {
    float currentTick = cSlowRateManager::Instance.m_fTickRate;
    static float launcherHoldStart = 0.0f;
    PlayerInputState input;

    if (IsKeyDown(VK_RBUTTON)) {
        input.rButtonHeld = true;
        if (launcherHoldStart == 0.0f)
            launcherHoldStart = currentTick;
        input.launcherHoldDuration = currentTick - launcherHoldStart;
        if (!player->isInAir()) input.rButton = true;
    }
    else {
        launcherHoldStart = 0.0f;
    }

    if (IsKeyDown(VK_LBUTTON))
        input.lButton = true;

    if (IsKeyDown(VK_LBUTTON) && IsKeyDown('W'))
        input.lButtonW = true;

    if (IsKeyDown('X') && !player->isInAir())
        input.xKey = true;

    if (IsKeyDown('A') && IsKeyDown('D') && !player->isInAir())
        input.adKeys = true;

    if (IsKeyDown('W'))
        input.wKey = true;

    return input;
}

// FSM + Combo Logic with proper animation chaining and fixed GetNextComboAnimation behavior

const char* GetNextComboAnimation(Pl0000* player, const PlayerInputState& input) {
    float now = cSlowRateManager::Instance.m_fTickRate;
	bool comboIsSpecial = false;
    if (now - lastComboTime > comboWindow) {
        totalAnimIndex = 0;
    }
    lastComboTime = now;

    if (input.rButtonHeld && input.launcherHoldDuration >= 500.0f) {
        totalAnimIndex = 0;
        std::string adAnims[] = {"3500","2361"};
        return adAnims[rand() % 2].c_str();
    }

    if (input.lButtonW) return "225a";
    if (input.xKey)     return "24b0";

    if (input.adKeys) {
        std::string adAnims[] = { "2490", "24a0", "2471" };
        return adAnims[rand() % 3].c_str();
    }

    static std::string sequence = nullptr;
    bool isAir = player->isInAir();

    if (input.rButton) {
        if (!isAir) {
            std::string normalCombo[] = {
                "2250", "2251", "2252", "2260",
                "2261", "2261", "2261", "2261", "2262"
            };
            std::string specialCombo[] = { "2c10", "2c11", "2c12" };

            if (totalAnimIndex == 0) {
                comboIsSpecial = (shared::random(0, 10) % 2 == 0); // Randomize only on first strike
            }

            if (comboIsSpecial) {
                sequence = specialCombo[totalAnimIndex % 3].c_str();
            }
            else {
                sequence = normalCombo[totalAnimIndex % 9].c_str();
            }
        }
        else {
            std::string airCombo[] = {
                "2210", "2420", "2265", "2266",
                "2467", "2467", "2268", "2421", "2422"
            };
            sequence = airCombo[totalAnimIndex % 9].c_str();
        }
    }

    ++totalAnimIndex;
	static const char* sequence1 = sequence.c_str();
    return sequence1;
}


const char* AdvanceCombo(Pl0000* player, PlayerInputState& input, bool isAir) {
    if (!currentCombo) return nullptr;

    static const char* nextAnim = GetNextComboAnimation(player, input);
    if (!nextAnim || strlen(nextAnim) == 0) {
        ePrintf("[AdvanceCombo] GetNextComboAnimation returned null/empty.\n");
        return nullptr;
    }

    currentCombo->animation = nextAnim;
    static const char* result = currentCombo->animation;

    if (isAir && currentCombo->airBranch) {
        currentCombo = currentCombo->airBranch;
        ePrintf("[AdvanceCombo] → airBranch\n");
    }
    else if (input.lButtonW && currentCombo->AlightBranch) {
        currentCombo = currentCombo->AlightBranch;
        ePrintf("[AdvanceCombo] → AlightBranch (alt combo)\n");
    }
    else if (input.lButton || input.rButton) {
        currentCombo = currentCombo->lightBranch;
        ePrintf("[AdvanceCombo] → lightBranch\n");
    }
    else {
        currentCombo = nullptr;
        ePrintf("[AdvanceCombo] Combo ended — no branch\n");
    }

    return result;
}

const char* ProcessComboFSM(Pl0000* player, PlayerInputState& cachedComboInput) {
    float now = cSlowRateManager::Instance.m_fTickRate;
    static ComboState comboState = ComboState::Idle;
    static PlayerInputState bufferedInput = {};
    static const char* animToPlay = nullptr;

    if (now - lastComboTime > comboWindow) {
        totalAnimIndex = 0;
        currentCombo = nullptr;
        comboState = ComboState::Idle;
    }

    switch (comboState) {
    case ComboState::Idle: {
        if (HasInitialInput(cachedComboInput)) {
            static const char* first = GetNextComboAnimation(player, cachedComboInput);
            if (first) {
                currentCombo = player->isInAir() ? &air1 : &c1;
                currentCombo->animation = first;
                animToPlay = first;
                comboState = ComboState::Executing;
                ePrintf("[FSM] → Executing | StartAnim: %s\n", first);
            }
        }
        break;
    }

    case ComboState::Executing: {
        if (CurrentAnimationCurrentlyCancelable(player)) {
            animToPlay = AdvanceCombo(player, cachedComboInput, player->isInAir());
            if (animToPlay) {
                comboState = ComboState::Executing;
                ePrintf("[FSM] → Executing | ContinueAnim: %s\n", animToPlay);
            }
            else {
                comboState = ComboState::Idle;
                ePrintf("[FSM] → Idle | No next anim\n");
            }
        }
        else {
            bufferedInput = cachedComboInput;
            ePrintf("[FSM] Waiting for cancel, input buffered\n");
        }
        break;
    }
    }

    if (!animToPlay && HandleComboBufferWindow(player, now, bufferedInput)) {
        animToPlay = AdvanceCombo(player, bufferedInput, player->isInAir());
        if (animToPlay) {
            comboState = ComboState::Executing;
            ePrintf("[FSM] Buffered combo continue: %s\n", animToPlay);
        }
        else {
            comboState = ComboState::Idle;
        }
    }

    return animToPlay;
}

bool anti_loop_1 = false;

void GenosInit()
{
    Pl0000* player = cGameUIManager::Instance.m_pPlayer;
    if (!anti_loop_1)
    {
        // Only proceed if valid player and correct model
        if (!player || player->m_nModelIndex != 0x10010) return;

        // Hide specific meshes
        player->toggleAnyMesh("wep", false);      // Gun player->field_79C 
        player->toggleAnyMesh("connect", false);  // Sheath
        player->toggleAnyMesh("equip_sheath", false);  // Sheath
    }
}

bool antiloop = false;
static const char* anim;

class GENOS {
public:
    GENOS() {
        static float lastInputTime = 0.0f;
        static float noInputBuffer = 0.4f;
        static bool canAttemptCombo = false;
        static PlayerInputState cachedComboInput = {}; // 400 ms no input delay
        static bool flag = 0;
        static int  totalAnimIndex1 = 0;

        // Create and initialize static member variables  
        Events::OnSceneStartupEvent.after += []() {
            if (!((BOOL(__thiscall*)(void*, eObjID, int))(shared::base + 0x600A60))((void*)(shared::base + 0x177B364), (eObjID)0x32040, 0))
                ePrintf("FAILED TO REQUEST OBJECT");
            };

        Events::OnSceneCleanupEvent.before += []() {
            ((BOOL(__thiscall*)(void*, eObjID, int))(shared::base + 0x600BD0))((void*)(shared::base + 0x177B364), (eObjID)0x32040, 0);

            };

        Events::OnTickEvent += [&]() {
        Pl0000* player = cGameUIManager::Instance.m_pPlayer;
        auto pl = PlayerManagerImplement::pInstance;
            if (player && pl) {
                if (!antiloop) {
                    GenosInit();
                    InitComboTree();
                    antiloop = true;
                }

                HandleWeaponToggle(player);
                ePrintf("[Tick] totalAnimIndex: %d | Action: %d\n", totalAnimIndex, player->m_nCurrentAction);

                static PlayerInputState cachedComboInput = {};
                static float lastInputTime = 0.0f;
                static const float noInputBuffer = 0.4f;
                static bool flag = false;
                static int totalAnimIndex1 = 0;

                float now = cSlowRateManager::Instance.m_fTickRate;
                cachedComboInput = UpdatePlayerInputState(player);

                if (HasInitialInput(cachedComboInput)) {
                    lastInputTime = now;
                }

                anim = ProcessComboFSM(player, cachedComboInput);
                if (anim == nullptr) flag = 1;
                else
                {
					flag = 0; 
                }

                if (flag) {
                    player->setState(200000 + totalAnimIndex1, 0, 0, 0);
                    if (player->m_nCurrentAction == 200000 + totalAnimIndex1) {
                        AddNewAction(player, currentCombo->animation);
                        sub_808430(player);
                        ++totalAnimIndex1;
                    }
                }
            }
        };
    }
}_GENOS;
