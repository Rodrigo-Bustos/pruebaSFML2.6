#pragma once

#include "Renderable.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Wall: public Renderable{
public:
  Wall(sf::Vector2f pos, sf::Vector2f size);
  static const std::vector<Wall*>& getS_Wall();

  const sf::Vector2f getPosition() const;
  const sf::Vector2f getSize() const;

private:
  static std::vector<Wall*> s_wall;
};