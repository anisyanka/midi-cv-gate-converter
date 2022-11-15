#ifndef MIDI_CV_ADAPTER_H
#define MIDI_CV_ADAPTER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

/**
 * Call this function during the init process.
 * This is goint to tie low level hardware function with DAC library.
 *
 * More details are in the midi_cv_adapter.c file.
 */
void midi_cv_init(void);

void midi_cv1_set(uint16_t value);
void midi_cv2_set(uint16_t value);
void midi_cv3_set(uint16_t value);
void midi_cv4_set(uint16_t value);

#ifdef __cplusplus
}
#endif

#endif  // MIDI_CV_ADAPTER_H
