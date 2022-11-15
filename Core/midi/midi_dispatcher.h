#ifndef MIDI_DISPATCHER_H
#define MIDI_DISPATCHER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Start UART in IT mode */
void midi_start_listener(void);

/* Call it inside INT handler function */
void midi_handle_byte(void);

/* Process each input byte */
void midi_process(void);

#ifdef __cplusplus
}
#endif

#endif  // MIDI_DISPATCHER_H
