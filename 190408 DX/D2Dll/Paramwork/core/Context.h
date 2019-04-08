#pragma once
#include "stdafx.h"
#include "subsystem/isubsystem.h"
class  Context final
{
public:
	Context() = default;
	~Context()
	{

	}
	template <typename T>
	T* RegisterSubsystem();


	//�ʿ��� �Լ��� �̾ƿ��°�
	template <typename T>
	T* GetSubsystem();
private:
	std::vector<ISubsystem*> subsystems;

};

template<typename T>
inline T * Context::RegisterSubsystem()
{
	return NULL;
}

template<typename T>
inline T * Context::GetSubsystem()
{
	//static_assert �����϶� ������ ��Ƴ�
	static_assert(std::is_base_of<ISubsystem, T>::value, "Provided type dose not implement Isubsystem"); 
	for (auto& subsystem : subsystems)
	{ //�θ� ĳ���õǱ��� �Լ�������?? �����ϰ� ����
		if (typeid(T) == typeid(*subsystem))
			return static_cast<T*>(subsystem);
	}
	return nullptr;
}
