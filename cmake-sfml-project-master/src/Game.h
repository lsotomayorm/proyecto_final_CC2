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
    sf::Font font;
    sf::Text player1HealthText;
    sf::Text player2HealthText;
    //Background
    sf::Texture backgTexture;
    sf::Sprite backgSprite;
    //Players
    Player* player1;
    Player* player2;
    //Enemies
    std::vector<Enemy*> enemies; 
    float spawnTimer;
    float spawnTimerMax;

    //Clock
    sf::Clock clock;
    //Funciones Privadas
    void initWindow();
    void initPlayer();
    void initTextures();
    void initBackground();
    void initEnemies();
    void updateCollisions();
    void initFonts();
    void initTexts();



public:
    bool misiles;
    Game(/* args */);
    ~Game();
    //Funciones
    void run();
    void updatePollEvents();
    void updateinput();
    void updateEnemies(const float& deltaTime);
    void update();
    void render();
};
#endif