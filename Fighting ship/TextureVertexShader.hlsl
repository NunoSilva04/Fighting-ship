cbuffer worldCb
{
    float4x4 WVP;
};

struct VS_input
{
    float3 inPosition : POSITION;
    float2 inTextCoord : TEXCOORD;
};

struct VS_output
{
    float4 outPosition : SV_Position;
    float2 outTextCoord : TEXCOORD;
};

VS_output main(VS_input input)
{
    VS_output output;
    
    output.outPosition = mul(float4(input.inPosition, 1.0f), WVP);
    output.outTextCoord = input.inTextCoord;
    
    return output;
}