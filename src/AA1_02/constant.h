#pragma once
#include <map>
#include <unordered_map>

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define FPS 60
#define DELAY_TIME 1000.0f/FPS

//CURSOR 
    //size
#define CURSOR_WIDTH 150    //350 base
#define CURSOR_HEIGHT 75    //100 base
    //speed              BASE 10 both
#define SPEED_X 10
#define SPEED_Y 10

//Sprite
#define widthSPRITE 6
#define heightSPRITE 1

//TIMER
#define gameTIME 60
// --- NUM
#define widthNUM 10
#define heightNUM 1

typedef std::unordered_map<std::string, SDL_Texture*> MTextures;
using MRects = std::unordered_map<std::string, SDL_Rect>;

//PATHS
    //Img
const std::string pathBG("../../res/img/bg.jpg");
const std::string pathPLAYER("../../res/img/kintoun.png");
const std::string pathSPRITE("../../res/img/sp01.png");
const std::string pathBGcastle("../../res/img/bgCastle.jpg");
const std::string pathNUM("../../res/img/num.png");
const std::string pathSPcastle("../../res/img/spCastle.png");
const std::string pathGOLD("../../res/img/gold.png");

//////////////////////////////////////////////////////////////////////

const std::string T_BG_MENU = "BackgroundMenu";
const std::string T_BG_INGAME = "BackgroundInGame";
const std::string T_CURSOR = "Cursor";
const std::string T_PLAYERS = "Players";
const std::string T_GOLD = "Gold";

    //Fonts
const std::string pathFONTsaiyan = ("../../res/ttf/saiyan.ttf");
const std::string pathFONTdefault = ("../../res/ttf/arial.ttf");
const std::string pathFONTdefault2 = "Sayan";
    //Mix
const std::string pathSOUNDTRACK("../../res/au/mainTheme.mp3");

//NOMBRE VARIABLES
    //Texturas
const std::string G_TF{ "textura fondo game" };
const std::string G_TIMER{ "textura Timer game" };
    //Rect
const std::string SCR_R{ "screen rect" };
        //TIMER RECTS
const std::string G_TIMER_mR{ "minRect" };
const std::string G_TIMER_mP{ "minPosition" };
const std::string G_TIMER_sR{ "secRect" };
const std::string G_TIMER_sP{ "secPosition" };
    //IMG
const std::string G_IF{ "IMG fondo game" };
    //TTF
const std::string SAYAN_F{ "SAYAN font" };
const std::string G_TEXT{ "Game text rect" };