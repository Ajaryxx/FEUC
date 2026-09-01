#include "PCH.hpp"
#include "modules/LenghtModule.hpp"

LenghtModule::LenghtModule(const std::vector<std::string>& args) : BaseModule(args)
{

}

LenghtModule::~LenghtModule()
{

}
void LenghtModule::Output(const std::string& str)
{
	std::cout << str << std::endl;
}

void LenghtModule::StartConvertUnit()
{
	ParseArguments(std::vector<std::string>({ "cm", "dm", "km"}));
}
