#include "stdafx.h"
#include "webview.h"
#include "serverManager.h"
#include "overload.h"
INITIALIZE_EASYLOGGINGPP

int _tmain(int argc, _TCHAR* argv[])
{
	Webview::configureCEF();
	Overload overload;
	overload.start();
	Webview::closeCEF();
	return 0;
}

