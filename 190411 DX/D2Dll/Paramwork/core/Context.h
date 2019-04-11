#pragma once
#include "stdafx.h"
#include "subsystem/isubsystem.h"
class  Context final
{
public:
	Context() = default;
	~Context()
	{
		//for (auto& subsystem : subsystems)
			//SAFE_DELETE(subsystem);
		for (int i = static_cast<int>(subsystems.size() - 1); 1 >= 0; i--) //������ üũ�ϱ����� int unsigend�� �����÷ο� �Ͼ
			SAFE_DELETE(subsystems[i]);

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
	static_assert(std::is_base_of<ISubsystem, T>::value, "Provided type dose not implement Isubsystem");
	return static_cast<T*> (subsystems.emplace_back(new T(this))); 
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
