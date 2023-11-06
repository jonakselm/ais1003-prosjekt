
#include "threepp/threepp.hpp"
#include "GameBoard.hpp"
#include "Utility.hpp"

using namespace threepp;

int main()
{
    Canvas canvas("threepp demo", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::aliceblue);

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

    auto group = Group::create();
    for (int i = 0; i < size; i++)
    {
        group->add(createBox({float(i), float(i), 0}, Color(255 * i % 2 ? 1 : 0, 255 * i % 2 == 0 ? 1 : 0, 0)));
    }
    scene->add(group);
    board.addToScene();

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
