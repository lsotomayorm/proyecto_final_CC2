#include "Animation.h"

Animation::Animation()
{

}

Animation::~Animation()
{
}

void Animation::initialize(sf::Texture* _texture, sf::Vector2u _imageCount, float _switchTime){
    this->imageCount = _imageCount;
    this->switchTime = _switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = _texture->getSize().x / float(imageCount.x);
    uvRect.height = _texture->getSize().y / float(imageCount.y);
}

void Animation::update(float _deltaTime){
    currentImage.y = 0;
    totalTime += _deltaTime;

    if(totalTime >= switchTime){
        totalTime -= switchTime;
        currentImage.x++;
        if(currentImage.x >= imageCount.x)
            currentImage.x = 0;
    }
    uvRect.left = currentImage.x * uvRect.width;
    //uvRect.top = currentImage.y * uvRect.height;
}