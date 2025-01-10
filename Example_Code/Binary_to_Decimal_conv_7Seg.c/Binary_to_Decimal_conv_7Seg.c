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
void Write_SR_7S(uint8_t, uint8_t);
void Write_7Seg(uint8_t, uint8_t);	
void Init_7Seg(void);	
	
int main(void)
{ 
	int i;
int number;
int temp;	
int Digit4=3;
int Digit3=4;
int Digit2=5;
int Digit1=6;
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  
	/*SystemCoreClockUpdate();*/
	
		
	Init_7Seg();
	

number=1974;

temp=number;

Digit1=temp%10; /* temp%10 =4   % gives the remainder*/
temp=temp/10; /*temp=197    / gives the quotient*/

Digit2=temp%10; /* temp%10 =7   % gives the remainder*/
temp=temp/10; /*temp=19    / gives the quotient*/

Digit3=temp%10; /* temp%10 =9   % gives the remainder*/
temp=temp/10; /*temp=1    / gives the quotient*/

Digit4=temp%10; /* temp%10 =1   % gives the remainder*/
temp=temp/10; /*temp=0    once the quotient =0, STOP dividing by 10 */

	
	while (1)
  {
				
		Write_7Seg(1, Digit4);
		Delay(1);
		Write_7Seg(2, Digit3);
		Delay(1);
		Write_7Seg(3, Digit2);
		Delay(1);
		Write_7Seg(4, Digit1);
		Delay(1);
	
	}	
		
		

	
  /* USER CODE END 3 */
}



void Init_7Seg()	
{	    		
			/*PB5 MOSI, PA7 /CS_7 latch , PB_3 shift clock */  
	uint32_t temp;		
	
	    RCC->IOPENR|=0x00000001;  /* enable GPIOA clock */
			RCC->IOPENR|=0x00000002;  /* enable GPIOB clock */
			
	     	 
			 
			 	 temp = GPIOA->MODER;
			 temp &= ~(0x03<<(2*7));
			 temp|=(0x01<<(2*7));
			 GPIOA->MODER = temp; 
			 
			 temp=GPIOA->OTYPER;
	temp &=~(0x01<<7);
	GPIOA->OTYPER=temp;
	
	
	temp=GPIOA->PUPDR;
	temp&=~(0x03<<(2*7));
	GPIOA->PUPDR=temp;

	
			 	 temp = GPIOB->MODER;
			 temp &= ~(0x03<<(2*5));
			 temp|=(0x01<<(2*5));
			 GPIOB->MODER = temp; 
			 
			 temp=GPIOB->OTYPER;
	temp &=~(0x01<<5);
	GPIOB->OTYPER=temp;
	
	
	temp=GPIOB->PUPDR;
	temp&=~(0x03<<(2*5));
	GPIOB->PUPDR=temp;
	
	
	
		 
				 	 temp = GPIOB->MODER;
			 temp &= ~(0x03<<(2*3));
			 temp|=(0x01<<(2*3));
			 GPIOB->MODER = temp; 
			 
			 temp=GPIOB->OTYPER;
	temp &=~(0x01<<3);
	GPIOB->OTYPER=temp;
	
	
	temp=GPIOB->PUPDR;
	temp&=~(0x03<<(2*3));
	GPIOB->PUPDR=temp;
}

void Write_7Seg(uint8_t temp_Enable, uint8_t temp_Digit)
{
	uint8_t Enable[5] = {0x00, 0x08, 0x04, 0x02, 0x01}; /* common anode use 1 to enable a segment and zeros to light the segments */
		 uint8_t Digit[10]= {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
	Write_SR_7S(Enable[temp_Enable], Digit[temp_Digit]);
}	


void Write_SR_7S(uint8_t temp_Enable, uint8_t temp_Digit)
{
int i;
uint8_t mask=0b10000000;
	
for(i=0; i<8; i++)	
{
	if((temp_Digit&mask)==0)
		GPIOB->ODR&=~(1<<5);
		else
		GPIOB->ODR|=(1<<5);
	
	/*  Sclck */
	GPIOB->ODR&=~(1<<3);
	
	GPIOB->ODR|=(1<<3);	
	
	
 mask=mask>>1;	
}	
	
	mask=0b10000000;
	
for(i=0; i<8; i++)	
{
	if((temp_Enable&mask)==0)
		GPIOB->ODR&=~(1<<5);
		else
		GPIOB->ODR|=(1<<5);
	
	/*  Sclck */
	GPIOB->ODR&=~(1<<3);
	/*Delay(1);*/
	GPIOB->ODR|=(1<<3);	
	/*Delay(1);	*/
	
 mask=mask>>1;	
}	
	
/*Latch*/
	GPIOA->ODR|=(1<<7);	
	GPIOA->ODR&=~(1<<7);	
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
