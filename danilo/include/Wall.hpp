#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Wall{
public:
  Wall(sf::Vector2f pos, sf::Vector2f size);
  static const std::vector<Wall*>& getS_Wall();
  void render(sf::RenderWindow& window);

  const sf::Vector2f getPosition() const;
  const sf::Vector2f getSize() const;

private:
  sf::Vector2f pos;
  sf::Vector2f size;
  sf::RectangleShape rectShape;

  static std::vector<Wall*> s_wall;
};