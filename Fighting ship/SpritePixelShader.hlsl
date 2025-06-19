Texture2D spriteTexture : register(t1);
SamplerState spriteSamplerState : register(s1);

struct PS_input
{
    float4 inPosition : SV_Position;
    float2 inTexCoord : TEXCOORD;
};

float4 main(PS_input input) : SV_Target
{
    return spriteTexture.Sample(spriteSamplerState, input.inTexCoord);
}