#pragma once

#include <filesystem>

namespace util {

void Init();

const std::filesystem::path& AssetPath();

std::string ToCharString(const std::wstring& str);
static inline const std::string& ToCharString(const std::string& str) { return str; }

}  // namespace util