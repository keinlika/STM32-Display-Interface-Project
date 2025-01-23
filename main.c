/* USER CODE BEGIN Header */
/**
******************************************************************************
* @file : main.c
* @brief : Main program body
******************************************************************************
* @attention
*
* Copyright (c) 2025 STMicroelectronics.
* All rights reserved.
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
******************************************************************************
*/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define CE_PORT GPIOB // PB6 chip enable (aka slave select)
#define CE_PIN GPIO_PIN_6
#define DC_PORT GPIOA // PA0 data/control
#define DC_PIN GPIO_PIN_0
#define RESET_PORT GPIOA // PA1 reset
#define RESET_PIN GPIO_PIN_1
#define GLCD_WIDTH 84
#define GLCD_HEIGHT 48
#define NUM_BANKS 6
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
const char font_table[][6] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // space
    { 0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00 }, // 'A'
    { 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00 }, // 'B'
    { 0x3e, 0x41, 0x41, 0x41, 0x22, 0x00 }, // 'C'
    { 0x7F, 0x41, 0x41, 0x41, 0x3e, 0x00 }, // 'D'
    { 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00 }, // 'E'
    { 0x7F, 0x09, 0x09, 0x09, 0x01, 0x00 }, // 'F'
    { 0x3e, 0x41, 0x49, 0x49, 0x7a, 0x00 }, // 'G'
    { 0x7F, 0x08, 0x08, 0x08, 0x7f, 0x00 }, // 'H'
    { 0x41, 0x41, 0x7f, 0x41, 0x41, 0x00 }, // 'I'
    { 0x20, 0x40, 0x40, 0x40, 0x3f, 0x00 }, // 'J'
    { 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00 }, // 'K'
    { 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00 }, // 'L'
    { 0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00 }, // 'M'
    { 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00 }, // 'N'
    { 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00 }, // 'O'
    { 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00 }, // 'P'
    { 0x3E, 0x41, 0x51, 0x61, 0x7E, 0x00 }, // 'Q'
    { 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00 }, // 'R'
    { 0x26, 0x49, 0x49, 0x49, 0x32, 0x00 }, // 'S'
    { 0x01, 0x7F, 0x01, 0x01, 0x01, 0x00 }, // 'T'
    { 0x63, 0x40, 0x40, 0x40, 0x3F, 0x00 }, // 'U'
    { 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00 }, // 'V'
    { 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00 }, // 'W'
    { 0x63, 0x14, 0x08, 0x14, 0x63, 0x00 }, // 'X'
    { 0x03, 0x04, 0x78, 0x04, 0x03, 0x00 }, // 'Y'
    { 0x61, 0x51, 0x49, 0x45, 0x43, 0x00 }, // 'Z'
    { 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00 }, // '!'
    { 0x7E, 0x81, 0xB5, 0xA1, 0xA1, 0xB5 }, // ' Smile '
    { 0x81, 0x7E, 0x00, 0x00, 0x00, 0x00 }, // 'Smile 2 '
    { 0xf8, 0xE0, 0xC0, 0xC0, 0x80, 0x80 }, // ' top far left '
    { 0x80, 0xC0, 0xC0, 0xE0, 0xF0, 0xFE }, // ' top middle-left '
    { 0xFF, 0xFD, 0xFF, 0xFF, 0x2F, 0x2F }, // ' top middle-right '
    { 0x2F, 0x0E, 0x00, 0x00, 0x00, 0x00 }, // ' top far right '
    { 0x03, 0x07, 0x0F, 0xFF, 0xFF, 0x9F }, // ' bottom far left '
    { 0x1F, 0x0F, 0x1F, 0xFF, 0xFF, 0x9F }, // ' bottom middle-left'
    { 0x1F, 0x0F, 0x03, 0x03, 0x03, 0x07 }, // ' bottom middle-right '
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ' bottom far right '
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void SPI_write(unsigned char data);
void GLCD_data_write(unsigned char data);
void GLCD_command_write(unsigned char data);
void GLCD_init(void);
void GLCD_setCursor(unsigned char x, unsigned char y);
void GLCD_clear(void);
void GLCD_putchar(int font_table_row);
unsigned char displayPosition = 0;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
* @brief The application entry point.
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
    MX_SPI1_Init();

    /* USER CODE BEGIN 2 */
    GLCD_init(); // initialize the screen
    GLCD_clear(); // clear the screen
    GLCD_putchar(0);
    GLCD_putchar