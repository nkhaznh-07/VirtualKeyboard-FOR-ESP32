#include "VirtualKeyboard.h"

// Bố cục bàn phím 5 hàng dựa theo ảnh mẫu
// Hàng 1: 1 2 3 4 5 6 7 8 9 0
// Hàng 2: Q W E R T Y U I O P  |  [ ] { } # % ^ * + =
// Hàng 3: A S D F G H J K L    |  - / : ; ( ) $ & @ "
// Hàng 4: [Shift] Z X C V B N M [Backspace]  |  [#+=] . , ? ! ' [Backspace]
// Hàng 5: [123/ABC] [,'] [ Space / Laban Key ] [.] [Nhập]

VirtualKeyboard::VirtualKeyboard() {
    currentMode = MODE_LOWERCASE;
    drawKeyCallback = nullptr;
}

void VirtualKeyboard::begin(int width, int height, int startY,
                           void (*drawFunc)(int x, int y, int w, int h, const char* label, bool isSpecial, bool isPressed)) {
    screenWidth = width;
    screenHeight = height;
    kbY = startY;
    kbHeight = height - startY;
    drawKeyCallback = drawFunc;
}

void VirtualKeyboard::setMode(KeyMode mode) {
    currentMode = mode;
    draw();
}

void VirtualKeyboard::draw() {
    if (!drawKeyCallback) return;

    // Thiết lập kích thước hàng và nút
    int rowHeight = kbHeight / 5;
    int margin = 2;

    // Hàng 1 (10 phím)
    const char* r1_lower[] = {"1","2","3","4","5","6","7","8","9","0"};
    const char* r1_sym[]   = {"1","2","3","4","5","6","7","8","9","0"};
    int w10 = (screenWidth - (11 * margin)) / 10;
    for (int i = 0; i < 10; i++) {
        int x = margin + i * (w10 + margin);
        int y = kbY + 0 * rowHeight + margin;
        const char* label = (currentMode == MODE_SYMBOLS) ? r1_sym[i] : r1_lower[i];
        drawKeyCallback(x, y, w10, rowHeight - margin*2, label, false, false);
    }

    // Hàng 2 (10 phím)
    const char* r2_lower[] = {"q","w","e","r","t","y","u","i","o","p"};
    const char* r2_upper[] = {"Q","W","E","R","T","Y","U","I","O","P"};
    const char* r2_num[]   = {"[","]","{","}","#","%","^","*","+","="};
    const char* r2_sym[]   = {"_","\\","|","~","<",">","€","£","¥","•"};
    for (int i = 0; i < 10; i++) {
        int x = margin + i * (w10 + margin);
        int y = kbY + 1 * rowHeight + margin;
        const char* label = r2_lower[i];
        if (currentMode == MODE_UPPERCASE) label = r2_upper[i];
        else if (currentMode == MODE_NUMBERS) label = r2_num[i];
        else if (currentMode == MODE_SYMBOLS) label = r2_sym[i];
        drawKeyCallback(x, y, w10, rowHeight - margin*2, label, false, false);
    }

    // Hàng 3 (9 phím - căn giữa)
    const char* r3_lower[] = {"a","s","d","f","g","h","j","k","l"};
    const char* r3_upper[] = {"A","S","D","F","G","H","J","K","L"};
    const char* r3_num[]   = {"-","/"," spaces",";","(",")","$","&","@","\""};
    int offset9 = (screenWidth - (9 * w10 + 8 * margin)) / 2;
    for (int i = 0; i < 9; i++) {
        int x = offset9 + i * (w10 + margin);
        int y = kbY + 2 * rowHeight + margin;
        const char* label = r3_lower[i];
        if (currentMode == MODE_UPPERCASE) label = r3_upper[i];
        else if (currentMode == MODE_NUMBERS || currentMode == MODE_SYMBOLS) label = r3_num[i];
        drawKeyCallback(x, y, w10, rowHeight - margin*2, label, false, false);
    }

    // Hàng 4 (Special Shift / Backspace)
    int y4 = kbY + 3 * rowHeight + margin;
    int wSpecial = (screenWidth - (7 * w10 + 8 * margin)) / 2;

    // Phím Shift / #+=
    if (currentMode == MODE_NUMBERS) {
        drawKeyCallback(margin, y4, wSpecial, rowHeight - margin*2, "#+=", true, false);
    } else if (currentMode == MODE_SYMBOLS) {
        drawKeyCallback(margin, y4, wSpecial, rowHeight - margin*2, "123", true, false);
    } else {
        drawKeyCallback(margin, y4, wSpecial, rowHeight - margin*2, "^", true, currentMode == MODE_UPPERCASE);
    }

    // Các phím giữa Hàng 4 (7 phím)
    const char* r4_lower[] = {"z","x","c","v","b","n","m"};
    const char* r4_upper[] = {"Z","X","C","V","B","N","M"};
    const char* r4_num[]   = {".",",","?","!","'","`","~"};
    for (int i = 0; i < 7; i++) {
        int x = margin + wSpecial + margin + i * (w10 + margin);
        const char* label = r4_lower[i];
        if (currentMode == MODE_UPPERCASE) label = r4_upper[i];
        else if (currentMode == MODE_NUMBERS || currentMode == MODE_SYMBOLS) label = r4_num[i];
        drawKeyCallback(x, y4, w10, rowHeight - margin*2, label, false, false);
    }

    // Phím Xóa (Backspace)
    int xDelete = screenWidth - margin - wSpecial;
    drawKeyCallback(xDelete, y4, wSpecial, rowHeight - margin*2, "<X", true, false);

    // Hàng 5 (123/ABC, Phẩy/VI, Spacebar, Chấm, Nhập)
    int y5 = kbY + 4 * rowHeight + margin;
    int wMode = w10 * 1.5;
    int wEnter = w10 * 1.8;
    int wComma = w10;
    int wDot = w10;
    int wSpace = screenWidth - (wMode + wComma + wDot + wEnter + 6 * margin);

    // Phím 123 / ABC
    const char* modeLabel = (currentMode == MODE_NUMBERS || currentMode == MODE_SYMBOLS) ? "ABC" : "123";
    drawKeyCallback(margin, y5, wMode, rowHeight - margin*2, modeLabel, true, false);

    // Phím phẩy / Tiếng Việt
    drawKeyCallback(margin * 2 + wMode, y5, wComma, rowHeight - margin*2, ",", false, false);

    // Phím Space (Laban Key)
    drawKeyCallback(margin * 3 + wMode + wComma, y5, wSpace, rowHeight - margin*2, "Laban Key", false, false);

    // Phím Chấm
    drawKeyCallback(margin * 4 + wMode + wComma + wSpace, y5, wDot, rowHeight - margin*2, ".", false, false);

    // Phím Nhập (Enter)
    drawKeyCallback(margin * 5 + wMode + wComma + wSpace + wDot, y5, wEnter, rowHeight - margin*2, "Nhap", true, false);
}

String VirtualKeyboard::handleTouch(int touchX, int touchY) {
    if (touchY < kbY || touchY > screenHeight) return "";

    int rowHeight = kbHeight / 5;
    int row = (touchY - kbY) / rowHeight;
    int margin = 2;
    int w10 = (screenWidth - (11 * margin)) / 10;

    // Xử lý chạm theo từng hàng
    if (row == 0) { // Hàng số 1-0
        int idx = (touchX - margin) / (w10 + margin);
        if (idx >= 0 && idx < 10) return String(idx == 9 ? 0 : idx + 1);
    }
    else if (row == 1) { // Hàng Q-P
        int idx = (touchX - margin) / (w10 + margin);
        if (idx >= 0 && idx < 10) {
            const char* charsLower[] = {"q","w","e","r","t","y","u","i","o","p"};
            const char* charsUpper[] = {"Q","W","E","R","T","Y","U","I","O","P"};
            const char* charsNum[]   = {"[","]","{","}","#","%","^","*","+","="};
            if (currentMode == MODE_UPPERCASE) return charsUpper[idx];
            if (currentMode == MODE_NUMBERS) return charsNum[idx];
            return charsLower[idx];
        }
    }
    else if (row == 3) { // Hàng Shift / Z-M / Backspace
        int wSpecial = (screenWidth - (7 * w10 + 8 * margin)) / 2;
        if (touchX < wSpecial + margin) {
            // Chạm nút Shift / Special
            if (currentMode == MODE_LOWERCASE) setMode(MODE_UPPERCASE);
            else if (currentMode == MODE_UPPERCASE) setMode(MODE_LOWERCASE);
            else if (currentMode == MODE_NUMBERS) setMode(MODE_SYMBOLS);
            else if (currentMode == MODE_SYMBOLS) setMode(MODE_NUMBERS);
            return "";
        }
        if (touchX > screenWidth - wSpecial - margin) {
            // Phím Backspace
            return "\b";
        }
    }
    else if (row == 4) { // Hàng dưới cùng
        int wMode = w10 * 1.5;
        if (touchX < wMode + margin) {
            // Chuyển chế độ ABC <-> 123
            if (currentMode == MODE_NUMBERS || currentMode == MODE_SYMBOLS) setMode(MODE_LOWERCASE);
            else setMode(MODE_NUMBERS);
            return "";
        }
        // Phím Enter
        int wEnter = w10 * 1.8;
        if (touchX > screenWidth - wEnter - margin) {
            return "\n";
        }
        // Phím Spacebar (nằm ở giữa)
        return " ";
    }

    return "";
}
