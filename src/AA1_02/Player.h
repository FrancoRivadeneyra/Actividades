#pragma once

#include <vector>
#include <unordered_map>

#include "Collisions.h"
//#include "GoldBag.h"

class GoldBag;

class Player
{
private:
    struct DirectionMove {
        EDirection eD;
        VEC2 vD;

        DirectionMove() : eD(EDirection::NONE), vD(VEC2()) {};

        DirectionMove(EDirection e, VEC2 v) {
            eD = e;
            vD = v;
        }
    };

public:
    enum class PlayerType { NONE = -1, PL1, PL2, COUNT };

private:
    int score;

    RECT position;
    RECT frame;
    PlayerType type;
    EDirection dir = EDirection::DOWN;

    int initCol, lastCol;
    int initRow, lastRow;
    int frameCount;
    int Speed, SpeedMultiplier;

    std::unordered_map<InputKeys, DirectionMove> _bKeys;

    void bindKeys(PlayerType);

public:

    Player();
    Player(PlayerType);
    ~Player();

    void Update(InputData*, std::vector<GoldBag*>& goldBags);
    bool Move(InputData*);
    bool MoveAI(InputData*, std::vector<GoldBag*>& goldBags);
    void UpdateSprite();
    void UpdateCollisions(std::vector<GoldBag*>& goldBags, InputData* input);
    void Reset();

    inline const RECT* getPosition()const { return &position; }
    inline const RECT* getFrame()const { return &frame; }

    void setPlayerValues(int textWidth, int textHeight, int nCol, int nRow, PlayerType _type);

    inline const int* getScore() const { return &score; }
};


