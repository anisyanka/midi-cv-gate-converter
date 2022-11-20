#include "midi_dispatcher.h"
#include "midi_cv_adapter.h"
#include "main.h"

#include <stdint.h>

/* Helpers for parser */
#define IS_STATUS_BYTE(rx)		((rx) & 0x80)
#define GET_MIDI_MSG_TYPE(rx)	(((rx) & ~0x80) >> 4)
#define GET_MIDI_CHANNEL(rx)	((rx) & 0x0f)

/* Type of midi messages */
#define MIDI_NOTE_ON			0x00
#define MIDI_NOTE_OFF			0x01
#define MIDI_POLYPH_AFTERTOUCH	0x02
#define MIDI_CC					0x03
#define MIDI_PROG_CHANGE		0x04
#define MIDI_CHAN_AFTERTOUCH	0x05
#define MIDI_PITCH_BEND_CHANGER	0x06
#define MIDI_SYSTEM_MSG			0x07

/* Hardware */
extern UART_HandleTypeDef huart1;

/* Local variables */ 
static uint8_t rx_byte = 0;
static int new_byte_flag = 0;

/* Helpers for parser */
enum note_on_of_parser_state
{
	WAITING_FOR_NOTE,
	WAITING_FOR_VELOCITY,
};

enum cc_parser_state
{
	WAITING_FOR_CC_NUMBER,
	WAITING_FOR_CC_VALUE,
};

static void note_on_off_parse(int is_new_event, uint8_t rx);
static void cc_parse(int is_new_event, uint8_t rx);

void midi_start_listener(void)
{
	HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
}

void midi_handle_byte(void)
{
	new_byte_flag = 1;
}

void midi_process(void)
{
	static uint8_t ch = 0;
	static uint8_t midi_type = 0;
	static int new_event_flag = 0;

	if (new_byte_flag)
	{
		new_byte_flag = 0;
		new_event_flag = 0;
		HAL_UART_Receive_IT(&huart1, &rx_byte, 1);

		/* Check if a new message */
		if (IS_STATUS_BYTE(rx_byte))
		{
			new_event_flag = 1;
			ch = GET_MIDI_CHANNEL(rx_byte);
			midi_type = GET_MIDI_MSG_TYPE(rx_byte);
		}
		else
		{
			/* add logic to read only particular channel here */

			switch (midi_type)
			{
				case MIDI_NOTE_ON:
					note_on_off_parse(new_event_flag, rx_byte);
					break;

				case MIDI_NOTE_OFF:
					note_on_off_parse(new_event_flag, rx_byte);
					break;

				case MIDI_POLYPH_AFTERTOUCH:
					break;

				case MIDI_CC:
					cc_parse(new_event_flag, rx_byte);
					break;

				case MIDI_PROG_CHANGE:
					break;

				case MIDI_CHAN_AFTERTOUCH:
					break;

				case MIDI_PITCH_BEND_CHANGER:
					break;

				case MIDI_SYSTEM_MSG:
					break;

				default:
					break;
			}
		}
	}
}

static void note_on_off_parse(int is_new_event, uint8_t rx)
{
	static uint8_t note = 0;
	static uint8_t velocity = 0;
	static enum note_on_of_parser_state parser_state = WAITING_FOR_NOTE;

	static uint8_t test_buf[3];

	if (is_new_event)
	{
		parser_state = WAITING_FOR_NOTE;
	}

	switch (parser_state)
	{
		case WAITING_FOR_NOTE:
			parser_state = WAITING_FOR_VELOCITY;
			note = rx;
			break;

		case WAITING_FOR_VELOCITY:
			velocity = rx;

			test_buf[0] = 0x80;
			test_buf[1] = note;
			test_buf[2] = velocity;

			HAL_UART_Transmit(&huart1, test_buf, 3, 100);
			break;

		default:
			break;
	}
}

static void cc_parse(int is_new_event, uint8_t rx)
{
	static uint8_t cc_type = 0;
	static uint8_t cc_value = 0;
	static enum cc_parser_state parser_state = WAITING_FOR_CC_NUMBER;
	int temp = 0;

	HAL_GPIO_TogglePin(GPIOB, GATE_OUT1_Pin);
	if (is_new_event)
	{
		HAL_GPIO_TogglePin(GPIOB, GATE_OUT2_Pin);
		parser_state = WAITING_FOR_CC_NUMBER;
	}

	switch (parser_state)
	{
		case WAITING_FOR_CC_NUMBER:
			HAL_GPIO_TogglePin(GPIOB, GATE_OUT3_Pin);
			parser_state = WAITING_FOR_CC_VALUE;
			cc_type = rx;
			break;

		case WAITING_FOR_CC_VALUE:
			cc_value = rx;
			HAL_GPIO_TogglePin(GPIOB, GATE_OUT3_Pin);
			/* call CV API */
			temp = (cc_value * 4095) / 127;
			midi_cv1_set((uint16_t)temp);
			break;

		default:
			break;
	}
}
