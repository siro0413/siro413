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


	//필요한 함수를 뽑아오는것
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
	//static_assert 컴파일때 오류를 잡아냄
	static_assert(std::is_base_of<ISubsystem, T>::value, "Provided type dose not implement Isubsystem"); 
	for (auto& subsystem : subsystems)
	{ //부모가 캐스팅되기전 함수가나옴?? 조사하고 수정
		if (typeid(T) == typeid(*subsystem))
			return static_cast<T*>(subsystem);
	}
	return nullptr;
}
