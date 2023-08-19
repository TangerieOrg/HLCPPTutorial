#include "Extensions.hpp"

namespace ModUtils::Extensions {

bool UBlueprintGeneratedClassExtended::ExHasInterface(std::wstring const& InterfaceName)
{
	if (this->GetInterfaces().Num() == 0) return false;
	for (auto interf : this->GetInterfaces()) {
		if (interf.Class->GetName() == InterfaceName) return true;
	}
	return false;
}

}