#include "Surface.hpp"

Surface::Surface() {
    collision = nullptr;
}

Surface::~Surface() {
    if (collision != nullptr) {
        delete collision;
    }
}

void Surface::setSurface(const std::string& path, const std::pair<int, int>& pos, const int& surfaceType) {
    loadIMG(path);
    setSize({32, 32});
    setRect({pos.first, pos.second});
}
