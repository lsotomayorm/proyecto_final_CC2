#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>
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
    //Enemies
    std::vector<Enemy*> enemies; 
    float spawnTimer;
    float spawnTimerMax;

    //Clock
    sf::Clock clock;
    //Private functions
    void initWindow();
    void initPlayer();
    void initTextures();
    void initBackground();
    void initEnemies();



public:
    Game(/* args */);
    ~Game();
    //Functions
    void run();
    void updatePollEvents();
    void updateinput();
    void updateEnemies(const float& deltaTime);
    void update();
    void render();
};
#endif