#include "Draw.h"


Draw::Draw() {									//Default Constructor

}

Draw::Draw(HDC desk, HWND handle) {				//Constructor - used to initliaze member objects.
	HDC_Desktop = desk;
	Handle = handle;
} 


Draw::~Draw() {									//Deconstructor

} 


void Draw::DrawFilledRect(int x, int y, int w, int h, HBRUSH brushColor) const
{
	RECT rect = { x,y,x + w,y + h };
	FillRect(HDC_Desktop, &rect, brushColor);
}

void Draw::DrawBorderBox(int x, int y, int w, int h, int thickness, HBRUSH brushColor)
{
	DrawFilledRect(x, y, w, thickness, brushColor);
	DrawFilledRect(x, y, thickness, h, brushColor);
	DrawFilledRect((x + w), y, thickness, h, brushColor);
	DrawFilledRect(x, y + h, w + thickness, thickness, brushColor);
}


void Draw::DrawESP(int x, int y, float distance, HBRUSH hBrush) {
	int width = 1100 / distance;
	int height = 2000 / distance;

	DrawBorderBox(x - (width / 2), y - height, width, height, 1, hBrush);
	
}



//Credits to UC/GH for worldToScreen()
bool Draw::WorldToScreen(vec3_t pos, vec3_t &screen, float matrix[16], int windowWidth, int windowHeight)
{

	vec4_t clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	vec3_t NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

