#include <nds.h>
 
//-------------------------------------------------------
void BOTTOM_SCREEN(int angle1,int angle2){
//-------------------------------------------------------
 
	glPushMatrix();
	glTranslatef(0, 0, -4);
	glRotatef32i(degreesToAngle(angle1), inttof32(1), inttof32(0), inttof32(0)); 
	glRotatef32i(degreesToAngle(angle2), inttof32(0), inttof32(0), inttof32(1)); 
	
	glBegin(GL_TRIANGLES);
		glColor3b(255,  0,  0);		glVertex3f(-1.0f,-1.0f, 1.0f);
		glColor3b(255,  0,255);		glVertex3f( 1.0f,-1.0f, 1.0f);
		glColor3b(  0,  0,255);		glVertex3f( 0.0f, 1.0f, 1.0f);
	 
	glPopMatrix(1);
}
 
 
//-------------------------------------------------------
void TOP_SCREEN(int angle1,int angle2){
//-------------------------------------------------------
 
	glPushMatrix();
	glTranslatef(0, 0, -4);
	glRotatef32i(degreesToAngle(angle1), inttof32(1), inttof32(0),inttof32(0)); 
	glRotatef32i(degreesToAngle(angle2), inttof32(0), inttof32(0), inttof32(1)); 
	
	glColor3b(255,  0,255);
	for(float i=-25;i<=25;i++)
	{
		glBegin(GL_QUADS);
			glVertex3f( i,+25, 0);
			glVertex3f( i+0.1,+25, 0);
			glVertex3f( i+0.1,-25, 0);
			glVertex3f( i,-25, 0);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f( +25, i, 0);
			glVertex3f( +25, i+0.1, 0);
			glVertex3f( -25, i+0.1, 0);
			glVertex3f( -25, i, 0);
		glEnd();

	}
 
	glPopMatrix(1);
}
 
//-------------------------------------------------------
void renderScene(bool top){
//-------------------------------------------------------
	static short angle1 = 0;
	static short angle2 = 0;
	scanKeys();
	int held = keysHeld();

	if (held & KEY_DOWN){angle1--;}
	if (held & KEY_UP){angle1++;}
	if (held & KEY_LEFT){angle2++;}
	if (held & KEY_RIGHT){angle2--;}

	swiWaitForVBlank();
 
	if(top)
		TOP_SCREEN(angle1,angle2);
	else
		BOTTOM_SCREEN(angle1,angle2);
	//angle1++;

}
 
 
//-------------------------------------------------------
void initSubSprites(void){
//-------------------------------------------------------
 
	oamInit(&oamSub, SpriteMapping_Bmp_2D_256, false);
 
	int x = 0;
	int y = 0;
 
	int id = 0;

	for(y = 0; y < 3; y++)
	for(x = 0; x < 4; x++)
	{
		oamSub.oamMemory[id].attribute[0] = ATTR0_BMP | ATTR0_SQUARE | (64 * y);
		oamSub.oamMemory[id].attribute[1] = ATTR1_SIZE_64 | (64 * x);
		oamSub.oamMemory[id].attribute[2] = ATTR2_ALPHA(1) | (8 * 32 * y) | (8 * x);
		id++;
	}
 
	swiWaitForVBlank();
 
	oamUpdate(&oamSub);
}
//-------------------------------------------------------
int main() {		
//-------------------------------------------------------
 
	videoSetMode(MODE_0_3D);
	videoSetModeSub(MODE_5_2D);
 
	glInit();
 
	initSubSprites();
 
	bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
 
//-------------------------------------------------------
	glEnable(GL_ANTIALIAS);
 
	glClearColor(0,0,0,31); 
	glClearPolyID(63);
	glClearDepth(0x7FFF);
 
	glViewport(0,0,255,191);
 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 256.0 / 192.0, 0.1, 100);
 
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);
 
//-------------------------------------------------------
	bool top = true;
 
	while (true) 
	{
		while(REG_DISPCAPCNT & DCAP_ENABLE);
 
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;

		//-------------------------------------------------------
		top = !top;
 
		if(top)
		{
			lcdMainOnBottom();
			vramSetBankC(VRAM_C_LCD);
			vramSetBankD(VRAM_D_SUB_SPRITE);
			REG_DISPCAPCNT = DCAP_BANK(2) | DCAP_ENABLE | DCAP_SIZE(3);
		}
		else
		{
			lcdMainOnTop();
			vramSetBankD(VRAM_D_LCD);
			vramSetBankC(VRAM_C_SUB_BG);
			REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3);
		}
 
		//-------------------------------------------------------
		glMatrixMode(GL_MODELVIEW);
 
		renderScene(top);
 
		glFlush(0);

	}
 
	return 0;
}
