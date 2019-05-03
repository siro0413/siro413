#pragma once

class FileSystem final
{
public:
	static auto Create_Directory(const std::string& path)-> const bool;
	static auto Delete_Directory(const std::string& path)->const bool;
	static auto Delete_file(const std::string& path)-> const bool;
	static auto Copy_file(const std::string& src,const std::string&dst)-> const bool;
	static auto IsDirectory(const std::string& path)-> const bool;
	static auto IsExostDorectory(const std::string& path) -> const bool;
	static auto IsExistFile(const std::string& path) -> const bool;

	static auto GetFileNameFormPath(const std::string& path)->const std::string;
	static auto GetIntactFileNameFromPath(const std::string& path)->const std::string;
	static auto GetDirectoryFromPath(const std::string& path)->const std::string;
	static auto GetExtensionFromPath(const std::string& path)->const std::string;
	static auto GetPathWithoutExtension(const std::string& path)->const std::string;
	static auto GetRelativeFromPath(const std::string& absolutePath)->const std::string;
	static auto GetParentDirectory(const std::string& path)->const std::string;
	static auto GetWorkingDirectory()->const std::string;

    static auto ToUpper(const std::string& lower) -> const std::string;
    static auto ToLower(const std::string& upper) -> const std::string;
    static auto ToString(const std::wstring& wstr) -> const std::string;
    static auto ToWstring(const std::string& str) -> const std::wstring;
};