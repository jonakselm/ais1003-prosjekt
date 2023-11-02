#ifndef THREEPP_VCPKG_DEMO_UTILITY_HPP
#define THREEPP_VCPKG_DEMO_UTILITY_HPP

#include "threepp/threepp.hpp"

namespace threepp
{
    inline auto createBox(const Vector3& pos, const Color& color)
    {
        auto geometry = BoxGeometry::create();
        auto material = MeshBasicMaterial::create();
        material->color.copy(color);
        auto mesh = Mesh::create(geometry, material);
        mesh->position.copy(pos);

        return mesh;
    }
} // namespace

#endif//THREEPP_VCPKG_DEMO_UTILITY_HPP
