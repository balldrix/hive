#pragma once

#include "pch.h"

#include "GlobalConstants.h"

using namespace GlobalConstants;

namespace ConstantBuffers
{
	struct WorldMatrixBuffer
	{
		Matrix worldMatrix;
	};

	struct ViewMatrixBuffer
	{
		Matrix viewMatrix;
	};

	struct ProjectionMatrixBuffer
	{
		Matrix projectionMatrix;
	};

	struct LightPositionBuffer
	{
		XMFLOAT4 lightPosition[NumLights];
	};

	struct LightColorBuffer
	{
		XMFLOAT4 diffuseColor[NumLights];
	};
}