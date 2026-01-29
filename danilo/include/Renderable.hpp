#pragma once
#include <SFML/Graphics.hpp>

class Renderable{
public:
  void render(sf::RenderWindow& window);
  Renderable(sf::Vector2f pos, sf::Vector2f size);

protected:
  sf::Vector2f pos;
  sf::Vector2f size;
  sf::RectangleShape rectShape;
};