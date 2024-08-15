/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ST7735/st7735.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BOTAO9 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)
#define BOTAO10 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)
#define BOTAO11 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)
#define BOTAO12 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)

#define LED3_LIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1)
#define LED4_LIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,1)
#define LED5_LIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1)
#define LED6_LIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1)

#define LED3_DESLIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0)
#define LED4_DESLIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,0)
#define LED5_DESLIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0)
#define LED6_DESLIGA HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,0)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
short tabuleiro [7][5] = {{0,0,0,0,0,0,0},
		                  {0,0,0,0,0,0,0},
		                  {0,0,0,0,0,0,0},
		                  {0,0,0,0,0,0,0},
		                  {0,0,0,0,0,0,0}};
int LugarX = 45, LugarY = 13;
int PosicaoX, PosicaoY;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);

void Menu(void);
void Controls(void);
void Jogo(void);
void Movimento(void);
void Bandeira (void);
void Selecionar (void);
/* USER CODE BEGIN PFP */

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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ST7735_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  Menu();

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

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7735_DC_Pin|ST7735_RES_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7735_CS_Pin */
  GPIO_InitStruct.Pin = ST7735_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7735_DC_Pin ST7735_RES_Pin PB3 PB4
                           PB5 PB6 */
  GPIO_InitStruct.Pin = ST7735_DC_Pin|ST7735_RES_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void Menu(void)
{
	while(1){
	ST7735_FillScreen(BLACK);
	ST7735_WriteString(35,0,"CAMPO MINEIRO", Font_7x10, WHITE, BLACK);
	ST7735_WriteString(20,30,"PA9 - PLAY", Font_7x10, WHITE, BLACK);
	ST7735_WriteString(20,45,"PA10 - BOMBS", Font_7x10, WHITE, BLACK);
	ST7735_WriteString(20,60,"PA11 - CONTROLS", Font_7x10, WHITE, BLACK);
    HAL_Delay(2000);

    while(1)
    {
    	if (BOTAO9 == 0 && BOTAO10 == 1 && BOTAO11 == 1 && BOTAO12 == 1) {
    	    Jogo();
    	    break;
    	}
    	else if (BOTAO9 == 1 && BOTAO10 == 1 && BOTAO11 == 0 && BOTAO12 == 1) {
    		Controls();
    		break;
    	}
    }
	}
}
void Controls(void) {

    ST7735_FillScreen(WHITE);
    ST7735_WriteString(10, 5, "Controles:", Font_7x10 , BLACK, WHITE);
    ST7735_WriteString(20, 20, "PA9 - ESQUERDA", Font_7x10 , BLACK, WHITE);
    ST7735_WriteString(20, 30, "PA11 - DIREITA", Font_7x10 , BLACK, WHITE);
    ST7735_WriteString(20, 40, "PA12 - CIMA", Font_7x10 , BLACK, WHITE);
    ST7735_WriteString(20, 50, "PA10 - BAIXO", Font_7x10 , BLACK, WHITE);
    ST7735_WriteString(20, 70, "PA12 -> MENU", Font_7x10 , BLACK, WHITE);

		while(1){

		   if (BOTAO9 == 1 && BOTAO10 == 1 && BOTAO11 == 1 && BOTAO12 == 0) {
			  break;
		   }
		}
}
void Jogo(void)
{
	ST7735_FillScreen(RED);
	ST7735_FillRectangle(40, 10, 110, 60, BLACK);
	// inicia tabuleiro
	for (int y = 13; y < 65; y += 9)
	{
		for (int x = 45; x < 150; x += 15)
		{
			ST7735_WriteString(x, y, "x", Font_7x10 , WHITE, BLACK);
		}
	}
	// randomiza local de bomba
	for (int i = 0; i < 9; i++)
		{
			PosicaoX = rand () % 6;
			PosicaoY = rand () % 4;
			tabuleiro [PosicaoX][PosicaoY] = 1;
		}
	Movimento();
}
void Movimento(void)
{
	LugarX = 45, LugarY = 13;
	PosicaoX = 0, PosicaoY = 0;

	ST7735_WriteString(LugarX, LugarY, "x", Font_7x10 , WHITE, YELLOW);
	while(1)
	{
	   if (BOTAO9 == 0 && BOTAO10 == 1 && BOTAO11 == 1 && BOTAO12 == 1 && LugarX>=55){
		   ST7735_WriteString(LugarX, LugarY, "x", Font_7x10 , WHITE, BLACK);
		   ST7735_WriteString(LugarX -= 15, LugarY, "x", Font_7x10 , WHITE, YELLOW);
		   if(PosicaoX > 0) PosicaoX -= 1;
		   HAL_Delay(750);
	   }
	   else if (BOTAO9 == 1 && BOTAO10 == 0 && BOTAO11 == 1 && BOTAO12 == 1 && LugarY<=56){
		   ST7735_WriteString(LugarX, LugarY, "x", Font_7x10 , WHITE, BLACK);
		   ST7735_WriteString(LugarX, LugarY += 9, "x", Font_7x10 , WHITE, YELLOW);
		   if(PosicaoY < 4) PosicaoX += 1;
		   HAL_Delay(750);
	   }
	   else if (BOTAO9 == 1 && BOTAO10 == 1 && BOTAO11 == 0 && BOTAO12 == 1 && LugarX<=134){
		   ST7735_WriteString(LugarX, LugarY, "x", Font_7x10 , WHITE, BLACK);
		   ST7735_WriteString(LugarX += 15, LugarY, "x", Font_7x10 , WHITE, YELLOW);
		   if(PosicaoX < 6) PosicaoX += 1;
		   HAL_Delay(750);
	   }
	   else if (BOTAO9 == 1 && BOTAO10 == 1 && BOTAO11 == 1 && BOTAO12 == 0 && LugarY>=22){
		   ST7735_WriteString(LugarX, LugarY, "x", Font_7x10 , WHITE, BLACK);
		   ST7735_WriteString(LugarX, LugarY -= 9, "x", Font_7x10 , WHITE, YELLOW);
		   if(PosicaoY > 0) PosicaoX -= 1;
		   HAL_Delay(750);
	   }
	   Bandeira();
	   Selecionar();
	}
}
void Bandeira (void){
	if (BOTAO9 == 0 && BOTAO10 == 0 && BOTAO11 == 1 && BOTAO12 == 1){
		ST7735_WriteString(LugarX, LugarY, "x", Font_7x10 , WHITE, BLUE);
		tabuleiro [PosicaoX][PosicaoY] = 2;
		HAL_Delay(750);
	}
}
void Selecionar (void) {
	if (BOTAO9 == 1 && BOTAO10 == 1 && BOTAO11 == 0 && BOTAO12 == 0 && tabuleiro [PosicaoX][PosicaoY] == 0){
		ST7735_FillRectangle(LugarX, LugarY, 7, 10, WHITE);
		HAL_Delay(750);
	}
	else if (BOTAO9 == 1 && BOTAO10 == 1 && BOTAO11 == 0 && BOTAO12 == 0 && tabuleiro [PosicaoX][PosicaoY] == 1){
			ST7735_FillRectangle(LugarX, LugarY, 7, 10, RED);
			HAL_Delay(750);
		}
}
void GameOver(void) {

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
  *         where the assert_param error has occurred.
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
