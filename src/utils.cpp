#include "utils.h"

bool previousDown = false;
bool previousUp = false;
bool previousLeft = false;
bool previousRight = false;
bool previous2nd = false;
bool previousAlpha = false;

void drawPlayer(Player& player, AnimationManager& manager, int playerId)
{
	if (!player.control)
	{
		switch (player.restingPosition)
		{
		case 0:
			gfx_RLETSprite(player_tile_0, player.x, player.y);
			break;

		case 1:
			gfx_RLETSprite(player_tile_2, player.x, player.y);
			break;

		case 2:
			gfx_RLETSprite(player_tile_1, player.x, player.y);
			break;

		case 3:
			gfx_RLETSprite(playerFlipped_tile_2, player.x, player.y);
			break;
		}

		return;
	}

	bool horizontal = false;
	bool vertical = false;

	if (kb_IsDown(kb_KeyLeft))
	{
		if (player.x >= MIDDLE_X)
		{
			player.x -= player.speed;
			horizontal = true;
		}
		else if (!player.xOffset && player.x >= TILE_WIDTH)
		{
			player.x -= player.speed;
			horizontal = true;
		}
		else if (player.xOffset)
		{
			player.xOffset -= player.speed;
			player.horizontalVelocity = -player.speed;
		}

		manager.setAnimation(playerId, &player.playerLeft);
		gfx_RLETSprite(manager.getCurrentFrame(playerId), player.x, player.y);

		player.restingPosition = 2;
	}
	else if (kb_IsDown(kb_KeyRight))
	{
		if (player.x <= MIDDLE_X)
		{
			player.x += player.speed;
			horizontal = true;
		}
		else if (player.xOffset < (TILEMAP_WIDTH * TILE_WIDTH) - (TILEMAP_DRAW_WIDTH * TILE_WIDTH))
		{
			player.xOffset += player.speed;
			player.horizontalVelocity = player.speed;
		}
		else if (player.x < GFX_LCD_WIDTH)
		{
			player.x += player.speed;
			horizontal = true;
		}

		manager.setAnimation(playerId, &player.playerRight);
		gfx_RLETSprite(manager.getCurrentFrame(playerId), player.x, player.y);

		player.restingPosition = 3;
	}
	else if (kb_IsDown(kb_KeyUp))
	{
		if (player.y >= MIDDLE_Y)
		{
			player.y -= player.speed;
			vertical = true;
		}
		else if (!player.yOffset && player.y >= TILE_HEIGHT * 2 + (TILE_HEIGHT * 3))
		{
			player.y -= player.speed;
			vertical = true;
		}
		else if (player.yOffset)
		{
			player.yOffset -= player.speed;
			player.verticalVelocity = -player.speed;
		}

		manager.setAnimation(playerId, &player.playerUp);
		gfx_RLETSprite(manager.getCurrentFrame(playerId), player.x, player.y);

		player.restingPosition = 1;
	}
	else if (kb_IsDown(kb_KeyDown))
	{
		if (player.y <= MIDDLE_Y)
		{
			player.y += player.speed;
			vertical = true;
		}
		else if (player.yOffset < (TILEMAP_HEIGHT * TILE_HEIGHT) - (TILEMAP_DRAW_HEIGHT * TILE_HEIGHT))
		{
			player.yOffset += player.speed;
			player.verticalVelocity = player.speed;
		}
		else if (player.y < GFX_LCD_HEIGHT)
		{
			player.y += player.speed;
			vertical = true;
		}

		manager.setAnimation(playerId, &player.playerDown);
		gfx_RLETSprite(manager.getCurrentFrame(playerId), player.x, player.y);

		player.restingPosition = 0;
	}
	else
	{
		switch (player.restingPosition)
		{
		case 0:
			gfx_RLETSprite(player_tile_0, player.x, player.y);
			break;

		case 1:
			gfx_RLETSprite(player_tile_2, player.x, player.y);
			break;

		case 2:
			gfx_RLETSprite(player_tile_1, player.x, player.y);
			break;

		case 3:
			gfx_RLETSprite(playerFlipped_tile_2, player.x, player.y);
			break;
		}
	}

	if ((!kb_IsDown(kb_KeyLeft) && !kb_IsDown(kb_KeyRight)) || horizontal)
		player.horizontalVelocity = 0;
	if ((!kb_IsDown(kb_KeyUp) && !kb_IsDown(kb_KeyDown)) || vertical)
		player.verticalVelocity = 0;
}

void drawPlayerSingle(Player& player, AnimationManager& manager, int playerId, gfx_tilemap_t& tilemap)
{
	if (!player.control)
	{
		switch (player.restingPosition)
		{
		case 0:
			gfx_RLETSprite(player_tile_0, player.x, player.y);
			break;

		case 1:
			gfx_RLETSprite(player_tile_2, player.x, player.y);
			break;

		case 2:
			gfx_RLETSprite(player_tile_1, player.x, player.y);
			break;

		case 3:
			gfx_RLETSprite(playerFlipped_tile_2, player.x, player.y);
			break;
		}

		return;
	}

	bool horizontal = false;
	bool vertical = false;

	if (getKey(kb_KeyLeft))
	{
		player.x -= player.speed;

		manager.setAnimation(playerId, &player.playerLeft);
		gfx_RLETSprite(manager.getCurrentFrame(playerId), player.x, player.y);

		player.restingPosition = 2;
	}
	else if (getKey(kb_KeyRight))
	{
		player.x += player.speed;

		manager.setAnimation(playerId, &player.playerRight);
		gfx_RLETSprite(manager.getCurrentFrame(playerId), player.x, player.y);

		player.restingPosition = 3;
	}
	else if (getKey(kb_KeyUp))
	{
		player.y -= player.speed;

		manager.setAnimation(playerId, &player.playerUp);
		gfx_RLETSprite(manager.getCurrentFrame(playerId), player.x, player.y);

		player.restingPosition = 1;
	}
	else if (getKey(kb_KeyDown))
	{
		player.y += player.speed;

		manager.setAnimation(playerId, &player.playerDown);
		gfx_RLETSprite(manager.getCurrentFrame(playerId), player.x, player.y);

		player.restingPosition = 0;
	}
	else
	{
		switch (player.restingPosition)
		{
		case 0:
			gfx_RLETSprite(player_tile_0, player.x, player.y);
			break;

		case 1:
			gfx_RLETSprite(player_tile_2, player.x, player.y);
			break;

		case 2:
			gfx_RLETSprite(player_tile_1, player.x, player.y);
			break;

		case 3:
			gfx_RLETSprite(playerFlipped_tile_2, player.x, player.y);
			break;
		}
	}

	if (player.x + 16 >= tilemap.width * TILE_WIDTH + tilemap.x_loc - TILE_WIDTH)
		player.x = tilemap.width * TILE_WIDTH + tilemap.x_loc - TILE_WIDTH - 16;
	if (player.x <= (int)tilemap.x_loc + TILE_WIDTH)
		player.x = (int)tilemap.x_loc + TILE_WIDTH;
	if (player.y <= tilemap.y_loc + (TILE_HEIGHT * 2))
		player.y = tilemap.y_loc + (TILE_HEIGHT * 2);
	if (player.y + 16 >= tilemap.height * TILE_HEIGHT + tilemap.y_loc - TILE_HEIGHT)
		player.y = tilemap.height * TILE_HEIGHT + tilemap.y_loc - TILE_HEIGHT - 16;

	if ((!kb_IsDown(kb_KeyLeft) && !kb_IsDown(kb_KeyRight)) || horizontal)
		player.horizontalVelocity = 0;
	if ((!kb_IsDown(kb_KeyUp) && !kb_IsDown(kb_KeyDown)) || vertical)
		player.verticalVelocity = 0;
}

int checkObjectCollision(Player& player, Object* objects[], gfx_tilemap_t& tilemap, unsigned int objectCount, bool single = false, unsigned int minimumDistance = 60, bool debug = false)
{
	int ids[5]{};
	unsigned int smallestDistance = minimumDistance + 10;

	// Whenever you're next to an object, it always does the door first!!!
	for (unsigned int i = 0; i < objectCount; i++)
	{
		if (checkCollision(0, 0, GFX_LCD_WIDTH, GFX_LCD_HEIGHT, objects[i]->x - player.xOffset, objects[i]->y - player.yOffset, objects[i]->width, objects[i]->height))
		{
			if (objects[i]->sprite != nullptr)
				gfx_RLETSprite(objects[i]->sprite, objects[i]->x - player.xOffset + player.horizontalVelocity, objects[i]->y - player.yOffset + player.verticalVelocity);

			unsigned int distanceToObject = distance(player.x, player.y, objects[i]->x - player.xOffset + player.horizontalVelocity, objects[i]->y - player.yOffset + player.verticalVelocity);

			if (distanceToObject > minimumDistance)
				continue;

			smallestDistance = distanceToObject;

			for (unsigned char j = 0; j < 5; j++)
			{
				if (ids[4] != 0)
					break;

				if (ids[j] == 0)
				{
					ids[j] = objects[i]->id;
					break;
				}
			}
		}
	}

	for (unsigned char i = 0; i < 5; i++)
	{
		if (ids[i] != 0 && objects[ids[i] - 1]->collidable)
		{
			unsigned char collision = checkCollisionSide(player.x, player.y, 16, 16, objects[ids[i] - 1]->x - player.xOffset + objects[ids[i] - 1]->xOffset + player.horizontalVelocity, objects[ids[i] - 1]->y - player.yOffset + objects[ids[i] - 1]->yOffset + player.verticalVelocity, objects[ids[i] - 1]->width, objects[ids[i] - 1]->height);

			if (debug)
			{
				gfx_SetColor(0xE8);
				gfx_Rectangle(objects[ids[i] - 1]->x - player.xOffset + objects[ids[i] - 1]->xOffset + player.horizontalVelocity, objects[ids[i] - 1]->y - player.yOffset + objects[ids[i] - 1]->yOffset + player.verticalVelocity, objects[ids[i] - 1]->width, objects[ids[i] - 1]->height);

				gfx_SetColor(0x58);
				gfx_Line(objects[ids[i] - 1]->x + 8 - player.xOffset, objects[ids[i] - 1]->y - player.yOffset + objects[ids[i] - 1]->height - 2, player.x + 8, player.y + 2);
				gfx_Rectangle(objects[ids[i] - 1]->x - player.xOffset - 4, objects[ids[i] - 1]->y - player.yOffset - 4, objects[ids[i] - 1]->width + 6, objects[ids[i] - 1]->height + 8);
			}


			// I'm sure there's a better way to do this but you know what, this works so I don't want to hear it
			if (single)
			{
				switch (collision)
				{
				case 3: // Above
					player.y -= player.speed;
					player.verticalVelocity = 0;
					break;

				case 4: // Below
					player.y += player.speed;
					player.verticalVelocity = 0;
					break;

				case 2: // Right
					player.x += player.speed;
					player.horizontalVelocity = 0;
					break;

				case 1: // Left
					player.x -= player.speed;
					player.horizontalVelocity = 0;
					break;
				}

			}
			else
			{
				switch (collision)
				{
				case 3: // Above
					if (player.y <= MIDDLE_Y)
						player.y -= player.speed;
					else if (player.yOffset < (TILEMAP_HEIGHT * TILE_HEIGHT) - (TILEMAP_DRAW_HEIGHT * TILE_HEIGHT))
						player.yOffset -= player.speed;
					else if (player.y < GFX_LCD_HEIGHT)
						player.y -= player.speed;

					player.verticalVelocity = 0;
					break;

				case 4: // Below
					if (player.y >= MIDDLE_Y)
						player.y += player.speed;
					else if (!player.yOffset && player.y >= TILE_HEIGHT * 2 + tilemap.y_loc)
						player.y += player.speed;
					else if (player.yOffset)
						player.yOffset += player.speed;

					player.verticalVelocity = 0;
					break;

				case 2: // Right
					if (player.x >= MIDDLE_X)
						player.x += player.speed;
					else if (!player.xOffset && player.x >= TILE_WIDTH)
						player.x += player.speed;
					else if (player.xOffset)
						player.xOffset += player.speed;

					player.horizontalVelocity = 0;
					break;

				case 1: // Left
					if (player.x <= MIDDLE_X)
						player.x -= player.speed;
					else if (player.xOffset < (TILEMAP_WIDTH * TILE_WIDTH) - (TILEMAP_DRAW_WIDTH * TILE_WIDTH))
						player.xOffset -= player.speed;
					else if (player.x < GFX_LCD_WIDTH)
						player.x -= player.speed;

					player.horizontalVelocity = 0;
					break;
				}
			}

			if (checkCollision(player.x, player.y, 16, 16, objects[ids[i] - 1]->x - player.xOffset - 4, objects[ids[i] - 1]->y - player.yOffset - 4, objects[ids[i] - 1]->width + 6, objects[ids[i] - 1]->height + 8))
				return ids[i];
		}
	}

	return 0;
}

bool getKeyDown(kb_lkey_t key)
{
	kb_Scan();

	bool pressed = false;

	switch (key)
	{
	case kb_KeyLeft:

		pressed = getKey(key) && !previousLeft;
		previousLeft = getKey(key);

		break;

	case kb_KeyRight:

		pressed = getKey(key) && !previousRight;
		previousRight = getKey(key);

		break;

	case kb_KeyUp:

		pressed = getKey(key) && !previousUp;
		previousUp = getKey(key);

		break;

	case kb_KeyDown:

		pressed = getKey(key) && !previousDown;
		previousDown = getKey(key);

		break;

	case kb_Key2nd:

		pressed = getKey(key) && !previous2nd;
		previous2nd = getKey(key);

		break;

	case kb_KeyAlpha:

		pressed = getKey(key) && !previousAlpha;
		previousAlpha = getKey(key);

		break;

	default:
		pressed = getKey(key);
	}

	return pressed;
}

bool getKey(kb_lkey_t key)
{
	return kb_IsDown(key);
}

// This took longer than I'd like to admit to figure out
bool checkCollision(int firstX, int firstY, int firstWidth, int firstHeight, int secondX, int secondY, int secondWidth, int secondHeight)
{
	return firstX < secondX + secondWidth // First object's left side is to the left of the second object's right side,         first object is on the right
		&& firstX + firstWidth > secondX // First object's right side is to the right of the second object's left side,         first object is on the left
		&& firstY < secondY + secondHeight // The first object's top is above the second object's bottom,                       first object is underneath
		&& firstY + firstHeight > secondY; // The first object's bottom is lower than the second object's top,                  first object is above
}

int absoluteValue(int value)
{
	if (value < 0)
		return -value;

	return value;
}

int distance(int x1, int y1, int x2, int y2)
{
	return sqrt((pow((x2 - x1), 2)) + (pow((y2 - y1), 2)));
}

// Quite taxing, don't do this more than once per frame
unsigned char checkCollisionSide(int firstX, int firstY, int firstWidth, int firstHeight, int secondX, int secondY, int secondWidth, int secondHeight)
{
	if (!checkCollision(firstX, firstY, firstWidth, firstHeight, secondX, secondY, secondWidth, secondHeight))
		return 0;

	int centerX1 = (firstX + (firstX + firstWidth)) / 2;
	int centerX2 = (secondX + (secondX + secondWidth)) / 2;

	int centerY1 = (firstY + (firstY + firstHeight)) / 2;
	int centerY2 = (secondY + (secondY + secondHeight)) / 2;

	if (absoluteValue(centerX1 - centerX2) > absoluteValue(centerY1 - centerY2))
	{
		// Horizontal collision

		if (centerX1 < centerX2)
			return 1; // Left
		else
			return 2; // Right
	}
	else
	{
		// Vertical collision

		if (centerY1 < centerY2)
			return 3; // Above
		else
			return 4; // Below
	}
}