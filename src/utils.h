#pragma once
#include <keypadc.h>
#include <math.h>
#include <graphx.h>

class Object
{
public:
	unsigned int id;

	unsigned int x;
	unsigned int y;

	char xOffset;
	char yOffset;

	unsigned char width;
	unsigned char height;

	bool collidable;

	gfx_rletsprite_t* sprite;

	Object(unsigned int id, unsigned int x, unsigned int y, unsigned char width, unsigned char height, bool collidable, gfx_rletsprite_t* sprite) : id(id), x(x), y(y), width(width), height(height), collidable(collidable), sprite(sprite) {}
};

bool getKeyDown(kb_lkey_t key);
bool getKey(kb_lkey_t key);

bool checkCollision(int firstX, int firstY, int firstWidth, int firstHeight, int secondX, int secondY, int secondWidth, int secondHeight);
unsigned char checkCollisionSide(int firstX, int firstY, int firstWidth, int firstHeight, int secondX, int secondY, int secondWidth, int secondHeight);

int absoluteValue(int value);
int distance(int x1, int y1, int x2, int y2);