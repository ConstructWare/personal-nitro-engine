
#include <NEMain.h>
#include "text_bmp_bin.h"
#include "text2_bmp_bin.h"

NE_Material * Text, * Text2;
NE_Palette * PalText2;

void Draw3DScene(void)
{
	NE_2DViewInit(); //Init 2D view

	scanKeys(); //Update stylus coordinates when screen is pressed
	static touchPosition touch;
	if(keysHeld() & KEY_TOUCH) touchRead(&touch);

	//Print text on columns/rows
	NE_TextPrint(0, 0,0, NE_White, "abcdefghijklmnopqrstuvwxyz012345\n6789\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n12345678901234567890123456789012");
	NE_TextPrint(1, 1,4, NE_Red, "AntonioND\n            rules!!!");
	NE_TextPrint(1, 8,8, NE_Yellow, "Yeah!!!");

	//Print text on any coordinates
	NE_TextPrintFree(1,touch.px, touch.py,NE_Blue,"Test");
	NE_TextPrintBoxFree(1,touch.px + 32, touch.py + 32,
		touch.px + 96, touch.py + 64,NE_Green, -1,"This is a\ntest!!");

	//Print formated text
	char text[64];
	sprintf(text, "Polys: %d\nVertices: %d\nCPU: %d%%",NE_GetPolygonCount(),NE_GetVertexCount(),NE_GetCPUPercent());
	NE_TextPrint(0, 0,13, NE_White,text);
}



int main()
{
	irqEnable(IRQ_HBLANK);
	irqSet(IRQ_VBLANK, NE_VBLFunc);  //Init Nitro Engine
	irqSet(IRQ_HBLANK, NE_HBLFunc);
	
	NE_Init3D();
	NE_SwapScreens();  //3D screen to lower screen
	
	Text = NE_MaterialCreate(); //Load RGB font
	NE_MaterialTexLoadBMPtoRGBA(Text,(void*)text_bmp_bin, true);

	Text2 = NE_MaterialCreate();
	PalText2 = NE_PaletteCreate(); //Load paletted font
	NE_MaterialTexLoadBMPtoRGB256(Text2, PalText2,(void*)text2_bmp_bin, true);
	
	NE_TextInit(0,  //Slot
	         Text,  //Image
			 8, 8); //Size of one character (x,y)
	NE_TextInit(1, Text2, 12, 16);
	
	while(1) 
	{
		
		NE_Process(Draw3DScene);
		NE_WaitForVBL(0);
	} 
	
	return 0;
}