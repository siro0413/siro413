#pragma once
#include "stdafx.h"
enum class ShaderStage :uint
{
	VS,PS,GS,CS,
};

struct TransformData
{
	D3DXMATRIX World;
	D3DXMATRIX View;
	D3DXMATRIX Proj;
};