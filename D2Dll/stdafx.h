#pragma once

//window
#include <Windows.h>
#include <assert.h>

//STL
#include <vector>
typedef unsigned int uint;
typedef unsigned long ulong;


//DirectX
#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>


#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")


//Macro Funtion
#define SAFE_RELEASE(p)         { if (p) { (p)->Release(); (p) = nullptr; } }
#define SAFE_DELETE(p)          { if (p) { delete (p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p)    { if (p) { delete[] (p); (p) = nullptr; } }



//Main system
#include "Pramwork/core/Settings.h"
#include "Pramwork/core/Context.h"

//subsystem
#include "Pramwork/core/subsystem/Graphics.h"