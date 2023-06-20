#pragma once

#include <Windows.h>
#include <stdlib.h>
#include "resource.h"

#define WINDOW_TITLE	"MU"
#define WINDOW_CLASS	"MainOption"

#define WINDOW_WIDTH	200		//160
#define WINDOW_HEIGHT	500		//340

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")