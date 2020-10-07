#ifndef LVGL_SDL_H
#define LVGL_SDL_H

#include "monitor.h"
#include "mouse.h"

typedef enum {
    LVGL_SDL_GESTURE_NONE            = 0x00,
    LVGL_SDL_GESTURE_SLIDE_DOWN      = 0x01,
    LVGL_SDL_GESTURE_SLIDE_UP        = 0x02,
    LVGL_SDL_GESTURE_SLIDE_LEFT      = 0x03,
    LVGL_SDL_GESTURE_SLIDE_RIGHT     = 0x04,
} lvgl_sdl_gesture_t;

int lvgl_sdl_simulator(void);
void lvgl_sdl_memory_monitor(int ms);

void lvgl_sdl_monitor_init(const char * title);
void lvgl_sdl_monitor_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

void lvgl_sdl_mouse_init(void);
bool lvgl_sdl_mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
lvgl_sdl_gesture_t lvgl_sdl_detect_gesture(lv_indev_data_t * data);

#endif
