#pragma once
#include "stdafx.h"

enum class ShaderStage : uint
{
    VS, PS, GS, CS,
};

struct CameraData
{
	D3DXMATRIX View;
	D3DXMATRIX Proj;
};

struct WorldData
{
	D3DXMATRIX World;
};