#include "Framework.h"
#include "FileSystem.h"
#include <filesystem>

using namespace std::filesystem;

//find()                - 주어진 문자열이 존재하는 위치 - 정방향
//rfind()               - 주어진 문자열이 존재하는 위치 - 역방향
//find_first_of()       - 주어진 문자중에 하나라도 걸리는 첫번째 위치
//find_last_of()        - 주어진 문자중에 하나라도 걸리는 마지막 위치
//find_first_not_of()   - 주어진 문자가 아닌 문자가 하나라도 걸리는 첫번째 위치
//find_last_not_of()    - 주어진 문자가 아닌 문자가 하나라도 걸리는 마지막 위치

auto FileSystem::Create_Directory(const std::string & path) -> const bool
{
    auto result = false;

    try
    {
        result = create_directories(path);
    }
    catch (filesystem_error error)
    {
        MessageBoxA(nullptr, error.what(), "ERROR!!", MB_OK);
    }

    return result;
}

auto FileSystem::Delete_Directory(const std::string & path) -> const bool
{
    auto result = false;

    try
    {
        result = remove_all(path) > 0;
    }
    catch (filesystem_error error)
    {
        MessageBoxA(nullptr, error.what(), "ERROR!!", MB_OK);
    }

    return result;
}

auto FileSystem::Delete_File(const std::string & path) -> const bool
{
    if (IsDirectory(path))
        return false;

    auto result = false;

    try
    {
        result = remove(path);
    }
    catch (filesystem_error error)
    {
        MessageBoxA(nullptr, error.what(), "ERROR!!", MB_OK);
    }

    return result;
}

auto FileSystem::Copy_File(const std::string & src, const std::string & dst) -> const bool
{
    if (src == dst)
        return false;

    if (!IsExistDirectory(GetDirectoryFromPath(dst)))
        Create_Directory(GetDirectoryFromPath(dst));

    auto result = false;

    try
    {
        result = copy_file(src, dst, copy_options::overwrite_existing);
    }
    catch (filesystem_error error)
    {
        MessageBoxA(nullptr, error.what(), "ERROR!!", MB_OK);
    }

    return result;
}

auto FileSystem::IsDirectory(const std::string & path) -> const bool
{
    auto result = false;

    try
    {
        result = is_directory(path);
    }
    catch (filesystem_error error)
    {
        MessageBoxA(nullptr, error.what(), "ERROR!!", MB_OK);
    }

    return result;
}

auto FileSystem::IsExistDirectory(const std::string & path) -> const bool
{
    auto result = false;

    try
    {
        result = exists(path);
    }
    catch (filesystem_error error)
    {
        MessageBoxA(nullptr, error.what(), "ERROR!!", MB_OK);
    }

    return result;
}

auto FileSystem::IsExistFile(const std::string & path) -> const bool
{
    auto result = false;

    try
    {
        result = exists(path);
    }
    catch (filesystem_error error)
    {
        MessageBoxA(nullptr, error.what(), "ERROR!!", MB_OK);
    }

    return result;
}

auto FileSystem::GetFileNameFromPath(const std::string & path) -> const std::string
{
    //../_Assets/Texture/Tree.png  -------------------> Tree.png

    auto lastIndex = path.find_last_of("\\/");
    auto fileName = path.substr(lastIndex + 1, path.length());

    return fileName;
}

auto FileSystem::GetIntactFileNameFromPath(const std::string & path) -> const std::string
{
    //../_Assets/Texture/Tree.png  -------------------> Tree

    auto fileName = GetFileNameFromPath(path);
    auto lastIndex = fileName.find_last_of('.');
    auto intactFileName = fileName.substr(0, lastIndex);

    return intactFileName;
}

auto FileSystem::GetDirectoryFromPath(const std::string & path) -> const std::string
{
    //../_Assets/Texture/Tree.png  -------------------> ../_Assets/Texture/
    
    auto lastIndex = path.find_last_of("\\/");
    auto directory = path.substr(0, lastIndex + 1);

    return directory;
}

auto FileSystem::GetExtensionFromPath(const std::string & path) -> const std::string
{
    //../_Assets/Texture/Tree.png  -------------------> .png

    auto lastIndex = path.find_last_of('.');

    if (lastIndex != std::string::npos)
        return path.substr(lastIndex, path.length());

    return "N/A";
}

auto FileSystem::GetPathWithoutExtension(const std::string & path) -> const std::string
{
    //../_Assets/Texture/Tree.png  -------------------> ../_Assets/Texture/Tree

    auto directory = GetDirectoryFromPath(path);
    auto fileName = GetIntactFileNameFromPath(path);

    return directory + fileName;
}

auto FileSystem::GetRelativeFromPath(const std::string & absolute_path) -> const std::string
{
    //절대 경로를 만듬
    path p = absolute(absolute_path);
    path r = absolute(GetWorkingDirectory());

    //루트 경로가 다를경우 절대경로 반환
    if (p.root_path() != r.root_path())
        return p.generic_string();

    path result;

    //두 경로가 갈라지는 지점을 체크
    path::const_iterator iter_path = p.begin();
    path::const_iterator iter_relative = r.begin();

    while (
        *iter_path == *iter_relative &&
        iter_path != p.end() &&
        iter_relative != r.end())
    {
        iter_path++;
        iter_relative++;
    }

    //relative에 남은 각 토큰에대해 ..을 추가
    if (iter_relative != r.end())
    {
        iter_relative++;
        while (iter_relative != r.end())
        {
            result /= "..";
            iter_relative++;
        }
    }

    //남은 경로 추가
    while (iter_path != p.end())
    {
        result /= *iter_path;
        iter_path++;
    }

    return result.generic_string();
}

auto FileSystem::GetParentDirectory(const std::string & path) -> const std::string
{
    auto found = path.find_last_of("\\/");
    auto result = path;

    if (found == std::string::npos)
        return path;

    if (found == path.length() - 1)
    {
        result = result.substr(0, found - 1);
        return GetParentDirectory(result);
    }

    return result.substr(0, found) + "/";
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