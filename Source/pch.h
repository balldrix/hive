// pch.h
// Christopher Ball 2016
// my pre compiled header file

#ifndef _PCH_H
#define _PCH_H

// includes needed for windows and directx projects
#include <Windows.h>
#include <mmsystem.h>

#include <d3d11.h>
#include <d3dcompiler.h>

#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>

#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#include "Audio.h"

// we must specify the exact location for the audio libray as it's now a legacy directx sdk
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2.h> 

#include "Time.h"

using namespace DirectX;
using namespace SimpleMath;

#endif _PCH_H
