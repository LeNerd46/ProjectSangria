#include <graphx.h>
#include <keypadc.h>
#include <time.h>

#include "utils.h"
#include "gfx/gfx.h"
#include "animations.h"

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
extern unsigned char hospital_start_room[];

int getDeltaTime()
{
	static clock_t previousTime;
	clock_t currentTime = clock();
	int output = 0;

	output = (currentTime - previousTime) * 1000 / CLOCKS_PER_SEC;

	previousTime = currentTime;
	return output;
}

float easeIn(float time, float startValue, float change, float duration)
{
	time /= duration / 2;

	if (time < 1)
		return change / 2 * time * time + startValue;

	time--;
	return -change / 2 * (time * (time - 2) - 1) + startValue;
};

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

void hospitalRoom(Player& player, AnimationManager& manager, int playerId)
{
	gfx_tilemap_t tilemap;
	tilemap.map = hospital_start_room;
	tilemap.tiles = hospital_tiles;
	tilemap.tile_width = gfx_tile_16_pixel;
	tilemap.tile_height = gfx_tile_16_pixel;
	tilemap.tile_width = TILE_WIDTH;
	tilemap.tile_height = TILE_HEIGHT;
	tilemap.draw_width = 8;
	tilemap.draw_height = 9;
	tilemap.width = 8;
	tilemap.height = 9;
	tilemap.x_loc = 141;
	tilemap.y_loc = 200 - (tilemap.height * TILE_HEIGHT);

	player.xOffset = 0;
	player.yOffset = 0;

	player.x = 200;
	player.y = 160;

	player.speed = 1;

	Object door(1, 221, 190, hospitalDoor_width, hospitalDoor_height, false, hospitalDoor); // Beyond the limits of the tilemap, will never collide
	Object stoolObject(2, 160, 155, stool_width, stool_height, true, stool);
	Object bed(3, 157, 124, hospitalBedPink_width, hospitalBedPink_height, true, hospitalBedPink);
	Object shelf(4, 160, 65, hospitalShelf_width, hospitalShelf_height, true, hospitalShelf);
	Object plant(5, 238, 88, mediumPlant_width, mediumPlant_height, true, mediumPlant);
	Object rotatedShelf(6, 244, 120, hospitalRotatedShelf_width, hospitalRotatedShelf_height, true, hospitalRotatedShelf);

	Object* objects[] = { &door, &stoolObject, &bed, &shelf, &plant, &rotatedShelf };

	bool debug = false;
	bool stoolThing = false;
	int timer = 0;
	float progress;

	do
	{
		kb_Scan();
		manager.update(getDeltaTime());

		gfx_FillScreen(0);
		// gfx_SetColor(3);
		// gfx_FillRectangle(0, 0, GFX_LCD_WIDTH, 180);
		gfx_Tilemap(&tilemap, 0, 0);

		drawPlayerSingle(player, manager, playerId, tilemap);

		if (getKeyDown(kb_KeyAlpha))
		{
			debug = !debug;
			gfx_FillScreen(3);
		}

		if (debug)
		{
			gfx_PrintStringXY("Debug", 270, 5);

			gfx_SetColor(0xE8);
			gfx_Rectangle(player.x, player.y, 16, 16);
		}

		int id = checkObjectCollision(player, objects, tilemap, 6, true, 40, debug);

		switch (id)
		{
		case 2:

			gfx_SetTextFGColor(3);
			gfx_PrintStringXY("Press [2nd] to sit", 80, 210);

			if (getKeyDown(kb_Key2nd))
			{
				player.control = false;
				stoolObject.collidable = false;

				player.x = 160;
				player.y = 148;
				player.restingPosition = 3;

				stoolThing = true;
				progress = 0;
			}

			break;
		}

		if (stoolThing)
		{
			gfx_RLETSprite(playerFlipped_tile_2, player.x, player.y);

			timer++;

			gfx_SetTextXY(5, 5);
			gfx_PrintInt(timer, 1);

			if (timer >= 50 && tilemap.x_loc < GFX_LCD_WIDTH)
			{
				tilemap.x_loc += 2;
				player.x += 2;

				for (unsigned char i = 0; i < 6; i++)
				{
					objects[i]->x += 2;
				}

			}
			else if (tilemap.x_loc >= GFX_LCD_WIDTH)
			{

			}
		}

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

	// int x = GFX_LCD_WIDTH / 2 - 8;
	// int y = GFX_LCD_HEIGHT / 2 - 8;

	Player player;

	gfx_tilemap_t tilemap;
	tilemap.map = hospital_begin_map;
	tilemap.tiles = hospital_tiles;
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

	bool debug = false;

	AnimationManager manager;
	int playerId = manager.createAnimation(&player.playerDown);

	// Door is at 30, 1/2
	Object realDoor(1, 480, 52, hospitalDoor_width, hospitalDoor_height, false, hospitalDoor);
	Object door1(5, 96, 52, hospitalDoor_width, hospitalDoor_height, false, hospitalDoor);
	Object door2(2, 192, 52, hospitalDoor_width, hospitalDoor_height, false, hospitalDoor);
	Object door3(3, 288, 52, hospitalDoor_width, hospitalDoor_height, false, hospitalDoor);
	Object door4(4, 384, 52, hospitalDoor_width, hospitalDoor_height, false, hospitalDoor);

	Object* objects[] = { &realDoor, &door4, &door3, &door2, &door1 };
	const char amountOfObjects = 5;

	// hospitalRoom(player, manager, playerId);

	do
	{
		kb_Scan();
		manager.update(getDeltaTime());

		gfx_FillScreen(0);
		// gfx_SetColor(3);
		// gfx_FillRectangle(0, 0, GFX_LCD_WIDTH, 25);
		gfx_Tilemap(&tilemap, player.xOffset, player.yOffset);

		drawPlayer(player, manager, playerId);

		if (player.y >= ((TILE_HEIGHT * TILEMAP_HEIGHT) - (TILEMAP_HEIGHT * 2) - 16) + tilemap.y_loc)
			player.y = ((TILE_HEIGHT * TILEMAP_HEIGHT) - (TILEMAP_HEIGHT * 2) - 16) + tilemap.y_loc;

		unsigned int id{};
		unsigned int smallestDistance = 60;

		for (unsigned int i = 0; i < amountOfObjects; i++)
		{
			if (checkCollision(0, 0, GFX_LCD_WIDTH, GFX_LCD_HEIGHT, objects[i]->x - player.xOffset + player.horizontalVelocity, objects[i]->y - player.yOffset + player.verticalVelocity, objects[i]->width, objects[i]->height))
			{
				if (objects[i]->sprite != nullptr)
					gfx_RLETSprite(objects[i]->sprite, objects[i]->x - player.xOffset + player.horizontalVelocity, objects[i]->y - player.yOffset + player.verticalVelocity);

				unsigned int distanceToObject = distance(player.x, player.y, objects[i]->x - player.xOffset + player.horizontalVelocity, objects[i]->y - player.yOffset + player.verticalVelocity);

				if (distanceToObject > 50)
					continue;

				if (distanceToObject < smallestDistance)
				{
					smallestDistance = distanceToObject;
					id = objects[i]->id;
				}
			}
		}

		if (debug && id != 0)
		{
			gfx_SetColor(0xE8);
			gfx_Rectangle(objects[id - 1]->x - player.xOffset, objects[id - 1]->y - player.yOffset, objects[id - 1]->width, objects[id - 1]->height);

			gfx_SetColor(0x58);
			gfx_Line(objects[id - 1]->x + 8 - player.xOffset, objects[id - 1]->y - player.yOffset + objects[id - 1]->height - 2, player.x + 8, player.y + 2);
			gfx_Rectangle(objects[id - 1]->x - player.xOffset - 4, objects[id - 1]->y - player.yOffset - 4, objects[id - 1]->width + 6, objects[id - 1]->height + 8);
		}

		// gfx_SetColor(3);
		// gfx_FillRectangle(95, 205, 150, 15);

		if (player.restingPosition == 1 && checkCollision(player.x, player.y, 16, 16, objects[id - 1]->x - player.xOffset - 4, objects[id - 1]->y - player.yOffset - 4, objects[id - 1]->width + 6, objects[id - 1]->height + 8))
		{
			if (id == 1)
			{
				gfx_SetTextFGColor(3);
				gfx_PrintStringXY("Press [2nd] to enter", 100, 210);

				if (getKeyDown(kb_Key2nd))
				{
					gfx_SetTextFGColor(3);
					gfx_PrintStringXY("You pressed [2nd]", 110, 30);

					switch (id)
					{
					case 1:

						int elapsedTime{};

						// It's at 48 right now
						while (tilemap.y_loc < 200)
						{
							elapsedTime += 1;

							if (elapsedTime >= 10)
							{
								elapsedTime = 0;
								tilemap.y_loc += 2;

								gfx_FillScreen(0);
								gfx_Tilemap(&tilemap, player.xOffset, player.yOffset);

								for (unsigned char i = 0; i < amountOfObjects; i++)
								{
									objects[i]->y += 2;

									if (objects[i]->sprite != nullptr)
										gfx_RLETSprite(objects[i]->sprite, objects[i]->x - player.xOffset + player.horizontalVelocity, objects[i]->y - player.yOffset + player.verticalVelocity);
								}

								gfx_SwapDraw();
							}
						}

						hospitalRoom(player, manager, playerId);

						break;
					}
				}
			}
		}

		if (id != 0 && objects[id - 1]->collidable)
		{
			unsigned char collision = checkCollisionSide(player.x, player.y, 16, 16, objects[id - 1]->x - player.xOffset + objects[id - 1]->xOffset, objects[id - 1]->y - player.yOffset + objects[id - 1]->yOffset, objects[id - 1]->width, objects[id - 1]->height);

			// I'm sure there's a better way to do this but you know what, this works so I don't want to hear it
			switch (collision)
			{
			case 3: // Above
				if (player.y <= MIDDLE_Y)
					player.y -= player.speed;
				else if (player.yOffset < (TILEMAP_HEIGHT * TILE_HEIGHT) - (TILEMAP_DRAW_HEIGHT * TILE_HEIGHT))
					player.yOffset -= player.speed;
				else if (player.y < GFX_LCD_HEIGHT)
					player.y -= player.speed;
				break;

			case 4: // Below
				if (player.y >= MIDDLE_Y)
					player.y += player.speed;
				else if (!player.yOffset && player.y >= TILE_HEIGHT * 2 + tilemap.y_loc)
					player.y += player.speed;
				else if (player.yOffset)
					player.yOffset += player.speed;
				break;

			case 2: // Right
				if (player.x >= MIDDLE_X)
					player.x += player.speed;
				else if (!player.xOffset && player.x >= TILE_WIDTH)
					player.x += player.speed;
				else if (player.xOffset)
					player.xOffset += player.speed;
				break;

			case 1: // Left
				if (player.x <= MIDDLE_X)
					player.x -= player.speed;
				else if (player.xOffset < (TILEMAP_WIDTH * TILE_WIDTH) - (TILEMAP_DRAW_WIDTH * TILE_WIDTH))
					player.xOffset -= player.speed;
				else if (player.x < GFX_LCD_WIDTH)
					player.x -= player.speed;
				break;
			}
		}

		smallestDistance = 60;

		if (getKeyDown(kb_KeyAlpha))
		{
			debug = !debug;
			gfx_FillScreen(3);
		}

		if (debug)
		{
			gfx_PrintStringXY("Debug", 270, 5);

			gfx_SetColor(0xE8);
			gfx_Rectangle(player.x, player.y, 16, 16);
		}

		gfx_SetTextFGColor(12);
		gfx_PrintStringXY("FPS: ", 5, 5);
		gfx_PrintInt(1000 / getDeltaTime(), 2);

		gfx_SwapDraw();

	} while (kb_Data[6] != kb_Clear);

	gfx_End();

	return 0;
}