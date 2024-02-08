#include <graphx.h>
#include <keypadc.h>
#include <time.h>

#include "utils.h"
#include "gfx/gfx.h"
#include "animations.h"

#define TILEMAP_WIDTH 37
#define TILEMAP_HEIGHT 9

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

// 21 x 14 for fullscreen (I think?)
#define TILEMAP_DRAW_WIDTH 21
#define TILEMAP_DRAW_HEIGHT 9

#define MIDDLE_X (GFX_LCD_WIDTH / 2 - 8)
#define MIDDLE_Y (GFX_LCD_HEIGHT / 2 - 8)

/*
* This is a very personal project, and I just want to share my story
* This story has changed throughout the past few years, and I'm still finding the best way to tell it
* I just want to say, I'm sorry. I know you won't see this, but I want to say it anyway
* I should've been more caring, I should've been there for you, I should've been better
* I know it's too late now, what's done is done, but I just really want you to know that I do still care
* You might hate me, that's fine, I probably would too were I in your shoes
* I'm still so grateful for the time I got to spend with you, thank you for all the memories
* I never got to do it then, so I'm doing it now
* This is my way of saying sorry, my way of saying goodbye
* Even if we're two different people now, even if we'll never see each other again, I just want to say
*
* I still care about you, and I'm sorry
* Thank you... for our time together
*/

extern unsigned char hospital_begin_map[];

int getDeltaTime()
{
	static clock_t previousTime;
	clock_t currentTime = clock();
	int output = 0;

	output = (currentTime - previousTime) * 1000 / CLOCKS_PER_SEC;

	previousTime = currentTime;
	return output;
}

void titleScreen()
{
	do
	{
		gfx_FillScreen(0xFF);

		gfx_SetTextFGColor(0xA0);
		gfx_PrintStringXY("Project Sangria", GFX_LCD_WIDTH / 3, GFX_LCD_HEIGHT / 4);

		gfx_PrintStringXY("Press [2nd] to start", GFX_LCD_WIDTH / 3 - 5, GFX_LCD_HEIGHT / 4 + 100);

		if (getKeyDown(kb_Key2nd))
			return;

		gfx_SwapDraw();

	} while (kb_Data[6] != kb_Clear);
}

int main()
{
	gfx_Begin();
	gfx_SetPalette(global_palette, sizeof_global_palette, 0);
	gfx_SetTransparentColor(2);
	gfx_SetDrawBuffer();

	titleScreen();

	gfx_FillScreen(0xFF);

	int x = GFX_LCD_WIDTH / 2 - 8;
	int y = GFX_LCD_HEIGHT / 2 - 8;

	gfx_tilemap_t tilemap;
	tilemap.map = hospital_begin_map;
	tilemap.tiles = hospital_begin_tiles;
	tilemap.type_width = gfx_tile_16_pixel;
	tilemap.type_height = gfx_tile_16_pixel;
	tilemap.tile_width = TILE_WIDTH;
	tilemap.tile_height = TILE_HEIGHT;
	tilemap.draw_width = TILEMAP_DRAW_WIDTH;
	tilemap.draw_height = TILEMAP_DRAW_HEIGHT;
	tilemap.width = TILEMAP_WIDTH;
	tilemap.height = TILEMAP_HEIGHT;
	tilemap.x_loc = 0;
	tilemap.y_loc = TILE_HEIGHT * 3;

	unsigned int xOffset = 0;
	unsigned int yOffset = 0;

	unsigned char speed = 3;
	unsigned char restingPosition{};

	bool debug = false;

	AnimationManager manager;

	gfx_rletsprite_t* playerDownFrames[] = { player_tile_0, player_tile_3, player_tile_0, player_tile_6 };
	gfx_rletsprite_t* playerUpFrames[] = { player_tile_2, player_tile_5, player_tile_2, player_tile_8 };
	gfx_rletsprite_t* playerLeftFrames[] = { player_tile_1, player_tile_4, player_tile_7, player_tile_8 };
	gfx_rletsprite_t* playerRightFrames[] = { playerFlipped_tile_2, playerFlipped_tile_1, playerFlipped_tile_2, playerFlipped_tile_0 };

	Animation playerDown(playerDownFrames, 6, 3);
	Animation playerUp(playerUpFrames, 6, 3);
	Animation playerLeft(playerLeftFrames, 6, 3);
	Animation playerRight(playerRightFrames, 6, 3);
	int playerId = manager.createAnimation(&playerDown);

	// Door is at 30, 1/2
	Object door(1, 464, 48, 16, 32, false, nullptr);

	Object* objects[] = { &door };

	do
	{
		kb_Scan();
		manager.update(getDeltaTime());

		// gfx_FillScreen(3);
		gfx_SetColor(3);
		gfx_FillRectangle(0, 0, GFX_LCD_WIDTH, 25);
		gfx_Tilemap(&tilemap, xOffset, yOffset);

		if (kb_IsDown(kb_KeyLeft))
		{
			if (x >= MIDDLE_X)
				x -= speed;
			else if (!xOffset && x >= TILE_WIDTH)
				x -= speed;
			else if (xOffset)
				xOffset -= speed;

			manager.setAnimation(playerId, &playerLeft);
			gfx_RLETSprite(manager.getCurrentFrame(playerId), x, y);

			restingPosition = 2;
		}
		else if (kb_IsDown(kb_KeyRight))
		{
			if (x <= MIDDLE_X)
				x += speed;
			else if (xOffset < (TILEMAP_WIDTH * TILE_WIDTH) - (TILEMAP_DRAW_WIDTH * TILE_WIDTH))
				xOffset += speed;
			else if (x < GFX_LCD_WIDTH)
				x += speed;

			manager.setAnimation(playerId, &playerRight);
			gfx_RLETSprite(manager.getCurrentFrame(playerId), x, y);

			restingPosition = 3;
		}
		else if (kb_IsDown(kb_KeyUp))
		{
			if (y >= MIDDLE_Y)
				y -= speed;
			else if (!yOffset && y >= TILE_HEIGHT * 2 + tilemap.y_loc)
				y -= speed;
			else if (yOffset)
				yOffset -= speed;

			manager.setAnimation(playerId, &playerUp);
			gfx_RLETSprite(manager.getCurrentFrame(playerId), x, y);

			restingPosition = 1;
		}
		else if (kb_IsDown(kb_KeyDown))
		{
			if (y <= MIDDLE_Y)
				y += speed;
			else if (yOffset < (TILEMAP_HEIGHT * TILE_HEIGHT) - (TILEMAP_DRAW_HEIGHT * TILE_HEIGHT))
				yOffset += speed;
			else if (y < GFX_LCD_HEIGHT)
				y += speed;

			manager.setAnimation(playerId, &playerDown);
			gfx_RLETSprite(manager.getCurrentFrame(playerId), x, y);

			restingPosition = 0;
		}
		else
		{
			if (restingPosition == 0)
				gfx_RLETSprite(player_tile_0, x, y);
			else if (restingPosition == 1)
				gfx_RLETSprite(player_tile_2, x, y);
			else if (restingPosition == 2)
				gfx_RLETSprite(player_tile_1, x, y);
			else if (restingPosition == 3)
				gfx_RLETSprite(playerFlipped_tile_2, x, y);
		}

		if (y >= ((TILE_HEIGHT * TILEMAP_HEIGHT) - (TILEMAP_HEIGHT * 2) - 16) + tilemap.y_loc)
			y = ((TILE_HEIGHT * TILEMAP_HEIGHT) - (TILEMAP_HEIGHT * 2) - 16) + tilemap.y_loc;

		unsigned int id{};
		unsigned int smallestDistance = 5000;

		for (unsigned int i = 0; i < 1; i++)
		{
			if (debug)
			{
				gfx_SetColor(0xE8);
				gfx_Rectangle(objects[i]->x - xOffset, objects[i]->y - yOffset, objects[i]->width, objects[i]->height);

				gfx_SetColor(0x58);
				gfx_Line(objects[i]->x + 8 - xOffset, objects[i]->y - yOffset + objects[i]->height - 2, x + 8, y + 2);
			}

			if (checkCollision(0, 0, GFX_LCD_WIDTH, GFX_LCD_HEIGHT, objects[i]->x - xOffset, objects[i]->y - yOffset, objects[i]->width, objects[i]->height))
			{
				if (objects[i]->sprite != nullptr)
					gfx_RLETSprite(objects[i]->sprite, objects[i]->x - xOffset, objects[i]->y - yOffset);


				unsigned int distanceToObject = distance(x, y, objects[i]->x - xOffset, objects[i]->y - yOffset);

				if (distanceToObject > 50)
					continue;

				if (distanceToObject < smallestDistance)
				{
					smallestDistance = distanceToObject;
					id = objects[i]->id;
				}
			}
		}

		gfx_SetColor(3);
		gfx_FillRectangle(95, 205, 150, 15);

		if (restingPosition == 1 && checkCollision(x, y, 16, 16, objects[id - 1]->x - xOffset - 4, objects[id - 1]->y - yOffset - 4, objects[id - 1]->width + 6, objects[id - 1]->height + 8))
		{
			gfx_SetTextFGColor(0);
			gfx_PrintStringXY("Press [2nd] to enter", 100, 210);
		}

		if (id != 0 && objects[id - 1]->collidable)
		{
			unsigned char collision = checkCollisionSide(x, y, 16, 16, objects[id - 1]->x - xOffset + objects[id - 1]->xOffset, objects[id - 1]->y - yOffset + objects[id - 1]->yOffset, objects[id - 1]->width, objects[id - 1]->height);

			// I'm sure there's a better way to do this but you know what, this works so I don't want to hear it
			switch (collision)
			{
			case 3: // Above
				if (y <= MIDDLE_Y)
					y -= speed;
				else if (yOffset < (TILEMAP_HEIGHT * TILE_HEIGHT) - (TILEMAP_DRAW_HEIGHT * TILE_HEIGHT))
					yOffset -= speed;
				else if (y < GFX_LCD_HEIGHT)
					y -= speed;
				break;

			case 4: // Below
				if (y >= MIDDLE_Y)
					y += speed;
				else if (!yOffset && y >= TILE_HEIGHT * 2 + tilemap.y_loc)
					y += speed;
				else if (yOffset)
					yOffset += speed;
				break;

			case 2: // Right
				if (x >= MIDDLE_X)
					x += speed;
				else if (!xOffset && x >= TILE_WIDTH)
					x += speed;
				else if (xOffset)
					xOffset += speed;
				break;

			case 1: // Left
				if (x <= MIDDLE_X)
					x -= speed;
				else if (xOffset < (TILEMAP_WIDTH * TILE_WIDTH) - (TILEMAP_DRAW_WIDTH * TILE_WIDTH))
					xOffset -= speed;
				else if (x < GFX_LCD_WIDTH)
					x -= speed;
				break;
			}
		}

		smallestDistance = 5000;

		if (getKeyDown(kb_KeyAlpha))
		{
			debug = !debug;
			gfx_FillScreen(3);
		}

		if (debug)
		{
			gfx_PrintStringXY("Debug", 270, 5);

			gfx_SetColor(0xE8);
			gfx_Rectangle(x, y, 16, 16);
		}

		gfx_SetTextFGColor(12);
		gfx_PrintStringXY("FPS: ", 5, 5);
		gfx_PrintInt(1000 / getDeltaTime(), 2);

		gfx_SwapDraw();

	} while (kb_Data[6] != kb_Clear);

	gfx_End();

	return 0;
}