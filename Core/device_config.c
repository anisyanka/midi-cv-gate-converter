#include <stdio.h>
#include <string.h>

#define JSMN_STATIC
#include "jsmn.h"

#define MULTILINE_STRING(...)	#__VA_ARGS__

#if 0
 #define MIDI_CV_GATE_CONVERTER_DEBUG_BOARD
#endif

#if defined(MIDI_CV_GATE_CONVERTER_DEBUG_BOARD)
/* JSON C-string containing default device configuration (Default MIDI-controls) */
const char *device_defconfig = MULTILINE_STRING(
{
	/* Common board info */
	"device-name": "DEBUG BOARD",
	"board-revision": "04.08.2022",

	/* Does particular digital interface exist on board? */
	"usb-interface": true,
	"midi-interface": true,

	/* GATE interface */
	"gates-in-cnt": 2,
	"gates-out-cnt": 4,

	/* CV interface */
	"cv-in-cnt": 4,
	"cv-out-cnt": 4,

	/* The FW will send MIDI CC to USB\MIDI, when gate inputs trigger */
	"gate-in-cc": {
			"gate1": 20,
			"gate2": 21,
	},

	/* The FW will trigger gate output, when receive specific MIDI CC via USB\MIDI */
	"gate-out-cc": {
		"gate-1": 22,
		"gate-2": 23,
		"gate-3": 24,
		"gate-4": 25,
	},

	/* The FW will send to USB\UART a midi CC message if CV-IN voltage changes */
	"cv-in-cc": {
		"cv-1": 9,
		"cv-2": 14,
		"cv-3": 15,
		"cv-4": 26,
	},

	/* The FW will set CV-OUT voltage if receives corresponding MIDI CC via USB\UART */
	"cv-out-cc": {
		"cv-1": 27,
		"cv-2": 28,
		"cv-3": 29,
		"cv-4": 30,	
	},
});
#else
const char *device_defconfig = NULL;
#endif


#if 0
int main()
{
	int r;
	jsmn_parser p;
	jsmntok_t t[64]; /* We expect no more than 128 JSON tokens */

	printf("%s\n", device_defconfig);

	jsmn_init(&p);
	r = jsmn_parse(&p, device_defconfig, strlen(device_defconfig), t, 128);

	printf("%d", r);

	return 0;
}
#endif