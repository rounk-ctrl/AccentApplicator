// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <sstream>
#include <shellapi.h>
#include <iostream>
#include <Uxtheme.h>
#include <map>
#include <vsstyle.h>
#include <vssym32.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "uxtheme.lib")
