#include "Player.h"

Player::Player() : position({1,1,40,40}), frame({0,0,20,20}), type(PlayerType::NONE){}

//void Player::Update(InputData input)
//{
//	Move(input);
//	UpdateSprite();
//}

//bool Player::Move(InputData input)
//{
//	dir = EDirection::NONE;
//	VEC2 newPos = { position.x,position.y };
//
//	switch (type)
//	{
//	case Player::PlayerType::PL1:
//		if (input.IsPressed(InputKeys::LEFT))
//		{
//			newPos.x--; 
//			dir = EDirection::LEFT;
//		}
//
//		if (input.IsPressed(InputKeys::RIGHT))
//		{
//			newPos.x++;
//			dir = EDirection::RIGHT;
//		}
//
//		if (input.IsPressed(InputKeys::UP))
//		{
//			newPos.y--;
//			dir = EDirection::UP;
//		}
//
//		if (input.IsPressed(InputKeys::DOWN))
//		{
//			newPos.y++;
//			dir = EDirection::DOWN;
//		}
//		break;
//
//	case Player::PlayerType::PL2:
//		if (input.IsPressed(InputKeys::A))
//		{
//			newPos.x--;
//			dir = EDirection::LEFT;
//		}
//
//		if (input.IsPressed(InputKeys::D))
//		{
//			newPos.x++;
//			dir = EDirection::RIGHT;
//		}
//
//		if (input.IsPressed(InputKeys::W))
//		{
//			newPos.y--;
//			dir = EDirection::UP;
//		}
//
//		if (input.IsPressed(InputKeys::S))
//		{
//			newPos.y++;
//			dir = EDirection::DOWN;
//		}
//		break;
//
//	default:
//		return false;
//		break;
//	}
//
//	//Check player Collision
//	
//
//	//Update Colision
//	if (newPos.x != position.x || newPos.y != position.y)
//	{
//		position.x = newPos.x;
//		position.y = newPos.y;
//		return true;
//	}
//
//	return false;
//}

void Player::UpdateSprite()
{
	if (dir != EDirection::NONE) frameCount++;

	if (60 / frameCount <= 9)
	{
		frameCount = 0;
		frame.x += frame.w;
		if (frame.x >= frame.w * lastCol)
			frame.x = frame.w * initCol;
	}

	switch (dir)
	{
	case EDirection::DOWN:
		frame.y = (initRow + 0) * frame.h;
		break;
	case EDirection::LEFT:
		frame.y = (initRow + 1) * frame.h;
		break;
	case EDirection::RIGHT:
		frame.y = (initRow + 2) * frame.h;
		break;
	case EDirection::UP:
		frame.y = (initRow + 3) * frame.h;
		break;
	case EDirection::NONE:
		frame.y = (initRow + 0) * frame.h;
		break;
	default:
		frame.y = (initRow + 0) * frame.h;
		break;
	}
}

//void Player::setPlayer(int textWidht, int textHeight, int ncol, int nRow, PlayerType _type)
//{
//	type = _type;
//
//	frame.w = textWidht / ncol;
//	frame.h = textHeight / nRow;
//
//	switch (_type)
//	{
//	case Player::PlayerType::PL1:
//		initCol = 3;
//		lastCol = initCol + 3;
//		initRow = 0;
//		lastRow = initRow + 4;
//		frame.x = frame.w * initCol;
//		frame.y = frame.h * initRow;
//
//		position.x = 100;
//		position.y = 250;
//		break;
//	case Player::PlayerType::PL2:
//		initCol = 6;
//		lastCol = initCol + 3;
//		initRow = 4;
//		lastRow = initRow + 4;
//		frame.x = frame.w * initCol;
//		frame.y = frame.h * initRow;
//
//		position.x = 600;
//		position.y = 250;
//		break;
//	default:
//		frame.x = 0;
//		frame.y = 0;
//		break;
//	}
//}

