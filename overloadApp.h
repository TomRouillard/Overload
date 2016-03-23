#pragma once
#include <include/cef_app.h>
#include "v8Handler.h"

#define JAVASCRIPT_API_FILE "js.api"
#define IPC_REGISTER_FUNCTION_KEY "registerFunction"
#define IPC_SYNCHRONIZE_VARIANT_KEY "synchronizeVariant"
#define IPC_EXECUTE_CALLBACK_KEY "executeCallback"
#define JS_FUNCTION_SYNCHRONIZE_VARIANT_KEY "getSynchronizedVariant"

class OverloadApp: public CefApp,
				   public CefBrowserProcessHandler,
				   public CefRenderProcessHandler
{
public:
	OverloadApp();

	// CefApp methods:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }

	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override { return this; }

	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override ;

	// CefBrowserProcessHandler methods:
	void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);

	void sendProcessMessage(CefRefPtr<CefProcessMessage> message);

	CefRefPtr<CefValue> getSynchronizedVariant(std::string key);

private:
	void registerFunctions(CefRefPtr<CefListValue> functionNames);

	void registerVariant(std::string key, CefRefPtr<CefValue> variant);

private:
	CefRefPtr<CefBrowser> _browser;
	CefRefPtr<V8Handler> _v8Handler;
	std::vector<std::string> _functionNames;
	std::map<std::string, CefRefPtr<CefValue>> _synchronizedValues;

	IMPLEMENT_REFCOUNTING(OverloadApp);
};

