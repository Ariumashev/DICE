#include <iostream>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "components/Card.hpp"
#include "components/Chip.hpp"
#include "core/GameObject.hpp"
#include "ui/View.hpp"
#include <spdlog/spdlog.h>

using dice::components::Card;
using dice::components::Chip;
using dice::core::GameObject;
using dice::view::View;
using dice::view::ViewConfig;

// Function for creating textures
sf::Texture createColoredTexture(int width, int height, const sf::Color& color) {
    sf::Texture texture;
    texture.create(width, height);
    sf::Image image;
    image.create(width, height, color);
    texture.update(image);
    return texture;
}

int main() {
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("DICE Application Starting...");

    sf::RenderWindow window(sf::VideoMode(1280, 720), "DICE");
    window.setFramerateLimit(60);

    View view(window);

    ViewConfig config;
    config.backgroundColor = sf::Color(30, 30, 40);
    config.showFPS = true;
    config.showObjectCount = true;
    config.showControls = true;
    view.setConfig(config);

    // Creating textures
    const sf::Texture cardFrontTex = createColoredTexture(100, 140, sf::Color(220, 220, 255));
    const sf::Texture cardBackTex = createColoredTexture(100, 140, sf::Color(80, 80, 120));
    const sf::Texture chipTex = createColoredTexture(64, 64, sf::Color::Red);
    const sf::Texture blueChipTex = createColoredTexture(64, 64, sf::Color(100, 100, 255));
    const sf::Texture boardTex = createColoredTexture(800, 600, sf::Color(150, 150, 150));

    std::vector<std::shared_ptr<GameObject>> objects;

    // Board
    auto board = std::make_shared<GameObject>("board", "Board");
    board->setTexture(&boardTex);
    board->setColor(sf::Color(200, 180, 140));
    board->setScale(1.6F, 1.2F);
    board->setPosition(640, 360);
    board->setZOrder(0);
    objects.push_back(board);

    // Cards
    auto card1 = std::make_shared<Card>("card1", "Dragon");
    card1->setFrontTexture(&cardFrontTex);
    card1->setBackTexture(&cardBackTex);
    card1->setPosition(300, 300);
    card1->setZOrder(10);
    card1->setPlayer(1);
    card1->setFaceUp(true);
    objects.push_back(card1);

    auto card2 = std::make_shared<Card>("card2", "Mage");
    card2->setFrontTexture(&cardFrontTex);
    card2->setBackTexture(&cardBackTex);
    card2->setPosition(420, 320);
    card2->setZOrder(11);
    card2->setPlayer(2);
    card2->setFaceUp(false);
    objects.push_back(card2);

    // Chips
    auto chip1 = std::make_shared<Chip>("chip1", "Red Chip");
    chip1->setTexture(&chipTex);
    chip1->setRadius(30.0F);
    chip1->setPosition(600, 350);
    chip1->setZOrder(20);
    chip1->setPlayer(1);
    objects.push_back(chip1);

    auto chip2 = std::make_shared<Chip>("chip2", "Blue Chip");
    chip2->setTexture(&blueChipTex);
    chip2->setRadius(30.0F);
    chip2->setPosition(700, 380);
    chip2->setZOrder(20);
    chip2->setPlayer(2);
    objects.push_back(chip2);

    spdlog::info("Created {} objects", objects.size());

    // Variables for interaction
    sf::Clock clock;

    spdlog::info("Entering main loop...");

    while (window.isOpen()) {
        const float deltaTime = clock.restart().asSeconds();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-union-access)
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            view.handleEvent(event);
        }

        view.update(deltaTime);

        view.render(objects);

        window.display();
    }

    spdlog::info("Application finished");
    return 0;
}