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


using namespace RC;
using namespace RC::Unreal;

namespace HLCPPTutorial {
class UGameplayStaticsExtended : public UObject {
	// Helper from Unreal submodule helps us automatically reference UFunctions
	struct StaticFunctions {
		static inline StaticReflectedFunctionBase<UGameplayStaticsExtended> GetGlobalTimeDilation{STR("/Script/Engine.GameplayStatics:GetGlobalTimeDilation")};
		static inline StaticReflectedFunctionBase<UGameplayStaticsExtended> SetGlobalTimeDilation{STR("/Script/Engine.GameplayStatics:SetGlobalTimeDilation")};
	};

public:
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
		if (!VerifySelf()) {
			return -1;
		}
		if (!StaticFunctions::GetGlobalTimeDilation.IsValid()) {
			return 0;
		}

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
		if (!VerifySelf()) {
			return;
		}
		if (!StaticFunctions::SetGlobalTimeDilation.IsValid()) {
			return;
		}

		struct Params
		{
			const UObject* WorldContextObject{};
			float TimeDilation;
			void* ReturnValue;
		};

		Params p{
			.WorldContextObject = WorldContextObject,
			.TimeDilation = TimeDilation
		};

		StaticFunctions::SetGlobalTimeDilation(p);

		return;
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
	}

	float currentDilation = 0;

	void on_unreal_init() override {
		LOG("Initialized");
		Hook::RegisterBeginPlayPostCallback([&](AActor* Context) {
			LOG("Begin Play");
			LOG_EXPR(Context->GetFullName());
			LOG_EXPR(UGameplayStaticsExtended::GetGlobalTimeDilation(Context));
			UGameplayStaticsExtended::SetGlobalTimeDilation(Context, 200);
		});
	}

	auto on_program_start() -> void override {

	}

	//int tick = -6000;
	auto on_update() -> void override
	{
		/*tick++;
		if (tick % 600 == 0) {
			LOG_EXPR(UGameplayStaticsExtended::GetGlobalTimeDilation());
		}*/
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