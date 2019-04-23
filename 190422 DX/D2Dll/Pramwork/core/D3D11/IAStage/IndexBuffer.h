#pragma once


class IndexBuffer final
{
public:
	IndexBuffer(class Context* context);
	~IndexBuffer();

	void Create
	(
		const std::vector<uint>& indices,
		const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT
	);
	void Clear();
	void BindPipeline();

private:
	class Graphics* graphics;
	ID3D11Buffer* buffer;
	uint offset;
	uint indexCount;
};

