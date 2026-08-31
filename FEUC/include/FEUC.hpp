#pragma once

class FEUC
{
public:
	FEUC(const std::vector<std::string>& args);
	~FEUC();

	int Run();

private:

	std::vector<std::string> m_args;
};