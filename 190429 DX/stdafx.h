#pragma once
#pragma warning(disable"4506")


#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

//Window
#include <Windows.h>
#include <assert.h>

//STL
#include <typeinfo>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <chrono>

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

typedef unsigned int uint;
typedef unsigned long ulong;

//Macro Function
#define SAFE_RELEASE(p)         { if (p) { (p)->Release(); (p) = nullptr; } }
#define SAFE_DELETE(p)          { if (p) { delete (p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p)    { if (p) { delete[] (p); (p) = nullptr; } }

//Utility
#include "./Framework/Utility/FileSystem.h"
#include "./Framework/Utility/Geometry_Generator.h"

//Main System
#include "./Framework/Core/Settings.h"
#include "./Framework/Core/Context.h"

//Basic Data
#include "./Framework/Core/D3D11/BasicData/D3D11_Config.h"
#include "./Framework/Core/D3D11/BasicData/Vertex.h"
#include "./Framework/Core/D3D11/BasicData/Geometry.h"

//Subsystem
#include "./Framework/Core/Subsystem/Input.h"
#include "./Framework/Core/Subsystem/Graphics.h"
#include "Framework/Core/Subsystem/ResourceManager.h"
#include "./Framework/Core/Subsystem/SceneManager.h"

//D3D11 Wrapper class
#include "./Framework/Core/D3D11/IAStage/VertexBuffer.h"
#include "./Framework/Core/D3D11/IAStage/IndexBuffer.h"
#include "./Framework/Core/D3D11/IAStage/InputLayout.h"
#include "./Framework/Core/D3D11/ShaderStage/VertexShader.h"
#include "./Framework/Core/D3D11/ShaderStage/PixelShader.h"
#include "./Framework/Core/D3D11/ShaderStage/ConstantBuffer.h"


//Resource
#include "Framework/Resource/Texture.h"
