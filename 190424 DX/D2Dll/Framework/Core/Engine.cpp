#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
    context  = new Context();
    graphics = context->RegisterSubsystem<Graphics>();
    input    = context->RegisterSubsystem<Input>();
	sManager = context->RegisterSubsystem<SceneManager>();
    context->Intialize();
}// 

Engine::~Engine()
{
    SAFE_DELETE(context);
}

void Engine::Update()
{
    input->Update();
	sManager->Update();
}

void Engine::Render()
{
    graphics->BeginScene();
    {
		sManager->Render();
    }
    graphics->EndScene();
}
