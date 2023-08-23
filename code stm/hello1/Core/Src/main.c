
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f1_rc522.h"
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t i;
uint8_t status;
uint8_t str[MAX_LEN]; // Max_LEN = 16

uint8_t serNum[5];
char password[16]="123456"; //Max lenght of password is 16 charaters
char keypass[16];
int cnt=0;
uint8_t key;
uint8_t check,check2;
//
uint8_t Key_Card[4]  = {0x64, 0x1C, 0x3F, 0x64};
uint8_t Key_Card2[4] = {0x64, 0x11, 0x0D, 0x64};
uint8_t Key_Card3[4] = {0x74, 0x36, 0x61, 0x64};
uint8_t Key_Card4[4] = {0x64, 0x00, 0x96, 0x64};

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
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
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  MFRC522_Init();
  char buffer[14]= " ";
  char input_pin[1]= " ";
  int flag=0;
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
      char left1,right1,left2,right2;
      HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
      HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
      HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
      HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
      HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  status = MFRC522_Request(PICC_REQIDL, str);	//MFRC522_Request(0x26, str)
	        	status = MFRC522_Anticoll(str);//Take a collision, look up 5 bytes
	        	memcpy(serNum, str, 5);//function for c language:(para1:that place save data,para2:the the source of data,para3:size)
	        	left1=HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
	        	right1=HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
	        	left2=HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);
	        	right2=HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
	        	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);
	        		    		   HAL_Delay(300);
	        		    		   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
	        		    		   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
	        		    		   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);

	        		    		   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
	        		    		   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);






	        	if((str[0]==0x74) && (str[1]==0x36) && (str[2]==0x61) && (str[3]==0x64) && flag==0 )
	        	{
	    		   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);
	    		   HAL_Delay(300);
	    		   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
	     	  		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, 0);
	     	  		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 0);
	     	  		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 0);
	     	  		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 0);
	               MFRC522_Init();
	              HAL_Delay(5000); /* Timer is supposed to be here */
	              flag==1;

	        	}
	        	else {         HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);

	        	        	                        if(left1==0&&right1==0)
	        	        	      	    	  		{


	        	        	                        	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, 250);
	        	        	      	    	  	        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 0);
	        	        	      	    	  	        __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 250);
	        	        	      	    	       	    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 0);


	        	        	      	    	  		}
	        	        	      	    	  		else if(left1==1&&right1==1)
	        	        	      	    	  		{



	        	        	      	    	  		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, 0);
	        	        	      	    	  		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 0);
	        	        	      	    	  		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 0);
	        	        	      	    	  		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 0);

	        	        	      	    	  		}
	        	        	      	    	  		else if(left1==1&&right1==0)
	        	        	      	    	  		{


	        	        	                        	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, 350);
	        	        	      	    	  	        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 0);
	        	        	      	    	  	        __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 0);
	        	        	      	    	       	    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 350);


	        	        	      	    	  		}
	        	        	      	    	  		else if(left1==0&&right1==1)
	        	        	      	    	  		{


	        	        	                        	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, 0);
	        	        	      	    	  	        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 350);
	        	        	      	    	  	        __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 350);
	        	        	      	    	       	    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 0);



	        	        	      	    	  		}

	        						}
	        	if((str[0]==0x64) && (str[1]==0x00) && (str[2]==0x96) && (str[3]==0x64) && flag==1 )
	        		                          	{

	        		                      		   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
	        		                       	  		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, 0);
	        		                       	  		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 0);
	        		                       	  		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 0);
	        		                       	  		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 0);
	        		                                 MFRC522_Init();
	        		                                HAL_Delay(2000); /* Timer is supposed to be here */
	        		                                flag=0;


	        		                          	}
	        		                     else {
	        		                          		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);
	        		                          	        	               if(left2==0&&right2==0)
	        		                          	        	      	    	  		{


	        		                          	        	                        	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, 0);
	        		                          	        	      	    	  	        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 250);
	        		                          	        	      	    	  	        __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 0);
	        		                          	        	      	    	       	    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 250);


	        		                          	        	      	    	  		}
	        		                          	        	      	    	  		else if(left2==1&&right2==1)
	        		                          	        	      	    	  		{
	        		                          	        	      	    	  		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, 0);
	        		                          	        	      	    	  		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 0);
	        		                          	        	      	    	  		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 0);
	        		                          	        	      	    	  		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 0);

	        		                          	        	      	    	  		}
	        		                          	        	      	    	  		else if(left2==1&&right2==0)
	        		                          	        	      	    	  		{


	        		                          	        	                        	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, 0);
	        		                          	        	      	    	  	        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 350);
	        		                          	        	      	    	  	        __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 350);
	        		                          	        	      	    	       	    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 0);

	        		                          	        	      	    	  		}
	        		                          	        	      	    	  		else if(left2==0&&right2==1)
	        		                          	        	      	    	  		{

	        		                          	        	                        	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, 350);
	        		                          	        	      	    	  	        __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, 0);
	        		                          	        	      	    	  	        __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 0);
	        		                          	        	      	    	       	    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 350);

	        		                          	        	      	    	  		}

	        		                          						}

	        	  /* USER CODE END 3 */
	        	}




	        }





  /* USER CODE END 3 */


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
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 127;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 625;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 127;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 625;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_MultiProcessor_Init(&huart1, 0, UART_WAKEUPMETHOD_IDLELINE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA8 PA9 PA10
                           PA11 PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB3 PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
