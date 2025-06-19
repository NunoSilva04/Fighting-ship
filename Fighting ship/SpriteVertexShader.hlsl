cbuffer worldViewProj
{
    float4x4 WVP;
};

struct VS_input
{
    float3 input_position : POSITION;
    float2 input_texcoord : TEXCOORD;
};

struct VS_output
{
    float4 output_position : SV_Position;
    float2 output_texcoord : TEXCOORD;
};

VS_output main(VS_input input)
{
    VS_output output;
    
    output.output_position = mul(float4(input.input_position, 1.0f), WVP);
    output.output_texcoord = input.input_texcoord;
    
    return output;
}