#include "GameObject.h"
#include <iostream>
float GameObject::PPM = 10.0f;

GameObject::GameObject(sf::RenderWindow& window,b2World* world,Type type,float size,float xPos,float yPos) {
	this->type = type;
	this->world = world;
	color = sf::Color::White;
	bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	physicalBody = this->world->CreateBody(bodyDef);
	b2CircleShape circle;
	b2PolygonShape poly;
	switch (type) {
		case GameObject::Ball:
		{
			circle.m_radius = size;
			fixture.shape = &circle;
			fixture.density = 1.0f;
			fixture.friction = 0.3f;
			fixture.restitution = 0.5f;
			physicalBody->CreateFixture(&fixture);
			physicalBody->SetTransform(b2Vec2(xPos, yPos), 0.0f);
			circleShape.setRadius(size * PPM);
			circleShape.setFillColor(color);
			circleShape.setPosition(xPos * PPM, yPos * PPM);
			std::cout << "Ball instantiated at (" << xPos << ", " << yPos << ")" << std::endl;
			break;
		}
		case GameObject::Box:
		{
			poly.SetAsBox(size, size, b2Vec2(xPos, yPos), 0.0f);
			fixture.shape = &poly;
			fixture.density = 1.0f;
			fixture.friction = 0.3f;
			fixture.restitution = 0.5f;
			physicalBody->CreateFixture(&fixture);
			physicalBody->SetTransform(b2Vec2(xPos, yPos), 0.0f);
			polyShape.setFillColor(color);
			polyShape.setPointCount(4);
			for (int i = 0; i < 4; ++i) {
				polyShape.setPoint(i, sf::Vector2f(poly.GetVertex(i).x*this->PPM, poly.GetVertex(i).y*this->PPM));
			}
			std::cout << "Box instantiated at (" << xPos << ", " << yPos << ")" << std::endl;
			break;
		}
	}			
}
void GameObject::UpdatePosition(sf::RenderWindow& window) {
	b2Transform transform = this->GetBody()->GetTransform();
	b2Fixture* fixture = this->GetBody()->GetFixtureList();
	b2Vec2 pos = transform.p;
	switch(this->type) {
		case GameObject::Ball:
				this->circleShape.setPosition(pos.x*this->PPM,pos.y*this->PPM);
				window.draw(this->circleShape);
				break;
		case GameObject::Box:
				b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
				polyShape.setPosition(pos.x*this->PPM,pos.y*this->PPM);
				window.draw(this->polyShape);
				break;
		}
	}
b2Vec2 GameObject::GetPosition() {
	b2Transform transform = this->GetBody()->GetTransform();
	return transform.p;
}
b2Body* GameObject::GetBody() {
		return this->physicalBody;
}
