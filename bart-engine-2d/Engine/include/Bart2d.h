#pragma once

/** 
 *  Les versions de l'engin durant le cours:
 *	MAJOR : la version de votre groupe
 *  MINOR : changements au projet de base
 *  REVISION : changements durant la phase jeu ou entre les cours.
 */
constexpr auto BART_ENGINE_VERSION_MAJOR = 4;
constexpr auto BART_ENGINE_VERSION_MINOR = 0;
constexpr auto BART_ENGINE_VERSION_REVISION = 0;
constexpr auto BART_ENGINE_VERSION_STRING = "4.0.0";

/** 
 * Redéfinition du new pour voir les fuites de mémoire
 */
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;
