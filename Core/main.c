#include "main.h"
#include "init.h"

#include "midi_cv_adapter.h"
#include "midi_dispatcher.h"

extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c2;
extern SPI_HandleTypeDef hspi1;

int main(void)
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	GPIO_Init();
	SPI1_Init();
	USART1_UART_Init();
	ADC1_Init();
	I2C2_Init();

	/* Initialize CV output channels */
	midi_cv_init();

	/* Start UART receiver */
	midi_start_listener();

	/* Infinite loop */
	while (1)
	{
		midi_process();
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		midi_handle_byte();
	}
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
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
void assert_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
