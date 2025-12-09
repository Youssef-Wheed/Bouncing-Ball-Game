#include <SFML/Graphics.hpp>
#include <cstdlib>   // for std::rand, std::srand
#include <ctime>     // for std::time
#include <iostream>

// Function to generate a random color
sf::Color randomColor() {
    return sf::Color(static_cast<sf::Uint8>(std::rand() % 256),
                     static_cast<sf::Uint8>(std::rand() % 256),
                     static_cast<sf::Uint8>(std::rand() % 256));
}

int main() {
    const unsigned int WINDOW_W = 800;
    const unsigned int WINDOW_H = 600;

    // Create the game window
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Bouncing Ball - Youssef");

    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create the ball
    const float radius = 20.f;
    sf::CircleShape ball(radius);
    ball.setOrigin(radius, radius); // Set origin to center for easier movement
    ball.setPosition(WINDOW_W / 2.f, WINDOW_H / 2.f); // Start at center
    ball.setFillColor(randomColor()); // Assign initial random color

    // Ball velocity in pixels per second
    sf::Vector2f velocity(200.f, 150.f);

    // Clock to calculate delta time
    sf::Clock clock;

    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            
            // Optional: change ball color when mouse is clicked
            if (event.type == sf::Event::MouseButtonPressed) {
                ball.setFillColor(randomColor());
            }
        }

        // Calculate delta time
        float dt = clock.restart().asSeconds();

        // Update ball position
        sf::Vector2f pos = ball.getPosition();
        pos += velocity * dt;
        ball.setPosition(pos);

        // Collision detection with window boundaries + reflection + color change
        bool hit = false;

        // Left wall
        if (pos.x - radius <= 0.f) {
            pos.x = radius;
            velocity.x = -velocity.x;
            hit = true;
        }
        // Right wall
        else if (pos.x + radius >= WINDOW_W) {
            pos.x = WINDOW_W - radius;
            velocity.x = -velocity.x;
            hit = true;
        }
        // Top wall
        if (pos.y - radius <= 0.f) {
            pos.y = radius;
            velocity.y = -velocity.y;
            hit = true;
        }
        // Bottom wall
        else if (pos.y + radius >= WINDOW_H) {
            pos.y = WINDOW_H - radius;
            velocity.y = -velocity.y;
            hit = true;
        }

        if (hit) {
            ball.setPosition(pos);           // Ensure ball stays inside window
            ball.setFillColor(randomColor()); // Change color on wall hit
        }

        // Rendering
        window.clear(sf::Color::Black); // Clear screen with black
        window.draw(ball);              // Draw the ball
        window.display();               // Display the current frame
    }

    return 0;
}
