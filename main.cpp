#include "stdafx.h"
#include "webview.h"
#include "serverManager.h"
#include "overload.h"
INITIALIZE_EASYLOGGINGPP

int _tmain(int argc, _TCHAR* argv[])
{
	Webview::configureCEF();
	el::Loggers::addFlag(el::LoggingFlag::AutoSpacing);
	Overload overload;
	overload.start();
	Webview::closeCEF();
	return 0;
}

