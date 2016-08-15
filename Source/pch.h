// pch.h
// Christopher Ball 2016
// my pre compiled header file

#ifndef _PCH_H
#define _PCH_H

// includes needed for windows and directx projects
#include <Windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <mmsystem.h>

#include <d3d11.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dcompiler.h>

#include <SimpleMath.h>

#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#include "Audio.h"
#include "SpriteBatch.h"

#include "Time.h"

using namespace DirectX;
using namespace SimpleMath;

#endif _PCH_H
