#include "Player.hpp"

Player::Player(sf::Vector2f pos, sf::Vector2f size): Renderable(pos,size){}

void Player::movementX(){
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
    pos.x -= speed.x;
  }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
    pos.x += speed.x;
  }

  collisionsX();
  lastPostion = pos;
}

void Player::movementY(){
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
    pos.y -= speed.y;
  }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
    pos.y += speed.y;
  }

  collisionsY();
  lastPostion = pos;
}

void Player::collisionsX(){
  for(Wall* wall : Wall::getS_Wall()){
    if(isColliding(*wall)){
      bool movingToTheRight = pos.x > lastPostion.x;
      if(movingToTheRight){
        pos.x -= (pos.x + size.x) - (wall->getPosition().x);
      } else{
        pos.x += (wall->getPosition().x + wall->getSize().x) - pos.x;
      }
    }
  }
}

void Player::collisionsY(){
  for(Wall* wall : Wall::getS_Wall()){
    if(isColliding(*wall)){
      bool movingDown = pos.y > lastPostion.y;
      if(movingDown){
        pos.y -= (pos.y + size.y) - (wall->getPosition().y);
      } else{
        pos.y += (wall->getPosition().y + wall->getSize().y) - pos.y;
      }
    }
  }
}

bool Player::isColliding(Wall& wall) const{
  bool HorizontalCollision = (pos.x + size.x > wall.getPosition().x && pos.x < wall.getPosition().x + wall.getSize().x);
  bool VerticalCollision = (pos.y + size.y > wall.getPosition().y && pos.y < wall.getPosition().y + wall.getSize().y);
  return HorizontalCollision && VerticalCollision;
}