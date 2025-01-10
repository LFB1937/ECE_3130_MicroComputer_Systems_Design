/* USER CODE BEGIN Header */
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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
	

void Delay(unsigned int);	
void Init_LED0(void);
void Init_LED1(void);
void Init_LED3(void);
void LED_on(int);
void LED_off(int);

int main(void)
{ 
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
    /* Configure the system clock */
  SystemClock_Config();

	Init_LED0();
	Init_LED1();
	Init_LED3();
	
	
	while (1)
  {
    LED_on(0);
		LED_off(1);
		LED_off(3);
		Delay(500);
		
		LED_off(0);
		LED_on(1);
		LED_off(3);
		Delay(500);
		
		
		LED_off(0);
		LED_off(1);
		LED_on(3);
		Delay(500);
		
  }
  
}

void LED_on(int i)
{
	if(i==0)
	{
		GPIOA->ODR|=(1<<12);
	}
	else if(i==1)
	{
	GPIOB->ODR|=(1<<0);
	}	
	else if(i==3)
	{
	GPIOB->ODR|=(1<<7);
	}	
	
}

void LED_off(int i )
{
	if(i==0)
	{
		GPIOA->ODR&=~(1<<12);    
	}
	else if(i==1)
	{
	GPIOB->ODR&=~(1<<0);    
	}	
	else if(i==3)
	{
	GPIOB->ODR&=~(1<<7);    
	}	
}	


void Init_LED0()
	{
		uint32_t temp;
		RCC->IOPENR|=0x00000001;  /* enable GPIOA clock */    /* equivalent to     *((uint32_t *) 0x4002102C) |= 0x00000001;    */
	  		
			 temp = GPIOA->MODER;      /*equivalent to temp = *((uint32_t *) 0x50000000) ;*/		 
			 temp &= ~(0x03<<(2*12));
			 temp|=(0x01<<(2*12));
			 GPIOA->MODER = temp; 
		
			 
			 temp=GPIOA->OTYPER; /*equivalent to temp = *((uint32_t *) 0x50000004) ;*/		 
	     temp &=~(0x01<<12);
	     GPIOA->OTYPER=temp;
		   
	
	     temp=GPIOA->PUPDR;    /*equivalent to temp = *((uint32_t *) 0x5000000C) ;*/		 
		temp&=~(0x03<<(2*12));
	     GPIOA->PUPDR=temp;
	}	
	
	void Init_LED1()
	{
		uint32_t temp;
		RCC->IOPENR|=0x00000002;  /* enable GPIOB clock */    /* equivalent to     *((uint32_t *) 0x4002102C) |= 0x00000001;    */
	  		
	temp = GPIOB->MODER;
	temp &= ~(0x03<<(2*0));
	temp|=(0x01<<(2*0));
	GPIOB->MODER = temp; 
			 
	temp=GPIOB->OTYPER;
	temp &=~(0x01<<0);
	GPIOB->OTYPER=temp;
		
	temp=GPIOB->PUPDR;
	temp&=~(0x03<<(2*0));
	GPIOB->PUPDR=temp;
	}	
	
void Init_LED3()
	{
		uint32_t temp;
		RCC->IOPENR|=0x00000002;  /* enable GPIOB clock */    /* equivalent to     *((uint32_t *) 0x4002102C) |= 0x00000001;    */
	  		
	temp = GPIOB->MODER;
	temp &= ~(0x03<<(2*7));
	temp|=(0x01<<(2*7));
	GPIOB->MODER = temp; 
			 
	temp=GPIOB->OTYPER;
	temp &=~(0x01<<7);
	GPIOB->OTYPER=temp;
		
	temp=GPIOB->PUPDR;
	temp&=~(0x03<<(2*7));
	GPIOB->PUPDR=temp;
	}	
	

void Delay(unsigned int n)
{
	int i;
    for (; n > 0; n--)
        for (i = 0; i < 136; i++) ;
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
