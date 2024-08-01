#include <nds.h>
#include <stdio.h>

void setPixel(int x, int y, u16 color) {
		int blockSize=8;
		for(int dy=0; dy<blockSize; dy++){
			for(int dx=0; dx<blockSize; dx++){
				int px=x+dx;
				int py=y+dy;
				if (px>=0 && px<256 && py>=0 && py < 192){
					VRAM_A[ py * 256 + px ] = color;
					VRAM_A[ py * 256 - px ] = color; }
		}
    }
}

void resetScreen(){
	for(int x=0;x<256;x++){
		for(int y=0;y<192;y++){
			if (x>=0 && x<256 && y>=0 && y<192){
				VRAM_A[ y * 256 + x ] = RGB15(0,0,0);
			}
		}
	}


}

int main(void) {
    consoleDemoInit();

    videoSetMode(MODE_FB0);
    vramSetBankA(VRAM_C_LCD);

    touchPosition touch;
    u16 color = RGB15(0, 31, 31);

    while (1) {
        scanKeys();
        touchRead(&touch);

        if (keysHeld() & KEY_TOUCH) {
            setPixel(touch.px, touch.py, color);
        }

		if (keysHeld() & KEY_START){
			resetScreen();
		}

        swiWaitForVBlank();
    }

    return 0;
}
