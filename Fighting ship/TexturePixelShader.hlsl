Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

struct PS_input
{
    float4 inPosition : SV_Position;
    float2 inTextCoord : TEXCOORD;
};

float4 main(PS_input input) : SV_Target
{
    return myTexture.Sample(mySampler, input.inTextCoord);
}