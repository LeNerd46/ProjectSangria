#include "utils.h"

bool previousDown = false;
bool previousUp = false;
bool previousLeft = false;
bool previousRight = false;
bool previous2nd = false;

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

        default:
            return kb_IsDown(key);
    }

    return false;
}

bool getKey(kb_lkey_t key)
{
    return kb_IsDown(key);
}