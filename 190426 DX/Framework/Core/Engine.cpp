#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
    context         = new Context();
    graphics        = context->RegisterSubsystem<Graphics>();
    input           = context->RegisterSubsystem<Input>();
					  context->RegisterSubsystem<ResourceManager>();
    sceneManager    = context->RegisterSubsystem<SceneManager>();

    context->Intialize(); 
}

Engine::~Engine()
{
    SAFE_DELETE(context);
}

void Engine::Update()
{
    input->Update();
    sceneManager->Update();
}

void Engine::Render()
{
    graphics->BeginScene();
    {
        sceneManager->Render();
    }
    graphics->EndScene();
}
