#pragma once
#include "stdafx.h"

namespace D3D11_Helper
{
	inline const bool ShaderErrorHandler(const HRESULT& hr, ID3DBlob* error)
	{
		if (FAILED(hr)) //실패하면 오류메시지 
			//어디서 실패인지는 ID3DBlob* error에 들어있음
		{
			if (error)
			{
				std::string str = reinterpret_cast<const char*> (error->GetBufferPointer());
				MessageBoxA
				(
					nullptr,
					str.c_str(),
					"Shader Error",
					MB_OK
				);
			}
			return false;
		}

		return true;
	}

	inline const bool CompileShader
	(
		const std::string& path,
		const std::string& entryPoint, //shader의 시작점
		const std::string& shaderModel, //vertex인지 pixel인지
		D3D_SHADER_MACRO* defines,
		ID3DBlob** blob //더블포인터 무언가를 집어넣겠다.
	)
	{
#ifdef _DEBUG
		uint flags = D3DCOMPILE_ENABLE_STRICTNESS; //엄격한

#else
		uint flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_OPTIMIZATION_LEVEL3;
		//D3DCOMPILE_OPTIMIZATION_LEVEL3 컴파일 (최적화)
		//shader는 병렬

#endif //_DEBUG

		ID3DBlob* error = nullptr;
		auto hr = D3DCompileFromFile
		(
			FileSystem::ToWstring(path).c_str(),
			defines,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entryPoint.c_str(),
			shaderModel.c_str(),
			flags,
			0,
			blob,
			&error
		);

		auto result = ShaderErrorHandler(hr, error);
		assert(result);

		SAFE_RELEASE(error);

		return result;



	}


}