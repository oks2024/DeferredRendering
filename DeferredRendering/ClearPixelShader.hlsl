struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex: TEXCOORD0;
};

struct PixelShaderOutput
{
	float4 Color : COLOR0;
	float4 Normal : COLOR1;
	float4 Depth : COLOR2;
};

PixelShaderOutput main(PS_INPUT input) : SV_TARGET
{
	PixelShaderOutput output;

	//// Black color
	output.Color = 0.0f;
	output.Color.a = 0.0f;

	// White color
	/*output.Color = 1.0f;
	output.Color.a = 1.0f;*/


	// When transforming 0.5f into [-1;1], we will get 0.0f.
	output.Normal.rgb = 0.5f;

	// No specular power;
	output.Normal.a = 0.0f;

	// Max depth;
	output.Depth = 1.0f;

	return output;
}