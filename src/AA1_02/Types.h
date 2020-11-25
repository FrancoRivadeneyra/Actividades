#pragma once
#include <math.h>
#include <time.h>
#include <string>

struct VEC2
{
	int x, y;
	VEC2() : x(0), y(0) {};
	VEC2(int _xy) : x(_xy), y(_xy) {};
	VEC2(int _x, int _y) : x(_x), y(_y) {};

};


struct RECT
{
	int x, y, w, h;
	RECT() : x(0), y(0), w(0), h(0) {};
	RECT(int _x, int _y) : x(_x), y(_y), w(0), h(0) {};
	RECT(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};

};

enum class InputKeys
{
	NONE, LEFT, RIGHT, UP, DOWN, P, ESC,
	MOUSE_LEFT, MOUSE_RIGHT, W, A, S, D, COUNT
};

enum class EDirection
{
	NONE = -1, DOWN, LEFT, RIGHT, UP, COUNT
};

struct InputData
{
private:
	bool keyboardPressed[(int)InputKeys::COUNT] = {};
	bool keyboardkeyDown[(int)InputKeys::COUNT] = {};
	VEC2 mouseCoords;
	VEC2 screenSize;

	clock_t lastTime = clock();
	float deltaTime = 0.f;


public:
	void UpdateDeltaTime()
	{
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
	}
	VEC2 GetMouseCoords() { return mouseCoords; };
	void SetMouseCoords(VEC2 coords) { mouseCoords = coords; };
	bool IsPressed(InputKeys key)
	{
		return keyboardPressed[(int)key];
	}
	bool JustPressed(InputKeys key)
	{
		return keyboardkeyDown[(int)key];
	}
	void SetKeyValue(InputKeys key, bool value)
	{
		if (!keyboardPressed[(int)key])
		{
			keyboardkeyDown[(int)key] = value;
		}
		else
		{
			keyboardkeyDown[(int)key] = false;
		}
		keyboardPressed[(int)key] = value;
	}
	void SetScreenSize(VEC2 sSize) { screenSize = sSize; }
	//void Update();
	inline const float* GetDeltaTime() const { return &deltaTime; }
};

struct Font {
	const std::string id;
	std::string path;
	int size;
};

struct Color {
	uint8_t r, g, b, a;
};

struct Text {
	std::string id;
	std::string text;
	Color color;
	int w;
	int h;
};