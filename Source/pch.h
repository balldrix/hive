// pch.h
// Christopher Ball 2018
// my pre compiled header file

#ifndef _PCH_H
#define _PCH_H

// includes needed for windows and directx projects
#include <Windows.h>
#include <mmsystem.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <GeometricPrimitive.h>

#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

#include "json.hpp"

#include "Time.h"

using namespace DirectX;
using namespace SimpleMath;

using json = nlohmann::json;

#endif _PCH_H
