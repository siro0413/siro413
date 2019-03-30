#include "stdafx.h"
#include "status.h"


status::status()

{
}

status::~status()
{
}

void status::Render()
{
	Renderer::Get().Render(this);
}

