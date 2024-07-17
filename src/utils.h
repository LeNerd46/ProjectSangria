#pragma once
#include <keypadc.h>
#include <math.h>
#include <graphx.h>

#include "gfx/gfx.h"
#include "animations.h"

#define TILEMAP_WIDTH 39
#define TILEMAP_HEIGHT 9

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

// 21 x 14 for fullscreen (I think?)
#define TILEMAP_DRAW_WIDTH 21
#define TILEMAP_DRAW_HEIGHT 9

#define MIDDLE_X (GFX_LCD_WIDTH / 2 - 8)
#define MIDDLE_Y (GFX_LCD_HEIGHT / 2 - 8)

struct Player
{
public:
	gfx_rletsprite_t* playerDownFrames[4];
	gfx_rletsprite_t* playerUpFrames[4];
	gfx_rletsprite_t* playerLeftFrames[4];
	gfx_rletsprite_t* playerRightFrames[4];

	Animation playerDown;
	Animation playerUp;
	Animation playerLeft;
	Animation playerRight;

	int x;
	int y;

	int xOffset{};
	int yOffset{};

	int horizontalVelocity{};
	int verticalVelocity{};

	unsigned char speed = 3;
	unsigned char restingPosition{};

	bool control;

	Player()
	{
		x = GFX_LCD_WIDTH / 2 - 8;
		y = GFX_LCD_HEIGHT / 2 - 8;

		playerDownFrames[0] = player_tile_0; playerDownFrames[1] = player_tile_3; playerDownFrames[2] = player_tile_0; playerDownFrames[3] = player_tile_6;
		playerUpFrames[0] = player_tile_2; playerUpFrames[1] = player_tile_5; playerUpFrames[2] = player_tile_2; playerUpFrames[3] = player_tile_8;
		playerLeftFrames[0] = player_tile_1; playerLeftFrames[1] = player_tile_4; playerLeftFrames[2] = player_tile_7; playerLeftFrames[3] = player_tile_8;
		playerRightFrames[0] = playerFlipped_tile_2; playerRightFrames[1] = playerFlipped_tile_1; playerRightFrames[2] = playerFlipped_tile_2; playerRightFrames[3] = playerFlipped_tile_0;

		playerDown = Animation(playerDownFrames, 6, 3);
		playerUp = Animation(playerUpFrames, 6, 3);
		playerLeft = Animation(playerLeftFrames, 6, 3);
		playerRight = Animation(playerRightFrames, 6, 3);

		control = true;
	}
};

class Object
{
public:
	unsigned int id;

	unsigned int x;
	unsigned int y;

	char xOffset{};
	char yOffset{};

	unsigned char width;
	unsigned char height;

	bool collidable;

	gfx_rletsprite_t* sprite;

	Object(unsigned int id, unsigned int x, unsigned int y, unsigned char width, unsigned char height, bool collidable, gfx_rletsprite_t* sprite) : id(id), x(x), y(y), width(width), height(height), collidable(collidable), sprite(sprite) {}
};

void drawPlayer(Player& player, AnimationManager& manager, int playerId);
void drawPlayerSingle(Player& player, AnimationManager& manager, int playerId, gfx_tilemap_t& tilemap);

int checkObjectCollision(Player& player, Object* objects[], gfx_tilemap_t& tilemap, unsigned int objectCount, bool single, unsigned int minimumDistance, bool debug);

bool getKeyDown(kb_lkey_t key);
bool getKey(kb_lkey_t key);

bool checkCollision(int firstX, int firstY, int firstWidth, int firstHeight, int secondX, int secondY, int secondWidth, int secondHeight);
unsigned char checkCollisionSide(int firstX, int firstY, int firstWidth, int firstHeight, int secondX, int secondY, int secondWidth, int secondHeight);

int absoluteValue(int value);
int distance(int x1, int y1, int x2, int y2);