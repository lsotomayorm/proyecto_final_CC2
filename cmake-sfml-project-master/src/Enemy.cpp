#include "Enemy.h"

void Enemy::initTexture()
{
    if(!this->texture.loadFromFile("src/Textures/Enemy.png")){
        std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file." << "\n";
    }

}

void Enemy::initSprite()
{

    this->sprite.setTexture(this->texture);
    this->sprite.scale(2.f,2.f);
}

Enemy::Enemy(float posX, float posY)
{
    this->movementSpeed = 150.0f;

    this->initTexture();
    this->initSprite();
    this->sprite.setPosition(posX,posY);

}

Enemy::~Enemy()
{

}

const sf::Vector2f &Enemy::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Enemy::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

void Enemy::move(const float dirX, const float dirY)
{
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Enemy::update(const float deltaTime)
{
    this->move(0.f, 1.f * deltaTime);
}

void Enemy::render(sf::RenderTarget &target)
{
     target.draw(this->sprite);
}
