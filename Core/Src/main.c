
#include "main.h"
#include "math.h"
#include <string.h>
#include <stdio.h>
#include "FloatToChar.h"
#include "LiquidCrystal.h"
#include "MPU6050.h"


#define TIMER_FREQUENCY_HZ             ((uint32_t)1000)    
ADC_HandleTypeDef    AdcHandle;
TIM_HandleTypeDef    TimHandle;
I2C_HandleTypeDef I2CHandle;


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void ADC_Config(void);
static void TIM_Config(void);
static void I2C_Config(void);
static void MX_GPIO_Init(void);


int main(void)
{
	uint16_t raw;
//char str[80];
	double resistance;
	float x;
	double digital;
	float Temp;
	char buff[10];
  
 
  HAL_Init();
	LiquidCrystal(GPIOA, GPIO_PIN_1, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_9, GPIO_PIN_8);
  
  print("Temp:");
  //createChar(0,three);
  // setCursor(7,0);
  // write(0);
  setCursor(0,1);

  /* Configure the system clock to 64 MHz */
  SystemClock_Config();
  /* Configure the ADC peripheral */
  ADC_Config();
  
  /* Configure the TIM peripheral */
  TIM_Config();
  
  MX_GPIO_Init();
  /* Configure the I2C peripheral */
  I2C_Config();
 
  MPU6050_Init();
  
  

  /* Timer counter enable */
  if (HAL_TIM_Base_Start(&TimHandle) != HAL_OK)
  {
    /* Counter Enable Error */
    Error_Handler();
		
  }
  
	HAL_ADC_Start(&AdcHandle);
  HAL_NVIC_SetPriority(EXTI3_IRQn , 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);
  /* Infinite loop */
  while (1)
  {
		
		//MPU6050_Read_Accel();
    HAL_ADC_PollForConversion(&AdcHandle, HAL_MAX_DELAY);
		
		//print("HEY");
		raw = HAL_ADC_GetValue(&AdcHandle);
		digital = (double)(3.3/4095)*raw;
	
		// initialized 12 bit resolution
		//so the max analog value is 2^12-1=4095
		//which corresponds to 5v so the 5/4095 
		//ration must be held
	
		resistance = (3.3-digital)*10000.0/digital;
	
		x = 0.00102219653793705 + 0.000253179116444952*((float)log(resistance)) -0.000000000058799201163101*((float)powf(log(resistance),3)); 
		Temp = 1.0/x - 273.15;

    // if(ACCEL_X<-0.2)
    // {
    //   //implement while loops, cleaner 
    //   //check for 0 or 8
    //   rightToLeft();
    //   setCursor(15,15);
    //   //t
    //   //write(5)
    //   //e
    //   //write(6)
    //   //m
    //   //write(7)
    //   //print("b:");
    //   // setCursor(15,0);
    //   // write(0);
    //   // write(1);
    //   // write(2);
    //   // write(3);
     
      
    // }
    // else
    // {
      leftToRight();
      float_char(buff,Temp,0);
      setCursor(0,1);
      
      print(buff);
      float_char(buff,ACCEL_X,0);
      setCursor(8,1);
      
      print(buff);
    // }
    
   
		
		HAL_Delay(1000);
	}
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 64000000
  *            HCLK(Hz)                       = 64000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 8000000
  *            PREDIV                         = RCC_PREDIV_DIV2 (2)
  *            PLLMUL                         = RCC_PLL_MUL16 (16)
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */


void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* HSI Oscillator already ON after system reset, activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  ADC configuration
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
  ADC_ChannelConfTypeDef   sConfig;
  
  /* Configuration of ADCx init structure: ADC parameters and regular group */
  AdcHandle.Instance = ADC1;

  AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.ScanConvMode          = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
  AdcHandle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
  AdcHandle.Init.LowPowerAutoWait      = DISABLE;
  AdcHandle.Init.ContinuousConvMode    = ENABLE;                       /* Continuous mode disabled to have only 1 conversion at each conversion trig */
  AdcHandle.Init.NbrOfConversion       = 1;                             /* Parameter discarded because sequencer is disabled */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
  AdcHandle.Init.NbrOfDiscConversion   = 1;                             /* Parameter discarded because sequencer is disabled */
  AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;  /* Trig of conversion start done by external event */
  AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
  AdcHandle.Init.DMAContinuousRequests = DISABLE;
  AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;

  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)
  {
    /* ADC initialization error */
    Error_Handler();
  }
  sConfig.Channel      = ADC_CHANNEL_1;
  sConfig.Rank         = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_181CYCLES_5;
  sConfig.SingleDiff   = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset       = 0;
  
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    /* Channel Configuration Error */
    Error_Handler();
  }
  

 
}
static void I2C_Config(void)
{
   I2CHandle.Instance = I2C1;
  I2CHandle.Init.Timing= 0x2000090E;
  I2CHandle.Init.OwnAddress1= 0;
  I2CHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  I2CHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2CHandle.Init.OwnAddress2 = 0;
  I2CHandle.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  I2CHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2CHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&I2CHandle) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&I2CHandle, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&I2CHandle, 0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  TIM configuration
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{
  TIM_MasterConfigTypeDef sMasterConfig;
  
  /* Time Base configuration */
  TimHandle.Instance = TIM1;
  
  /* Configure timer frequency */
  /* Note: Setting of timer prescaler to 1099 to increase the maximum range   */
  /*       of the timer, to fit within timer range of 0xFFFF.                 */
  /*       Setting of reload period to SysClk/1099 to maintain a base         */
  /*       frequency of 1us.                                                  */
  /*       With SysClk set to 72MHz, timer frequency (defined by label        */
  /*       TIMER_FREQUENCY_HZ range) is min=1Hz, max=32.757kHz.               */
  /* Note: Timer clock source frequency is retrieved with function            */
  /*       HAL_RCC_GetPCLK1Freq().                                            */
  /*       Alternate possibility, depending on prescaler settings:            */
  /*       use variable "SystemCoreClock" holding HCLK frequency, updated by  */
  /*       function HAL_RCC_ClockConfig().                                    */
  TimHandle.Init.Period = ((HAL_RCC_GetPCLK1Freq() / (1099 * TIMER_FREQUENCY_HZ)) - 1);
  TimHandle.Init.Prescaler = (1099-1);
  TimHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  TimHandle.Init.RepetitionCounter = 0x0;
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
  {
    /* Timer initialization Error */
    Error_Handler();
  }

  /* Timer TRGO selection */
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

  if (HAL_TIMEx_MasterConfigSynchronization(&TimHandle, &sMasterConfig) != HAL_OK)
  {
    /* Timer TRGO selection Error */
    Error_Handler();
  }
  
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
  GPIO_InitStruct.Pin=GPIO_PIN_3;
  GPIO_InitStruct.Mode=GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull=GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
}

/**
  * @brief  DAC configuration
  * @param  None
  * @retval None
  */



/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */


/**
  * @brief  Conversion complete callback in non blocking mode
  * @param  AdcHandle : AdcHandle handle
  * @note   This example shows a simple way to report end of conversion
  *         and get conversion result. You can add your own implementation.
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{

}

/**
  * @brief  Conversion DMA half-transfer callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{

}
  
/**
  * @brief  Analog watchdog callback in non blocking mode. 
  * @note:  In case of several analog watchdog enabled, if needed to know
            which one triggered and on which ADCx, check Analog Watchdog flag
            ADC_FLAG_AWD1/2/3 into HAL_ADC_LevelOutOfWindowCallback() function.
            For example:"if (__HAL_ADC_GET_FLAG(hadc1, ADC_FLAG_AWD1) != RESET)"
  * @param  hadc: ADC handle
  * @retval None
  */
  void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
  /* Set variable to report analog watchdog out of window status to main      */
  /* program.                                                                 */
  
}

/**
  * @brief  ADC error callback in non blocking mode
  *        (ADC conversion with interruption or transfer by DMA)
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
  /* In case of ADC error, call main error handler */
  Error_Handler();
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* User may add here some code to deal with a potential error */
  
  /* In case of error, LED2 is toggling at a frequency of 1Hz */
  while(1)
  {
    /* Toggle LED2 */
  
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

