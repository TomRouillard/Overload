#include "stdafx.h"
#include "webview.h"
#include "serverManager.h"
#include "overload.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Webview::configureCEF();
	Overload overload;
	overload.start();
	Webview::closeCEF();
	return 0;
}

