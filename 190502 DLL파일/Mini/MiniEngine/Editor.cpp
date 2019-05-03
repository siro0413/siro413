#include "stdafx.h"
#include "Editor.h"
#include "Core/Engine.h"
Editor::Editor()
{
	engine = new Engine();
	context = engine->GetContext();
	graphics = context->GetSubsystem<Graphics>();
}

Editor::~Editor()
{
}

void Editor::Resize(const uint & width, const uint & height)
{
}

void Editor::Update()
{
}

void Editor::Render()
{
}
