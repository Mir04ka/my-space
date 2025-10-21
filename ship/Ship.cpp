#include "Ship.h"

Ship::Ship(Vector2d position, Vector2d velocity, double mass, double radius, double rotation)
    : Object(position, velocity, mass, radius), rotation(rotation) { }

Ship::~Ship() {

}

void Ship::applyForceAndMove(Vector2d force, float deltaTime) {
    velocity += ((force + additionalForce) / mass) * deltaTime;

    position += velocity * deltaTime;
}

void Ship::draw() {
    DrawTriangle(Vector2(0, -200000), Vector2(-100000, 0), Vector2(100000, 0), BLUE);
}

void Ship::input() {
    if (IsKeyDown(KEY_W)) additionalForce.y = -1000;
    if (IsKeyDown(KEY_A)) additionalForce.x = -1000;
    if (IsKeyDown(KEY_D)) additionalForce.x = 1000;
}