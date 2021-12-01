#ifndef STDAFX_H
#define STDAFX_H

// Custom types:
typedef          bool      bool8;

typedef          char      char8;

typedef signed   char      int8;
typedef signed   short     int16;
typedef signed   int       int32;
typedef signed   long long int64;

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

typedef float              float32;
typedef double             float64;

// C++:
#include <optional>
#include <string>
#include <memory>
#include <queue>
#include <bitset>
#include <random>
#include <chrono>
#include <fstream>

// Windows:
#define NOMINMAX
#include <windows.h>

// DirectX9:
#include <d3d9.h>
#include <d3dx9.h>

// Assimp:
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <assimp/cimport.h>

#endif // STDAFX_H