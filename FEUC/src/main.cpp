#include "PCH.hpp"
#include "FEUC.hpp"

int main(int argc, char* argv[])
{
	std::vector<std::string> args;
	for (size_t i = 0; i < argc; i++)
		args.push_back(argv[i]);

	FEUC feuc(args);
	feuc.Run();

	return EXIT_SUCCESS;
}