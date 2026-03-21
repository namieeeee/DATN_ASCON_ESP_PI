#include "DHT22.h"
#include "esp_timer.h"
#include "esp_rom_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h" // Thêm thư viện in log

#define TIMEOUT_US 1000
static portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
static const char *TAG = "DHT22_DRV";

// Hàm đo thời gian chính xác
static int wait_for_state(gpio_num_t pin, int state) {
    int64_t start_time = esp_timer_get_time();
    while (gpio_get_level(pin) != state) {
        if (esp_timer_get_time() - start_time > TIMEOUT_US) {
            return -1;
        }
    }
    return (int)(esp_timer_get_time() - start_time);
}

int dht22_read(gpio_num_t pin, float *temperature, float *humidity) {
    uint8_t data[5] = {0};

    // BÍ QUYẾT: Dùng chế độ Open-Drain để Vừa Đọc Vừa Ghi cực nhanh (Không bị trễ)
    gpio_set_direction(pin, GPIO_MODE_INPUT_OUTPUT_OD);
    gpio_set_pull_mode(pin, GPIO_PULLUP_ONLY);

    // --- Start signal ---
    gpio_set_level(pin, 0);
    esp_rom_delay_us(20000); // Kéo LOW 20ms (An toàn cho cả DHT11 và DHT22)

    // Nhả chân ra (trạng thái High-Z), điện trở Pull-up sẽ tự kéo lên HIGH
    gpio_set_level(pin, 1);
    esp_rom_delay_us(30);

    taskENTER_CRITICAL(&mux);

    // --- Chờ Response ---
    if (wait_for_state(pin, 0) < 0 ||
        wait_for_state(pin, 1) < 0 ||
        wait_for_state(pin, 0) < 0) {
        taskEXIT_CRITICAL(&mux);
        return DHT22_ERR_TIMEOUT;
    }

    // --- Đọc 40 bit ---
    for (int i = 0; i < 40; i++) {
        if (wait_for_state(pin, 1) < 0) {
            taskEXIT_CRITICAL(&mux);
            return DHT22_ERR_TIMEOUT;
        }

        int high_time = wait_for_state(pin, 0);
        if (high_time < 0) {
            taskEXIT_CRITICAL(&mux);
            return DHT22_ERR_TIMEOUT;
        }

        if (high_time > 40) {
            data[i / 8] |= (1 << (7 - (i % 8)));
        }
    }

    taskEXIT_CRITICAL(&mux);

    // IN RA 5 BYTE ĐỂ TÌM LỖI (Mở Console xem dòng này nhé)
    ESP_LOGI(TAG, " %02X %02X %02X %02X %02X", data[0], data[1], data[2], data[3], data[4]);

    // --- Checksum ---
    if (data[4] != ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
        return DHT22_ERR_CHECKSUM;
    }

    // =========================================================
    // NẾU BẠN DÙNG DHT11 (Màu Xanh Dương), HÃY DÙNG 2 DÒNG NÀY:
    // *humidity = data[0];
    // *temperature = data[2];
    // =========================================================

    // =========================================================
    // NẾU BẠN DÙNG DHT22 (Màu Trắng), HÃY DÙNG CÁC DÒNG NÀY:
    *humidity = ((data[0] << 8) | data[1]) * 0.1;
    int temp_raw = ((data[2] & 0x7F) << 8) | data[3];
    *temperature = temp_raw * 0.1;
    if (data[2] & 0x80) *temperature = -*temperature;
    // =========================================================

    return DHT22_OK;
}