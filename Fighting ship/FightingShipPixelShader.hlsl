SamplerState mySampler : register(s2);
Texture2D myTexture : register(t2);

struct PS_input
{
    float4 inputPosition : SV_Position;
    float2 inputTexCoord : TEXCOORD;
};

float4 main(PS_input input) : SV_Target
{
    return myTexture.Sample(mySampler, input.inputTexCoord);
}