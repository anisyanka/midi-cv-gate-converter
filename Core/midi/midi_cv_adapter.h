#ifndef MIDI_CV_ADAPTER_H
#define MIDI_CV_ADAPTER_H

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * Call this function during the init process.
 * This is goint to tie low level hardware function with DAC library.
 *
 * More details are in the midi_cv_adapter.c file.
 */
void midi_cv_init(void);

#ifdef __cplusplus
}
#endif

#endif  // MIDI_CV_ADAPTER_H
