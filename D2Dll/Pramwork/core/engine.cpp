#include "stdafx.h"
#include "engine.h"

Engine::Engine()
{
	context = new Context();
	graphics = context->RegisterSubsystem<Graphics>(); 

	context->Intialize(); //Graphics�� Intialize�� �ҷ�����
}

Engine::~Engine()
{
	SAFE_DELETE(context);
}

void Engine::Update()
{

}

void Engine::Render()
{
	//auto graphics = context->GetSubsystem<Graphics>();
	graphics->BeginScene();
	{

	}
	graphics->EndScene();
}
