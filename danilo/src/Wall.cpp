#include "Wall.hpp"
#include "Renderable.hpp"

Wall::Wall(sf::Vector2f pos, sf::Vector2f size): Renderable(pos, size){
  s_wall.push_back(this);
};

std::vector<Wall*> Wall::s_wall;

const std::vector<Wall*>& Wall::getS_Wall(){
  return s_wall;
}

const sf::Vector2f Wall::getPosition() const{
  return pos;
}

const sf::Vector2f Wall::getSize() const{
  return size;
}