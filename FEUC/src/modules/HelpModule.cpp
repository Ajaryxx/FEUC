#include "PCH.hpp"
#include "modules/HelpModule.hpp"

HelpModule::HelpModule(const std::vector<std::string>& args) : BaseModule(args)
{

}

HelpModule::~HelpModule()
{

}
void HelpModule::Output(const std::string& str)
{
	std::cout << str << std::endl;
}

void HelpModule::StartConvertUnit()
{

	std::string out = R"(Fast-Easy-Unit-Converter
Usage:
Modules)";


	//We just output the help text and ignore arguments after help
	//Output(out);
	
}
