
struct VertexInput
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};

struct PixelInput
{
    //SV = ��ǻ�Ϳ� ���� ��ġ����
    float4 Position : SV_POSITION0;
    float4 Color : COLOR0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = input.Position;
    output.Color = input.Color;

    return output;

}

//OM������ ��ȭ�� ��8���� ��𿡾�����
float4 PS(PixelInput input) :SV_Target
{
    return input.Color;
}