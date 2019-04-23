cbuffer TansformBuffer : register(b0)
{
    //row_major 열우선을 행우선으로 바꿔라
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
    //SV = 컴퓨터에 찍을 위치지정
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

Texture2D SourceTexture1 : register(t0);
Texture2D SourceTexture2 : register(t1);


SamplerState samp: register(s0);

//OM에들어가는 도화지 총8장중 어디에쓸건지
float4 PS(PixelInput input) :SV_Target
{
    float4 color = 0;
    if(input.Uv.x<1.0f)
        color = SourceTexture1.Sample(samp, input.Uv);
    else
        color = SourceTexture2.Sample(samp, float2(input.Uv.x - 1.0f, input.Uv.y));


    return color;
}