#include "Board/GameBoard.hpp"
#include "BoardController.hpp"
#include "BoardView.hpp"
#include "Utility.hpp"
#include "threepp/threepp.hpp"
#include <iostream>

using namespace threepp;

int main()
{
    Canvas canvas("Tetris", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    // Funke kun med partall
    // Creating camera 20x20
    int size = 20;
    auto camera = OrthographicCamera::create(-size / 2, size / 2, -size / 2, size / 2);
    camera->position.z = 1;
    camera->position.x = float(size) / 2 - 0.5f;
    camera->position.y = float(size) / 2 - 0.5f;

    auto scene = Scene::create();
    //GameBoard board(*scene);

    renderer.enableTextRendering();

    Clock clock;

    BoardController bc(renderer, *scene, canvas.size());

    canvas.addKeyListener(&bc);

    int c;

    canvas.onWindowResize([&](const WindowSize &size)
    {
        camera->updateProjectionMatrix();
        renderer.setSize(size);
        bc.onWindowResize(size);
    });

    clock.start();
    canvas.animate([&]()
    {
        bc.update(clock.getDelta());
        renderer.render(*scene, *camera);
        c++;
    });
    std::cout << (float)c / clock.getElapsedTime() << std::endl;
}
