#include <stdio.h>
#include <string>
#include <Mod/CppUserModBase.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/ReflectedFunction.hpp>
#include <Unreal/GameplayStatics.hpp>
#include <Unreal/Hooks.hpp>
#include <Input/Handler.hpp>

#include <ModUtils/Extensions.hpp>
#include <Macros.hpp>


using namespace RC;
using namespace RC::Unreal;

namespace HLCPPTutorial {

class SloMoMod : public CppUserModBase
{
public:
    SloMoMod() : CppUserModBase()
	{
		ModName = STR("SloMoMod");
		ModVersion = STR("1.0");
		ModDescription = STR("103 - SloMoMod");
		ModAuthors = STR("HLCPPTutorial");
	}

	~SloMoMod()
	{
	}

	// Helper from Unreal submodule helps us automatically reference UFunctions
	struct StaticFunctions {
		static inline StaticReflectedFunctionBase<UGameplayStatics> GetGlobalTimeDilation{STR("/Script/Engine.GameplayStatics:GetGlobalTimeDilation")};
		static inline StaticReflectedFunctionBase<UGameplayStatics> SetGlobalTimeDilation{STR("/Script/Engine.GameplayStatics:SetGlobalTimeDilation")};
	};

	static float GetGlobalTimeDilation() {
		if (!UObjectGlobals::StaticFindObject<UGameplayStatics*>(nullptr, nullptr, STR("/Script/Engine.Default__GameplayStatics"))) {
			return -1;
		}
		if (!StaticFunctions::GetGlobalTimeDilation.IsValid()) {
			LOG("GetGlobalTimeDilation Is Invalid");
			return 0;
		}

		struct Params
		{
			const UObject* WorldContextObject;
			float ReturnValue;
		};

		Params p {};

		StaticFunctions::GetGlobalTimeDilation(p);

		return p.ReturnValue;
	}

	static void SetGlobalTimeDilation(float TimeDilation) {
		if (!StaticFunctions::SetGlobalTimeDilation.IsValid()) {
			LOG("SetGlobalTimeDilation Is Invalid");
			return;
		}

		struct Params
		{
			const UObject* WorldContextObject{};
			float TimeDilation;
			void* ReturnValue;
		};

		Params p {
			.TimeDilation = TimeDilation
		};

		//StaticFunctions::SetGlobalTimeDilation(p);

		return;
	}

	float currentDilation = 0;

	void on_unreal_init() override {
		LOG("Initialized");
	}

	auto on_program_start() -> void override {
		LOG("Started");
	}

	int tick = -500;
	auto on_update() -> void override
	{
		tick++;
		if (tick % 600 == 0) {
			LOG_EXPR(GetGlobalTimeDilation());
		}
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