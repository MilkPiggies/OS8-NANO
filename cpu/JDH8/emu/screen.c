#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#if defined(WIN32) || defined(_WIN32)
    #include "win/win.h"
#else
    #include <sys/mman.h>
#endif

#include <SDL.h>

#include "emu.h"

#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480

#define SCANLINE_WIDTH  256
#define SCREEN_WIDTH    208
#define SCREEN_HEIGHT   240
#define SCANLINE_OFFSET (4 * 8)

// shared global
static struct {
    u8 *bank;
    bool stop;
} screen;

static pthread_t child;
static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;

static void screen_destroy(struct JDH8 *state, struct Device *dev) {
    screen.stop = true;
    pthread_join(child, NULL);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    remove_bank(state, 1);
}

static u8 screen_send(struct JDH8 *state, struct Device *dev) {
    return 0;
}

static void screen_receive(struct JDH8 *state, struct Device *dev, u8 data) {

}

static void screen_tick(struct JDH8 *state, struct Device *dev) {
    if (screen.stop) {
        remove_device(state, dev->id);
    } else {
        // SDL events must be polled on main thread
        for (SDL_Event e; SDL_PollEvent(&e);) {
            // defined in kb.c
            extern void kb_set_data(struct JDH8*, struct Device*, u8);

            switch (e.type) {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    if (has_device(state, 2)) {
                        kb_set_data(
                            state, &state->devices[2],
                            (e.type == SDL_KEYUP ? 0x80 : 0x00) |
                                e.key.keysym.scancode
                        );
                    }
                    break;
                case SDL_QUIT:
                    screen.stop = true;
                    pthread_join(child, NULL);
                    remove_device(state, dev->id);
                    break;
                default:
                    break;
            }
        }
    }
}

static void fchild(struct Device *dev) {
    u32 data[SCREEN_HEIGHT][SCREEN_WIDTH];

    while (!screen.stop) {
        // convert memory bank into texture data
        for (usize y = 0; y < SCREEN_HEIGHT; y++) {
            for (usize x = 0; x < SCREEN_WIDTH; x++) {
                const usize i =
                    (y * (SCANLINE_WIDTH / 8))
                        + ((x / 8) + (SCANLINE_OFFSET / 8));
                data[y][x] =
                    (((((u8 *) screen.bank)[i]) >> (x % 8)) & 0x01)
                        ? 0xFFFFFFFF : 0x00000000;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_UpdateTexture(texture, NULL, data, SCREEN_WIDTH * 4);
        SDL_RenderCopy(
            renderer, texture,
            &((SDL_Rect) { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }),
            &((SDL_Rect) {
                (WINDOW_WIDTH - (SCREEN_WIDTH * 2)) / 2,
                (WINDOW_HEIGHT - (SCREEN_HEIGHT * 2)) / 2,
                SCREEN_WIDTH * 2,
                SCREEN_HEIGHT * 2 }));
        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);

        // TODO: find a better framerate cap mechanism
        SDL_Delay(16);
    }
}

void screen_init(struct JDH8 *state, struct Device *dev) {
    *dev = (struct Device) {
        .id = 64,
        .send = screen_send,
        .receive = screen_receive,
        .tick = screen_tick,
        .destroy = screen_destroy
    };
    strncpy(dev->name, "SCREEN", sizeof(dev->name));

    screen.bank = add_bank(state, 1);
    screen.stop = false;

    assert(!SDL_Init(SDL_INIT_VIDEO));
    window = SDL_CreateWindow(
        "JDH8",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0
    );
    assert(window);
    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    assert(renderer);
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
        SCREEN_WIDTH, SCREEN_HEIGHT
    );
    assert(texture);
    assert(!pthread_create(&child, NULL, (void* (*)(void*)) fchild, dev));
}