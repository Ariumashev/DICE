#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include <spdlog/spdlog.h>

// For sol2 and Lua
extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}
#include <sol/sol.hpp>

#include "components/Card.hpp"
#include "components/Chip.hpp"
#include "core/GameObject.hpp"

int main() {
    // Initializing the logger
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("DICE Application Starting...");

    // Creating an SFML window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "DICE - Components Demo");
    window.setFramerateLimit(60);

    // === Creating a texture ===

    // Texture for card (the front side)
    sf::Texture cardFrontTexture;
    cardFrontTexture.create(100, 140);
    sf::Image cardFrontImage;
    cardFrontImage.create(100, 140, sf::Color(200, 255, 220));
    // Drawing a frame
    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 140; y++) {
            if (x < 5 || x > 94 || y < 5 || y > 134) {
                cardFrontImage.setPixel(x, y, sf::Color(150, 150, 200));
            }
        }
    }
    cardFrontTexture.update(cardFrontImage);

    // Texture for card (the back side)
    sf::Texture cardBackTexture;
    cardBackTexture.create(100, 140);
    sf::Image cardBackImage;
    cardBackImage.create(100, 140, sf::Color(80, 80, 120));
    // Drawing a pattern
    for (int x = 0; x < 100; x += 10) {
        for (int y = 0; y < 140; y += 10) {
            cardBackImage.setPixel(x, y, sf::Color(150, 150, 200));
        }
    }
    cardBackTexture.update(cardBackImage);

    // Texture for chips
    sf::Texture chipTexture;
    chipTexture.create(64, 64);
    sf::Image chipImage;
    chipImage.create(64, 64, sf::Color::Transparent);
    // Drawing a circle
    for (int x = 0; x < 64; x++) {
        for (int y = 0; y < 64; y++) {
            int dx = x - 32;
            int dy = y - 32;
            if (dx * dx + dy * dy <= 30 * 30) {
                chipImage.setPixel(x, y, sf::Color::Red);
            }
        }
    }
    chipTexture.update(chipImage);

    // === Creating objects ===
    std::vector<std::shared_ptr<dice::core::GameObject>> objects;

    // Card 1 (face up)
    auto card1 = std::make_shared<dice::components::Card>("card1", "Dragon");
    card1->setFrontTexture(&cardFrontTexture);
    card1->setBackTexture(&cardBackTexture);
    card1->setFaceUp(true);
    card1->setPosition(350, 450);
    card1->setZOrder(10);
    card1->setPlayer(1);
    card1->addTag("creature");
    card1->setProperty<int>("attack", 8);
    objects.push_back(card1);

    // Card 2 (not face up)
    auto card2 = std::make_shared<dice::components::Card>("card2", "Wizard");
    card2->setFrontTexture(&cardFrontTexture);
    card2->setBackTexture(&cardBackTexture);
    card2->setFaceUp(false);
    card2->setPosition(350, 300);
    card2->setZOrder(10);
    card2->setPlayer(2);
    card2->addTag("spellcaster");
    objects.push_back(card2);

    // Chip 2
    auto chip1 = std::make_shared<dice::components::Chip>("chip1", "Red Chip");
    chip1->setTexture(&chipTexture);
    chip1->setRadius(30.f);
    chip1->setPosition(550, 300);
    chip1->setZOrder(20);
    chip1->setPlayer(1);
    chip1->addTag("player1");
    objects.push_back(chip1);

    // Chip 2 (the dark version)
    auto chip2 = std::make_shared<dice::components::Chip>("chip2", "Dark red Chip");
    chip2->setTexture(&chipTexture);
    chip2->setColor(sf::Color(100, 100, 255));
    chip2->setRadius(30.f);
    chip2->setPosition(550, 400);
    chip2->setZOrder(20);
    chip2->setPlayer(2);
    chip2->addTag("player2");
    objects.push_back(chip2);

    // background/board
    auto board = std::make_shared<dice::core::GameObject>("board", "The playing field");
    board->setTexture(&cardBackTexture);
    board->setColor(sf::Color(150, 150, 150));
    board->setScale(5.f, 3.f);
    board->setPosition(512, 384);
    board->setZOrder(0);
    objects.push_back(board);

    spdlog::info("{} objects created", objects.size());

    // === LUA (test) ===
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.script(R"(
        function onCardClick(card_name)
            print("Lua: clicked on the card " .. card_name)
            return "ok"
        end
    )");

    // === Game Cycle ===
    sf::Clock clock;
    std::shared_ptr<dice::core::GameObject> selectedObject = nullptr;
    sf::Vector2f dragOffset;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            // Processing mouse clicks
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                // Looking for an object under the mouse (starting from the end)
                selectedObject = nullptr;
                for (auto it = objects.rbegin(); it != objects.rend(); ++it) {
                    auto& obj = *it;

                    if (obj->getType() == "Chip") {
                        auto chip = std::dynamic_pointer_cast<dice::components::Chip>(obj);
                        if (chip && chip->hitTest(mousePos)) {
                            selectedObject = obj;
                            spdlog::info("Selected Chip: {}", obj->getName());
                            break;
                        }
                    } else {
                        if (obj->contains(mousePos)) {
                            selectedObject = obj;
                            spdlog::info(
                                "Selected object: {} ({})", obj->getName(), obj->getType());

                            // For cards, turn it over
                            if (obj->getType() == "Card") {
                                auto card = std::dynamic_pointer_cast<dice::components::Card>(obj);
                                card->flip();
                                spdlog::debug("The card is turned over. Face up: {}",
                                              card->isFaceUp());

                                // Calling Lua
                                try {
                                    lua["onCardClick"](obj->getName());
                                } catch (...) {
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }

        // Rendering
        window.clear(sf::Color(50, 50, 50));

        std::sort(objects.begin(), objects.end(), [](const auto& a, const auto& b) {
            return a->getZOrder() < b->getZOrder();
        });

        for (auto& obj : objects) {
            window.draw(*obj);
        }

        window.display();
    }

    // === Serialization ===
    spdlog::info("=== Serialization ===");
    nlohmann::json sceneJson = nlohmann::json::array();
    for (auto& obj : objects) {
        sceneJson.push_back(obj->toJson());
    }
    spdlog::debug("JSON size: {} objects", sceneJson.size());

    std::ofstream file("scene_save.json");
    file << sceneJson.dump(2);
    file.close();
    spdlog::info("The scene is saved in scene_save.json");

    spdlog::info("The DICE application is shutting down...");
    return 0;
}