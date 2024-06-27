#include "Game.h"
//Private functions
void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game 2", sf::Style::Close | sf::Style::Titlebar);
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
    if (!this->backgTexture.loadFromFile("src/Textures/Fondo.png"))
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

//Con/Des
Game::Game()
{
    this->initWindow();
    this->initTextures();
    this->initBackground();
    this->initPlayer();
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

void Game::update()
{
    
    this->updatePollEvents();
    this->updateinput();

    float deltaTime = this->clock.restart().asSeconds();
    this->player->update(deltaTime);
    
}

void Game::render()
{
    this->window->clear();
    this->window->draw(this->backgSprite);
    //Draw all the stuffs
    this->player->render(*this->window);

    this->window->display();
}
