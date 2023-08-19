#include <stdio.h>
#include <string>
#include <Mod/CppUserModBase.hpp>
#include <DynamicOutput/DynamicOutput.hpp>

using namespace RC;
//using namespace RC::Unreal;

namespace HLCPPTutorial {

class TemplateMod : public CppUserModBase
{
public:
    TemplateMod() : CppUserModBase()
	{
		ModName = STR("TemplateMod");
		ModVersion = STR("1.0");
		ModDescription = STR("This is my awesome mod");
		ModAuthors = STR("HLCPPTutorial");
	}

	~TemplateMod()
	{
	}


	void on_unreal_init() override {
        Output::send<LogLevel::Normal>(STR("[TemplateMod] Unreal Initialized\n"));
	}



	auto on_program_start() -> void override {
	}

	auto on_update() -> void override
	{
	}
};

}

#define MY_AWESOME_MOD_API __declspec(dllexport)
extern "C"
{
	MY_AWESOME_MOD_API RC::CppUserModBase* start_mod()
	{
		return new HLCPPTutorial::TemplateMod();
	}

	MY_AWESOME_MOD_API void uninstall_mod(RC::CppUserModBase* mod)
	{
		delete mod;
	}
}