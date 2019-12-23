#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include "Util.h"

#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_filesystem.h>

#include <codecvt>
#include <locale>

namespace fs = std::filesystem;

static constexpr size_t kMaxUnicodePathSize = 32767;

static fs::path asset_path;

void util::Init(void) {
  const char* base_path = SDL_GetBasePath();
  SDL_assert_always(base_path != nullptr);
  asset_path = fs::canonical(fs::u8path(base_path)) / "resources";
}

const fs::path& util::AssetPath(void) { return asset_path; }

std::string util::ToCharString(const std::wstring& str) {
  return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(str);
}