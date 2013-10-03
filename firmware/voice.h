#ifndef VOICE_H
#define VOICE_H

enum {
	SOUND_CLANG = 0,
	SOUND_JARVIS,
	SOUND_REPULSOR,
	SOUND_REPULSOR_RESHOT,
	SOUND_ACDC
};

void voice_init(void);

void voice_play(int sound);
uint8_t voice_is_busy(void);

#endif // VOICE_H
