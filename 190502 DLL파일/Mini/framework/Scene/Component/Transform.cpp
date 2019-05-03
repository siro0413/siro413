#include "Framework.h"
#include "Transform.h"
//크기는 0이되면안된다 따라서 초기값은 1
Transform::Transform(Context * context)
 : context(context)
 ,local_scale(1,1,1)
 ,local_rotation(0, 0, 0)
 ,local_translation(0, 0, 0)
 ,parent(nullptr)
{
	D3DXMatrixIdentity(&local);
	D3DXMatrixIdentity(&world);

}

Transform::~Transform()
{
}

void Transform::SetLocalScale(const D3DXVECTOR3 & local_scale)
{
	if (this->local_scale = local_scale)
		return;

	this->local_scale = local_scale;
	UpdateTransform();
	//이럴경우 쓸대없는계산이 일어남
	//스케일이 변하지않을때 그래서 걸러줘야함 
}

void Transform::SetLocalRotation(const D3DXVECTOR3 & local_rotation)
{
	if (this->local_rotation = local_rotation)
		return;

	this->local_rotation = local_rotation;
	UpdateTransform();
}

void Transform::SetLocalTranslation(const D3DXVECTOR3 & local_translation)
{
	if (this->local_translation = local_translation)
		return;

	this->local_translation = local_translation;
	UpdateTransform();
}

auto Transform::GetScale() -> const D3DXVECTOR3
{
	D3DXVECTOR3 scale;
	D3DXMatrixDecompose
	(
		//world view 등등을 분리해줌
		&scale,
		&D3DXQUATERNION(),
		&D3DXVECTOR3(),
		&world
	);
	return scale;
}

void Transform::SetScale(const D3DXVECTOR3 & world_scale)
{
	if (GetScale() == world_scale)
		return;
	if (HasParent())
	{
		D3DXVECTOR3 parent_scale = parent->GetScale();
		D3DXVECTOR3 scale;

		scale.x = world_scale.x / parent_scale.x;
		scale.y = world_scale.y / parent_scale.y;
		scale.z = world_scale.z / parent_scale.z;

		SetLocalScale(scale);
	}
	else
		SetLocalScale(world_scale);
}

auto Transform::GetRotation() -> const D3DXVECTOR3
{
	D3DXQUATERNION rotation;
	D3DXMatrixDecompose
	(
		//world view 등등을 분리해줌
		&D3DXVECTOR3(),
		&rotation,
		&D3DXVECTOR3(),
		&world
	);

	auto temp = GetEulerAngle(rotation);

	return D3DXVECTOR3
	(
		Math::ToRadian(temp.x),
		Math::ToRadian(temp.y),
		Math::ToRadian(temp.z)
	);
		
}

void Transform::SetRotation(const D3DXVECTOR3 & world_rotation)
{
	if (GetRotation() == world_rotation)
		return;

	if (HasParent())
	{
		D3DXMATRIX inverse;
		D3DXMatrixInverse(&inverse, nullptr, &parent->GetWorldRotationMatrix());

		D3DXVECTOR3 rotation;
		D3DXVec3TransformNormal(&rotation, &world_rotation, &inverse);

		SetLocalRotation(rotation);
	}
	else
		SetLocalRotation(world_rotation);
}

auto Transform::GetTranslation() -> const D3DXVECTOR3
{
	D3DXVECTOR3 translation;
	D3DXMatrixDecompose
	(
		//world view 등등을 분리해줌
		&D3DXVECTOR3(),
		&D3DXQUATERNION(),
		&translation,
		&world
	);
	return translation;
}

void Transform::SetTranslation(const D3DXVECTOR3 & world_translation)
{
	if (GetTranslation() == world_translation)
		return;

	if (HasParent())
	{
		D3DXMATRIX inverse;
		D3DXMatrixInverse(&inverse, nullptr, &parent->GetWorldMatrix());
		
		D3DXVECTOR3 translation;
		D3DXVec3TransformCoord(&translation, &world_translation, &inverse);
		SetLocalTranslation(translation);
	}
	else
		SetLocalTranslation(world_translation);
}

auto Transform::GetWorldRotationMatrix() -> const D3DXMATRIX
{
	D3DXMATRIX R;
	D3DXQUATERNION quaternion;
	D3DXMatrixDecompose(&D3DXVECTOR3(), &quaternion, &D3DXVECTOR3(), &world);

	D3DXMatrixRotationQuaternion(&R, &quaternion);

	return R;
}


auto Transform::GetEulerAngle(const D3DXQUATERNION & quaternion) -> const D3DXVECTOR3
{
	float x = quaternion.x;
	float y = quaternion.y;
	float z = quaternion.z;
	float w = quaternion.w;

	// Order of rotations: Z first, then X, then Y
	float check = 2.0f * (-y * z + w * x);

	if (check < -0.995f)
	{
		return D3DXVECTOR3
		(
			-90.0f,
			0.0f,
			-atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * Math::TO_DEG
		);
	}

	if (check > 0.995f)
	{
		return D3DXVECTOR3
		(
			90.0f,
			0.0f,
			atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * Math::TO_DEG
		);
	}

	return D3DXVECTOR3
	(
		asinf(check) * Math::TO_DEG,
		atan2f(2.0f * (x * z + w * y), 1.0f - 2.0f * (x * x + y * y)) * Math::TO_DEG,
		atan2f(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z)) * Math::TO_DEG
	);
}

void Transform::UpdateTransform()
{
	D3DXMATRIX S, R, T;
	D3DXMatrixScaling(&S, local_scale.x, local_scale.y, local_scale.z);
	D3DXMatrixRotationZ(&R, local_rotation.z);
	D3DXMatrixTranslation(&T, local_translation.x, local_translation.y, local_translation.z);

	local = S * R * T;
	if (HasParent())
		world = local * parent->GetWorldMatrix();
	else
		world = local;

	for (const auto&childs : childs)
		childs->UpdateTransform();
}
