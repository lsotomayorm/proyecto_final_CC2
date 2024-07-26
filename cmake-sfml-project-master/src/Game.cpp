#include "Game.h"
//Funciones Privadas
void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Bomb Storm", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(55);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
    this->player1 = new Player;
    this->player2 = new Player;
    this->player2->setPosition(400.f,538.f);
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

void Game::updateCollisions()
{
    for(auto* enemy : this->enemies)
    {
        if(enemy->getBounds().intersects(this->player1->getBounds()))
        {
            this->player1->takeDamage(enemy->getDamage());

            delete enemy;
            this->enemies.erase(std::remove(this->enemies.begin(), this->enemies.end(), enemy), this->enemies.end());

        }

        if(enemy->getBounds().intersects(this->player2->getBounds()))
        {
            this->player2->takeDamage(enemy->getDamage());

            delete enemy;
            this->enemies.erase(std::remove(this->enemies.begin(), this->enemies.end(), enemy), this->enemies.end());
            
        }
    }

    if(this->player1->getHealth() == 0){
        this->player1->setPosition(-400.f,-538.f);
        misiles = false;
    }
    if(this->player2->getHealth() == 0){
        this->player2->setPosition(-400.f,-538.f);misiles = false;
        misiles = false;
    }
}

void Game::initFonts()
{
    if (!this->font.loadFromFile("../../src/Fonts/pixel-letters.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Could not load font file." << "\n";
    }
}

void Game::initTexts()
{
    this->player1HealthText.setFont(this->font);
    this->player1HealthText.setCharacterSize(20);
    this->player1HealthText.setFillColor(sf::Color::White);
    this->player1HealthText.setPosition(10.f, 10.f);

    this->player2HealthText.setFont(this->font);
    this->player2HealthText.setCharacterSize(20);
    this->player2HealthText.setFillColor(sf::Color::White);
    this->player2HealthText.setPosition(600.f, 10.f);
}

//Con/Des
Game::Game()
{
    this->initWindow();
    this->initTextures();
    this->initBackground();
    this->initPlayer();
    this->initEnemies();
    this->initFonts();
    this->initTexts();
    misiles = true;
}

Game::~Game()
{
    delete this->window;
    delete this->player1;
    delete this->player2;

}
//Funciones
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
    //Mover al Player1
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->player1->move(-1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->player1->move(1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        this->player1->jump();
    }
    //Mover al Player2
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        this->player2->move(-1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        this->player2->move(1.f, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        this->player2->jump();
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
    this->player1->update(deltaTime);
    this->player2->update(deltaTime);
    this->updateEnemies(deltaTime);
    this->updateCollisions();

    this->player1HealthText.setString("Player 1 Health " + std::to_string(this->player1->getHealth()));
    this->player2HealthText.setString("Player 2 Health " + std::to_string(this->player2->getHealth()));
    
}

void Game::render()
{
    this->window->clear();
    this->window->draw(this->backgSprite);
    //Dibuja todas las cosas
    this->player1->render(*this->window);
    this->player2->render(*this->window);
    //Dibuja a los enmigos
    for (auto* enemy : this->enemies)
    {
        enemy->render(*this->window);
    }
    this->window->draw(this->player1HealthText);
    this->window->draw(this->player2HealthText);
    this->window->display();
}
