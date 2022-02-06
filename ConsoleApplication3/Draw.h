#include <windows.h> //Brush
#include "Structs.h" //vec3

class Draw {
private:
	//ESP
	HDC HDC_Desktop;
	HFONT Font;
	HWND TargetWnd;
	HWND Handle;
	COLORREF TextCOLOR;

public:
	/*Constructor/Deconstructors*/
	Draw();
	Draw(HDC desk, HWND handle);
	~Draw();

#ifndef DRAW
#define DRAW
	/*Function Declarations / Function Prototypes*/
	void DrawFilledRect(int x, int y, int w, int h, HBRUSH brushColor) const;
	void DrawBorderBox(int x, int y, int w, int h, int thickness, HBRUSH brushColor);
	void DrawESP(int x, int y, float distance, HBRUSH hBrush);
	bool WorldToScreen(vec3_t pos, vec3_t &screen, float matrix[16], int windowWidth, int windowHeight);
#endif
};


