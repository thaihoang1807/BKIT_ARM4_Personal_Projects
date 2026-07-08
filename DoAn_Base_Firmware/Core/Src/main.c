/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fsmc.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
#include "led_7seg.h"
#include "button.h"
#include "lcd.h"
#include "picture.h"
#include "ds3231.h"
#include "uart.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void system_init(void);
void test_LedDebug(void);
void test_LedY0(void);
void test_LedY1(void);
void test_SuperProject(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_FSMC_Init();

  /* USER CODE BEGIN 2 */
  system_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      while(!flag_timer2);
      flag_timer2 = 0; // Chạy mỗi 50ms

      // 1. Quét phần cứng liên tục
      button_Scan();
      ds3231_ReadTime();

      // 2. Chạy các task giao diện và điều khiển
      test_LedDebug();
      test_LedY0();
      test_LedY1();
      test_SuperProject();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void system_init(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DEBUG_LED_Pin | OUTPUT_Y0_Pin | OUTPUT_Y1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	// Tắt các LED khi khởi động
	HAL_GPIO_WritePin(GPIOE, OUTPUT_Y0_Pin|OUTPUT_Y1_Pin|DEBUG_LED_Pin, GPIO_PIN_RESET);

	// 2. Khởi tạo các module
	timer_init();
	led7_init();
	button_init();

	// 3. MỞ KHÓA MÀN HÌNH LCD
	lcd_init();

	// 4. LẤY GIỜ TỰ ĐỘNG TỪ MÁY TÍNH (Chèn vào đây!)
	int h, m, s;
	sscanf(__TIME__, "%d:%d:%d", &h, &m, &s);

	// Ghi giờ, phút, giây xuống chip RTC theo địa chỉ thanh ghi
	ds3231_Write(ADDRESS_HOUR, h);
	ds3231_Write(ADDRESS_MIN,  m);
	ds3231_Write(ADDRESS_SEC,  s);

	// 5. Các khởi tạo cuối cùng
	uart_init_rs232();
	lcd_Clear(WHITE);
	setTimer2(50);
}

// Các biến đếm cho LED đơn
uint16_t count_led_debug = 0;
uint16_t count_led_Y0 = 0;
uint16_t count_led_Y1 = 0;

void test_LedDebug(){
    count_led_debug = (count_led_debug + 1) % 20;
    if(count_led_debug == 0){
        HAL_GPIO_TogglePin(DEBUG_LED_GPIO_Port, DEBUG_LED_Pin);
    }
}

void test_LedY0(){
    count_led_Y0 = (count_led_Y0 + 1) % 100;
    if(count_led_Y0 > 40){
        HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(OUTPUT_Y0_GPIO_Port, OUTPUT_Y0_Pin, GPIO_PIN_RESET);
    }
}

void test_LedY1(){
    count_led_Y1 = (count_led_Y1 + 1) % 40;
    if(count_led_Y1 > 10){
        HAL_GPIO_WritePin(OUTPUT_Y1_GPIO_Port, OUTPUT_Y1_Pin, GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(OUTPUT_Y1_GPIO_Port, OUTPUT_Y1_Pin, GPIO_PIN_SET);
    }
}

void test_SuperProject(){
    // 1. Hiển thị giờ và phút thực tế lên màn hình LED 7 đoạn
    led7_SetDigit(ds3231_hours / 10, 0, 0);
    led7_SetDigit(ds3231_hours % 10, 1, 0);
    led7_SetDigit(ds3231_min / 10, 2, 0);
    led7_SetDigit(ds3231_min % 10, 3, 0);

    // Chớp dấu 2 chấm (Colon) của LED 7 đoạn theo giây
    if(ds3231_sec % 2 == 0) led7_SetColon(1);
    else led7_SetColon(0);

    // 2. Xử lý logic Nút nhấn, màn LCD và giao tiếp UART
    for(int i = 0; i < 16; i++){
        if(button_count[i] == 1){
            // In số thứ tự phím vừa bấm lên màn hình LCD
            lcd_ShowIntNum(140, 105, i, 2, BRED, WHITE, 32);

            // Bấm phím 12 -> bắn dữ liệu thời gian lên Terminal máy tính
            if(i == 12){
                char buffer[50];
                sprintf(buffer, "Time: %02d:%02d:%02d\r\n", ds3231_hours, ds3231_min, ds3231_sec);
                uart_Rs232SendString((uint8_t*)buffer);
            }
        }
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  * where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
