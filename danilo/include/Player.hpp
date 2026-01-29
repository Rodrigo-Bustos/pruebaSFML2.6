#include "Wall.hpp"

class Player{
public:
  Player(sf::Vector2f pos, sf::Vector2f size);
  void render(sf::RenderWindow& window);

  void movementX();
  void movementY();
  
private:
  const sf::Vector2f speed = {2,2};
  sf::Vector2f lastPostion;

  sf::Vector2f pos;
  sf::Vector2f size;
  sf::RectangleShape rectShape;

private:
  void collisionsX();
  void collisionsY();
  bool isColliding(Wall& wall) const;
};