#Thư viện ASCON-128 AEAD cho hệ thống nhúng
#SOURCE CHÍNH : DATN_ASCON_ESP_PI/tree/main/04_University/HK_225/225_DATN_KTDT/Code_Esp/Merg_Node_V3

## Giới thiệu

Dự án này triển khai thuật toán **ASCON-128** – một thuật toán **Lightweight Cryptography** (được chuẩn hóa trong NIST LWC) – dùng để **mã hóa và xác thực dữ liệu (AEAD)** trong hệ thống nhúng.

Thư viện được viết **thuần C**, tối ưu để chạy trên các vi điều khiển như **ESP32, STM32, SONIX...**, và có thể tích hợp vào các hệ thống IoT thực tế.

---
## Security Note
- Nonce phải không được reuse
- Key cần được bảo vệ (flash encryption / secure storage)
## Mục tiêu dự án

* Xây dựng **thư viện mã hóa độc lập phần cứng**
* Áp dụng **ASCON-128 AEAD** cho bảo mật dữ liệu IoT
* Thiết kế API rõ ràng, dễ tích hợp
* Demo truyền dữ liệu giữa:
* 
  * ESP32 (Node)**
  * Raspberry Pi 4 (Gateway)
## Ứng dụng thực tế

* Bảo mật dữ liệu cảm biến IoT
* Giao tiếp an toàn Node → Gateway
* Hệ thống embedded yêu cầu nhẹ và nhanh
* Automotive / Industrial IoT

---

## Nền tảng sử dụng
* Ngôn ngữ: C (thuần)
* MCU: ESP32C6 160MHZ
* Gateway: Raspberry Pi 4
* Framework: ESP-IDF / HAL
---
## Hướng phát triển

* Tích hợp FreeRTOS
* Benchmark hiệu năng
* Tối ưu RAM/Flash
* Kết hợp DMA + UART/SPI
* Thêm secure key storage
---
## Tác giả
**Tran Van Nam**
Quan tâm: Embedded Systems, IoT Security, Cryptography
---

##  Ghi chú
> Đây là project mang tính nghiên cứu và học tập về **bảo mật lightweight trong hệ thống nhúng**, tập trung vào thiết kế thư viện và tích hợp thực tế.
> Thông tin benchmark và đánh giá hiệu năng chi tiết có thể được cung cấp theo yêu cầu.  
> Liên hệ: trannam6362@gmail.com
