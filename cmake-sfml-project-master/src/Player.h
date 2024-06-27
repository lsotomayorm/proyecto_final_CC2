#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
class Player
{
private:
    sf::Sprite sprite;
    sf::Texture texture;

    float movementSpeed;
    float jumpStrength;
    float gravity;
    sf::Vector2f velocity;
    bool isJumping;
    float groundLevel;

    //Funciones Privadas
    void initTexture();
    void initSprite();
public:
    Player();
    ~Player();
    //Accesors
    const sf::Vector2f& getPos() const;

    //Funciones
    void move(const float dirX, const float dirY);
    void jump();
    void update(const float DeltaTime);
    void render(sf::RenderTarget& target);
};

#endif