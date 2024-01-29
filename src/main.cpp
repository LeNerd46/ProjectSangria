#include <graphx.h>
#include <keypadc.h>

#include "utils.h"

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