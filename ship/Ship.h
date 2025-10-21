#pragma once
#include "../object/Object.h"

class Ship : public Object {
    private:
    double rotation;
    Vector2d additionalForce;

    public:
    Ship(Vector2d position, Vector2d velocity, double mass, double radius, double rotation);
    ~Ship();

    void applyForceAndMove(Vector2d force, float deltaTime) override;
    void draw() override;
    void input() override;
};

