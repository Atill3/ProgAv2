#pragma once

/** librairie utilisée par l'engin.
 */
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

/** Les versions de l'engin durant le cours:
 *	MAJOR : la version de votre groupe (c'est la 3e fois que je redonne ce cours)
 *  MINOR : changements au projet de base (probablement à tous les cours)
 *  REVISION : changements durant la phase jeu ou entre les cours.
 */
#define BART_ENGINE_VERSION_MAJOR 3
#define BART_ENGINE_VERSION_MINOR 0
#define BART_ENGINE_VERSION_REVISION 1
#define BART_ENGINE_VERSION_STRING "3.0.1"

 /** Redéfinition du new pour voir les fuites de mémoire
  */
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;