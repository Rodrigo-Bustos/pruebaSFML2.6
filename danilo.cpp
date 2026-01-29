#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFMl/Graphics.hpp>
#include <vector>

class Wall{
public:
  Wall(sf::Vector2f pos, sf::Vector2f size): pos(pos), size(size){
    s_wall.push_back(this);
  };

  static const std::vector<Wall*>& getS_Wall(){
    return s_wall;
  }

  void render(sf::RenderWindow& window){
    rectShape.setPosition(pos);
    rectShape.setSize(size);
    window.draw(rectShape);
  }

  const sf::Vector2f getPosition() const{
    return pos;
  }

  const sf::Vector2f getSize() const{
    return size;
  }

private:
  sf::Vector2f pos;
  sf::Vector2f size;
  sf::RectangleShape rectShape;

  static std::vector<Wall*> s_wall;
};

std::vector<Wall*> Wall::s_wall;

class Player{
public:
  Player(sf::Vector2f pos, sf::Vector2f size): pos(pos), size(size){}

  void render(sf::RenderWindow& window){
    rectShape.setPosition(pos);
    rectShape.setSize(size);
    window.draw(rectShape);
  }

  void movementX(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
      pos.x -= speed.x;
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
      pos.x += speed.x;
    }

    collisionsX();
    lastPostion = pos;
  }

  void movementY(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
      pos.y -= speed.y;
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
      pos.y += speed.y;
    }

    collisionsY();
    lastPostion = pos;
  }
  
private:
  const sf::Vector2f speed = {2,2};
  sf::Vector2f lastPostion;

  sf::Vector2f pos;
  sf::Vector2f size;
  sf::RectangleShape rectShape;

private:
  void collisionsX(){
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

  void collisionsY(){
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

  bool isColliding(Wall& wall){
    bool HorizontalCollision = (pos.x + size.x > wall.getPosition().x && pos.x < wall.getPosition().x + wall.getSize().x);
    bool VerticalCollision = (pos.y + size.y > wall.getPosition().y && pos.y < wall.getPosition().y + wall.getSize().y);
    return HorizontalCollision && VerticalCollision;
  }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Danilito");
    window.setFramerateLimit(120);

    Player player(
      {0,0},
      {15,15}
    );

    Wall wall(
      {100,100},
      {50,50}
    );

    Wall wall2(
      {200,100},
      {50,50}
    );

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
          if (event.type == sf::Event::Closed) window.close();
        }

        player.movementX();
        player.movementY();

        // Window
        window.clear();
        player.render(window);

        for(auto& wall : Wall::getS_Wall()){
          wall ->render(window);
        }

        window.display();
    }

    return 0;
}