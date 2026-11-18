#ifndef VIRTUAL_KEYBOARD_H
#define VIRTUAL_KEYBOARD_H

#include <Arduino.h>

// Các chế độ bàn phím
enum KeyMode {
    MODE_LOWERCASE,  // Chữ thường (a-z)
    MODE_UPPERCASE,  // Chữ hoa (A-Z)
    MODE_NUMBERS,    // Chữ số & Ký tự cơ bản (123)
    MODE_SYMBOLS     // Ký tự đặc biệt (#+=)
};

// Loại phím
enum KeyType {
    KEY_CHAR,       // Ký tự thường
    KEY_SHIFT,      // Phím Shift / Chuyển hoa-thường
    KEY_BACKSPACE,  // Phím Xóa (Backspace)
    KEY_MODE_NUM,   // Phím chuyển sang mode 123
    KEY_MODE_SYM,   // Phím chuyển sang mode #+=
    KEY_MODE_ABC,   // Phím chuyển về mode ABC
    KEY_SPACE,      // Phím Spacebar (Laban Key)
    KEY_ENTER       // Phím Nhập (Enter)
};

// Cấu trúc cho 1 nút bấm
struct Key {
    int x, y, w, h;
    const char* labelLower;
    const char* labelUpper;
    const char* labelNum;
    const char* labelSym;
    KeyType type;
};

class VirtualKeyboard {
private:
    KeyMode currentMode;
    int screenWidth;
    int screenHeight;
    int kbY;          // Tọa độ Y bắt đầu của bàn phím
    int kbHeight;     // Chiều cao toàn bộ bàn phím

    // Callback hàm vẽ nút (được định nghĩa bên ngoài tùy loại màn hình TFT)
    void (*drawKeyCallback)(int x, int y, int w, int h, const char* label, bool isSpecial, bool isPressed);

public:
    VirtualKeyboard();

    // Khởi tạo kích thước vùng hiển thị bàn phím
    void begin(int width, int height, int startY,
               void (*drawFunc)(int x, int y, int w, int h, const char* label, bool isSpecial, bool isPressed));

    // Vẽ lại toàn bộ bàn phím
    void draw();

    // Chế độ hiện tại
    KeyMode getMode() { return currentMode; }
    void setMode(KeyMode mode);

    // Xử lý tọa độ cảm ứng khi người dùng chạm vào màn hình
    // Trả về ký tự nhấn (String) hoặc chuỗi điều khiển ("\b" cho Backspace, "\n" cho Enter, "" cho các phím chuyển mode)
    String handleTouch(int touchX, int touchY);
};

#endif
