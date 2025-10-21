#pragma once
#include <deque>
#include <raylib.h>
#include "../types/Vector2d.h"
#include <raymath.h>
#include <string>
#include <random>
#include <vector>

class Object {
protected:
    Vector2d position;
    Vector2d velocity;
    double mass;
    double radius;
    std::vector<Vector2> historyPositions;
    std::string name;
    std::mt19937 gen;
    std::uniform_real_distribution<> dist_double;

public:
    Object(Vector2d position, Vector2d velocity, double mass, double radius);
    Object(Vector2d position, Vector2d velocity, double mass, double radius, std::string name);
    virtual ~Object();

    virtual void applyForceAndMove(Vector2d force, float deltaTime);
    virtual void draw();
    virtual void input() {}

    double getMass();
    double getRadius() const;
    Vector2d getPosition();
    Vector2d getVelocity();

    Vector2d getRandomPositionInside();
};
