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
	//부모가 없으면 local 과같음
	//world와 local의 자표는 다름 부모가 있다면
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
	/*과제 부모와 자식관계를 정확히알기위해서
	태양이미지를 만들어서 자전 지구이미지 넣기 같이돌기
	지구주변으로 달*/ 

	auto HasParent() const -> const bool { return parent ? true : false; }
	auto HasChilds() const -> const bool { return !childs.empty(); }
	
	void UpdateTransform();


private:
	class Context* context;
	D3DXVECTOR3 local_scale;
	D3DXVECTOR3 local_rotation;
	D3DXVECTOR3 local_translation;
	//위에 locla_~~을 합친게 local
	// S*R*T 가 로컬
	D3DXMATRIX local;
	D3DXMATRIX world;
	
	Transform* parent;
	std::vector<Transform*> childs;

};

