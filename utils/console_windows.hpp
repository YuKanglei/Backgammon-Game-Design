#pragma once
#include "console_abstract.hpp"
#include <windows.h>

namespace utils {

    class console_windows : public console_abstract {
    public:
        console_windows();
        ~console_windows();

        bool write(char character, const utils::point_uint& coordinate) override;
        void set_color(int color) override;
        void clear() override;

    private:
        HANDLE hConsole;
    };

    inline console_windows::console_windows() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    inline console_windows::~console_windows() {
    }

    inline bool console_windows::write(char character, const utils::point_uint& coordinate) {
        COORD pos;
        pos.X = coordinate.get_x();
        pos.Y = coordinate.get_y();
        SetConsoleCursorPosition(hConsole, pos);
        DWORD written;
        return WriteConsole(hConsole, &character, 1, &written, nullptr);
    }

    inline void console_windows::set_color(int color) {
        SetConsoleTextAttribute(hConsole, color);
    }

    inline void console_windows::clear() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD count;
        DWORD cellCount;
        COORD homeCoords = { 0, 0 };

        if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            return;
        }

        cellCount = csbi.dwSize.X * csbi.dwSize.Y;

        if (!FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count)) {
            return;
        }

        if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count)) {
            return;
        }

        SetConsoleCursorPosition(hConsole, homeCoords);
    }

} // namespace utils
