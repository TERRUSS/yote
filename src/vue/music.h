#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

static const char *MY_COOL_MP3 = "./src/assets/nightcall.mp3";
Mix_Music *music;

void initMusic() {
    int result = 0;
    int flags = MIX_INIT_MP3;

    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    music = Mix_LoadMUS(MY_COOL_MP3);

    Mix_PlayMusic(music, 1);
}
