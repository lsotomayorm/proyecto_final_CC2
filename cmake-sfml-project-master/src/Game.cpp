#include "Game.h"
//Private functions
void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Bomb Storm", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(55);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
    this->player = new Player;
}

void Game::initTextures()
{

}

void Game::initBackground()
{
    if (!this->backgTexture.loadFromFile("../../src/Textures/Fondo.png"))
    {
        std::cout << "ERROR::GAME::INITBACKGROUND::Could not load background texture file." << "\n";
    }
    this->backgSprite.setTexture(this->backgTexture);
    sf::Vector2u windowSize = this->window->getSize();
    sf::Vector2u textureSize = this->backgTexture.getSize();

    this->backgSprite.setScale(
        float(windowSize.x) / float(textureSize.x),
        float(windowSize.y) / float(textureSize.y)
    );
}

void Game::initEnemies()
{
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
}

//Con/Des
Game::Game()
{
    this->initWindow();
    this->initTextures();
    this->initBackground();
    this->initPlayer();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
    delete this->player;
    //Delete textures

}
//Functions
void Game::run()
{
    while(this->window->isOpen())
    {
        this->update();
        this->render();
    }
}
void Game::updatePollEvents()
{
    sf::Event evnt;
    while(this->window->pollEvent(evnt)){
        if(evnt.type == sf::Event::Closed){
            this->window->close();
        }
        if(evnt.KeyPressed && evnt.key.code == sf::Keyboard::Escape){
            this->window->close();
        }
    }
}

void Game::updateinput()
{
    //move player
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->player->move(-1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->player->move(1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        this->player->jump();
    }
}

void Game::updateEnemies(const float& DeltaTime)
{
    if(this->spawnTimer < this->spawnTimerMax)
        this->spawnTimer += 1.f;
    else{
        for (int i = 0; i < 4; i++)
        {
            this->enemies.push_back(new Enemy(static_cast<float>(rand() % this->window->getSize().x - 50.0f), -50.0f));
        }
        
        this->spawnTimer = 0.f;
    }
    unsigned counter = 0;
    for (auto* enemy : this->enemies)
    {
        enemy->update(DeltaTime);

        // Si el enemigo ha pasado la parte inferior de la pantalla, elimínalo.
        if (enemy->getBounds().top > this->window->getSize().y)
        {
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
            --counter;
        }

        ++counter;
    }
}

void Game::update()
{
    
    this->updatePollEvents();
    this->updateinput();

    float deltaTime = this->clock.restart().asSeconds();
    this->player->update(deltaTime);
    this->updateEnemies(deltaTime);
    
}

void Game::render()
{
    this->window->clear();
    this->window->draw(this->backgSprite);
    //Draw all the stuffs
    this->player->render(*this->window);
    //Draw Enemies
    for (auto* enemy : this->enemies)
    {
        enemy->render(*this->window);
    }

    this->window->display();
}
