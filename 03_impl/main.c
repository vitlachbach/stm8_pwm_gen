/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "stm8s_tim1.h"
#include "stm8s_tim2.h"

/* Private defines -----------------------------------------------------------*/
#define GPIO_PWM_PORT (GPIOC)
#define GPIO_PWM_PIN  (GPIO_PIN_3)

#define GPIO_LED_PORT (GPIOD)
#define GPIO_LED_PINS (GPIO_PIN_3)
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void gpio_init(void);
void pwm_init(void);
void delay_trivial(uint16_t count);
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{

  /* Initialize I/Os in Output Mode */
  gpio_init();
  pwm_init();
  while (1)
  {
  }

}
void gpio_init(void)
{
  GPIO_Init(GPIO_PWM_PORT, (GPIO_Pin_TypeDef)GPIO_PWM_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIO_LED_PORT, (GPIO_Pin_TypeDef)GPIO_LED_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
  return;
}
void pwm_init(void)
{
  // input clk is 2Mhz -> period = 52 means the pwm freq is 2Mhz / 52 ~= 38.5Khz
  uint16_t pwm1_period = 52;
  // time_pulse = (period*duty/100) - 1;
  uint16_t tim_pulse =  (pwm1_period * 50 / 100) - 1;

  TIM1_DeInit();
  TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, pwm1_period, 0);
  TIM1_OC3Init(TIM1_OCMODE_PWM2, 
                TIM1_OUTPUTSTATE_ENABLE,
                TIM1_OUTPUTNSTATE_ENABLE,
                tim_pulse, TIM1_OCPOLARITY_LOW,
                TIM1_OCNPOLARITY_LOW, 
                TIM1_OCIDLESTATE_SET, 
                TIM1_OCNIDLESTATE_RESET);
  TIM1_Cmd(ENABLE);
  TIM1_CtrlPWMOutputs(ENABLE);

/* Time base configuration */
  TIM2_DeInit();
  TIM2_TimeBaseInit(TIM2_PRESCALER_32768, 51);

  /* PWM1 Mode configuration: Channel2 */ 
  TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,24, TIM2_OCPOLARITY_HIGH);
  TIM2_OC2PreloadConfig(ENABLE);

  TIM2_ARRPreloadConfig(ENABLE);

  /* TIM2 enable counter */
  TIM2_Cmd(ENABLE);
}
/**
  * @brief Delay
  * @param nCount
  * @retval None
  */

void delay_trivial(uint16_t count)
{
  while (count != 0)
  {
    count--;
  }
}
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/