#pragma once

class Transform final
{
public:
	Transform(class Context* context);
	~Transform();

	/*--------------------------------*/
	//Local
	/*--------------------------------*/
	auto GetLocalScale()const -> const D3DXVECTOR3&{ return local_scale; }
	void SetLocalScale(const D3DXVECTOR3& local_scale);

	auto GetLocalRotation()const -> const D3DXVECTOR3& { return local_rotation; }
	void SetLocalRotation(const D3DXVECTOR3& local_rotation);

	auto GetLocalTranslation()const -> const D3DXVECTOR3& { return local_translation; }
	void SetLocalTranslation(const D3DXVECTOR3& local_translation);

	auto GetLocalMatrix() const -> const D3DMATRIX& { return local; }
	/*--------------------------------*/
	//World
	/*--------------------------------*/
	//�θ� ������ local ������
	//world�� local�� ��ǥ�� �ٸ� �θ� �ִٸ�
	//P(local)*m -> P(world)
	auto GetScale() -> const D3DXVECTOR3;
	void SetScale(const D3DXVECTOR3& world_scale);

	auto GetRotation() -> const D3DXVECTOR3;
	void SetRotation(const D3DXVECTOR3& world_rotation);

	auto GetTranslation() -> const D3DXVECTOR3;
	void SetTranslation(const D3DXVECTOR3& world_translation);

	auto GetWorldMatrix() const -> const D3DXMATRIX& { return world; }
	auto GetWorldRotationMatrix()-> const D3DXMATRIX;


	/*--------------------------------*/
	//Math
	/*--------------------------------*/
	auto GetEulerAngle(const D3DXQUATERNION& quaternion)->const D3DXVECTOR3;


	/*--------------------------------*/
	//Transform
	/*--------------------------------*/
	auto GetParent()const -> Transform* { return parent; }
	void SetParent(Transform* newParent) { this->parent = newParent; }
	/*���� �θ�� �ڽİ��踦 ��Ȯ���˱����ؼ�
	�¾��̹����� ���� ���� �����̹��� �ֱ� ���̵���
	�����ֺ����� ��*/ 

	auto HasParent() const -> const bool { return parent ? true : false; }
	auto HasChilds() const -> const bool { return !childs.empty(); }
	
	void UpdateTransform();


private:
	class Context* context;
	D3DXVECTOR3 local_scale;
	D3DXVECTOR3 local_rotation;
	D3DXVECTOR3 local_translation;
	//���� locla_~~�� ��ģ�� local
	// S*R*T �� ����
	D3DXMATRIX local;
	D3DXMATRIX world;
	
	Transform* parent;
	std::vector<Transform*> childs;

};

