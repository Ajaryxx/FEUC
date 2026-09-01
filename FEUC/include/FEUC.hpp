#pragma once

class BaseModule;

struct Result
{
	std::unique_ptr<BaseModule> module;
	
	inline bool HasError() const { return !ErrorMessage.empty(); }
	inline void SetErrorMessage(const std::string& str) { ErrorMessage = str; }
	inline std::string GetErrorMessage() const { return ErrorMessage; }

private:
	std::string ErrorMessage;

};

class FEUC
{
public:
	FEUC(const std::vector<std::string>& args);
	~FEUC();

	void Run();

public:

private:
	Result GetModuleFromCMDL();
	

private:
	std::vector<std::string> m_args;

	static bool m_ErrorState;
	static std::string m_ErrString;
};