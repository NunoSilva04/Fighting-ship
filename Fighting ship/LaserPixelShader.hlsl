Texture2D myTexture : register(t4);
SamplerState mySampler : register(s4);

struct PS_input
{
    float4 input_position : SV_Position;
    float2 input_texCoord : TEXCOORD;
};

float4 main(PS_input input) : SV_Target
{
    return myTexture.Sample(mySampler, input.input_texCoord);
}