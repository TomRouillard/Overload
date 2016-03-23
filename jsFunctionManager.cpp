#include "stdafx.h"
#include "JSFunctionManager.h"

void JSFunctionManager::addFunction(std::string key, std::unique_ptr<JSFunction> function)
{
	if (!isFunctionRegistered(key))
	{
		_functions[key] = std::move(function);
	}
	else
	{
		std::cerr << "Function already registered: " << key << std::endl;
	}
}

void JSFunctionManager::executeFunction(Webview& webview, std::string key, std::vector<Variant> arguments)
{
	if (isFunctionRegistered(key))
	{
		auto function = _functions.find(key);
		function->second->execute(webview, arguments);
	}
	else
	{
		std::cerr << "Unregistered function: " << key << std::endl;
	}
}

bool JSFunctionManager::isFunctionRegistered(std::string key)
{
	return _functions.find(key) != _functions.end();
}