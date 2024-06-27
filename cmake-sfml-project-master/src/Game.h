#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include <map>
class Game
{
private:
    //Window
    sf::RenderWindow* window;
    //Resources
    //Background
    sf::Texture backgTexture;
    sf::Sprite backgSprite;
    //Player
    Player* player;
    //Clock
    sf::Clock clock;
    //Private functions
    void initWindow();
    void initPlayer();
    void initTextures();
    void initBackground();



public:
    Game(/* args */);
    ~Game();
    //Functions
    void run();
    void updatePollEvents();
    void updateinput();
    void update();
    void render();
};
#endif