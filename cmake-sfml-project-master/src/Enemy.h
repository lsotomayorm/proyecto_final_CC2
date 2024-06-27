#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> 
#include <iostream> 
class Enemy
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float movementSpeed;

    //Funciones Privadas
    void initTexture();
    void initSprite(); 

public:
    Enemy(float posX, float posY);
    ~Enemy();

    // Accessors
    const sf::Vector2f& getPos() const;
    const sf::FloatRect getBounds() const;

    // Funciones
    void move(const float dirX, const float dirY);
    void update(const float deltaTime);
    void render(sf::RenderTarget& target);
};

#endif