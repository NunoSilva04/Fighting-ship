cbuffer worldCb
{
    float4x4 WVP;
};

struct VS_input
{
    float3 input_position : POSITION;
    float4 input_color : COLOR;
};

struct VS_output
{
    float4 output_position : SV_Position;
    float4 output_color : COLOR;
};

VS_output main(VS_input input)
{
    VS_output output;
    
    output.output_position = mul(float4(input.input_position, 1.0f), WVP);
    output.output_color = input.input_color;
    
    return output;
}