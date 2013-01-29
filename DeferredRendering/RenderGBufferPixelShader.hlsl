cbuffer ConstantBuffer: register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
}

struct GBufferVertexShaderOutput
{
	float4 Position : SV_POSITION;
	float3 Normal : NORMAL0;
	float2 TexCoord : TEXCOORD0;
	float2 Depth : TEXCOORD1;
	//float3x3 tangentToWorld : TEXCOORD2;
};

struct GBufferPixelShaderOutput
{
	half4 Color : COLOR0;
	half4 Normal : COLOR1;
	half4 Depth: COLOR2;
};

GBufferPixelShaderOutput main(GBufferVertexShaderOutput input) : SV_TARGET
{
	GBufferPixelShaderOutput output;

	output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);//tex2D(diffuseSampler, input.TexCoord);
	
	//float4 specularAttributes = tex2D(specularSampler, input.TexCoord);

	// Specular intensity.
	output.Color.a = 0.0f;//specularAttributes.r;

	//// Read the normal from the normal map.
	//float3 normalFromMap = tex2D(normalSampler, input.TexCoord);
	float3 normalFromMap = input.Normal;
	//
	//// Transform to [1, 1].
	//normalFromMap = 2.0f * normalFromMap - 1.0f;

	//// Transform into world space.
	//normalFromMap = mul(normalFromMap, input.tangentToWorld);
	normalFromMap = mul(normalFromMap, World);

	//// Normalize the result.
	normalFromMap = normalize(normalFromMap);

	// Output the normal in [0, 1] space.
	output.Normal.rgb = 0.5f * (normalFromMap + 1.0f);

	// Specular Power.
	output.Normal.a = 1.0f;//specularAttributes.a;

	// Depth.
	output.Depth = input.Depth.x / input.Depth.y;

	return output;
}