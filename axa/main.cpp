#include <Windows.h>
#include <iostream>

const int Threshold = 20;

COLORREF GetPixelColorAt(int x, int y) {
    HDC hdcScreen = GetDC(NULL);
    COLORREF color = GetPixel(hdcScreen, x, y);

    // Check if the color is valid
    if (color == CLR_INVALID) {
        std::cerr << "Error retrieving pixel color!" << std::endl;
        ReleaseDC(NULL, hdcScreen);
        return RGB(0, 0, 0); // Return black color
    }

    ReleaseDC(NULL, hdcScreen);
    return color;
}

void MouseClick() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

bool ColorsDiffer(COLORREF color1, COLORREF color2, int threshold) {
    int deltaR = abs(GetRValue(color1) - GetRValue(color2));
    int deltaG = abs(GetGValue(color1) - GetGValue(color2));
    int deltaB = abs(GetBValue(color1) - GetBValue(color2));

    return (deltaR > threshold) || (deltaG > threshold) || (deltaB > threshold);
}

int main() {
    std::cout << "Program started. Press 'X' to begin monitoring color changes." << std::endl;

    while (true) {
        if (GetAsyncKeyState('X') & 0x8000) {
            POINT cursorPos;
            GetCursorPos(&cursorPos);

            // Check if cursor coordinates are within valid screen bounds
            if (cursorPos.x < 0 || cursorPos.y < 0 ||
                cursorPos.x >= GetSystemMetrics(SM_CXSCREEN) ||
                cursorPos.y >= GetSystemMetrics(SM_CYSCREEN)) {
                std::cerr << "Cursor coordinates are out of screen bounds!" << std::endl;
                continue; // Skip to the next iteration
            }

            COLORREF initialColor = GetPixelColorAt(cursorPos.x + 2, cursorPos.y + 2);
            std::cout << "Initial color: RGB("
                << static_cast<int>(GetRValue(initialColor)) << ", "
                << static_cast<int>(GetGValue(initialColor)) << ", "
                << static_cast<int>(GetBValue(initialColor)) << ")" << std::endl;

            while (GetAsyncKeyState('X') & 0x8000) {
                Sleep(1);
                GetCursorPos(&cursorPos);

                // Check if cursor coordinates are still within valid bounds
                if (cursorPos.x < 0 || cursorPos.y < 0 ||
                    cursorPos.x >= GetSystemMetrics(SM_CXSCREEN) ||
                    cursorPos.y >= GetSystemMetrics(SM_CYSCREEN)) {
                    std::cerr << "Cursor coordinates are out of screen bounds!" << std::endl;
                    continue; // Skip to the next iteration
                }

                COLORREF currentColor = GetPixelColorAt(cursorPos.x + 2, cursorPos.y + 2);

                if (ColorsDiffer(initialColor, currentColor, Threshold)) {
                    std::cout << "Detected color change: RGB("
                        << static_cast<int>(GetRValue(currentColor)) << ", "
                        << static_cast<int>(GetGValue(currentColor)) << ", "
                        << static_cast<int>(GetBValue(currentColor)) << ")" << std::endl;

                    MouseClick();
                    std::cout << "Mouse click!" << std::endl;
                    Sleep(450); // Adjustable delay
                    initialColor = currentColor; // Update the base color
                }
            }
            std::cout << "'X' has been released. Monitoring stopped." << std::endl;
        }
        if (GetAsyncKeyState(VK_END) & 0x8000) {
            std::cout << "Program terminated." << std::endl;
            break;
        }
    }
    return 0;
}
