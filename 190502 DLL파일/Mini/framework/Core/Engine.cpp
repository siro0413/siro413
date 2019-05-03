#include "Framework.h"
#include "Engine.h"

Engine::Engine()
{
    context         = new Context();
    timer           = context->RegisterSubsystem<Timer>();
    input           = context->RegisterSubsystem<Input>();
    graphics        = context->RegisterSubsystem<Graphics>();
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
    timer->Update();
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
