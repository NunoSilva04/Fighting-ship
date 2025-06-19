struct PS_input
{
    float4 input_position : SV_Position;
    float4 input_color : COLOR;
};

float4 main(PS_input input) : SV_Target
{
    return input.input_color;
}