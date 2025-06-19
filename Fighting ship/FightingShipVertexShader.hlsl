cbuffer WorldViewProjection
{
    float4x4 WVP;
};

struct VS_input
{
    float3 inputPosition : POSITION;
    float2 inputTexCoord : TEXCOORD;
};

struct VS_output
{
    float4 outputPosition : SV_Position;
    float2 outputTexCoord : TEXCOORD;
};

VS_output main(VS_input input)
{
    VS_output output;

    output.outputPosition = mul(float4(input.inputPosition, 1.0f), WVP);
    output.outputTexCoord = input.inputTexCoord;
    
    return output;
}