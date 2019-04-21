#pragma once

class VertexBuffer final
{
public:
	VertexBuffer(class Context* context);
	~VertexBuffer();


	//default 는 모호성이 애매해서 사용할경우 오버러드 하지않기
	template <typename T>
	void Create
	(
		const std::vector<T>& vertices,
		const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT
	);


	void Clear();
	void BindPipeline();

private:
	class Graphics* graphics;

	ID3D11Buffer* buffer;
	uint stride;
	uint offset;
	uint vertexCount;

};

template<typename T>
inline void VertexBuffer::Create(const std::vector<T>& vertices, const D3D11_USAGE & usage)
{
	//정점하나의 크기
	stride = sizeof(T);
	vertexCount = vertices.size();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	switch (usage)
	{
	case D3D11_USAGE_IMMUTABLE: //GPU에서 읽기만 가능.CPU에서 접근 급지!
	case D3D11_USAGE_DEFAULT:	//GPU에 의해서 읽고 쓰기 접근이 가능.
		desc.CPUAccessFlags = 0;
		break;
	case D3D11_USAGE_DYNAMIC:	//GPU에서 읽기만, CPU에서는 쓰기만
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_STAGING:	//GPU에서 CPU로 값을 전달. (양방향다가능 읽고쓰기)
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		break;

	}

	desc.Usage = usage;
	//usage에따라 바뀌는애(다이나믹)
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = stride * vertices.size();

	D3D11_SUBRESOURCE_DATA subDate;
	ZeroMemory(&subDate, sizeof(D3D11_SUBRESOURCE_DATA));
	subDate.pSysMem = vertices.data();

	auto hr = graphics->GetDevice()->CreateBuffer
	(
		&desc,
		&subDate,
		&buffer
	);
	assert(SUCCEEDED(hr));

}
