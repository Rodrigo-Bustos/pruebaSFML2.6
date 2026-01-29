#include "Renderable.hpp"

Renderable::Renderable(sf::Vector2f pos, sf::Vector2f size): pos(pos), size(size){}

void Renderable::render(sf::RenderWindow& window){
  rectShape.setPosition(pos);
  rectShape.setSize(size);
  window.draw(rectShape);
}
