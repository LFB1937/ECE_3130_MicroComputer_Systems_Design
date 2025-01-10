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

	
void Init_LED0(void);	
void EXTI_PA5_Init(void); 
void Delay(unsigned int);	


int main(void)
{ 
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
    /* Configure the system clock */
  SystemClock_Config();

	Init_LED0();
	EXTI_PA5_Init(); 
	
  while (1) {	}

}

void Delay(unsigned int n)
{
	int i;
    for (; n > 0; n--)
        for (i = 0; i < 136; i++) ;
	}


void EXTI_PA5_Init(void)
{
	uint32_t temp;
	
//===== (1) Configure PA5 input  

RCC->IOPENR|=0x00000001;  /* enable GPIOA clock */	

//Configure PA5 pin input 
	     temp = GPIOA->MODER;
			 temp &= ~(0x03<<(2*5));
			 GPIOA->MODER = temp; 
	
	temp=GPIOA->OTYPER;
	temp &=~(0x01<<5);
	GPIOA->OTYPER=temp;
	
  // Add Pull down resistance 
  //  Pull-up (01), Pull-down (10), Reserved (11)
  temp=GPIOA->PUPDR;
	temp&=~(0x03<<(2*5));
	temp|=(0x02<<(2*5));
	GPIOA->PUPDR=temp;  // Pull down

//============================================
	
// ===== (2) Connect External Line to the GPI

//enable the clock of SYSCFG
RCC->APB2ENR |= 0x00000001; //  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

//clear the 4 bits of the EXIT5
SYSCFG->EXTICR[1] &= ~(0x00F0);  //SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI5; 

//select port A	
SYSCFG->EXTICR[1] |= 0x0000;  //SYSCFG->EXTICR[1] |=  SYSCFG_EXTICR2_EXTI5_PA; 
//===============================


// ===== (3) Rising trigger selection
  // 0 = trigger disabled, 1 = trigger enabled
   EXTI->RTSR |= (1<<5);  //EXTI->RTSR |= EXTI_RTSR_RT5;  
//==========================	


// ===== (4) Enable interrupt
		
// 4.1 NVIC enable bit		
NVIC->ISER[0U] = 1<<7;  //OR NVIC_EnableIRQ(EXTI4_15_IRQn); 

//4.2 Peripheral enable bit
  // 0 = marked, 1 = not masked (enabled)
  EXTI->IMR |= (1<<5);  //EXTI->IMR |= EXTI_IMR_IM5;     
		

}

void EXTI4_15_IRQHandler(void) {  

GPIOA->ODR^=(1<<12);// Toggle LED
					
// Cleared flag by writing 1   
EXTI->PR |= (1<<5);  //EXTI->PR |= EXTI_PR_PIF5;


	
// debouncing code	
Delay(10);	
while((GPIOA->IDR&(1<<5))!=0)
{} // wait until the button is released
Delay(10);		
	

}

//====================================


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
