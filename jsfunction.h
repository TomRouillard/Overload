#pragma once

#include "variant.h"

class Webview;
class JSFunction
{
public:
	virtual void execute(Webview& webview, std::vector<Variant> arguments) = 0;
};