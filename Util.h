#pragma once

#include <filesystem>
#include <memory>

#include <SDL2/SDL_surface.h>

namespace util {

void Init();

const std::filesystem::path& AssetPath();

std::string ToCharString(const std::wstring& str);
static inline const std::string& ToCharString(const std::string& str) { return str; }

namespace detail {
struct SurfaceDeleter {
  void operator()(SDL_Surface* surf) const { SDL_FreeSurface(surf); }
};
}

using unique_surface_ptr = std::unique_ptr<SDL_Surface, detail::SurfaceDeleter>;

static inline unique_surface_ptr WrapSurface(SDL_Surface* surf) { return unique_surface_ptr(surf); }

}  // namespace util