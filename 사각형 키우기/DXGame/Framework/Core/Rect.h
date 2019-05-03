#pragma once

struct VertexColor
{
	D3DXVECTOR3 position;
	D3DXCOLOR color;
};

struct rtPos
{
	float left;
	float top;
	float bottom;
	float right;
};

class Rect
{
public:
	Rect();
	Rect(class Graphics* graphics, D3DXCOLOR color);
	void init(class Graphics* graphics, D3DXCOLOR color);
	//void init2(class Graphics* graphics);
	~Rect();

	void Update();
	void Update2();
	void autoMove();
	void Render();

	void Setdir();

	rtPos rectPos;
	rtPos rectsPos;

	int dir = 0;
	bool playing = true;

private:
	friend class Game;
	class Graphics* graphics;

	//------------------------------
	VertexColor* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT* indices;
	ID3D11Buffer* indexBuffer;

	ID3D11VertexShader* vertexShader;
	ID3DBlob* vsBlob;

	ID3D11PixelShader* pixelShader;
	ID3DBlob* psBlob;

	ID3D11InputLayout* inputLayout;

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX proj;

	struct TransformData
	{
		D3DXMATRIX World;
		D3DXMATRIX View;
		D3DXMATRIX Proj;
	}data;
	ID3D11Buffer* cbuffer;

	ID3D11RasterizerState* rsState;

	D3DXVECTOR2 size;
	D3DXVECTOR2 pos;
	D3DXCOLOR _color;
};