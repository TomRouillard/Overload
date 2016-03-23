#include "stdafx.h"
#include "webview.h"
#include "overloadApp.h"
#include "jsFunctionManager.h"

Webview::Webview(HWND hwnd, std::string windowName)
{
	CefWindowInfo info;

	RECT rect;
	rect.bottom = 1080;
	rect.top = 0;
	rect.left = 0;
	rect.right = 1920;
	//GetWindowRect(hwnd, &rect);
	info.SetAsChild(hwnd, rect);
	CefBrowserSettings browserSettings;
	browserSettings.caret_browsing = STATE_ENABLED;
	browserSettings.universal_access_from_file_urls = STATE_ENABLED;
	browserSettings.web_security = STATE_DISABLED;
	CefBrowserHost::CreateBrowserSync(info, this, "", browserSettings, nullptr);
}

Webview::~Webview()
{
}

void Webview::close()
{
	REQUIRE_UI_THREAD();
	if (_browser.get())
	{
		_browser->StopLoad();
		_browser->GetHost()->CloseBrowser(true);
	}
}

void Webview::registerFunction(std::string name, std::unique_ptr<JSFunction> function)
{
	_jsFunctionManager.addFunction(name, std::move(function));
}

void Webview::loadUrl(std::string url)
{
	if (_browser.get())
	{
		_browser->GetMainFrame()->LoadURL(url);
	}
	else
	{
		_url = url;
	}
}

void Webview::synchronizeVariant(std::string key, Variant variant)
{
	CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(IPC_SYNCHRONIZE_VARIANT_KEY);
	message.get()->GetArgumentList().get()->SetString(0, key);
	message.get()->GetArgumentList().get()->SetValue(1, utils::CefUtils::variantToCefValue(variant));
	_browser->SendProcessMessage(PID_RENDERER, message);
}

bool Webview::OnProcessMessageReceived(CefRefPtr< CefBrowser > browser, CefProcessId source_process, CefRefPtr< CefProcessMessage > message)
{
	std::string functionName = message.get()->GetName().ToString();

	CefRefPtr<CefListValue> params = message.get()->GetArgumentList();
	std::vector<Variant> arguments = utils::CefUtils::cefListToVariantList(params);
	_jsFunctionManager.executeFunction(*this, functionName, arguments);

	return true;
}

void Webview::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	REQUIRE_UI_THREAD();
	if (!_browser.get())
	{
		_browser = browser;
		if (_url != "")
		{
			loadUrl(_url);
		}
	}
}

void Webview::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	REQUIRE_UI_THREAD();

	if (_browser->GetIdentifier() == browser->GetIdentifier())
	{
		_browser = nullptr;
	}
}

void Webview::configureCEF()
{
	CefRefPtr<OverloadApp> app(new OverloadApp);
	CefSettings settings;
	settings.remote_debugging_port = 9222;
	CefString(&settings.locale) = "fr";
	settings.multi_threaded_message_loop = false;

	CefMainArgs main_args;
	int exitCode = CefExecuteProcess(main_args, app.get(), NULL);
	if (exitCode >= 0)
	{
		std::exit(0);
	}

	CefInitialize(main_args, settings, app.get(), NULL);
}

void Webview::updateWebviews()
{
	CefDoMessageLoopWork();
}

void Webview::closeCEF()
{
	CefShutdown();
}