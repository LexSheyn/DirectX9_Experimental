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
#include <iostream>
#include <io.h>
#include <fcntl.h>

// Windows:
#define NOMINMAX
#include <windows.h>

// DirectX9:
#include <d3d9.h>
#include <d3dx9.h>

// Disable warnings from FBX SDK:
#pragma warning( push ) // FBX SDK - Begin
#pragma warning( disable : 4701)
#pragma warning( disable : 4702)
#pragma warning( disable : 4703)
#pragma warning( disable : 26451)
#pragma warning( disable : 26495)
#pragma warning( disable : 26812)

// Autodesk FBX SDK:
#include <fbxsdk.h>

#pragma warning( pop ) // FBX SDK - End

// ImGui:
//#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx9.h"

#endif // STDAFX_H