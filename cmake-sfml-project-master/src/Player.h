#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Animation.h"
class Player
{
private:
    sf::RectangleShape player;
    sf::Sprite sprite;
    sf::Texture playerTexture;

    float movementSpeed;
    float jumpStrength;
    float gravity;
    sf::Vector2f velocity;
    bool isJumping;
    float groundLevel;

    Animation animationPlayer;

    //Private functions
    void initTexture();
    void initSprite();
public:
    Player();
    ~Player();
    //Accesors
    const sf::Vector2f& getPos() const;

    //Functions
    void move(const float dirX, const float dirY);
    void jump();
    void update(const float DeltaTime);
    void render(sf::RenderTarget& target);
};

#endif