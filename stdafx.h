// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#define _CRT_SECURE_NO_DEPRECATE
#include <vector>
#include <stdio.h>
#include <tchar.h>
#include <thread>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <psapi.h>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <direct.h>
#define GetCurrentDir _getcwd

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace web;
using namespace web::json;
using namespace web::http;
using namespace web::http::client;

#include <include/cef_client.h>
#include <include/cef_v8.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define ASSERT(condition) ((void)0)
#define REQUIRE_UI_THREAD()   ASSERT(CefCurrentlyOn(TID_UI));
#define REQUIRE_IO_THREAD()   ASSERT(CefCurrentlyOn(TID_IO));
#define REQUIRE_FILE_THREAD() ASSERT(CefCurrentlyOn(TID_FILE));

#include "utils.h"

// TODO: reference additional headers your program requires here
