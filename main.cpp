#include <iostream>
#include "GameObject.h"

float32 timeStep = 1.0f / 60.0f;
int32 velocityIterations = 10;
int32 positionIterations = 8;
b2Vec2 gravity(0.0, 9.8);

int main() {
	b2World* world = new b2World(gravity);
	sf::RenderWindow window(sf::VideoMode(1280, 800), "Test");
	sf::Color color = sf::Color::White;
	// take the vertices from body coordinate system in box2d (Meters)
	// world coordinate system and then multiply by PPM to finally bring in to screen coordinates
	// 1m = 10px
	GameObject ball(window, world, GameObject::Ball, 4.0f, 64.0f, 0.0f);
	GameObject box(window, world, GameObject::Box, 4.0f, 15.0f, 0.0f);
	window.setFramerateLimit(60);
	while (window.isOpen()) {
		world->Step(timeStep, velocityIterations, positionIterations);
		ball.UpdatePosition(window);
		box.UpdatePosition(window);
		window.display();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
	}
}