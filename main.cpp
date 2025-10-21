#include <iostream>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include <cmath>

#include "raygui.h"
#include "vector"
#include "object/Object.h"
#include "types/Vector2d.h"
#include "types/Constants.h"

const float camera_speed = 100;

std::vector<Object> objects;

Camera2D camera = { 0 };

void init() {
    SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "My space simulator");
    SetTargetFPS(1000);

    camera.target = (Vector2){ 960.0, 540.0 };
    camera.offset = (Vector2){ 960.0, 540.0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void handleInput() {
    camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*1.0f));
    if (IsKeyDown(KEY_D)) camera.target.x += camera_speed;
    if (IsKeyDown(KEY_A)) camera.target.x -= camera_speed;
    if (IsKeyDown(KEY_W)) camera.target.y -= camera_speed;
    if (IsKeyDown(KEY_S)) camera.target.y += camera_speed;
}

void collide() {
    std::vector<bool> removeMask(objects.size(), false);
    std::vector<Object> newObjects;
    newObjects.reserve(objects.size());

    for (size_t i = 0; i < objects.size(); i++) {
        for (size_t j = i + 1; j < objects.size(); j++) {
            if (objects[i].getPosition().distanceTo(objects[j].getPosition()) <= (objects[i].getRadius() + objects[j].getRadius())) {
                removeMask[i] = true;
                removeMask[j] = true;

                Vector2d newObjectPosition = objects[i].getPosition() + (objects[j].getPosition() - objects[i].getPosition()).normalize() * objects[i].getRadius();
                Vector2d newObjectVelocity = (objects[i].getVelocity() * objects[i].getMass() + objects[j].getVelocity() * objects[j].getMass()) / (objects[i].getMass() + objects[j].getMass());

                newObjects.emplace_back(newObjectPosition, newObjectVelocity, objects[i].getMass() + objects[j].getMass(), (cbrt(pow(objects[i].getRadius(), 3) + cbrt(objects[j].getRadius()))));
            }
        }
    }

    for (size_t i = 0; i < objects.size(); i++) {
        if (!removeMask[i]) {
            newObjects.emplace_back(std::move(objects[i]));
        }
    }
    objects.swap(newObjects);
}

void applyForceAndMove(float deltaTime) {
    for (auto &object : objects) {
        Vector2d totalForce(0, 0);
        for (auto &object2 : objects) {
            if (&object != &object2) {
                totalForce += (object2.getPosition() - object.getPosition()) * (object.getMass() * object2.getMass()) * physics::G / pow(object.getPosition().distanceTo(object2.getPosition()), 3);
            }
        }
        object.applyForceAndMove(totalForce, deltaTime);
    }
}

void drawUI() {
    DrawFPS(5, 5);
}

void draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(camera);

    for (auto &object : objects) {
        object.draw();
    }

    EndMode2D();

    drawUI();

    EndDrawing();
}

int main() {
    init();

    objects.emplace_back(Vector2d(960.0, 540.0), Vector2d(0.0, 0.0), 1.989e30, 6.963e8);  //SUN
    objects.emplace_back(Vector2d(960.0 + 1.496e11, 540.0), Vector2d(0.0, -29780.0), 5.972e24, 6.371e6);  //EARTH
    objects.emplace_back(Vector2d(960.0 + 1.496e11 + 3.844e8, 540.0), Vector2d(0.0, -1022.0), 7.348e22, 1.737e6); //MOON

    // objects.emplace_back(Vector2d(960.0, 540.0), Vector2d(0.0, 0.0), 1.0, 10);
    // objects.emplace_back(Vector2d(970.0, 540.0), Vector2d(0.0, 0.0), 1.0, 10);

    // std::random_device dev;
    // std::mt19937 rng(dev());
    // std::uniform_real_distribution<float> distf(0.0f, 20000.0f);
    // std::uniform_real_distribution<float> distfm(1.0f, 500.0f);
    // std::uniform_int_distribution<std::mt19937::result_type> disti(1,15); // distribution in range [1, 6]

    // for (int i = 0; i < 1000; i++) {
    //     objects.emplace_back(Vector2d(distf(rng), distf(rng)), Vector2d(0.0, 0.0), distfm(rng)*1e15, disti(rng));
    // }

    // objects.emplace_back(Vector2d(960.0, 540.0), Vector2d(0.0, 0.0), 1e15, 5);
    // objects.emplace_back(Vector2d(660.0, 140.0), Vector2d(0.0, 0.0), 1e15, 10);
    // objects.emplace_back(Vector2d(1260.0, 340.0), Vector2d(0.0, 0.0), 18e13 , 2);

    while (!WindowShouldClose())
    {
        handleInput();
        applyForceAndMove(GetFrameTime());
        collide();
        draw();
    }

    CloseWindow();

    return 0;
}