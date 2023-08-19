#pragma once
#include <string>
#include <Helpers/String.hpp>
#include <ExceptionHandling.hpp>
#include <DynamicOutput/Output.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UObjectArray.hpp>
#include <Unreal/UFunction.hpp>
#include <Unreal/UPackage.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/UClass.hpp>
#include <Unreal/FFrame.hpp>
#include <Unreal/FField.hpp>
#include <Unreal/AActor.hpp>
#include <Unreal/Hooks.hpp>


#include <Unreal/Property/NumericPropertyTypes.hpp>
#include <Unreal/Property/FStructProperty.hpp>
#include <Unreal/Property/FBoolProperty.hpp>
#include <Unreal/Property/FNameProperty.hpp>
#include <Unreal/Property/FTextProperty.hpp>
#include <Unreal/Property/FEnumProperty.hpp> 
#include <Unreal/Property/FStrProperty.hpp>

#include <Unreal/Property/FArrayProperty.hpp>
#include <Unreal/Property/FMapProperty.hpp>
#include <Unreal/Property/FSetProperty.hpp>

#include <Unreal/UScriptStruct.hpp>
#include <Unreal/FScriptArray.hpp>
#include <Unreal/UEnum.hpp>
#include <Mod/CppUserModBase.hpp>

#define MOD_NAME STR("SloMoMod")

#define LOG(S, ...) { Output::send<LogLevel::Normal>(STR("[") MOD_NAME STR("] ") STR(##S) STR("\n"), __VA_ARGS__); }
#define LOG_EXPR(...) { LOG(#__VA_ARGS__ L" = {}", __VA_ARGS__); }

#define DAUTO decltype(auto)
// From UML
#define BPFUNCTION(Function) void Function(UObject* Context, Extensions::FFrameExtended* Stack, void* RESULT_DECL)

#define CALL_BPFUNCTION(FunctionToCall) FunctionToCall(Context, Stack, RESULT_DECL)