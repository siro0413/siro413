#pragma once

class VertexBuffer final
{
public:
	VertexBuffer(class Context* context);
	~VertexBuffer();


	//default �� ��ȣ���� �ָ��ؼ� ����Ұ�� �������� �����ʱ�
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
	//�����ϳ��� ũ��
	stride = sizeof(T);
	vertexCount = vertices.size();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	switch (usage)
	{
	case D3D11_USAGE_IMMUTABLE: //GPU���� �б⸸ ����.CPU���� ���� ����!
	case D3D11_USAGE_DEFAULT:	//GPU�� ���ؼ� �а� ���� ������ ����.
		desc.CPUAccessFlags = 0;
		break;
	case D3D11_USAGE_DYNAMIC:	//GPU���� �б⸸, CPU������ ���⸸
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_STAGING:	//GPU���� CPU�� ���� ����. (�����ٰ��� �а���)
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		break;

	}

	desc.Usage = usage;
	//usage������ �ٲ�¾�(���̳���)
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
