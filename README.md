# 🛠️ BKIT ARM4 Personal Projects

Kho lưu trữ (Repository) tổng hợp các dự án, bài tập và mã nguồn phát triển trên **Kit vi điều khiển BKIT ARM4** (Chip xử lý chính: **STM32F407ZGT6** Cortex-M4).

---

## 📁 Cấu trúc Thư mục Dự án

Repository này được tổ chức theo cấu trúc **Monorepo** để dễ dàng quản lý nhiều dự án độc lập trong cùng một nơi:

* **[DoAn_Base_Firmware](./DoAn_Base_Firmware):** * *Mô tả:* Bộ khung cấu hình ngoại vi cơ bản đã test chạy ổn định cho Đồ án Tốt nghiệp (Quản lý cây cảnh).
    * *Ngoại vi tích hợp:* LCD (FSMC tốc độ cao), RTC DS3231, Ngắt Timer, Ma trận phím (Keypad 4x4), LED 7 đoạn.
* **[Project_Alarm_Stopwatch](./Project_Alarm_Stopwatch) *(Sắp triển khai)*:** * *Mô tả:* Hệ thống đa nhiệm Đồng hồ thời gian thực kết hợp Báo thức (Alarm) và Bấm giờ thể thao chính xác cao (Stopwatch).
    * *Kiến trúc:* Sử dụng Máy trạng thái hữu hạn (FSM) quản lý qua nhịp ngắt Timer.

---

## 💻 Môi trường Phát triển & Công cụ

* **Hardware Kit:** BKIT ARM4 (STM32F407ZGT6)
* **IDE:** STM32CubeIDE (Phiên bản mới nhất)
* **Cấu hình cấu trúc:** STM32CubeMX
* **Ngôn ngữ:** C (Embedded)
* **Trình nạp:** ST-Link V2 / On-board debugger

---

## 🚀 Hướng dẫn Nạp & Chạy Dự án trên Máy cục bộ

Để clone và mở một dự án con bất kỳ trong STM32CubeIDE mà không bị lỗi đường dẫn, hãy làm theo các bước sau:

1. **Clone Repository này về máy:**
   ```bash
   git clone [https://github.com/YOUR_USERNAME/BKIT_ARM4_Personal_Projects.git](https://github.com/YOUR_USERNAME/BKIT_ARM4_Personal_Projects.git)
