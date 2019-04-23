#pragma once

#ifdef _DEBUG
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")


#endif // _DEBUG 콘솔을 사용하게해주는 정리되어있는 명령어


//window
#include <Windows.h>
#include <assert.h>
//STL
#include <typeinfo>
#include <iostream>
#include <vector>
#include <functional>
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

//Utility
#include "Pramwork/Utilty/FileSystem.h"

//Main system
#include "Pramwork/core/Settings.h"
#include "Pramwork/core/Context.h"

//Basic Data
#include "Pramwork/core/D3D11/BasicData/D3D11Config.h"
#include "Pramwork/core/D3D11/BasicData/Vertex.h"
#include "Pramwork/core/D3D11/BasicData/Geometry.h"

//subsystem
#include "Pramwork/core/subsystem/Input.h"
#include "Pramwork/core/subsystem/Graphics.h"

//D3D11 Wrapper class
#include "Pramwork/core/D3D11/IAStage/VertexBuffer.h"
#include "Pramwork/core/D3D11/IAStage/IndexBuffer.h"
#include "Pramwork/core/D3D11/IAStage/InputLayout.h"
#include "Pramwork/core/D3D11/ShaderSatge/PixelShader.h"
#include "Pramwork/core/D3D11/ShaderSatge/VertexShader.h"
#include "Pramwork/core/D3D11/ShaderSatge/ConstantBuffer.h"
