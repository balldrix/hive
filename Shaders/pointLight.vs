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
	float3 position : POSITION;	// semantics set in the input layout element desc
	float2 texcoord : TEXCOORD;	
	row_major float4x4 instancePosition : INSTANCE_POSITION;
	float2 instanceUVOffset : INSTANCE_TEXOFFSET;
	float2 instanceUVScale : INSTANCE_TEXSCALE;
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
	int i;
	
	float4 instancePosition = mul(float4(input.position, 1.0f), input.instancePosition);
	output.position = mul(mul(mul(instancePosition, worldMatrix), viewMatrix), projectionMatrix);
	
	output.texcoord = input.texcoord * input.instanceUVScale;	
	output.texcoord += input.instanceUVOffset;
		
	for(i = 0; i < NUM_LIGHTS; i++)
	{
		output.lightPos[i] = lightPosition[i].xyz;
	}

	return output;
}
