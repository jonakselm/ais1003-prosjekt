
#include "Board/GameBoard.hpp"
#include "BoardController.hpp"
#include "BoardView.hpp"
#include "Utility.hpp"
#include "threepp/threepp.hpp"
#include <iostream>

using namespace threepp;

class MenuElement
{
public:
    MenuElement(threepp::GLRenderer &renderer, threepp::Scene &scene, const std::string &text, const threepp::Vector2 &position)
        : m_renderer(renderer),
          m_scene(scene),
          m_text(m_renderer.textHandle(text)),
          m_str(text),
          m_position(position)
    {
        m_text.setPosition(position.x, position.y);
        m_activeBox = createBox({ 0, 0 }, threepp::Color::yellow);
    }

    const threepp::Vector2 &getPosition() const
    {
        return m_position;
    }

    void setActive()
    {
        //m_scene.add(*m_activeBox);
        m_text.setText("- " + m_str);
    }

    void setUnactive()
    {
        m_text.setText(m_str);
    }

    void onItemUse(std::function<void()> &&func)
    {
        m_function = func;
    }

    void invoke()
    {
        m_function();
    }

private:
    threepp::GLRenderer &m_renderer;
    threepp::Scene &m_scene;
    threepp::TextHandle &m_text;
    std::string m_str;
    std::unique_ptr<threepp::Mesh> m_activeBox;
    threepp::Vector2 m_position;
    std::function<void()> m_function;
};

class Menu : public KeyListener
{
public:
    Menu(threepp::GLRenderer &renderer, threepp::Scene &scene)
        : m_renderer(renderer),
          m_scene(scene)
    {

    }

    void addElement(const std::string &text, std::function<void()> func)
    {
        threepp::Vector2 pos = { 20, 20 };
        if (!m_elements.empty())
        {
            pos = m_elements.back().getPosition();
            pos.y += 20;
        }
        m_elements.emplace_back(MenuElement(m_renderer, m_scene, text, pos));
        m_elements.back().onItemUse(std::move(func));
    }

    void onKeyPressed(threepp::KeyEvent keyEvent) override
    {
        m_elements.at(m_active).setUnactive();
        switch (keyEvent.key)
        {
        case threepp::Key::UP:
            if (m_active > 0)
            {
                m_active--;
            }
            break;
        case threepp::Key::DOWN:
            if (m_active < m_elements.size() - 1)
            {
                m_elements.at(m_active).setUnactive();
                m_active++;
                m_elements.at(m_active).setActive();
            }
            break;
        case threepp::Key::ENTER:
            m_elements.at(m_active).invoke();
            break;
        }
        m_elements.at(m_active).setActive();
    }

private:
    threepp::GLRenderer &m_renderer;
    threepp::Scene &m_scene;
    std::vector<MenuElement> m_elements;
    int m_active = 0;
};

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

    bool updateBoard = false;
    BoardController bc(renderer, *scene);

    Menu menu(renderer, *scene);
    menu.addElement("noge", [&updateBoard, &canvas, &menu, &bc]()
    {
        updateBoard = true;
        canvas.removeKeyListener(&menu);
        canvas.addKeyListener(&bc);
    });
    menu.addElement("aent", [](){});
    menu.addElement("tull", [](){});

    canvas.addKeyListener(&menu);

    //canvas.addKeyListener(&bc);

    int c;

    clock.start();
    canvas.animate([&]()
    {
                       if (updateBoard)
        bc.update(clock.getDelta());
        renderer.render(*scene, *camera);
        c++;
    });
    std::cout << (float)c / clock.getElapsedTime() << std::endl;
}
