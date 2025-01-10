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
	


void Init_OC_PB0(uint32_t, uint32_t, uint32_t);
void Delay(unsigned int);	

	
int main(void)
{ 

	
uint32_t pres = 2096;	
uint32_t ccr = 800;		
uint32_t arr = 1000;		


Init_OC_PB0(pres, ccr, arr);	
	
while(1)	
{
	
//Delay(700);	

//ccr = ccr+100; 
//if (ccr> arr)
//{
//ccr=100;
//}	
	
	
//TIM2->CCR3=	ccr;
	
	
}	
	
}



void Delay(unsigned int n)
{
	int i;
    for (; n > 0; n--)
        for (i = 0; i < 136; i++) ;
	}


void Init_OC_PB0(uint32_t P, uint32_t C, uint32_t A)
	{
		uint32_t temp;
		RCC->IOPENR|=0x00000002;  /* enable GPIOA clock */    /* equivalent to     *((uint32_t *) 0x4002102C) |= 0x00000001;    */
	  		
		
//set PB0 I/O mode as alternate function
//input(00), output(01)
//alternate function (10)
temp = GPIOB->MODER;
temp &= ~(0x03<<(2*0));
temp|=(0x02<<(2*0));
GPIOB->MODER = temp;
		
			 
			 temp=GPIOB->OTYPER; 		//push pull 
	     temp &=~(0x01<<0);
	     GPIOB->OTYPER=temp;
		   
	
	     temp=GPIOB->PUPDR; //no pull-up no pull-down    
		temp&=~(0x03<<(2*0));
	     GPIOB->PUPDR=temp;
		
// TIM2_C3 (AF5) connected to PB0 
// The first 4 bits of GPIOB->AFR[0] is 5
GPIOB->AFR[0] &= ~(0xF<<(4*0));   // clear the 4 bits of the pin of interest
GPIOB->AFR[0] |= (5<<(4*0));   // clear the 4 bits of the pin of interest


// Enable the clock of TIM2
RCC->APB1ENR|= 0x1;  // enable TIM2

// Prescalar 

TIM2->PSC=P;
TIM2->CCR3=C;
TIM2->ARR=A;

//set OC 011 toggle 
//OC3M Output  cCompare 3 Mode  - bits 4 to 6 
TIM2->CCMR2&=~(0x1<<6);    //PWM mode TIM2->CCMR2|=(0x1<<6);
TIM2->CCMR2|=(0x1<<4);
TIM2->CCMR2|=(0x1<<5);

//Enable Compare output for channel 3
TIM2->CCER|=(0x1<<8);  


temp=TIM2->CR1;

//temp|=(0x1<<5);
//temp|=(0x1<<6);
//temp&=~(0x1<<4);
temp|=0x1;

TIM2->CR1=temp;

//TIM2->CR1|=(0x1<<4);    // counting up  

TIM2->CR1|=(0x1<<5); //center aligned mode
TIM2->CR1|=(0x1<<6); 

// enable counting TIM2
//TIM2->CR1|=0x1; 

TIM2->DIER|=(1<<3);	// enable interrupt of channel 3
TIM2->DIER|=(1<<0);	// enable interrupt of channel 3
NVIC_EnableIRQ(15);	


	}	


	void TIM2_IRQHandler(void) 
	{

		if((TIM2->SR&(1<<3))!=0)
		{
		TIM2->SR&=~(1<<3);
		}
		
		if((TIM2->SR&(1<<0))!=0)
		{
		TIM2->SR&=~(1<<0);
		}
		
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
