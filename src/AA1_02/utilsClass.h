#pragma once
#include "utils.h"

enum SceneState { RUNNING, EXIT };
enum SceneType { MENU, GAME, QUIT };

class Player {
public:
    Vec2 position;
    const char* pathSprite;

    Player(Vec2 pos, const char* spritePath)
    {
        position.x = pos.x;
        position.y = pos.y;
        pathSprite = spritePath;
    }

    void move();
    void update();

};


class Scene {

private:
    SceneState state;
    const char* pathSprite;
    const char* pathSound;
    SDL_Renderer* m_renderer;
    Vec2 screenSize;

public:
    Scene(const char* soundPaht, const char* spritePath, Vec2 sizeScreen, SDL_Renderer* renderer_m) {
        pathSound = soundPaht;
        pathSprite = spritePath;
        screenSize.x = sizeScreen.x;
        screenSize.y = sizeScreen.y;
        m_renderer = renderer_m;
        state = RUNNING;
    }

    SceneState getState() { return state; }

    void draw()
    {
        //Background
        SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, pathSprite) };
        if (bgTexture == nullptr) throw "Error: bgTexture init";
        SDL_Rect bgRect{ 0,0,screenSize.x, screenSize.y };

    }

};