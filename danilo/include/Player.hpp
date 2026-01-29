#pragma once
#include "Renderable.hpp"
#include "Wall.hpp"

class Player: public Renderable{
public:
  Player(sf::Vector2f pos, sf::Vector2f size);

  void movementX();
  void movementY();
  
private:
  const sf::Vector2f speed = {2,2};
  sf::Vector2f lastPostion;

private:
  void collisionsX();
  void collisionsY();
  bool isColliding(Wall& wall) const;
};