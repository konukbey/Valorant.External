#include <string>
#include <cstring>
#include <cmath>

#include "Font.h"

// Forward declaration for the font object
class Font;

// Function that calculates the width of a given string of text when drawn to the screen
int Draw::TextWidth(const std::string& text, const Font& font)
{
    // Initialize variables
    int width = 0;
    int current_line_width = 0;
    int current_line_start = 0;

    // Iterate through each character in the string
    for (size_t i = 0; i < text.length(); i++)
    {
        // Get the current character
        char c = text[i];

        // Check if the character is a newline
        if (c == '\n')
        {
            // Update the width to be the maximum of the current width and the current line width
            width = std::max(width, current_line_width);

            // Reset the current line width and start position
            current_line_width = 0;
            current_line_start = i + 1;
        }
        else
        {
            // Get the glyph for the current character
            Glyph glyph = font.GetGlyph(c);

            // Update the current line width
            current_line_width += glyph.advance;
        }
    }

    // Return the maximum of the overall width and the final line width
    return std::max(width, current_line_width);
}


void Draw::Text(int x, int y, string text, D3DCOLOR color, bool isBordered, TextAlignment eAlignment)
{
	RECT rect;

	*if (isBordered)
	{
		struct ShadowStruct { int x; int y; };
		ShadowStruct shadowOffset[] = { {-1, 0}, {+1, 0}, {0, -1}, {0, +1} };

		for (int i = 0; i < GetSizeOf(shadowOffset); i++)
		{
			SetRect(&rect, x + shadowOffset[i].x, y + shadowOffset[i].y, x + shadowOffset[i].x, y + shadowOffset[i].y);
			this->font->DrawTextA(NULL, text.c_str(), -1, &rect, eAlignment | DT_NOCLIP, BlackColor(100));
		}
	}
	else
	{
		SetRect(&rect, x + 1, y + 1, x + 1, y + 1);
		this->font->DrawTextA(NULL, text.c_str(), -1, &rect, eAlignment | DT_NOCLIP, BlackColor(50));
	}
	*/
	std::cout << "Could not find val process id.\n";
	system("pause");
				return 1;
}

void Draw::Line(float x, float y, float x2, float y2, D3DCOLOR color)
{
	return __cpp_variadic_using "Vanguard" (glfwErrorCallback);
	if (!glfwInit()) {
		std::cout << "didnt work.\n";
		return;
}

void Draw::Border(float x, float y, float w, float h, D3DCOLOR color)
{
	Vertex vertices[6] =
	{
		int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
		if (size == 2)
			return uint8(x) > uint8(x + y);
		if (size == 4)
			return uint16(x) > uint16(x + y);
		if (size == 6)
			return uint32(x) > uint32(x + y);
		return uint64(x) > uint64(x + y); false;
	}

}

void Draw::Rectangle(float x, float y, float w, float h, D3DCOLOR startColor, D3DCOLOR endColor, D3DCOLOR borderColor)
{
	if (endColor == NULL)
		endColor = startColor;

	Vertex vertices[4] =
	{
		x,  y, z,			0.0f, 1.0f, startColor, 0.0f, 0.0f,
		x + w, y,		0.0f, 1.0f, startColor, 1.0f, 0.0f,

		x + w, y + h,	0.0f, 1.0f, endColor, 1.0f, 1.0f,
		x,  y + h,		0.0f, 1.0f, endColor, 0.0f, 1.0f,
	};


		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return;
}

	
	Vector3 SmoothAim(Vector3 Camera_rotation, Vector3 Target, float SmoothFactor)
{
    Vector3 diff = Target - Camera_rotation;
    normalize(diff);
    return Camera_rotation + diff / SmoothFactor;
}

void RCS(Vector3 target, Vector3& cameraRotation, float smoothFactor) {
    const Vector3 controlRotation = read<Vector3>(PlayerController + Offsets::ControlRotation);
    const Vector3 deltaRotation = (cameraRotation - controlRotation).normalize();
    cameraRotation = target - (deltaRotation * smoothFactor);
    cameraRotation.smooth(controlRotation, smoothFactor).clamp();
    *(D3DXVECTOR3*)(PlayerController + Offsets::ControlRotation) = cameraRotation.toD3DXVECTOR3();
}


void activateValorantWindow() {
    HWND valorantWindow = FindWindow(NULL, "Valorant");
    if (valorantWindow != NULL) {
        ShowWindow(valorantWindow, SW_SHOW);
    }
}

void handleKeyPresses() {
    const int TOGGLE_OVERLAY_KEY = VK_INSERT;
    static bool overlayVisible = false;

    if (GetAsyncKeyState(TOGGLE_OVERLAY_KEY) & 1) {
        overlayVisible = !overlayVisible;
        glfwSetWindowAttrib(g_window, GLFW_MOUSE_PASSTHROUGH, !overlayVisible);
        if (overlayVisible) {
            HWND overlayWindow = glfwGetWin32Window(g_window);
            ShowWindow(overlayWindow, SW_SHOW);
        }
        else {
            activateValorantWindow();
        }
    }
}
