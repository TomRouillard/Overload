#pragma once

class OverloadApp;
class V8Handler: public CefV8Handler
{
public:
	V8Handler(OverloadApp& overloadApp);

	virtual bool Execute(const CefString& name, CefRefPtr< CefV8Value > object, const CefV8ValueList& arguments, CefRefPtr< CefV8Value >& retval, CefString& exception) override;

	void executeJavascriptCallback(CefRefPtr<CefListValue> params);

private:
	OverloadApp& _overloadApp;
	std::map<int, std::pair<CefRefPtr<CefV8Context>, CefRefPtr<CefV8Value>>> _callbacks;
	int _callbacksId;

	IMPLEMENT_REFCOUNTING(V8Handler);
};

