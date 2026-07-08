# DoAn_Base_Firmware

Đây là bộ mã nguồn nền tảng (Base Firmware) dành cho đồ án, được thiết kế và cấu hình chuẩn xác trên vi điều khiển STM32F407ZGT6. Dự án đã tích hợp sẵn các ngoại vi và thư viện giao tiếp cơ bản, đóng vai trò như một bộ khung vững chắc để phát triển các tính năng cao hơn mà không lo xung đột phần cứng.

## Phần cứng sử dụng
- **Vi điều khiển chính:** STM32F407ZGT6.
- **Mạch nạp & Debug:** ST-LINK (Giao thức SWD).

## Các Module đã tích hợp
- **Định thời (System Tick):** Timer 2 (Ngắt toàn cục 50ms) dùng làm hệ điều hành đa nhiệm cơ bản.
- **Giao diện người dùng (UI):**
  - Màn hình LCD (Giao tiếp FSMC, tốc độ cao).
  - Cụm LED 7 đoạn (Giao tiếp SPI1 qua IC dịch chốt 74HC595).
  - Ma trận nút nhấn (Đọc tín hiệu qua IC 74HC165).
  - LED đơn hiển thị trạng thái (Debug, Y0, Y1).
- **Thời gian thực:** Đọc module RTC DS3231 (Giao tiếp I2C1).
- **Truyền thông:** USART1 (Baudrate 115200) truyền nhận dữ liệu trực tiếp qua cổng Type-C.

---

## 🚀 Thành quả thực tế đã đạt được (Milestones)
- [x] **Cấu hình phần cứng ổn định:** Fix triệt để lỗi sụt áp nguồn bằng cách chuyển đổi sang adapter nguồn ngoài. Cấu hình thành công 3 chân LED đơn (PE4 - DEBUG, PE5 - Y0, PE6 - Y1).
- [x] **Hệ điều hành & Quét ngoại vi:** Khởi tạo thành công ngắt Timer 2 (nhịp 50ms) chạy ổn định liên tục mà không bị treo mạch. Tích hợp thư viện quét ma trận nút nhấn (16 phím).
- [x] **Giao tiếp tốc độ cao (FSMC):** Cấu hình thành công bộ điều khiển bộ nhớ tĩnh linh hoạt (FSMC), khởi tạo và xóa nền LCD màu trắng, sẵn sàng cho việc in ký tự và xử lý giao diện đồ họa.
- [x] **Đồng bộ thời gian thực (I2C):** Kết nối thành công với chip RTC DS3231 qua bus I2C1. Giải quyết lỗi treo bus dữ liệu, bóc tách và đồng bộ thời gian thực tự động từ máy tính (Compiler Macros `__TIME__`) xuống chip.

## 📊 Kết quả kiểm thử trên Kit (Test Results)
- **Đèn LED đơn:** Hoạt động đúng kịch bản ngắt thời gian (LED Y0 chớp tắt luân phiên theo chu kỳ định sẵn).
- **Màn hình LCD & Phím:** Màn hình hiển thị màu trắng tinh, khi bấm các phím ma trận lập tức in ra số thứ tự phím màu đỏ tại tọa độ chỉ định.
- **Dữ liệu thời gian:** LED 7 đoạn hiển thị chính xác giờ và phút. Hệ thống tự chạy bằng pin CMOS của chip DS3231 sau khi ngắt lệnh ghi.

---

## Hướng dẫn Clone và Cài đặt

1. Clone repository này về máy cá nhân.
2. Mở phần mềm STM32CubeIDE, chọn **File -> Import -> Existing Projects into Workspace** và trỏ đường dẫn đến thư mục vừa clone.
3. **Lưu ý quan trọng:** Tuyệt đối chỉ viết code điều khiển vào giữa các cặp thẻ `/* USER CODE BEGIN ... */` và `/* USER CODE END ... */` trong file `main.c` để tránh bị xóa mất code khi Generate lại bằng CubeMX.
4. Nhấn **Ctrl + B** để biên dịch (Build) và nhấn **Run** để nạp xuống kit.<img width="1153" height="2560" alt="anh bkit" src="https://github.com/user-attachments/assets/9e567694-19c0-42a3-b877-25dde73724d9" />



