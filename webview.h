#pragma once

#include "jsFunctionManager.h"

class Webview : public CefClient,
				public CefLifeSpanHandler
{
public:
	Webview(HWND hwnd, std::string windowName);

	~Webview();

	CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }

	void registerFunction(std::string name, std::unique_ptr<JSFunction> function);

	void loadUrl(std::string url);

	void close();

	void synchronizeVariant(std::string key, Variant variant);
	
	// CefClient methods
	bool OnProcessMessageReceived(CefRefPtr< CefBrowser > browser, CefProcessId source_process, CefRefPtr< CefProcessMessage > message) override;

	// CefLifeSpanHandler methods
	void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

	void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

	static void configureCEF();

	static void updateWebviews();

	static void closeCEF();

private:
	void injectFunction(std::string functionName);

	void updateSynchronizedValue(std::string key);

private:
	std::string _url;
	CefRefPtr<CefBrowser> _browser;
	JSFunctionManager _jsFunctionManager;
	std::vector<std::string> _registeredFunctions;
	IMPLEMENT_REFCOUNTING(Webview);
};

