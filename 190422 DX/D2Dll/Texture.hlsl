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
    float2 Uv : TEXCOORD0;
};

struct PixelInput
{
    //SV = ��ǻ�Ϳ� ���� ��ġ����
    float4 Position : SV_POSITION0;
    float2 Uv : TEXCOORD0;
};

PixelInput VS(VertexInput input)
{

    PixelInput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Proj);
    output.Uv = input.Uv;

    return output;

}

Texture2D SourceTexture : register(t0);
SamplerState samp: register(s0);

//OM������ ��ȭ�� ��8���� ��𿡾�����
float4 PS(PixelInput input) :SV_Target
{
    float4 color = SourceTexture.Sample(samp,input.Uv);

    //cliping
    //clip(color.a - 0.9f);


    return color;
}