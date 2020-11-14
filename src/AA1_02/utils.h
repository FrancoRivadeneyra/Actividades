#pragma once
#include <SDL.h>        // Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <exception>
#include <iostream>
#include <string>
#include <time.h>
#include "constant.h"

struct Vec2 {
    int x, y;
    Vec2(int a, int b) { x = a; y = b; }
    Vec2() { x = y = NULL; }
};

//put i rect un dins l'altre
bool pointInRect(Vec2 vec, SDL_Rect rect)
{
    return vec.x<rect.x + rect.w && vec.x>rect.x && vec.y<rect.y + rect.h && vec.y>rect.y;
}

//rect i rect
bool rectInRect(SDL_Rect rect1, SDL_Rect rect2)
{
    Vec2 aux(rect1.x, rect1.y);
    if (pointInRect(aux, rect2))return true;
    aux.x = rect1.x + rect1.w;
    if (pointInRect(aux, rect2))return true;
    aux.y = rect1.y + rect1.h;
    if (pointInRect(aux, rect2))return true;
    aux.x = rect1.x;
    if (pointInRect(aux, rect2))return true;

    return false;
}

void buttonMakerDefaultTexture(const char* text, SDL_Color color, int size, SDL_Renderer* m_renderer, Vec2 pos)
//Just need to renderPresent
{
    TTF_Font* defaultFont = TTF_OpenFont(pathFONTdefault, size);
    SDL_Surface* defaultSurface = TTF_RenderText_Solid(defaultFont, text, color);
    SDL_Texture* defaultTexture = SDL_CreateTextureFromSurface(m_renderer, defaultSurface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(defaultTexture, NULL, NULL, &texW, &texH);
    SDL_Rect defaultRect = { pos.x,pos.y,texW,texH };

    SDL_RenderCopy(m_renderer, defaultTexture, nullptr, &defaultRect);
    TTF_CloseFont(defaultFont);
    SDL_DestroyTexture(defaultTexture);
    SDL_FreeSurface(defaultSurface);
}