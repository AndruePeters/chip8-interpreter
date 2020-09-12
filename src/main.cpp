#include <fmt/printf.h>


#include <cpu_lib/memory.hpp>
#include <cpu_lib/register.hpp>
#include <cpu_lib/stack.hpp>
#include <chip8cpu.h>

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>


int main()
{
  chip8::CPU cpu;
  sf::ContextSettings settings;
  settings.antialiasingLevel = 1;
  sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3", sf::Style::Default, settings);
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  sf::CircleShape shape(100.f);
  shape.setPointCount(1000);
  shape.setFillColor(sf::Color::Green);
  shape.setOutlineColor(sf::Color::Cyan);
  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    ImGui::SFML::Update(window, deltaClock.restart());


    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();

    ImGui::Begin("ram");
      ImGui::Columns(8);
        for (const auto ramVal : cpu.ram_) {
          ImGui::Text("0x%.2X", ramVal);
          ImGui::NextColumn();
        }
    ImGui::End();

    ImGui::Begin("call stack");
      for (const auto stackVal : cpu.call_stack_) {
        ImGui::Text("0x%.4X", stackVal);
      }
    ImGui::End();

    window.clear();
    //window.draw(shape);
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
