#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include "Util.h"

#if defined(_WIN32)
#include <windows.h>  // GetModuleFileNameW
#elif defined(LINUX)
#include <unistd.h>  // readlink
#endif

#include <array>
#include <codecvt>
#include <locale>
#include <memory>

namespace fs = std::filesystem;

static constexpr size_t kMaxUnicodePathSize = 32767;

static fs::path asset_path;

void util::Init(void) {
#if defined(_WIN32)
  auto unicode_path =
      std::make_unique<std::array<wchar_t, kMaxUnicodePathSize>>();
  const auto path_len =
      ::GetModuleFileNameW(nullptr, unicode_path->data(), static_cast<DWORD>(unicode_path->size()));

  const auto bin_path = std::wstring_view(unicode_path->data(), path_len);
#elif defined LINUX
  std::array<char, 4096> path_buf{};
  const auto num_read =
      readlink("/proc/self/exe", path_buf.data(), path_buf.size() - 1);
  if (num_read == -1) {
    perror("Failed to read binary path");
    exit(1);
  }
  const auto bin_path = std::string_view(path_buf.data(), num_read);
#else
#error "Unsupported platform"
#endif

  asset_path = fs::canonical(bin_path).parent_path() /= "resources";
}

const fs::path& util::AssetPath(void) { return asset_path; }

std::string util::ToCharString(const std::wstring& str) {
  return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(str);
}