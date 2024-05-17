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
#include "st7789\st7789.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define BTNUP_ON  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == GPIO_PIN_RESET
#define BTNDOWN_ON  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_RESET
#define BTNLEFT_ON  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_RESET
#define BTNRIGHT_ON  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET

#define LED1ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1)
#define LED2ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1)
#define LED3ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1)
#define LED4ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1)
#define LED1OFF  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0)
#define LED2OFF  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0)
#define LED3OFF  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0)
#define LED4OFF  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
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
  ST7789_Init();
  ST7789_Fill_Color(BLACK);




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /* USER CODE END WHILE */
      /* USER CODE BEGIN 3 */
	  MainMenu();
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
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
  HAL_GPIO_WritePin(ST7789_CS_GPIO_Port, ST7789_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7789_DC_Pin|ST7789_RST_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7789_CS_Pin */
  GPIO_InitStruct.Pin = ST7789_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7789_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7789_DC_Pin ST7789_RST_Pin PB3 PB4
                           PB5 PB6 */
  GPIO_InitStruct.Pin = ST7789_DC_Pin|ST7789_RST_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
int x_barrier = 0;
int y_barrier = 0;
int choice_menu = 0;
int confirm_choice = 0;
int choice_velocity = 0;
int velocity = 0;
int confirm_velocity = 0;
int x_snake = 20;
int y_snake = 60;
int btnvalue = 0;
int collision_true = 0;
int x_snake_old = 0;
int y_snake_old = 0;
int back_menu = 0;
int confirm_back = 0;
int x_collectable = 0;
int y_collectable = 0;
int playerscore = 0;
int unity_score = 0;
int ten_score = 0;
int record = 0;
int unity_record = 0;
int ten_record = 0;

void MainMenu()
{
	ST7789_WriteString(25,20," Snake Zika ", Font_16x26, BLACK, CYAN);
	ST7789_WriteString(60,75," Play (UP) ", Font_11x18, WHITE, BLACK);
	ST7789_WriteString(25,110," Velocity (DOWN) ", Font_11x18, WHITE, BLACK);
	ST7789_WriteString(50,150," RECORD >  ", Font_11x18, WHITE, BLACK);
	ST7789_WriteChar(170, 150,unity_record + '0', Font_11x18, WHITE, BLACK);
    ST7789_WriteChar(160, 150,ten_record + '0', Font_11x18, WHITE, BLACK);
	ST7789_WriteString(55,200," Confirm (RIGHT) ", Font_7x10, WHITE, BLACK);


	if(BTNUP_ON ==1)
	{
		choice_menu = 1;
	}
	else if(BTNDOWN_ON ==1)
	{
		choice_menu = 2;
	}

	switch(choice_menu)
	{
		case 1:
			ST7789_WriteString(60,75," Play (UP) ", Font_11x18, BLACK, CYAN);
			LED1ON;
			LED2OFF;
		break;

		case 2:
			ST7789_WriteString(25,110," Velocity (DOWN) ", Font_11x18, BLACK, CYAN);
			LED2ON;
			LED1OFF;
		break;
	}

	if(BTNRIGHT_ON == 1)
	{
		confirm_choice = 1;
		LED2OFF;
	}

	if(choice_menu == 1 && confirm_choice == 1)
	{
		confirm_choice = 0;
		ST7789_Fill_Color(BLACK);
		StartGame();
	}
	else if (choice_menu == 2 && confirm_choice == 1)
	{
		confirm_choice = 0;
		ST7789_Fill_Color(BLACK);
		ChooseVelocity();
	}
}

void ChooseVelocity()
{
	while (confirm_velocity == 0)
	{
		ST7789_WriteString(25,20," Snake Zika ", Font_16x26, BLACK, CYAN);
		ST7789_WriteString(60,75," Fast (UP) ", Font_11x18, WHITE, BLACK);
		ST7789_WriteString(30,110," Medium (LEFT) ", Font_11x18, WHITE, BLACK);
		ST7789_WriteString(50,145," Slow (DOWN) ", Font_11x18, WHITE, BLACK);
		ST7789_WriteString(55,190," Confirm (RIGHT) ", Font_7x10, WHITE, BLACK);

		if(BTNUP_ON ==1)
		{
			choice_velocity = 1;
		}
		else if(BTNLEFT_ON ==1)
		{
			choice_velocity = 2;
		}
		else if(BTNDOWN_ON ==1)
		{
			choice_velocity = 3;
		}

		switch(choice_velocity)
		{
			case 1:
				ST7789_WriteString(60,75," Fast (UP) ", Font_11x18, BLACK, CYAN);
				LED1ON;
				LED2OFF;
				LED3OFF;
			break;

			case 2:
				ST7789_WriteString(30,110," Medium (LEFT) ", Font_11x18, BLACK, CYAN);
				LED1OFF;
				LED2ON;
				LED3OFF;
			break;

			case 3:
				ST7789_WriteString(50,145," Slow (DOWN) ", Font_11x18, BLACK, CYAN);
				LED1OFF;
				LED2OFF;
				LED3ON;
			break;
		}

		if(BTNRIGHT_ON == 1)
		{
			confirm_velocity = 1;
			LED1OFF;
			LED2OFF;
			LED3OFF;
		}
	}
	if(choice_velocity == 1 && confirm_velocity == 1)
	{
		confirm_velocity = 0;
		velocity = 0;
		ST7789_Fill_Color(BLACK);
		MainMenu();
	}
	else if (choice_velocity == 2 && confirm_velocity == 1)
	{
		confirm_velocity = 0;
		velocity = 75;
		ST7789_Fill_Color(BLACK);
		MainMenu();

	}
	else if (choice_velocity == 3 && confirm_velocity == 1)
	{
		confirm_velocity = 0;
		velocity = 150;
		ST7789_Fill_Color(BLACK);
		MainMenu();
	}

}

void StartGame()
{
	ST7789_WriteString(0 ,230,"Your Score: ", Font_7x10, WHITE, BLACK);
	ST7789_WriteString(120, 230,"High Score: ", Font_7x10, WHITE, BLACK);

	x_snake = 20;
	y_snake = 60;
    collision_true = 0;
    playerscore = 0;
    unity_score = 0;
    ten_score = 0;

    DrawBarrier();
    GenerateCollectable();
	Snake();


}

void VerifyCollision()
{
	if ((x_snake <= 10 || x_snake >= 238) || (y_snake <= 2 || y_snake >= 215))
	{
		collision_true = 1;
	}
	else
    {
		collision_true = 0;
	}

}

int VerifyCatch()
{

	if(x_snake <= x_collectable + 5 && x_snake  >= x_collectable - 5 && y_snake <= y_collectable + 5 && y_snake >= y_collectable - 5)
	{
		unity_score++;
		playerscore++;
		ST7789_DrawFilledCircle(x_collectable, y_collectable, 7, BLACK);
		GenerateCollectable();
		UpdateScore();
		UpdateRecord();
	}

}

void GenerateCollectable()
{
		x_collectable = rand() % 228 + 1;
	    y_collectable = rand() % 205 + 1;

	    if ((x_collectable <= 14 || x_collectable >= 234) || ( y_collectable <= 6 ||  y_collectable >= 211))
	    {
	    	ST7789_DrawFilledCircle(85,100, 3, MAGENTA);
	    }
	    else
	    {
	    	ST7789_DrawFilledCircle(x_collectable, y_collectable, 3, MAGENTA);
	    }

}

void UpdateScore()
{

	if (unity_score > 9)
	{
		unity_score = 0;
		ten_score ++;
	}

	ST7789_WriteChar(95, 230,unity_score + '0', Font_7x10, WHITE, BLACK);
    ST7789_WriteChar(85, 230,ten_score + '0', Font_7x10, WHITE, BLACK);
}

void UpdateRecord()
{
	if (playerscore > record)
	{
		record = playerscore;
		unity_record = unity_score;
		ten_record = ten_score;

		if (unity_record > 9)
		{
			unity_record = 0;
			ten_record ++;
		}
	}
	ST7789_WriteChar(210, 230,unity_record + '0', Font_7x10, WHITE, BLACK);
	ST7789_WriteChar(200, 230,ten_record + '0', Font_7x10, WHITE, BLACK);
}

void Snake()
{
	while (collision_true == 0)
	{
		ST7789_DrawFilledCircle(x_snake, y_snake,7, GREEN);

		x_snake_old = x_snake;
		y_snake_old = y_snake;

		if(BTNUP_ON == 1)
		{
			btnvalue = 1;
		}

        else if(BTNDOWN_ON == 1)
        {
        	btnvalue = 2;
		}

		else if(BTNLEFT_ON == 1)
		{
			btnvalue = 3;
		}

		else if(BTNRIGHT_ON == 1)
		{
			btnvalue = 4;
		}

		x_snake_old = x_snake;
		y_snake_old = y_snake;



		switch (btnvalue)
		{
			case 1:
				y_snake-=10;
				ST7789_DrawFilledCircle(x_snake, y_snake,7, GREEN);
				ST7789_DrawFilledCircle(x_snake_old, y_snake_old, 7, BLACK);
				HAL_Delay(velocity);
				VerifyCollision();
				VerifyCatch();
		    break;

		    case 2:
		    	y_snake+=10;
		    	ST7789_DrawFilledCircle(x_snake, y_snake,7, GREEN);
		    	ST7789_DrawFilledCircle(x_snake_old, y_snake_old, 7, BLACK);
		    	HAL_Delay(velocity);
		    	VerifyCollision();
		    	VerifyCatch();
		    break;

		    case 3:
		    	x_snake-=10;
		    	ST7789_DrawFilledCircle(x_snake, y_snake,7, GREEN);
		    	ST7789_DrawFilledCircle(x_snake_old, y_snake_old, 7, BLACK);
		    	HAL_Delay(velocity);
		    	VerifyCollision();
		    	VerifyCatch();
		    break;

		    case 4:
		    	x_snake+=10;
		    	ST7789_DrawFilledCircle(x_snake, y_snake,7, GREEN);
		    	ST7789_DrawFilledCircle(x_snake_old, y_snake_old, 7, BLACK);
		    	HAL_Delay(velocity);
		    	VerifyCollision();
		    	VerifyCatch();
		    break;

		}

	}
	btnvalue = 0;
	GameOver();
}


void DrawBarrier()
{
	for(x_barrier = 2 ; x_barrier <= 238; x_barrier++)
	{
		ST7789_DrawFilledCircle(x_barrier,2, 2, BLUE);
		ST7789_DrawFilledCircle(x_barrier,215, 2, BLUE);
	}
	for (y_barrier = 2; y_barrier <= 215; y_barrier++)
	{
		ST7789_DrawFilledCircle(2,y_barrier, 2, BLUE);
		ST7789_DrawFilledCircle(238,y_barrier, 2, BLUE);
	}
}

void GameOver()
{
	ST7789_Fill_Color(BLACK);
	ST7789_WriteString(50,40,">> YOU <<", Font_16x26, BLACK, CYAN);
	ST7789_WriteString(40,65,">> LOSE <<", Font_16x26, BLACK, CYAN);
	ST7789_WriteString(70,190,"MENU (UP)", Font_11x18, CYAN, BLACK);
	LED1ON;
	LED2ON;
	LED3ON;
	LED4ON;

	while(confirm_back == 0)
	{
		if (BTNUP_ON == 1)
		{
			ST7789_WriteString(70,190,"MENU (UP)", Font_11x18, BLACK, CYAN);
			back_menu = 1;
		}

		if (BTNRIGHT_ON == 1)
		{
			confirm_back = 1;
		}
	}
	confirm_back = 0;
	ST7789_Fill_Color(BLACK);
	LED1OFF;
	LED2OFF;
	LED3OFF;
	LED4OFF;
	MainMenu();
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence
  * @retval None
  */
void Error_Handler()
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
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
