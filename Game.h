#ifndef GAME_H
#define GAME_H

#include "rpi-gpio.h"
#include "rpi-armtimer.h"
#include "rpi-uart.h"
#include "WiiClassic.h"
#include "WS2812B.h"
#include <stdint.h>
#include <stdbool.h>
#include "defines.h"
#include "rpi-pwm.h"

#define game_pixels 60
#define distance_from_border_start game_pixels/15
#define bullet_speed 10
#define bullet_spacing 5

void play_animation();
void init_game();
void game_tick();
void spawn_object();
bool can_objects_spawn();


#endif
