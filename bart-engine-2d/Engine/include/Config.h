#pragma once

#define _USE_SDL

#ifdef _USE_SDL
#include <SdlGraphics.h>
#include <SdlTimer.h>
#include <SdlInput.h>
#else
// ?
#endif

#ifdef _DEBUG
#include <ConsoleLogger.h>
#else
	#include <FileLogger.h>
#endif

#include <SceneService.h>
#include <MathService.h>
