#include "utils.h"

bool previousDown = false;
bool previousUp = false;
bool previousLeft = false;
bool previousRight = false;
bool previous2nd = false;
bool previousAlpha = false;

bool getKeyDown(kb_lkey_t key)
{
    kb_Scan();

    switch (key)
    {
        case kb_KeyLeft:
            if (kb_IsDown(key) && !previousLeft)
            {
                previousLeft = true;
                return true;
            }

            previousLeft = false;
            return false;

        case kb_KeyRight:
            if (kb_IsDown(key) && !previousRight)
            {
                previousRight = true;
                return true;
            }

            previousRight = false;
            return false;

        case kb_KeyUp:
            if (kb_IsDown(key) && !previousUp)
            {
                previousUp = true;
                return true;
            }

            previousUp = false;
            return false;

        case kb_KeyDown:
            if (kb_IsDown(key) && !previousDown)
            {
                previousDown = true;
                return true;
            }

            previousDown = false;
            return false;

        case kb_Key2nd:
            if (kb_IsDown(key) && !previous2nd)
            {
                previous2nd = true;
                return true;
            }

            previous2nd = false;
            return false;

        case kb_KeyAlpha:
            if (kb_IsDown(key) && !previousAlpha)
            {
				previousAlpha = true;
				return true;
			}

            previousAlpha = false;
            return false;

        default:
            return kb_IsDown(key);
    }

    return false;
}

bool getKey(kb_lkey_t key)
{
    return kb_IsDown(key);
}

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