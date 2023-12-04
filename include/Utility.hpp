#ifndef THREEPP_TETRIS_UTILITY_HPP
#define THREEPP_TETRIS_UTILITY_HPP

#include "threepp/threepp.hpp"


inline auto createBox(const threepp::Vector2 &pos, const threepp::Color &color)
{
    auto geometry = threepp::BoxGeometry::create();
    auto material = threepp::MeshBasicMaterial::create();
    material->color.copy(color);
    auto mesh = std::make_unique<threepp::Mesh>(threepp::Mesh(geometry, material));
    // Adds space between boxes making a visible grid
    mesh->scale = { 0.95f, 0.95f, 0 };
    mesh->position.copy({ pos.x, pos.y, 0});
    return mesh;
}

#endif//THREEPP_TETRIS_UTILITY_HPP
