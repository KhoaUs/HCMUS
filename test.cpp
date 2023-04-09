#include <iostream>
#include <Windows.h>

const int ROW = 6;
const int COL = 8;
const int CELL_WIDTH = 4;

int main()
{
    // Khởi tạo bảng
    char board[ROW][COL] = {
        {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
        {'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
        {'Y', 'Z', '0', '1', '2', '3', '4', '5'},
        {'6', '7', '8', '9', '@', '#', '$', '%'},
        {'^', '&', '*', '(', ')', '-', '+', '='}
    };

    // Khởi tạo con trỏ chuột ở giữa bảng
    COORD cursorPos = {COL / 2, ROW / 2};
    COORD oldCursorPos = cursorPos;

    while (true) {
        // Kiểm tra nếu con trỏ đã di chuyển, thì mới cần xóa và in lại bảng
        if (cursorPos.X != oldCursorPos.X || cursorPos.Y != oldCursorPos.Y) {
            system("cls");

            // In bảng
            for (int i = 0; i < ROW; i++) {
                for (int j = 0; j < COL; j++) {
                    if (i == cursorPos.Y && j == cursorPos.X) {
                        // In ô đang được trỏ tới với màu nền nháy đậm
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        std::cout << board[i][j];
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    } else {
                        std::cout << board[i][j];
                    }
                    std::cout.width(CELL_WIDTH);
                }
                std::cout << std::endl;
            }

            // Lưu vị trí cũ của con trỏ
            oldCursorPos = cursorPos;
        }

        // Xử lý phím mũi tên
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
           
        // Di chuyển con trỏ sang trái
        cursorPos.X = std::max(cursorPos.X - 1, 0);
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        // Di chuyển con trỏ sang phải
        cursorPos.X = std::min(cursorPos.X + 1, COL - 1);
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        // Di chuyển con trỏ lên trên
        cursorPos.Y = std::max(cursorPos.Y - 1, 0);
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        // Di chuyển con trỏ xuống dưới
        cursorPos.Y = std::min(cursorPos.Y + 1, ROW - 1);
    }

    // Đợi 100ms trước khi lặp lại vòng while
    Sleep(100);
}

return 0;
}
