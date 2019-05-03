#include "stdafx.h"
#include "FileSystem.h"
#include <filesystem>

using namespace std::filesystem;

//find()				- �־��� ���ڿ��� �����ϴ� ��ġ - ������ �˻�
// Hello world ���� "wor"�Է������� �ɸ��°� world
//rfind()				- �־��� ���ڿ��� �����ϴ� ��ġ - ������ �˻�
//find_first_of()		- �־��� ���ڿ��߿� �ϳ��� �ɸ��� ù��° ��ġ
//find_last_of()		- �־��� ���ڿ��߿� �ϳ��� �ɸ��� ������ ��ġ
//find_first_not_of()	- �־��� ���ڰ� �ƴ� ���ڰ� �ϳ��� �ɸ��� ù��° ��ġ
//find_last_not_of()	- �־��� ���ڰ� �ƴ� ���ڰ� �ϳ��� �ɸ��� ������ ��ġ



auto FileSystem::Create_Directory(const std::string & path) -> const bool
{
	auto result = false;

	try //���� �õ��� ���� �������߸� catch���� ����
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

	try //���� �õ��� ���� �������߸� catch���� ����
	{
		//remove_all ������ uint max
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
	//�������� �������� �˻�
	auto result = false;

	try //���� �õ��� ���� �������߸� catch���� ����
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

	if(!IsExostDorectory(GetDirectoryFromPath(dst))) // �����̾ƴ� ������ΰ� �ʿ��Ѱ�
		Create_Directory(GetDirectoryFromPath(dst));


	auto result = false;

	try //���� �õ��� ���� �������߸� catch���� ����
	{
		result = copy_file(src,dst,copy_options::overwrite_existing);//�����ϸ� ������
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

	try //���� �õ��� ���� �������߸� catch���� ����
	{
		result = is_directory(path); //���ã��
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

	try //���� �õ��� ���� �������߸� catch���� ����
	{
		result = exists(path); //���ã��
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

	try //���� �õ��� ���� �������߸� catch���� ����
	{
		result = exists(path); //���ã��
	}
	catch (filesystem_error error)
	{
		MessageBoxA(nullptr, error.what(), "error", MB_OK);
	}

	return result;
}

auto FileSystem::GetFileNameFormPath(const std::string & path) -> const std::string
{
	//../_Assets/Texture/Tree.png ------> Tree.png �����ϰ�
	auto lastIndex = path.find_last_of("\\/");
	auto fileName = path.substr(lastIndex + 1, path.length());
	return fileName;
}
//������ ���ϳ���
auto FileSystem::GetIntactFileNameFromPath(const std::string & path) -> const std::string
//../_Assets/Texture/Tree.png ------> Tree Ȯ���ڻ���
{
	auto filename = GetFileNameFormPath(path);
	auto lastIndex = filename.find_last_of('.');
	auto intactfilename = filename.substr(0, lastIndex);
	//lastIndex ����ϸ� .������ +1 ���ؾ� .�̳��� 
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
	//���� ��θ� ����
	path p = absolute(absolutePath);				//path p�� ���� �� absolute(absolutePath)�� �ʱ�ȭ
	path r = absolute(GetWorkingDirectory());		//path r�� ������ absolute(GetWorkingDirectory())�� �ʱ�ȭ

	//��Ʈ ��ΰ� �ٸ���� ������ ��ȯ
		if (p.root_path() != r.root_path())			//���� p�� r�� ��Ʈ�� �ٸ����
			return p.generic_string();				// ��Ʈ���������� ��ȯ

	path result; 

	//�� ��ΰ� �������� ������ üũ
	path::const_iterator iter_path = p.begin();		//const T*�� �����ǹ��̸� iterator�� ����Ű�� ����� ������������ p.begin() ���� �ʱ�ȭ
	path::const_iterator iter_relative = r.begin(); 

	while (
		*iter_path == *iter_relative &&				//�ΰ��� ������Ұ� ����
		iter_path != p.end() &&						//��� ����� ����
		iter_relative != r.end())					//���������� �ݺ��ϸ�
	{
		iter_path++;								//��ΰ� ����
		iter_relative++;							
	}

	//relative�� ���� �� ��ū������ ..�� �߰�
	if (iter_relative != r.end()) //���� iter_relative�� ������ �ʾҴٸ�
	{
		iter_relative++;  //��� ����
		while (iter_relative != r.end()) //������ �ݺ��� �ȴٸ�
		{
			result /= ".."; //..�� �߰��Ѵ�
			iter_relative++;//��� ����
		}
	}

	//���� ��� �߰�
	while (iter_path != p.end()) //iter_path�� ������ �ݺ��ϸ�
	{
		result /= *iter_path; //iter_path�� ������ ���涧���� result�� /�� ���δ�
		iter_path++; //�������
	}

	return result.generic_string();
}

auto FileSystem::GetParentDirectory(const std::string & path) -> const std::string
{
	auto found = path.find_last_of("\\/"); // \//�߿� �ϳ��� �ɸ��� ����
	auto result = path; 

	if (found == std::string::npos) //�����̶��
		return path; //��ȯ

	if (found == path.length() - 1) //found�� ���� path�� ������ 1�� ���Ͱ� ������
	{
		result = result.substr(0, found - 1); //result�� ó������ found-1RKwl eodlq
		return GetParentDirectory(result); //result���� �ְ� �ٽ� ��ȯ
	}

	return result.substr(0, found) + "/"; // /�������� /�ϳ��� ���߰��Ѵ�
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
    //���� : 
    return std::string();
}

auto FileSystem::ToWstring(const std::string & str) -> const std::wstring
{
    std::wstring result;
    result.assign(str.begin(), str.end());

    return result;
}
