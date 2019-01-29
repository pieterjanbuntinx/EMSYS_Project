#include "Game.h"

uint8_t player1_pos;
uint8_t player2_pos;
uint8_t count_till_next_step1;
uint8_t count_till_next_step2;
bool player1_cooldown;
bool player2_cooldown;
uint8_t player1_health;
uint8_t player2_health;
uint8_t player1_move_wait;
uint8_t player2_move_wait;
bool player1_lost_round = false;
bool player2_lost_round = false;

uint8_t bullet1_pos;
uint8_t bullet2_pos;
bool bullet1_shot;
bool bullet2_shot;
uint8_t bullet1_move_counter;
uint8_t bullet2_move_counter;

bool objects[game_pixels];

uint8_t left_joy_neutral;
uint8_t right_joy_neutral;

uint8_t brightness;
bool game_ended = true;
bool spawn_objects = false;
uint16_t count = 0;

static void next_round();
static void remove_objects();
static void game_reset();
static void kill_player1();
static void kill_player2();
static bool is_position_accessible(uint8_t position);
static void move_player1();
static void move_player2();
static void handle_objects();
static void play_win_animation(uint8_t location, uint8_t color);
static void show_health();
static uint8_t rand_range(uint8_t min, uint8_t max);

static uint8_t rand_range(uint8_t min, uint8_t max) {
    return rand() % (max + 1 - min) + min;
}

bool side; // true: side player1, false: side player2
void spawn_object() {
    remove_objects();
    uint16_t rand_num;
    if (!side) {
        rand_num = rand_range(7, 23);
        while(rand_num == player1_pos) rand_num = rand_range(7, 22);
        side = true;
    } else {
        rand_num = rand_range(35, 52);
        while(rand_num == player2_pos) rand_num = rand_range(35, 52);
        side = false;
    }
    objects[rand_num] = true;      
}

bool can_objects_spawn() {
    return spawn_objects;
}

static void remove_objects() {
    uint8_t i;
    for (i=0; i<game_pixels; i++) {
        objects[i] = false;
    }

    objects[29] = true;
    objects[0] = true;
    objects[59] = true;
}

#define animation_frame_timing 6000
void play_animation() {
    uint8_t b;
	for (b = 0; b<brightness; b++) {
		uint8_t i;
		for (i = 0; i<game_pixels; i++)
			ws2812b_setpixel(b, 0, 0, true, i);
		ws2812b_update();
		micros(animation_frame_timing);		
	}

	micros(200*1000);

	for (b = brightness+1; b>0; b--) {
		uint8_t i;
		for (i = 0; i<game_pixels; i++)
			ws2812b_setpixel(b-1, 0, 0, true, i);
		ws2812b_update();
		micros(animation_frame_timing);		
	}

	micros(200*1000);

	for (b = 0; b<brightness; b++) {
		uint8_t i;
		for (i = 0; i<game_pixels; i++)
			ws2812b_setpixel(0, b, 0, true, i);
		ws2812b_update();
		micros(animation_frame_timing);		
	}

	micros(200*1000);

	for (b = brightness+1; b>0; b--) {
		uint8_t i;
		for (i = 0; i<game_pixels; i++)
			ws2812b_setpixel(0, b-1, 0, true, i);
		ws2812b_update();
		micros(animation_frame_timing);		
	}

	micros(200*1000);

	for (b = 0; b<brightness; b++) {
		uint8_t i;
		for (i = 0; i<game_pixels; i++)
			ws2812b_setpixel(0, 0, b, true, i);
		ws2812b_update();
		micros(animation_frame_timing);		
	}

	micros(200*1000);

	for (b = brightness+1; b>0; b--) {
		uint8_t i;
		for (i = 0; i<game_pixels; i++)
			ws2812b_setpixel(0, 0, b-1, true, i);
		ws2812b_update();
		micros(animation_frame_timing);		
	}

	micros(200*1000);
}

static void play_win_animation(uint8_t location, uint8_t color) {
    if (location > 59) return;

    uint8_t i;
    uint8_t up = location;
    uint8_t down = location;
    switch (color) {
        case 0:
            ws2812b_setpixel(brightness, 0, 0, true, location);
            break;
        case 1:
            ws2812b_setpixel(0, brightness, 0, true, location);
            break;
        case 2:
            ws2812b_setpixel(0, 0, brightness, true, location);
            break;
        default:
            ws2812b_setpixel(brightness, brightness, brightness, true, location);
            break;
    }
    ws2812b_update();
    micros(1000*10);

    for (i=0; i<game_pixels; i++) {
        if (up < 59) up++;
        if (down > 0) down--;
        switch (color) {
            case 0:
                ws2812b_setpixel(brightness, 0, 0, true, up);
                ws2812b_setpixel(brightness, 0, 0, true, down);
                break;
            case 1:
                ws2812b_setpixel(0, brightness, 0, true, up);
                ws2812b_setpixel(0, brightness, 0, true, down);
                break;
            case 2:
                ws2812b_setpixel(0, 0, brightness, true, up);
                ws2812b_setpixel(0, 0, brightness, true, down);
                break;
            default:
                ws2812b_setpixel(brightness, brightness, brightness, true, up);
                ws2812b_setpixel(brightness, brightness, brightness, true, down);
                break;
        }
        ws2812b_update();
        micros(1000*10);
        if (up == 59 && down == 0) break;
    }
    micros(500*1000);
}

const uint8_t health_leds[3][3] = {    
    { 0, 1, 2 },
    { 4, 5, 6 },
    { 8, 9, 10 }
};

static void show_health() {
    ws2812b_turnoff();
    uint8_t i;
    for (i=0; i<3; i++) {
        uint8_t j;
        if (i+1>player1_health) {
            for (j=0; j<3; j++) 
                ws2812b_setpixel(0, brightness, 0, false, health_leds[i][j]);
        } else {
            for (j=0; j<3; j++) 
                ws2812b_setpixel(0, brightness, 0, true, health_leds[i][j]);
        }
    }

    for (i=0; i<3; i++) {
        uint8_t j;
        if (i+1>player2_health) {
            for (j=0; j<3; j++) 
                ws2812b_setpixel(0, 0, brightness, false, 59-health_leds[i][j]);
        } else {
            for (j=0; j<3; j++) 
                ws2812b_setpixel(0, 0, brightness, true, 59-health_leds[i][j]);
        }
    }

    ws2812b_update();
    micros(500*1000);

    if (player1_lost_round) {
        for (i=0; i<3; i++) {
            ws2812b_enable_pixel(health_leds[player1_health][i]);
        }
        ws2812b_update();
        micros(500*1000);
        for (i=0; i<3; i++) {
            ws2812b_disable_pixel(health_leds[player1_health][i]);
        }
        ws2812b_update();
        micros(500*1000);
        for (i=0; i<3; i++) {
            ws2812b_enable_pixel(health_leds[player1_health][i]);
        }
        ws2812b_update();
        micros(500*1000);
        for (i=0; i<3; i++) {
            ws2812b_disable_pixel(health_leds[player1_health][i]);
        }
        ws2812b_update();
        micros(500*1000);
        for (i=0; i<3; i++) {
            ws2812b_enable_pixel(health_leds[player1_health][i]);
        }
        ws2812b_update();
        micros(500*1000);
        for (i=0; i<3; i++) {
            ws2812b_disable_pixel(health_leds[player1_health][i]);
        }
        ws2812b_update();
        micros(500*1000);
    }

    if (player2_lost_round) {
        for (i=0; i<3; i++) {
            ws2812b_enable_pixel(59-health_leds[player2_health][i]);
        }
        ws2812b_update();
        micros(500*1000);
        for (i=0; i<3; i++) {
            ws2812b_disable_pixel(59-health_leds[player2_health][i]);
        }
        ws2812b_update();
        micros(500*1000);
        for (i=0; i<3; i++) {
            ws2812b_enable_pixel(59-health_leds[player2_health][i]);
        }
        ws2812b_update();
        micros(500*1000);
        for (i=0; i<3; i++) {
            ws2812b_disable_pixel(59-health_leds[player2_health][i]);
        }
        ws2812b_update();
        micros(500*1000);
        for (i=0; i<3; i++) {
            ws2812b_enable_pixel(59-health_leds[player2_health][i]);
        }
        ws2812b_update();
        micros(500*1000);
        for (i=0; i<3; i++) {
            ws2812b_disable_pixel(59-health_leds[player2_health][i]);
        }
        ws2812b_update();
        micros(500*1000);
    }

    ws2812b_update();
    micros(1000*1000);
}

static void next_round(){
    spawn_objects = false;
    remove_objects();
    spawn_objects = true;
    player1_pos = (distance_from_border_start - 1);
    player2_pos = (game_pixels - distance_from_border_start - 1);
    count_till_next_step1 = 10;
    count_till_next_step2 = 10;
    player1_cooldown = true;
    player2_cooldown = true;

    bullet1_shot = false;
    bullet2_shot = false;
    bullet1_move_counter = 0;
    bullet2_move_counter = 0;
}

static void game_reset(){
    game_ended = false;
    side = true;
    next_round();
    player1_health = 3;
    player2_health = 3;
    play_animation();
    micros(1000*1000);
    show_health();
}

void init_game() {
    read_WiiClassic(0);
    micros(100*1000);

    left_joy_neutral = LY >> 1; 
    right_joy_neutral = RX;
    brightness = 0x0F;
    game_reset();
}

static void kill_player1() {
    if (player1_health > 0) player1_health--;
    if (player1_health <= 0) {
        spawn_objects = false;
        play_win_animation(player2_pos, 2);
        game_ended=true;
    } else {
        spawn_objects = false;
        player1_lost_round = true;
        show_health();
        player1_lost_round = false;
        next_round();
    }
}

static void kill_player2() {
    if (player2_health > 0) player2_health--;
    if (player2_health <= 0) {
        spawn_objects = false;
        play_win_animation(player1_pos, 1);
        game_ended=true;
    } else {
        spawn_objects = false;
        player2_lost_round = true;
        show_health();
        player2_lost_round = false;
        next_round();
    }
}

static bool is_position_accessible(uint8_t position) {
    if (position > 59) return false;
    if (position < 0) return false;
    uint8_t i;
    for (i=0; i<game_pixels; i++) {
        if (i == position && objects[i]) return false;
    }
    return true;
}

bool drift1 = true;
static void move_player1() {
    uint8_t speed = (LY >> 1);
    bool neg;
    if (speed < left_joy_neutral) {
        neg = true;
        speed = left_joy_neutral - speed;
    }
    else {
        neg = false;
        speed = speed - left_joy_neutral;
    }

    if (speed > 0 && drift1) {
        drift1 = false;
        return;
    } else if (speed == 0 && !drift1) {
        drift1 = true;
        return;
    }

    if (neg) {
        if ((count_till_next_step1 - speed) < 10) {
            if (player1_pos > 0) {
                count_till_next_step1 = 240;
                if (!is_position_accessible(player1_pos-1)) return;
                player1_pos--;
            }
        } else {
            count_till_next_step1 -= speed;
        }
    } else {
        if ((count_till_next_step1 + speed) > 240) {
            if (player1_pos < 59) {
                count_till_next_step1 = 10;
                if (!is_position_accessible(player1_pos+1)) return;
                player1_pos++;
            }
        } else {
            count_till_next_step1 += speed;
        }
    }
}

bool drift2 = true;
static void move_player2() {
    uint8_t speed = RY;
    bool neg;
    if (speed < right_joy_neutral) {
        neg = true;
        speed = right_joy_neutral - speed;
    }
    else {
        neg = false;
        speed = speed - right_joy_neutral;
    }

    if (speed > 0 && drift2) {
        drift2 = false;
        return;
    } else if (speed == 0 && !drift2) {
        drift2 = true;
        return;
    }

    if (neg) {
        if ((count_till_next_step2 - speed) < 10) {
            if (player2_pos > 0) {
                count_till_next_step2 = 240;
                if (!is_position_accessible(player2_pos-1)) return;
                player2_pos--;
            }
        } else {
            count_till_next_step2 -= speed;
        }
    } else {
        if ((count_till_next_step2 + speed) > 240) {
            if (player2_pos < 59) {
                count_till_next_step2 = 10;
                if (!is_position_accessible(player2_pos+1)) return;
                player2_pos++;
            }
        } else {
            count_till_next_step2 += speed;
        }
    }
}

static void handle_objects() {
    //reset game when pressing home button
    if (!BUTTONS[7]) {
        game_reset();
        micros(10000);
        return;
    }

    //increase brightness when pressing + button
    if (!BUTTONS[6]) {
        if (brightness < 255) brightness++;
    }

    //decrease brightness when pressing - button
    if (!BUTTONS[8]) {
        if (brightness > 0) brightness--;
    }

    // shoot bullet for player 1 when pressing ZL and bullet for player 2 when pressing ZR
    if (!BUTTONS[0]){ // ZR
        if (!bullet2_shot) {
            if (player2_pos > 1) {
                bullet2_shot = true;
                bullet2_pos = player2_pos - 2;
            }
        }
    }
    if (!BUTTONS[1]) { // ZL
        if (!bullet1_shot) {
            if (player1_pos < 58) {
                bullet1_pos = player1_pos + 2;
                bullet1_shot = true;
            }
        }
    }

    //move bullet 1 if it has been shot
    if (bullet1_shot) {
        if (bullet1_move_counter > 255-bullet_speed) {
            bullet1_move_counter = 0;
            if (bullet1_pos < 60-bullet_spacing) bullet1_pos += bullet_spacing;
            else bullet1_pos = 59;
        } else bullet1_move_counter += bullet_speed;
    }

    //move bullet 2 if it has been shot
    if (bullet2_shot) {
        if (bullet2_move_counter > 255-bullet_speed) {
            bullet2_move_counter = 0;
            if (bullet2_pos > bullet_spacing - 1) bullet2_pos -= bullet_spacing;
            else bullet2_pos = 0;
        } else bullet2_move_counter += bullet_speed;
    }

    //keep the bullets within bounds 
    if (bullet1_pos > 58) {
        bullet1_shot = false;
    }
    
    if (bullet2_pos < 1) {
        bullet2_shot = false;
    }

}

void game_tick() {
    count++;
    if (count > 100 * 5) {
        count = 0;
        if (can_objects_spawn()) {
            spawn_object();
        }
    }
    read_WiiClassic(0);
    move_player1();
    move_player2();
    handle_objects();
    if (game_ended) return;
    ws2812b_turnoff();
    ws2812b_setpixel(0, brightness, 0, true, player1_pos);
    ws2812b_setpixel(0, 0, brightness, true, player2_pos);
    ws2812b_setpixel(brightness, 0, 0, bullet1_shot, bullet1_pos);
    ws2812b_setpixel(brightness, 0, 0, bullet2_shot, bullet2_pos);
    uint8_t i;
    for (i = 0; i<game_pixels; i++) {
        if (objects[i]) ws2812b_setpixel(brightness, brightness, brightness, true, i);
    }
    ws2812b_update();
    if ((bullet1_pos == player1_pos && bullet1_shot) || (bullet2_pos == player1_pos && bullet2_shot))
        kill_player1();
    if ((bullet1_pos == player2_pos && bullet1_shot) || (bullet2_pos == player2_pos && bullet2_shot)) 
        kill_player2();
}
