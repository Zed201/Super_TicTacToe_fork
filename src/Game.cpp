#include "../include/Game.hpp"
#include "../include/events.hpp"
#include <iostream>
#include <ctime>

using std::make_unique;

// Private funtions
void Game::init_variables()
{
    window = nullptr;

    // Game logic
    // max_squares = 9;
    
    // squares.resize(9);
    // for (size_t i = 0; i < 9; i++)
    //     squares[i].reserve(9);

    lines.reserve(4);
}

void Game::init_window()
{
    video_mode.height = 900;
    video_mode.width = 1680;
    // video_mode.getDesktopMode();

    window = make_unique<sf::RenderWindow>(video_mode, "Super Tic Tac Toe", sf::Style::Close); 
    window->setFramerateLimit(60);
}

void Game::init_board()
{
    vertical_line.setSize(sf::Vector2f(10.f, 790.f));
    vertical_line.setFillColor(sf::Color::Black);

    Horizontal_line.setSize(sf::Vector2f(790.f, 10.f));
    Horizontal_line.setFillColor(sf::Color::Black);
}


// Constructor / Destructor
Game::Game()
{
    init_variables(); // init game objects
    init_window();
    init_board();
    spawn_board();
}

Game::~Game()
{
}

// Accessors
const bool Game::running() const
{
    return window->isOpen();
}

// Functions

/* will set the position of all the 81 squares and insert them into the squares vector */
void Game::spawn_board()
{
    float x = 500.f, y = 100.f;
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
            tick.board[i][j].rect.setPosition({x + i * 75, y + j * 75});
    }
    
    // vertical lines
    for (int i = 0; i < 2; i++)
    {
        vertical_line.setPosition({720 + static_cast<float>(225 * i), y-60});
        lines.push_back(vertical_line);
    }
    
    // horizontal lines
    for (int i = 0; i < 2; i++)
    {
        Horizontal_line.setPosition({x-55, y + 220 + static_cast<float>(225 * i)});
        lines.push_back(Horizontal_line);
    }
}

void Game::update_poll_events()
{
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
            
            // pressing Esc to close
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
                break;

            default:
                break;
        }   
    }
}

/* update the squares if they were scored or selected */
void Game::update_squares()
{
    sf::Mouse::Button button;
    for (auto &i : tick.board)
    {
        for (auto &s : i)
        {
            button_click(button, s, window, tick, player);
        }
    }
}

/* Updates the mouse position on the game window */
void Game::update_mouse_pos()
{
    mouse_pos = sf::Mouse::getPosition(*window);
}

void Game::update()
{
    update_poll_events();
    update_mouse_pos();
    update_squares();
}

void Game::render_squares()
{
    for (auto &i : tick.board)
        for (auto &s : i)
            window->draw(s.rect);
    
    for (auto &l : lines)
        window->draw(l);
}

void Game::render()
{
    window->clear(sf::Color::White); // clear old frame

    // Draw game objects
    render_squares();

    window->display(); // done drawing
}
