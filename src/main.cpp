#include <graphx.h>
#include <keypadc.h>

#include "utils.h"

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

	titleScreen();

	int x{};
	int y{};

	do
	{
		kb_Scan();

		gfx_FillScreen(0xFF);

		if (kb_IsDown(kb_KeyLeft))
			x--;
		if(kb_IsDown(kb_KeyRight))
			x++;
		if(kb_IsDown(kb_KeyUp))
			y--;
		if(kb_IsDown(kb_KeyDown))
			y++;

		gfx_SetColor(0x00);
		gfx_FillRectangle(x, y, 16, 16);

		gfx_SwapDraw();

	} while (kb_Data[6] != kb_Clear);

	gfx_End();

	return 0;
}