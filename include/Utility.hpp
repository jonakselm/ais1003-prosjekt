#ifndef THREEPP_TETRIS_UTILITY_HPP
#define THREEPP_TETRIS_UTILITY_HPP

#include "threepp/threepp.hpp"


inline auto createBox(const threepp::Vector3& pos, const threepp::Color& color)
{
    auto geometry = threepp::BoxGeometry::create();
    auto material = threepp::MeshBasicMaterial::create();
    material->color.copy(color);
    auto mesh = std::make_unique<threepp::Mesh>(threepp::Mesh(geometry, material));
    mesh->position.copy(pos);
    return mesh;
}

#endif//THREEPP_TETRIS_UTILITY_HPP
