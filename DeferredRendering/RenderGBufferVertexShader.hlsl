cbuffer ConstantBuffer: register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
}

struct GBufferVertexShaderInput
{
	float3 Position : POSITION0;
	float3 Normal : NORMAL0;
	float2 TexCoord : TEXCOORD0;
	//float3 Binormal : BINORMAL0;
	//float3 Tangent : TANGENT0;
};

struct GBufferVertexShaderOutput
{
	float4 Position : SV_POSITION;
	float3 Normal : NORMAL0;
	float2 TexCoord : TEXCOORD0;
	float2 Depth : TEXCOORD1;
	//float3x3 tangentToWorld : TEXCOORD2;
};

GBufferVertexShaderOutput main(GBufferVertexShaderInput input)
{
	GBufferVertexShaderOutput output = (GBufferVertexShaderOutput)0;

	float4 worldPosition = mul(float4(input.Position.xyz, 1.0f), World);
	float4 viewPosition = mul(worldPosition, View);
	output.Position = mul(viewPosition, Projection);

	output.Normal = input.Normal;

	output.TexCoord = input.TexCoord;

	output.Depth.x = output.Position.z;
	output.Depth.y = output.Position.w;

	// Calculate tangent space to world space matrix using the world space tanget, binormal and normal as basis vector.
	//output.tangentToWorld[0] = mul(float4(input.Tangent, 1.0), World).xyz;
	//output.tangentToWorld[1] = mul(float4(input.Binormal, 1.0), World).xyz;
	//output.tangentToWorld[2] = mul(float4(input.Normal, 1.0), World).xyz;

	return output;
}