#include <iostream>
#include <array>
#include <cmath>
#include "SFML/Graphics.hpp"

bool IsColliding(sf::VertexArray triangle1, sf::VertexArray triangle2)
{
    for(int i = 0; i < 3; i++)
    {
        float x1 = triangle2[i].position.x;
        float y1 = triangle2[i].position.y;
        float x2 = triangle2[(i + 1) % 3].position.x;
        float y2 = triangle2[(i + 1) % 3].position.y;

        for(int h = 0; h < 3; h++)
        {
            float x3 = triangle1[h].position.x;
            float y3 = triangle1[h].position.y;
            float x4 = triangle1[(h + 1) % 3].position.x;
            float y4 = triangle1[(h + 1) % 3].position.y;

            float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

            if(denominator == 0)
            {
                return false;
            }

            float a = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
            float b = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;

            if (a >= 0 && a <= 1 && b >= 0 && b <= 1)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle Collide");

    sf::VertexArray triangle1(sf::Triangles, 3);
    triangle1[0].position = sf::Vector2f(200, 200);
    triangle1[1].position = sf::Vector2f(400, 200);
    triangle1[2].position = sf::Vector2f(300, 400);
    triangle1[0].color = sf::Color::Red; triangle1[1].color = sf::Color::Red; triangle1[2].color = sf::Color::Red;

    sf::VertexArray triangle2(sf::Triangles, 3);
    triangle2[0].position = sf::Vector2f(500, 500);
    triangle2[1].position = sf::Vector2f(700, 300);
    triangle2[2].position = sf::Vector2f(600, 700);
    triangle2[0].color = sf::Color::Blue; triangle2[1].color = sf::Color::Blue; triangle2[2].color = sf::Color::Blue;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            triangle1[0].position.x -= 1.0f;
            triangle1[1].position.x -= 1.0f;
            triangle1[2].position.x -= 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            triangle1[0].position.x += 1.0f;
            triangle1[1].position.x += 1.0f;
            triangle1[2].position.x += 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            triangle1[0].position.y -= 1.0f;
            triangle1[1].position.y -= 1.0f;
            triangle1[2].position.y -= 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            triangle1[0].position.y += 1.0f;
            triangle1[1].position.y += 1.0f;
            triangle1[2].position.y += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            triangle2[0].position.x -= 1.0f;
            triangle2[1].position.x -= 1.0f;
            triangle2[2].position.x -= 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            triangle2[0].position.x += 1.0f;
            triangle2[1].position.x += 1.0f;
            triangle2[2].position.x += 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            triangle2[0].position.y -= 1.0f;
            triangle2[1].position.y -= 1.0f;
            triangle2[2].position.y -= 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            triangle2[0].position.y += 1.0f;
            triangle2[1].position.y += 1.0f;
            triangle2[2].position.y += 1.0f;
        }

        window.clear();
        if(IsColliding(triangle1, triangle2))
        {
            sf::Font font;
            font.loadFromFile("orange juice 2.0.ttf");

            sf::Text collide;
            collide.setFont(font);
            collide.setString("Triangles Collide");
            collide.setCharacterSize(24);
            collide.setFillColor(sf::Color::Green);
            collide.setPosition(0, 0);
            window.draw(collide);
        }
        window.draw(triangle1);
        window.draw(triangle2);
        window.display();
    }
}