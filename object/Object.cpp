#include "Object.h"

#include <iostream>
#include <bits/ostream.tcc>

Object::Object(Vector2d position, Vector2d velocity, double mass, double radius)
    : position(position), velocity(velocity), mass(mass), radius(radius) {
    name = "Object";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist_double(0.0, 1.0);
}

Object::Object(Vector2d position, Vector2d velocity, double mass, double radius, std::string name)
    : position(position), velocity(velocity), mass(mass), radius(radius), name(name) { }

void Object::applyForceAndMove(Vector2d force, float deltaTime) {
    velocity += (force / mass) * deltaTime;

    historyPositions.push_back(toVector2(position));

    position += velocity * deltaTime;
}

void Object::draw() {
    std::vector<Vector2> pointsVector(historyPositions.begin(), historyPositions.end());
    DrawSplineLinear(pointsVector.data(), pointsVector.size(), 1.0, GRAY);
    DrawCircleV(toVector2(position), radius, WHITE);
}

double Object::getMass() {
    return mass;
}

double Object::getRadius() const {
    return radius;
}

Vector2d Object::getVelocity() {
    return velocity;
}

Vector2d Object::getPosition() {
    return position;
}

Vector2d Object::getRandomPositionInside() {
    double r = getRadius() * sqrt(dist_double(gen));
    double theta = 2 * M_PI * dist_double(gen);

    return {getPosition().x + r * cos(theta), getPosition().y + r * sin(theta)};
}

Object::~Object() {

}
