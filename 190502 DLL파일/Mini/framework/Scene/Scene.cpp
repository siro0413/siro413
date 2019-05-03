#include "Framework.h"
#include "Scene.h"
#include "./Component/Camera.h"
#include "./Object/Rect.h"

Scene::Scene(Context * context)
    : context(context)
    , name("")
{
    camera = new Camera(context);
    cameraBuffer = new ConstantBuffer(context);
    cameraBuffer->Create<CameraData>();

    rect1 = new Rect(context);
}

Scene::~Scene()
{
    SAFE_DELETE(rect1);

    SAFE_DELETE(cameraBuffer);
    SAFE_DELETE(camera);
}

void Scene::Update()
{
    camera->Update();

    auto data = cameraBuffer->Map<CameraData>();
    {
        D3DXMatrixTranspose(&data->View, &camera->GetViewMatrix());
        D3DXMatrixTranspose(&data->Proj, &camera->GetProjMatrix());
    }
    cameraBuffer->Unmap();

    rect1->Update();
}

void Scene::Render()
{
    cameraBuffer->BindPipeline(ShaderStage::VS, 0);
    rect1->Render();
}
