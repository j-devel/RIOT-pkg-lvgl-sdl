#include "lvgl_sdl.h"

int main_simulator(int argc, char **argv);
void memory_monitor(lv_task_t *param);


int lvgl_sdl_simulator(void) {
    return main_simulator(0, NULL);
}

void lvgl_sdl_memory_monitor(int ms) {
    lv_task_create(memory_monitor, ms, LV_TASK_PRIO_MID, NULL);
}

void lvgl_sdl_monitor_init(const char * title) {
    monitor_init(title);
}
void lvgl_sdl_monitor_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {
    monitor_flush(disp_drv, area, color_p);
}

void lvgl_sdl_mouse_init(void) {
    mouse_init();
}
bool lvgl_sdl_mouse_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data) {
    bool tf = mouse_read(indev_drv, data);
    // printf("@@ lvgl_sdl_mouse_read(): %u:%u\n", data->point.x, data->point.y);
    return tf;
}

static int16_t last_x = 0;
static int16_t last_y = 0;
static lv_indev_state_t last_state = LV_INDEV_STATE_REL;

lvgl_sdl_gesture_t lvgl_sdl_detect_gesture(lv_indev_data_t * data) {
    int16_t curr_x = data->point.x;
    int16_t curr_y = data->point.y;
    lv_indev_state_t curr_state = data->state;

    int16_t dx = curr_x - last_x;
    int16_t dy = curr_y - last_y;
    bool ds = last_state == LV_INDEV_STATE_PR &&
        curr_state == LV_INDEV_STATE_REL;
    int16_t thresh = 4;

    lvgl_sdl_gesture_t gesture = LVGL_SDL_GESTURE_NONE;
    if (ds) {
        if (dy < -thresh) {
            gesture = LVGL_SDL_GESTURE_SLIDE_UP;
        } else if (dy > thresh) {
            gesture = LVGL_SDL_GESTURE_SLIDE_DOWN;
        } else if (dx < -thresh) {
            gesture = LVGL_SDL_GESTURE_SLIDE_LEFT;
        } else if (dx > thresh) {
            gesture = LVGL_SDL_GESTURE_SLIDE_RIGHT;
        }
    }

    last_x = curr_x;
    last_y = curr_y;
    last_state = curr_state;
    return gesture;
}
