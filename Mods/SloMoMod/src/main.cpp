#include <stdio.h>
#include <string>
#include <Mod/CppUserModBase.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/ReflectedFunction.hpp>
#include <Unreal/GameplayStatics.hpp>
#include <Unreal/Hooks.hpp>
#include <Unreal/World.hpp>
#include <Input/Handler.hpp>

#include <ModUtils/Extensions.hpp>
#include <Macros.hpp>
#include <Windows.h>


using namespace RC;
using namespace RC::Unreal;

namespace HLCPPTutorial {
class UGameplayStaticsExtended : public UObject {
	// Helper from Unreal submodule helps us automatically reference UFunctions
	struct StaticFunctions {
		// Template type is reqired for the Self pointer in StaticReflectedFunctionBase
		static inline StaticReflectedFunctionBase<UGameplayStaticsExtended> GetGlobalTimeDilation{STR("/Script/Engine.GameplayStatics:GetGlobalTimeDilation")};
		static inline StaticReflectedFunctionBase<UGameplayStaticsExtended> SetGlobalTimeDilation{STR("/Script/Engine.GameplayStatics:SetGlobalTimeDilation")};
	};

public:
	// Required for static functions by StaticReflectedFunctionBase (Unreal/ReflectedFunction.hpp Line 35)
	static inline UGameplayStaticsExtended* Self{nullptr};

private:
	static bool VerifySelf() {
		if (!Self)
		{
			Self = UObjectGlobals::StaticFindObject<UGameplayStaticsExtended*>(nullptr, nullptr, STR("/Script/Engine.Default__GameplayStatics"));
			if (!Self)
			{
				Output::send(STR("Was unable to locate GameplayStatics\n"));
				return false;
			}
		}

		return true;
	}

public:
	static float GetGlobalTimeDilation(UObject* WorldContextObject) {
		// Checks/assigns the instance if its available
		if (!VerifySelf() || !StaticFunctions::GetGlobalTimeDilation.IsValid()) {
			return 1;
		}

		// Parameters are passed as a struct (including the return value)
		// The properties for this can be seen in live view
		struct Params
		{
			const UObject* WorldContextObject;
			float ReturnValue;
		};

		Params p {
			.WorldContextObject = WorldContextObject
		};

		StaticFunctions::GetGlobalTimeDilation(p);
		return p.ReturnValue;
	}

	static void SetGlobalTimeDilation(UObject* WorldContextObject, float TimeDilation) {
		if (!VerifySelf() || !StaticFunctions::SetGlobalTimeDilation.IsValid()) {
			return;
		}

		struct Params
		{
			const UObject* WorldContextObject{};
			float TimeDilation;
		};

		Params p{
			.WorldContextObject = WorldContextObject,
			.TimeDilation = TimeDilation
		};

		StaticFunctions::SetGlobalTimeDilation(p);
	}
};

class SloMoMod : public CppUserModBase
{
public:
    SloMoMod() : CppUserModBase()
	{
		ModName = MOD_NAME;
		ModVersion = STR("1.0");
		ModDescription = STR("103 - SloMoMod");
		ModAuthors = STR("HLCPPTutorial");
	}

	~SloMoMod()
	{
		// If mod is disabled, reset the dilation
		SetDilation(1.0);
	}

	float currentDilation = 0;

	AActor* player_controller = nullptr;

	bool CheckPlayer() {
		// Check if player is valid
		if (!player_controller || !Unreal::UObjectArray::IsValid(player_controller->GetObjectItem(), false)) {
			if (player_controller) LOG("Player became invalid");
			player_controller = nullptr;
			return false;
		}
		return true;
	}

	float GetDilation() {
		if (CheckPlayer()) {
			return UGameplayStaticsExtended::GetGlobalTimeDilation(player_controller);
		}
		else {
			return 1.0;
		}
	}

	void SetDilation(float dilation) {
		if (CheckPlayer()) {
			UGameplayStaticsExtended::SetGlobalTimeDilation(player_controller, dilation);
		}
	}

	void on_unreal_init() override {
		Hook::RegisterBeginPlayPostCallback([&](AActor* Context) {
			// Doubt this is needed
			if (!(Context && Context->GetClassPrivate())) return;
			if (Context->GetClassPrivate()->GetName() == STR("BP_Phoenix_Player_Controller_C")) {
				player_controller = Context;
				LOG_EXPR((void*)player_controller);
			}
		});
	}

	auto on_program_start() -> void override {

	}

	auto on_update() -> void override
	{
		TRY([&]() {
			// TODO => Use Input::Handler for window focus stuff
			if (GetAsyncKeyState(Input::Key::OEM_COMMA)) {
				if (GetAsyncKeyState(Input::ModifierKey::ALT)) {
					SetDilation(0.33);
				}
				else if (GetAsyncKeyState(Input::ModifierKey::CONTROL)) {
					SetDilation(0.5);
				}
				else if (GetAsyncKeyState(Input::ModifierKey::SHIFT)) {
					SetDilation(0.66);
				}
				else {
					SetDilation(1.0);
				}
			}
		});
		
	}
};

}

#define MY_AWESOME_MOD_API __declspec(dllexport)
extern "C"
{
	MY_AWESOME_MOD_API RC::CppUserModBase* start_mod()
	{
		return new HLCPPTutorial::SloMoMod();
	}

	MY_AWESOME_MOD_API void uninstall_mod(RC::CppUserModBase* mod)
	{
		delete mod;
	}
}