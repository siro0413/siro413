cbuffer TansformBuffer : register(b0)
{
    //row_major ���켱�� ��켱���� �ٲ��
   matrix World;
   matrix View;
   matrix Proj;
};




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
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Proj);
    output.Color = input.Color;

    return output;

}

//OM������ ��ȭ�� ��8���� ��𿡾�����
float4 PS(PixelInput input) :SV_Target
{
    return input.Color;
}