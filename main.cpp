
#include "Board/GameBoard.hpp"
#include "Utility.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

int main()
{
    Canvas canvas("Tetris", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    // Funke kun med partall
    int size = 20;
    auto camera = OrthographicCamera::create(-size / 2, size / 2, -size / 2, size / 2);
    camera->position.z = 1;
    camera->position.x = float(size) / 2 - 0.5f;
    camera->position.y = float(size) / 2 - 0.5f;
    // Fiks dette

    auto scene = Scene::create();
    GameBoard board(*scene);
    canvas.addKeyListener(&board);

    float time = 0;

    Clock clock;
    float rotationSpeed = 1;

    Vector2 dir = { 0, 0 };

    canvas.animate([&]()
    {
        board.update(clock.getDelta());
        //group->rotation.y += rotationSpeed * dt;

        renderer.render(*scene, *camera);
    });
}
