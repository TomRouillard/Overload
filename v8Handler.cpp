#include "stdafx.h"
#include "v8Handler.h"
#include "overloadApp.h"

V8Handler::V8Handler(OverloadApp& overloadApp) : _overloadApp(overloadApp)
{
}

bool V8Handler::Execute(const CefString& name, CefRefPtr< CefV8Value > object, const CefV8ValueList& arguments, CefRefPtr< CefV8Value >& retval, CefString& exception)
{
	if (name == JS_FUNCTION_SYNCHRONIZE_VARIANT_KEY && arguments.size() == 1)
	{
		retval = utils::CefUtils::cefValueToV8Value(_overloadApp.getSynchronizedVariant(arguments[0]->GetStringValue()));
		return true;
	}
	
	CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(name);

	for (unsigned int i = 0; i < arguments.size(); i++)
	{
		if (arguments[i]->IsString())
		{
			message->GetArgumentList()->SetString(i, arguments[i]->GetStringValue().ToString());
		}
		else if (arguments[i]->IsInt())
		{
			message->GetArgumentList()->SetInt(i, arguments[i]->GetIntValue());
		}
		else if (arguments[i]->IsDouble())
		{
			message->GetArgumentList()->SetDouble(i, arguments[i]->GetDoubleValue());
		}
		else if (arguments[i]->IsBool())
		{
			message->GetArgumentList()->SetBool(i, arguments[i]->GetBoolValue());
		}
		else if (arguments[i]->IsFunction())
		{
			std::pair<CefRefPtr<CefV8Context>, CefRefPtr<CefV8Value> > callback(CefV8Context::GetEnteredContext(), arguments[i]);
			_callbacks[_callbacksId] = callback;
			message->GetArgumentList()->SetInt(i, _callbacksId++);
		}
	}

	_overloadApp.sendProcessMessage(message);
	return true;
}

void V8Handler::executeJavascriptCallback(CefRefPtr<CefListValue> params)
{
	int callbackId = params->GetInt(0);
	CefRefPtr<CefListValue> callbackParams = params->GetList(1);
	CefRefPtr<CefV8Context> context = _callbacks[callbackId].first;
	CefRefPtr<CefV8Value> function = _callbacks[callbackId].second;
	context->Enter();
	CefV8ValueList args = utils::CefUtils::cefListValueToCefV8ValueList(params);

	if (function->ExecuteFunctionWithContext(context, NULL, args) == NULL)
	{
		//fail
	}
	context->Exit();
	_callbacks.erase(callbackId);
}
