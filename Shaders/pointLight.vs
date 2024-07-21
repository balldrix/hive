#define NUM_LIGHTS 4

cbuffer ConstantBufferWorld : register(b0)
{
	matrix worldMatrix;
}

cbuffer ConstantBufferView : register(b1)
{
	matrix viewMatrix;
}

cbuffer ConstantBufferProjection : register(b2)
{
	matrix projectionMatrix;
}

cbuffer LightPositionBuffer : register(b3)
{
	float4 lightPosition[NUM_LIGHTS];
};

struct VertextInputType
{
	float4 position : POSITION;	// semantics set in the input layout element desc
	float2 texcoord : TEXCOORD0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
	float3 lightPos[NUM_LIGHTS] : TEXCOORD1;
};

PixelInputType PointLightVertexShader(VertextInputType input)
{
	PixelInputType output = (PixelInputType)0;
	float4 worldPosition;
	int i;
	
	output.position.w = 1.0f;
	output.position = mul(mul(mul(input.position, worldMatrix), viewMatrix), projectionMatrix);
	output.texcoord = input.texcoord;

	worldPosition = mul(input.position, worldMatrix);

	for(i = 0; i < NUM_LIGHTS; i++)
	{
		output.lightPos[i] = lightPosition[i].xyz;
	}

	return output;
}
