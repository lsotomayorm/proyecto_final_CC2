#include "Player.h"

void Player::initTexture()
{
    //Load a texture from file

    if(!this->playerTexture.loadFromFile("../../src/Textures/Idle.png")){
        std::cout <<"ERROR::PLAYER::INITTEXTURE::Could not load texture file. " << "\n";
    }
}

void Player::initSprite()
{   
    
    //set the texture of sprite
    this->sprite.setTexture(this->playerTexture);
    this->sprite.setPosition(50.0f, groundLevel);
    this->sprite.setScale(2.1f, 2.1f);
    //sf::Vector2u textureSize = this->texture.getSize();
    //textureSize.x /= 11;
    //textureSize.y /= 1;
    //this->sprite.setTextureRect(sf::IntRect(textureSize.x * 2, 0, textureSize.x, textureSize.y));
    //Resize the sprite
    //this->sprite.scale(2.1f, 2.1f);
}

Player::Player()
{
    this->movementSpeed = 5.f;
    this->jumpStrength = 450.f;
    this->gravity = 980.f;
    this->velocity = sf::Vector2f(0.0f, 0.0f);
    this->isJumping = false;
    this->groundLevel = 538.0f;

    //this->player.setSize(sf::Vector2f(100.0f, 150.0f));

    this->initTexture();
    this->initSprite();

    this->animationPlayer.initialize(&playerTexture, sf::Vector2u(11,1), 0.3f);
}

Player::~Player()
{
}

const sf::Vector2f &Player::getPos() const
{
    return this->sprite.getPosition();
}

void Player::move(const float dirX, const float dirY)
{   
    sf::Vector2f newPos = this->sprite.getPosition() + sf::Vector2f(this->movementSpeed * dirX, this->movementSpeed * dirY);
    if (newPos.x < 0) newPos.x = 0;
    if (newPos.y < 0) newPos.y = 0;
    if (newPos.x + this->sprite.getGlobalBounds().width > 800) newPos.x = 800 - this->sprite.getGlobalBounds().width;
    //if (newPos.y + this->sprite.getGlobalBounds().height > 600) newPos.y = 600 - this->sprite.getGlobalBounds().height;

    this->sprite.setPosition(newPos);
}

void Player::jump()
{
    if (!this->isJumping) {
        this->isJumping = true;
        this->velocity.y = -this->jumpStrength;
    }
}

void Player::update(const float deltaTime)
{
    animationPlayer.update(deltaTime);
    this->sprite.setTextureRect(animationPlayer.uvRect);
    //this->sprite.scale(2.1f, 2.1f);

    if (this->isJumping) {
        this->velocity.y += this->gravity * deltaTime;
        this->sprite.move(0.0f, this->velocity.y * deltaTime);
        if (this->sprite.getPosition().y >= this->groundLevel) {
            this->sprite.setPosition(this->sprite.getPosition().x, this->groundLevel);
            this->isJumping = false;
            this->velocity.y = 0.0f;
        }
    }
}

void Player::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}
