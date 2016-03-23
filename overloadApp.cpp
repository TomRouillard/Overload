#include "stdafx.h"
#include "OverloadApp.h"

OverloadApp::OverloadApp()
{
	_browser = nullptr;
	_v8Handler = nullptr;

	_functionNames.push_back(JS_FUNCTION_SYNCHRONIZE_VARIANT_KEY);

}

void OverloadApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
	REQUIRE_UI_THREAD();
	_v8Handler = new V8Handler(*this);
	if (frame->IsMain())
	{
		CefRefPtr<CefV8Value> object = context->GetGlobal();

		for (std::size_t i = 0; i < _functionNames.size(); i++)
		{
			object->SetValue(_functionNames[i], CefV8Value::CreateFunction(_functionNames[i], _v8Handler.get()), V8_PROPERTY_ATTRIBUTE_NONE);
		}
	}	
	_browser = browser;
}

bool OverloadApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
	std::string functionName = message->GetName().ToString();
	CefRefPtr<CefListValue> arguments = message->GetArgumentList();

	if (functionName == IPC_REGISTER_FUNCTION_KEY)
	{
		registerFunctions(arguments);
	}
	else if (functionName == IPC_SYNCHRONIZE_VARIANT_KEY)
	{
		registerVariant(arguments->GetString(0), arguments->GetValue(1));
	}
	else if (functionName == IPC_EXECUTE_CALLBACK_KEY)
	{
		if (_v8Handler != NULL)
		{
			_v8Handler->executeJavascriptCallback(arguments);
		}
	}

	return true;
}

void OverloadApp::sendProcessMessage(CefRefPtr<CefProcessMessage> message)
{
	if (_browser.get() && _browser != nullptr)
	{
		_browser->SendProcessMessage(PID_BROWSER, message);
	}
}

void OverloadApp::registerFunctions(CefRefPtr<CefListValue> functionNames)
{
	if (_browser != nullptr)
	{
		CefRefPtr<CefV8Context> currentContext = _browser->GetMainFrame()->GetV8Context();
		currentContext->Enter();
		CefRefPtr<CefV8Value> object = currentContext->GetGlobal();

		for (std::size_t i = 0; i < functionNames->GetSize(); i++)
		{
			std::string functionName = functionNames->GetString(i).ToString();
			object->SetValue(functionName, CefV8Value::CreateFunction(functionName, _v8Handler.get()), V8_PROPERTY_ATTRIBUTE_NONE);
			_functionNames.push_back(functionName);
		}

		currentContext->Exit();
	}
	else
	{
		for (std::size_t i = 0; i < functionNames->GetSize(); i++)
		{
			_functionNames.push_back(functionNames->GetString(i).ToString());
		}
	}
}

CefRefPtr<CefValue> OverloadApp::getSynchronizedVariant(std::string key)
{
	if (_synchronizedValues.find(key) != _synchronizedValues.end())
	{
		return _synchronizedValues[key];
	}
	CefRefPtr<CefValue> value = CefValue::Create();
	value->SetNull();
	return value;
}

void OverloadApp::registerVariant(std::string key, CefRefPtr<CefValue> variant)
{
	_synchronizedValues[key] = variant;
}