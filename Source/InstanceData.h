#pragma once

#include <DirectXMath.h>

using namespace DirectX;

struct InstanceType
{
	XMFLOAT4X4 position;
	XMFLOAT2 texOffset;
	XMFLOAT2 texScale;
};