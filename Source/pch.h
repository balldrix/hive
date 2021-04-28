#pragma once

#include <winsdkver.h>
#define _WIN32_WINNT 0x0601
#include <sdkddkver.h>

#define NOMINMAX
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP
#define NOMCX
#define NOSERVICE
#define NOHELP

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <wrl/client.h>
#include <mmsystem.h>

#include <d3d11_1.h>
#include <dxgi1_2.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <cstdint>
#include <cmath>
#include <exception>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <random>
#include <memory>
#include <stdexcept>
#include <SimpleMath.h>
#include "json.hpp"
#include <SpriteBatch.h>
#include <SpriteFont.h>

using namespace DirectX;
using namespace SimpleMath;

using json = nlohmann::json;

namespace DX
{
    inline void ThrowIfFailed(HRESULT hr)
    {
        if(FAILED(hr))
        {
            // Set a breakpoint on this line to catch DirectX API errors
            throw std::exception();
        }
    }
}