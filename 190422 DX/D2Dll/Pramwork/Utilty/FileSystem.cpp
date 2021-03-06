#include "stdafx.h"
#include "FileSystem.h"

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
	std::string wstr1;
	wstr1.assign(wstr.begin(), wstr.end());

	return wstr1;
}

auto FileSystem::ToWstring(const std::string & str) -> const std::wstring
{
	std::wstring result;
	result.assign(str.begin(), str.end());

	return result;
}
