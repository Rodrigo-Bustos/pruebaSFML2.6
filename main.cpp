#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

void movimientoJugador(sf::Vector2f &posicionRectangulo)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        posicionRectangulo.y--;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        posicionRectangulo.x--;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        posicionRectangulo.y++;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        posicionRectangulo.x++;
    }
}

std::array<float, 4> getBorder(sf::Vector2f shapeSize, sf::Vector2f posicionRectangulo)
{
    std::array<float, 4> bordes;
    float topBorder = posicionRectangulo.y;
    float leftBorder = posicionRectangulo.x;
    float bottomBorder = shapeSize.y;
    float rightBorder = shapeSize.x;

    bordes = {topBorder, leftBorder, bottomBorder, rightBorder};

    return bordes;
}

void activarColisionX(std::array<float, 4> bordes1, std::array<float, 4> bordes2, sf::Vector2f &posicionRectangulo ,int direccionX, int direccionY)
{
    if (direccionX != 0)
    {
        if(direccionX == 1)
        {
            posicionRectangulo.x = bordes2[1]-bordes1[3];
            direccionX=0;
        }
        else if(direccionX == -1)
        {
            posicionRectangulo.x = bordes2[1] + bordes2[3];
            direccionX=0;
        }
    }
    else if (direccionY != 0)
    {
        if (direccionY == 1)
        {
            posicionRectangulo.y = bordes2[0] - bordes1[2];
        }
        else
        {
            posicionRectangulo.y = bordes2[2] + bordes2[0];
        }
    }
}

void activarColisionY(std::array<float, 4> bordes1, std::array<float, 4> bordes2, sf::Vector2f &posicionRectangulo ,int direccionX, int direccionY)
{
    if (direccionY != 0)
    {
        if (direccionY == 1)
        {
            posicionRectangulo.y = bordes2[0] - bordes1[2];
        }
        else
        {
            posicionRectangulo.y = bordes2[2] + bordes2[0];
        }
    }
}

bool checarColision(std::array<float, 4> bordes1, std::array<float, 4> bordes2)
{
    float ladoArriba1 = bordes1[0];
    float ladoIzquierda1 = bordes1[1];
    float ladoAbajo1 = bordes1[2];
    float ladoDerecha1 = bordes1[3];
    float ladoArriba2 = bordes2[0];
    float ladoIzquierda2 = bordes2[1];
    float ladoAbajo2 = bordes2[2];
    float ladoDerecha2 = bordes2[3];

    if ((ladoIzquierda1 + ladoDerecha1 >= ladoIzquierda2 && ladoIzquierda1 <= ladoIzquierda2 + ladoDerecha2) &&
    (ladoArriba1 + ladoAbajo1 >= ladoArriba2 && ladoArriba1 <= ladoArriba2 + ladoAbajo2))
    {
        std::cout << bordes1[1] << " " << ladoArriba1 << std::endl;
        return true;
    }
    return false;
}

void actualizarDireccion(sf::Vector2f posicionRectangulo, float prePosicionX, float prePosicionY, int &direccionX, int &direccionY)
{
    (posicionRectangulo.x > prePosicionX) ? direccionX = 1 : direccionX = -1;
    (posicionRectangulo.y > prePosicionY) ? direccionY = 1 : direccionY = -1;
    if (posicionRectangulo.x == prePosicionX)
    {
        direccionX = 0;
    } 
    if (posicionRectangulo.y == prePosicionY)
    {
        direccionY = 0;
    } 
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(500, 500), "Danilito");
    window.setFramerateLimit(120);

    sf::Vector2f shapeSize = {50.f, 50.f};
    sf::RectangleShape shape(shapeSize);
    shape.setFillColor(sf::Color::Red);
    sf::Vector2f posicionRectangulo = {120.f, 120.f};
    shape.setPosition(posicionRectangulo);

    sf::Vector2f barreraSize = {20.f, 120.f};
    sf::RectangleShape barrera(barreraSize);
    barrera.setFillColor(sf::Color::Green);
    sf::Vector2f posicionBarrera = {180.f, 280.f};
    barrera.setPosition(posicionBarrera);

    float prePosicionX = posicionRectangulo.x;
    float prePosicionY = posicionRectangulo.y;
    int direccionX = 0;
    int direccionY = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        movimientoJugador(posicionRectangulo);
        actualizarDireccion(posicionRectangulo, prePosicionX, prePosicionY, direccionX, direccionY);
        
        std::array<float, 4> shapeBordes = getBorder(shapeSize, posicionRectangulo);
        std::array<float, 4> barreraBordes = getBorder(barreraSize, posicionBarrera);
        std::cout << direccionX << std::endl;
        if (checarColision(shapeBordes, barreraBordes))
            activarColisionX(shapeBordes, barreraBordes, posicionRectangulo, direccionX, direccionY);
        if (checarColision(shapeBordes, barreraBordes))
            activarColisionY(shapeBordes, barreraBordes, posicionRectangulo, direccionX, direccionY);
        shape.setPosition(posicionRectangulo);
        prePosicionX = posicionRectangulo.x;
        prePosicionY = posicionRectangulo.y;
        // WIndow
        window.clear();
        window.draw(barrera);
        window.draw(shape);
        window.display();
    }

    return 0;
}