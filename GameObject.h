#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class GameObject {
private:
	b2Body* physicalBody;
	b2World* world;
public:
	static float PPM;
	const typedef enum Type {
		Ball,
		Box
	};
	b2BodyDef* bodyDef;
	b2FixtureDef fixture;
	Type type;
	sf::Color color;
	sf::CircleShape circleShape;
	sf::RectangleShape rectShape;
	sf::ConvexShape polyShape;
	GameObject(sf::RenderWindow& window, b2World* world, Type type, float size, float xPos, float yPos);
	void UpdatePosition(sf::RenderWindow& window);
	b2Vec2 GetPosition();
	b2Body* GetBody();
};