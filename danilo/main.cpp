#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Wall.hpp"

int main(){
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

  while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) window.close();
    }

    player.movementX();
    player.movementY();

    window.clear();
    player.render(window);

    for(auto& wall : Wall::getS_Wall()){
      wall ->render(window);
    }

    window.display();
  }

  return 0;
}