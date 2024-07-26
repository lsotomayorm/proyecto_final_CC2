#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
class Animation{
    public:
        Animation();
        ~Animation();

        void initialize(sf::Texture*, sf::Vector2u, float);
        void update(float);

        sf::IntRect uvRect;
    private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        float totalTime;
        float switchTime;
};

#endif