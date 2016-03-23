#pragma once
#include "jsfunction.h"

class JSFunctionManager
{
public:
	void addFunction(std::string key, std::unique_ptr<JSFunction> function);

	void executeFunction(Webview& webview, std::string key, std::vector<Variant> arguments);

private:
	bool isFunctionRegistered(std::string key);

private:
	std::map<std::string, std::unique_ptr<JSFunction>> _functions;
};

