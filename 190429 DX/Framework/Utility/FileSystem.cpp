#include "stdafx.h"
#include "FileSystem.h"
#include <filesystem>

using namespace std::filesystem;

//find()				- 주어진 문자열이 존재하는 위치 - 정방향 검색
// Hello world 에서 "wor"입력했을때 걸리는곳 world
//rfind()				- 주어진 문자열이 존재하는 위치 - 역방향 검색
//find_first_of()		- 주어진 문자열중에 하나라도 걸리는 첫번째 위치
//find_last_of()		- 주어진 문자열중에 하나라도 걸리는 마지막 위치
//find_first_not_of()	- 주어진 문자가 아닌 문자가 하나라도 걸리는 첫번째 위치
//find_last_not_of()	- 주어진 문자가 아닌 문자가 하나라도 걸리는 마지막 위치



auto FileSystem::Create_Directory(const std::string & path) -> const bool
{
	auto result = false;

	try //먼저 시도를 한후 오류가뜨면 catch에서 잡음
	{
		result = create_directories(path);
	}
	catch(filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "error", MB_OK);
	}

	return result;
}

auto FileSystem::Delete_Directory(const std::string & path) -> const bool
{
	auto result = false;

	try //먼저 시도를 한후 오류가뜨면 catch에서 잡음
	{
		//remove_all 정수값 uint max
		result = remove_all(path)>0;
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "error", MB_OK);
	}

	return result;
}

auto FileSystem::Delete_file(const std::string & path) -> const bool
{
	if (IsDirectory(path))
		return false;
	//폴더인지 파일인지 검사
	auto result = false;

	try //먼저 시도를 한후 오류가뜨면 catch에서 잡음
	{
		result = remove(path);
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "error", MB_OK);
	}

	return result;

}

auto FileSystem::Copy_file(const std::string & src, const std::string & dst) -> const bool
{
	if (src == dst)
		return false;

	if(!IsExostDorectory(GetDirectoryFromPath(dst))) // 파일이아닌 폴더경로가 필요한것
		Create_Directory(GetDirectoryFromPath(dst));


	auto result = false;

	try //먼저 시도를 한후 오류가뜨면 catch에서 잡음
	{
		result = copy_file(src,dst,copy_options::overwrite_existing);//존재하면 덮어써라
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "error", MB_OK);
	}

	return result;
}

auto FileSystem::IsDirectory(const std::string & path) -> const bool
{
	auto result = false;

	try //먼저 시도를 한후 오류가뜨면 catch에서 잡음
	{
		result = is_directory(path); //경로찾기
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "error", MB_OK);
	}

	return result;
}

auto FileSystem::IsExostDorectory(const std::string & path) -> const bool
{
	auto result = false;

	try //먼저 시도를 한후 오류가뜨면 catch에서 잡음
	{
		result = exists(path); //경로찾기
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "error", MB_OK);
	}

	return result;
}

auto FileSystem::IsExistFile(const std::string & path) -> const bool
{
	auto result = false;

	try //먼저 시도를 한후 오류가뜨면 catch에서 잡음
	{
		result = exists(path); //경로찾기
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "error", MB_OK);
	}

	return result;
}

auto FileSystem::GetFileNameFormPath(const std::string & path) -> const std::string
{
	//../_Assets/Texture/Tree.png ------> Tree.png 간단하게
	auto lastIndex = path.find_last_of("\\/");
	auto fileName = path.substr(lastIndex + 1, path.length());
	return fileName;
}
//온전한 파일네임
auto FileSystem::GetIntactFileNameFromPath(const std::string & path) -> const std::string
//../_Assets/Texture/Tree.png ------> Tree 확장자빼고
{
	auto filename = GetFileNameFormPath(path);
	auto lastIndex = filename.find_last_of('.');
	auto intactfilename = filename.substr(0, lastIndex);
	//lastIndex 라고하면 .전까지 +1 을해야 .이나옴 
	return intactfilename;
}

auto FileSystem::GetDirectoryFromPath(const std::string & path) -> const std::string
{
	//../_Assets/Texture/Tree.png ------> ../_Assets/Texture/
	auto lastIndex = path.find_last_of("\\/");
	auto directory = path.substr(0, lastIndex + 1);
	return directory;
}

auto FileSystem::GetExtensionFromPath(const std::string & path) -> const std::string
{
	//../_Assets/Texture/Tree.png ------> .png

	auto lastIndex = path.find_last_of('.');
	if (lastIndex != std::string::npos)
		return path.substr(lastIndex,path.length());
	return "N/A";
}

auto FileSystem::GetPathWithoutExtension(const std::string & path) -> const std::string
{
	//../_Assets/Texture/Tree.png ------> ../_Assets/Texture/Tree
	auto directory = GetDirectoryFromPath(path);
	auto filename = GetIntactFileNameFromPath(path);

	return directory + filename;
}

auto FileSystem::GetRelativeFromPath(const std::string & absolutePath) -> const std::string
{
	//절대 경로를 만듬
	path p = absolute(absolutePath);				//path p를 선언 후 absolute(absolutePath)로 초기화
	path r = absolute(GetWorkingDirectory());		//path r를 선언후 absolute(GetWorkingDirectory())로 초기화

	//루트 경로가 다를경우 절대경로 반환
		if (p.root_path() != r.root_path())			//만약 p와 r의 루트가 다를경우
			return p.generic_string();				// 스트링형식으로 변환

	path result; 

	//두 경로가 갈라지는 지점을 체크
	path::const_iterator iter_path = p.begin();		//const T*와 같은의미이며 iterator가 가르키는 대상을 수정하지못함 p.begin() 으로 초기화
	path::const_iterator iter_relative = r.begin(); 

	while (
		*iter_path == *iter_relative &&				//두개의 구성요소가 같고
		iter_path != p.end() &&						//모든 경로의 끝과
		iter_relative != r.end())					//공백전까지 반복하며
	{
		iter_path++;								//경로가 증가
		iter_relative++;							
	}

	//relative에 남은 각 토큰에대해 ..을 추가
	if (iter_relative != r.end()) //만약 iter_relative이 끝나지 않았다면
	{
		iter_relative++;  //계속 증가
		while (iter_relative != r.end()) //끝까지 반복이 된다면
		{
			result /= ".."; //..을 추가한다
			iter_relative++;//계속 증가
		}
	}

	//남은 경로 추가
	while (iter_path != p.end()) //iter_path를 끝까지 반복하며
	{
		result /= *iter_path; //iter_path에 공백이 생길때까지 result에 /를 붙인다
		iter_path++; //경로증가
	}

	return result.generic_string();
}

auto FileSystem::GetParentDirectory(const std::string & path) -> const std::string
{
	auto found = path.find_last_of("\\/"); // \//중에 하나라도 걸리면 멈춤
	auto result = path; 

	if (found == std::string::npos) //공백이라면
		return path; //반환

	if (found == path.length() - 1) //found의 값이 path의 값에서 1을 뺀것과 같을시
	{
		result = result.substr(0, found - 1); //result에 처음부터 found-1RKwl eodlq
		return GetParentDirectory(result); //result값을 넣고 다시 반환
	}

	return result.substr(0, found) + "/"; // /마지막에 /하나를 더추가한다
}

auto FileSystem::GetWorkingDirectory() -> const std::string
{
	
	return current_path().generic_string() + "/";
}

auto FileSystem::ToUpper(const std::string & lower) -> const std::string
{
    std::string upper;
    for (const auto& character : lower)
        upper += toupper(character);

    return upper;
}

auto FileSystem::ToLower(const std::string & upper) -> const std::string
{
    std::string lower;
    for (const auto& character : upper)
        lower += tolower(character);

    return lower;
}

auto FileSystem::ToString(const std::wstring & wstr) -> const std::string
{
    //과제 : 
    return std::string();
}

auto FileSystem::ToWstring(const std::string & str) -> const std::wstring
{
    std::wstring result;
    result.assign(str.begin(), str.end());

    return result;
}
