/*
 * state_machine_pure_c.c
 * Thuần C, mô phỏng 2 nút: Mode (3 chế độ xoay vòng) và Shutdown.
 * Build:  gcc state_machine_pure_c.c -o sm && ./sm
 * Windows (MSVC): cl state_machine_pure_c.c /Fe:sm.exe
 */

#include <stdio.h>
#include <string.h>

/* ====== Kiểu dữ liệu, hằng số ====== */
typedef enum { FALSE = 0, TRUE = 1 } bool_t;

typedef enum
{
    R_OK = 0,
    R_ERROR = -1
} ERROR_CODE_T;

typedef enum
{
    OFF = 0,
    ON  = 1
} ONOFF_T;

typedef enum
{
    STATE_INIT = 0,
    STATE_IDLE,
    STATE_RUN,
    STATE_ERROR,
    STATE_SHUTDOWN,
    STATE_STOP,
    STATE_MAX
} SystemState_t;

typedef enum
{
    EVENT_NONE = 0,
    EVENT_INIT_SUCCESS,
    EVENT_INIT_FAIL,
    EVENT_START_SUCCESS,
    EVENT_START_FAIL,
    EVENT_SHUTDOWN_REQUEST,
    EVENT_SHUTDOWN_SUCCESS,
    EVENT_SHUTDOWN_FAIL,
    EVENT_FORCE_STOP
} SystemEvent_t;

/* ====== “Driver” mock & macro log ====== */
#define MAIN_PRINT_TRACE(fmt, ...)  printf("[TRACE] " fmt, ##__VA_ARGS__)
#define MAIN_PRINT_INFO(fmt, ...)   printf("[INFO ] " fmt, ##__VA_ARGS__)
#define MAIN_PRINT_WARN(fmt, ...)   printf("[WARN ] " fmt, ##__VA_ARGS__)
#define MAIN_PRINT_ERR(fmt, ...)    printf("[ERROR] " fmt, ##__VA_ARGS__)

/* ====== Biến trạng thái hệ thống ====== */
static volatile SystemEvent_t s_event = EVENT_NONE;
static volatile bool_t        s_run_at_first = FALSE;
static volatile bool_t        s_error_occured = FALSE;
static volatile bool_t        s_flag_request_shutdown = FALSE;

/* Mô phỏng nguồn xe (trong code gốc vehicleRunning = OFF) */
static volatile ONOFF_T       vehicleRunning = OFF;

/* Nút MODE xoay 3 mode 1→2→3→1… */
static int g_mode = 1;  /* 1..3 */

/* ====== Khai báo hàm ====== */
static ERROR_CODE_T s_initialize_peripheral(void);
static ERROR_CODE_T Deinit_all(void);
static ERROR_CODE_T Process_state_RUN(void);
static void         printf_ring_buf(void);

static void         post_user_input(char c);
static void         print_help(void);

static void         Set_event(SystemEvent_t ev) { s_event = ev; }

/* ====== Phần “logic” của bạn: execute_action ====== */
static void execute_action(SystemState_t state)
{
    ERROR_CODE_T ret = R_OK;

    switch (state)
    {
        case STATE_INIT:
        {
            s_run_at_first  = TRUE;
            ret             = s_initialize_peripheral();

            if (ret == R_OK)
            {
                Set_event(EVENT_INIT_SUCCESS);
                MAIN_PRINT_TRACE("next event: EVENT_INIT_SUCCESS\r\n");
            }
            else
            {
                Set_event(EVENT_INIT_FAIL);
                MAIN_PRINT_TRACE("next event: EVENT_INIT_FAIL\r\n");
            }
        }
        break;

        case STATE_IDLE:
        {
            /* vehicleRunning = OFF trong demo */
            vehicleRunning = OFF;

            if (vehicleRunning == OFF)
            {
                Set_event(EVENT_START_SUCCESS);
                MAIN_PRINT_TRACE("next event: EVENT_START_SUCCESS\r\n");
            }
            else if (s_error_occured == TRUE)
            {
                Set_event(EVENT_START_FAIL);
                MAIN_PRINT_TRACE("next event: EVENT_START_FAIL\r\n");
            }
        }
        break;

        case STATE_RUN:
        {
            /* Nếu có yêu cầu tắt, bắn event shutdown */
            if (s_flag_request_shutdown == TRUE)
            {
                Set_event(EVENT_SHUTDOWN_REQUEST);
                MAIN_PRINT_TRACE("next event: EVENT_SHUTDOWN_REQUEST\r\n");
            }
            else
            {
                /* Xử lý RUN “thực” */
                ret = Process_state_RUN();
                (void)ret; /* demo: không dùng ret để bắn lỗi */
            }
        }
        break;

        case STATE_ERROR:
        {
            MAIN_PRINT_ERR("Enter STATE_ERROR -> force reset (demo = về STOP)\n");
            Set_event(EVENT_FORCE_STOP);
        }
        break;

        case STATE_SHUTDOWN:
        {
            ERROR_CODE_T d = Deinit_all();
            printf_ring_buf();
            if (d == R_OK)
            {
                Set_event(EVENT_SHUTDOWN_SUCCESS);
                MAIN_PRINT_TRACE("next event: EVENT_SHUTDOWN_SUCCESS\r\n");
            }
            else
            {
                Set_event(EVENT_SHUTDOWN_FAIL);
                MAIN_PRINT_TRACE("next event: EVENT_SHUTDOWN_FAIL\r\n");
            }
        }
        break;

        case STATE_STOP:
        case STATE_MAX:
        default:
        break;
    }
}

/* ====== Bộ chuyển trạng thái theo event ======
 * Giản lược, bám sát flow quen thuộc:
 * INIT -> (INIT_SUCCESS) -> IDLE -> (START_SUCCESS) -> RUN
 * RUN -> (SHUTDOWN_REQUEST) -> SHUTDOWN -> (SHUTDOWN_SUCCESS) -> STOP
 */
static SystemState_t transit_state(SystemState_t cur, SystemEvent_t ev)
{
    switch (cur)
    {
        case STATE_INIT:
            if (ev == EVENT_INIT_SUCCESS) return STATE_IDLE;
            if (ev == EVENT_INIT_FAIL)    return STATE_ERROR;
            break;

        case STATE_IDLE:
            if (ev == EVENT_START_SUCCESS) return STATE_RUN;
            if (ev == EVENT_START_FAIL)    return STATE_ERROR;
            break;

        case STATE_RUN:
            if (ev == EVENT_SHUTDOWN_REQUEST) return STATE_SHUTDOWN;
            break;

        case STATE_SHUTDOWN:
            if (ev == EVENT_SHUTDOWN_SUCCESS) return STATE_STOP;
            if (ev == EVENT_SHUTDOWN_FAIL)    return STATE_ERROR;
            break;

        case STATE_ERROR:
            if (ev == EVENT_FORCE_STOP) return STATE_STOP;
            break;

        default:
            break;
    }
    return cur; /* không đổi nếu event không hợp lệ */
}

/* ====== Demo “drivers” / business stubs ====== */
static ERROR_CODE_T s_initialize_peripheral(void)
{
    MAIN_PRINT_INFO("Init peripherals (mock)… OK\n");
    return R_OK;
}

static ERROR_CODE_T Deinit_all(void)
{
    MAIN_PRINT_WARN("Deinit all (mock)… OK\n");
    /* In yêu cầu bài toán: “shutdown” */
    printf("shutdown\n");
    return R_OK;
}

static void printf_ring_buf(void)
{
    /* Demo: giả sử flush log cuối */
    MAIN_PRINT_INFO("Flush ring buffer (mock)\n");
}

/* Ở RUN, in mode hiện tại. Nút MODE sẽ tăng g_mode (1..3) ở post_user_input() */
static ERROR_CODE_T Process_state_RUN(void)
{
    MAIN_PRINT_INFO("RUN: current MODE = %d\n", g_mode);
    return R_OK;
}

/* ====== Input người dùng -> mô phỏng nút ====== */
static void post_user_input(char c)
{
    if (c == 'm' || c == 'M')
    {
        /* Mode: 1->2->3->1… */
        g_mode++;
        if (g_mode > 3) g_mode = 1;
        MAIN_PRINT_INFO("Button MODE pressed -> MODE = %d\n", g_mode);
    }
    else if (c == 's' || c == 'S')
    {
        /* Yêu cầu Shutdown */
        s_flag_request_shutdown = TRUE;
        MAIN_PRINT_WARN("Button SHUTDOWN pressed -> request shutdown\n");
    }
    else if (c == 'q' || c == 'Q')
    {
        MAIN_PRINT_WARN("Quit shortcut -> force stop\n");
        Set_event(EVENT_FORCE_STOP);
    }
}

/* ====== Hướng dẫn ====== */
static void print_help(void)
{
    printf("\n=== DEMO NUT NHAN ===\n");
    printf(" m : MODE (xoay 1->2->3->1...)\n");
    printf(" s : SHUTDOWN (in \"shutdown\" khi deinit)\n");
    printf(" q : Thoat nhanh (force stop)\n");
    printf("======================\n\n");
}

/* ====== main loop ====== */
int main(void)
{
    SystemState_t state = STATE_INIT;
    MAIN_PRINT_INFO("System start\n");
    print_help();

    /* Vòng lặp until STATE_STOP */
    while (state != STATE_STOP)
    {
        /* 1) Thực thi hành động của state hiện tại (có thể bắn event) */
        execute_action(state);

        /* 2) Nếu có input người dùng, xử lý */
        {
            char line[64];
            printf("> Nhap lenh (m/s/q) + Enter: ");
            if (fgets(line, sizeof(line), stdin) != NULL)
            {
                if (line[0] != '\n' && line[0] != '\0')
                {
                    post_user_input(line[0]);
                }
            }
            /* Nếu người dùng vừa nhấn shutdown, execute_action(RUN) sẽ bắn EVENT_SHUTDOWN_REQUEST */
        }

        /* 3) Đọc event và chuyển trạng thái */
        if (s_event != EVENT_NONE)
        {
            SystemEvent_t ev = s_event;
            s_event = EVENT_NONE;

            SystemState_t next = transit_state(state, ev);
            if (next != state)
            {
                MAIN_PRINT_TRACE("STATE %d -> %d (event=%d)\n", state, next, ev);
                state = next;
            }
        }

        /* 4) Một số “auto” nhỏ để demo mượt hơn */
        if (state == STATE_RUN && s_flag_request_shutdown == TRUE)
        {
            /* Để lần sau vào execute_action(RUN) không bắn lại */
            s_flag_request_shutdown = FALSE;
        }

        if (state == STATE_ERROR)
        {
            /* Cho demo: vào ERROR thì loop sẽ chuyển STOP nhờ EVENT_FORCE_STOP ở execute_action() */
        }
    }

    MAIN_PRINT_INFO("System stopped. Bye!\n");
    return 0;
}
