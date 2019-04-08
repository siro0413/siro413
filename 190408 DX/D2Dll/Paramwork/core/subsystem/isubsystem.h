#pragma once
#include "stdafx.h"

class ISubsystem
{
public:
	ISubsystem(Context* context)
		:context(context)
	{}

	virtual ~ISubsystem() = default;

	virtual const bool Initialize() = 0;


protected:
	Context * context;
};