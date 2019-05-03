#include "stdafx.h"
#include "Rect.h"

Rect::Rect()
{
	size.x = 100;
	size.y = 100;
	pos.x = 0;
	pos.y = 0;

	vertices = new VertexColor[4];
	vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); //0
	vertices[1].position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f); //1
	vertices[2].position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f); //2
	vertices[3].position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f); //3
}

Rect::Rect(Graphics * graphics, D3DXCOLOR color)
	:graphics(graphics)
{
	Setdir();

	std::random_device rd;
	std::mt19937 re(rd());

	std::uniform_real_distribution<float> range(50, 100);
	size.x = range(re);
	size.y = range(re);

	if (size.x != 0 && size.y != 0)
	{
		std::uniform_real_distribution<float> range(-550, 550);
		pos.x = range(re);
	}

	if (pos.x != 0)
	{
		std::uniform_real_distribution<float> range(-270, 270);
		pos.y = range(re);
	}
	//-------------------------------------------------------
	/*
		1    3

		0    2
	*/

	//Create Vertex Data
	{
		vertices = new VertexColor[4];
		vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); //0

		vertices[1].position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f); //1

		vertices[2].position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f); //2

		vertices[3].position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f); //3

		_color = color;

		for (int i = 0; i < 4; i++)
		{
			vertices[i].color = _color;
		}
	}

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(VertexColor) * 4;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = vertices;

		HRESULT hr = graphics->GetDevice()->CreateBuffer
		(
			&desc,
			&subData,
			&vertexBuffer
		);
		assert(SUCCEEDED(hr));
	}

	//Create Index Data
	{
		indices = new UINT[6]{ 0, 1, 2, 2, 1, 3 };
	}

	//Create Index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(UINT) * 6;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = indices;

		HRESULT hr = graphics->GetDevice()->CreateBuffer
		(
			&desc,
			&subData,
			&indexBuffer
		);
		assert(SUCCEEDED(hr));
	}

	//Create Vertex Shader
	{
		HRESULT hr = D3DX11CompileFromFileA
		(
			"Color.hlsl",
			nullptr,
			nullptr,
			"VS",
			"vs_5_0",
			0,
			0,
			nullptr,
			&vsBlob,
			nullptr,
			nullptr
		);
		assert(SUCCEEDED(hr));

		hr = graphics->GetDevice()->CreateVertexShader
		(
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			nullptr,
			&vertexShader
		);
		assert(SUCCEEDED(hr));
	}

	//Create Pixel Shader
	{
		HRESULT hr = D3DX11CompileFromFileA
		(
			"Color.hlsl",
			nullptr,
			nullptr,
			"PS",
			"ps_5_0",
			0,
			0,
			nullptr,
			&psBlob,
			nullptr,
			nullptr
		);
		assert(SUCCEEDED(hr));

		hr = graphics->GetDevice()->CreatePixelShader
		(
			psBlob->GetBufferPointer(),
			psBlob->GetBufferSize(),
			nullptr,
			&pixelShader
		);
		assert(SUCCEEDED(hr));
	}

	//Create InputLayout
	{
		D3D11_INPUT_ELEMENT_DESC layoutDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		HRESULT hr = graphics->GetDevice()->CreateInputLayout
		(
			layoutDescs,
			2,
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			&inputLayout
		);
		assert(SUCCEEDED(hr));
	}

	//Create World, View, Projection
	{
		D3DXMatrixIdentity(&world);
		D3DXMatrixIdentity(&view);
		D3DXMatrixIdentity(&proj);

		D3DXMatrixLookAtLH
		(
			&view,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 1),
			&D3DXVECTOR3(0, 1, 0)
		);

		D3DXMatrixOrthoLH
		(
			&proj,
			Settings::Get().GetWindowWidth(),
			Settings::Get().GetWindowHeight(),
			0.0f,
			1.0f
		);


	}

	//Create Constant Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(TransformData);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = graphics->GetDevice()->CreateBuffer
		(
			&desc,
			nullptr,
			&cbuffer
		);
		assert(SUCCEEDED(hr));
	}

	//Create Rasterizer State
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_BACK;
		desc.FrontCounterClockwise = false;

		HRESULT hr = graphics->GetDevice()->CreateRasterizerState
		(
			&desc,
			&rsState
		);
		assert(SUCCEEDED(hr));
	}
}

void Rect::init(Graphics * graphics, D3DXCOLOR color)
{
	this->graphics = graphics;

	{
		for (int i = 0; i < 4; i++)
		{
			vertices[i].color = color;
		}
	}

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(VertexColor) * 4;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = vertices;

		HRESULT hr = graphics->GetDevice()->CreateBuffer
		(
			&desc,
			&subData,
			&vertexBuffer
		);
		assert(SUCCEEDED(hr));
	}

	//Create Index Data
	{
		indices = new UINT[6]{ 0, 1, 2, 2, 1, 3 };
	}

	//Create Index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(UINT) * 6;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = indices;

		HRESULT hr = graphics->GetDevice()->CreateBuffer
		(
			&desc,
			&subData,
			&indexBuffer
		);
		assert(SUCCEEDED(hr));
	}

	//Create Vertex Shader
	{
		HRESULT hr = D3DX11CompileFromFileA
		(
			"Color.hlsl",
			nullptr,
			nullptr,
			"VS",
			"vs_5_0",
			0,
			0,
			nullptr,
			&vsBlob,
			nullptr,
			nullptr
		);
		assert(SUCCEEDED(hr));

		hr = graphics->GetDevice()->CreateVertexShader
		(
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			nullptr,
			&vertexShader
		);
		assert(SUCCEEDED(hr));
	}

	//Create Pixel Shader
	{
		HRESULT hr = D3DX11CompileFromFileA
		(
			"Color.hlsl",
			nullptr,
			nullptr,
			"PS",
			"ps_5_0",
			0,
			0,
			nullptr,
			&psBlob,
			nullptr,
			nullptr
		);
		assert(SUCCEEDED(hr));

		hr = graphics->GetDevice()->CreatePixelShader
		(
			psBlob->GetBufferPointer(),
			psBlob->GetBufferSize(),
			nullptr,
			&pixelShader
		);
		assert(SUCCEEDED(hr));
	}

	//Create InputLayout
	{
		D3D11_INPUT_ELEMENT_DESC layoutDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		HRESULT hr = graphics->GetDevice()->CreateInputLayout
		(
			layoutDescs,
			2,
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			&inputLayout
		);
		assert(SUCCEEDED(hr));
	}

	//Create World, View, Projection
	{
		D3DXMatrixIdentity(&world);
		D3DXMatrixIdentity(&view);
		D3DXMatrixIdentity(&proj);

		D3DXMatrixLookAtLH
		(
			&view,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 1),
			&D3DXVECTOR3(0, 1, 0)
		);

		D3DXMatrixOrthoLH
		(
			&proj,
			Settings::Get().GetWindowWidth(),
			Settings::Get().GetWindowHeight(),
			0.0f,
			1.0f
		);

	}

	//Create Constant Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(TransformData);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = graphics->GetDevice()->CreateBuffer
		(
			&desc,
			nullptr,
			&cbuffer
		);
		assert(SUCCEEDED(hr));
	}

	//Create Rasterizer State
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_BACK;
		desc.FrontCounterClockwise = false;

		HRESULT hr = graphics->GetDevice()->CreateRasterizerState
		(
			&desc,
			&rsState
		);
		assert(SUCCEEDED(hr));
	}
}



Rect::~Rect()
{
	SAFE_RELEASE(rsState);
	SAFE_RELEASE(cbuffer);
	SAFE_RELEASE(inputLayout);
	SAFE_RELEASE(psBlob);
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(pixelShader);
	SAFE_RELEASE(vertexShader);
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(vertexBuffer);
	SAFE_DELETE_ARRAY(indices);
	SAFE_DELETE_ARRAY(vertices);
}

void Rect::Update()
{
	if (playing)
	{
		D3DXMATRIX S, R, T;
		D3DXMatrixScaling(&S, size.x, size.y, 1);
		D3DXMatrixTranslation(&T, pos.x, pos.y, 0);

		world = S * T;

		D3DXMatrixTranspose(&data.World, &world);
		D3DXMatrixTranspose(&data.View, &view);
		D3DXMatrixTranspose(&data.Proj, &proj);

		rectPos.top = pos.y + size.y * 0.5f;
		rectPos.bottom = pos.y - size.y * 0.5f;
		rectPos.right = pos.x + size.x * 0.5f;
		rectPos.left = pos.x - size.x * 0.5f;

		D3D11_MAPPED_SUBRESOURCE subResource;
		graphics->GetDeviceContext()->Map
		(
			cbuffer,
			0,
			D3D11_MAP_WRITE_DISCARD,
			0,
			&subResource
		);

		memcpy(subResource.pData, &data, sizeof(TransformData));

		graphics->GetDeviceContext()->Unmap(cbuffer, 0);
	}
}

void Rect::Update2()
{
	if (playing)
	{
		D3DXMATRIX S, R, T;
		D3DXMatrixScaling(&S, size.x, size.y, 1);
		D3DXMatrixTranslation(&T, pos.x, pos.y, 0);

		world = S * T;

		D3DXMatrixTranspose(&data.World, &world);
		D3DXMatrixTranspose(&data.View, &view);
		D3DXMatrixTranspose(&data.Proj, &proj);

		rectsPos.top = pos.y + size.y * 0.5f;
		rectsPos.bottom = pos.y - size.y * 0.5f;
		rectsPos.right = pos.x + size.x * 0.5f;
		rectsPos.left = pos.x - size.x * 0.5f;

		D3D11_MAPPED_SUBRESOURCE subResource;
		graphics->GetDeviceContext()->Map
		(
			cbuffer,
			0,
			D3D11_MAP_WRITE_DISCARD,
			0,
			&subResource
		);

		memcpy(subResource.pData, &data, sizeof(TransformData));

		graphics->GetDeviceContext()->Unmap(cbuffer, 0);
	}
}

void Rect::autoMove()
{
	if (playing)
	{
		std::random_device rd;
		std::mt19937 re(rd());

		//enum
		//{
		//	UP, RIGHT, DOWN, LEFT, URIGHT, DRIGHT, DLEFT, ULEFT
		//};

		switch (dir)
		{
		case 0:
		{
			pos.y += 2;
			break;
		}
		case 1:
		{
			pos.x += 2;
			break;
		}
		case 2:
		{
			pos.y -= 2;
			break;
		}
		case 3:
		{
			pos.x -= 2;
			break;
		}
		case 4:
		{
			pos.y += 2;
			pos.x += 2;
			break;
		}
		case 5:
		{
			pos.y -= 2;
			pos.x += 2;
			break;
		}
		case 6:
		{
			pos.y -= 2;
			pos.x -= 2;
			break;
		}
		case 7:
		{
			pos.y += 2;
			pos.x -= 2;
			break;
		}
		}

		bool bCheck = false;
		bCheck |= pos.x <= -570;
		bCheck |= pos.x >= 570;
		bCheck |= pos.y <= -290;
		bCheck |= pos.y >= 290;

		if (bCheck)
		{
			if (dir == 0)
			{
				pos.y -= 2;
			}
			if (dir == 1)
			{
				pos.x -= 2;
			}
			if (dir == 2)
			{
				pos.y += 2;
			}
			if (dir == 3)
			{
				pos.x += 2;
			}
			if (dir == 4)
			{
				pos.y -= 2;
				pos.x -= 2;
			}
			if (dir == 5)
			{
				pos.y += 2;
				pos.x -= 2;
			}
			if (dir == 6)
			{
				pos.y += 2;
				pos.x += 2;
			}
			if (dir == 7)
			{
				pos.y -= 2;
				pos.x += 2;
			}
		}

		if (bCheck)
		{
			std::random_device rd;
			std::mt19937 re(rd());
			std::uniform_int_distribution<int> range(0, 7);

			int tempDir = range(re);

			dir = tempDir;
		}
	}

}

void Rect::Render()
{
	if (playing)
	{
		UINT stride = sizeof(VertexColor);
		UINT offset = 0;

		graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		graphics->GetDeviceContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		graphics->GetDeviceContext()->IASetInputLayout(inputLayout);
		graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		graphics->GetDeviceContext()->VSSetShader(vertexShader, nullptr, 0);
		graphics->GetDeviceContext()->VSSetConstantBuffers(0, 1, &cbuffer);

		graphics->GetDeviceContext()->RSSetState(rsState);

		graphics->GetDeviceContext()->PSSetShader(pixelShader, nullptr, 0);

		graphics->GetDeviceContext()->DrawIndexed(6, 0, 0);
	}
}

void Rect::Setdir()
{
	std::random_device rd;
	std::mt19937 re(rd());

	std::uniform_int_distribution<int> range(0, 7);
	dir = range(re);
}