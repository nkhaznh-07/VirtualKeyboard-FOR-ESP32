# ⌨️ VirtualKeyboard FOR ESP32

Thư viện bàn phím ảo cảm ứng 5 hàng (lấy cảm hứng từ bố cục Laban Key) viết bằng C++ dành cho **ESP32** và các vi điều khiển tương thích Arduino. 

Thư viện được thiết kế độc lập với phần cứng màn hình thông qua cơ chế **Callback**, giúp bạn dễ dàng tích hợp với bất kỳ thư viện đồ họa TFT nào (`TFT_eSPI`, `Adafruit_GFX`, `LovyanGFX`, v.v.) và bất kỳ chip cảm ứng nào (`XPT2046`, `FT6236`, `GT911`, v.v.).

---

## ✨ Tính năng nổi bật

- **Bố cục 5 hàng quen thuộc:** Hàng số cố định (`1-0`) kết hợp bàn phím QWERTY tiêu chuẩn.
- **Đa dạng chế độ nhập liệu (4 Modes):**
  - `MODE_LOWERCASE`: Chữ thường (`a-z`)
  - `MODE_UPPERCASE`: Chữ hoa (`A-Z`)
  - `MODE_NUMBERS`: Số & ký tự cơ bản (`[ ] { } # % ^ * + = ...`)
  - `MODE_SYMBOLS`: Ký tự đặc biệt nâng cao (`_ \ | ~ < > € £ ¥ • ...`)
- **Độc lập phần cứng (Hardware Agnostic):** Tự động tính toán tọa độ, kích thước nút theo độ phân giải màn hình và gọi hàm `drawKeyCallback` do người dùng định nghĩa để vẽ giao diện.
- **Xử lý cảm ứng thông minh:** Trả về trực tiếp ký tự vừa nhấn hoặc mã điều khiển chuẩn (`\b` cho Backspace, `\n` cho Enter).

---

## 🗂️ Cấu trúc thư mục

```text
VirtualKeyboard-FOR-ESP32/
├── VirtualKeyboard.h      # Khai báo lớp VirtualKeyboard, enum KeyMode, KeyType và API
├── VirtualKeyboard.cpp    # Xử lý logic bố cục 5 hàng, chuyển đổi chế độ và tọa độ chạm
└── README.md              # Tài liệu hướng dẫn sử dụng
