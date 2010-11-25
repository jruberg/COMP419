#include "worldobject.h"

WorldObject::WorldObject(CIwFVec2 position, Game* game) : position(position), game(game) { 
    setPosition(position);
}

WorldObject::WorldObject(const WorldObject& newObj) : position(newObj.position), game(newObj.game), theta(0.0f), r(0.0f) { }

void WorldObject::setPosition(float x, float y) {
    position = CIwFVec2(x, y);
    
    CIwFVec2 polar(position);
	polarize(polar);
	r = polar.x;
	theta = polar.y;
}

void WorldObject::setPosition(const CIwFVec2& newPosition) {
    setPosition(newPosition.x, newPosition.y);
}

CIwFVec2 WorldObject::getPosition() {
	return position; 
}

float WorldObject::getX() {
	return position.x;
}

float WorldObject::getY() {
	return position.y;
}

void WorldObject::setPolarPosition(float _r, float _theta){
	r = _r;
	theta = _theta;
	position.x = r * cos(theta);
	position.y = r * sin(theta);
}


float WorldObject::getR() {
	return r;
}

float WorldObject::getTheta() {
	return theta;
}

Game* WorldObject::getGame() {
	return game;
}