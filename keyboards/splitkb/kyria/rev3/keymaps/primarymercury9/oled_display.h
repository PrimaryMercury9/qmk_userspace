#pragma once

#include "quantum.h"
#include "layers.h"
#include "qmk-vim/src/vim.h"
#include "qmk-vim/src/modes.h" //required to display which vim mode is active on OLED

void oled_render_vim_mode(void);
void oled_render_status(void);
void oled_render_wpm(void);
void oled_render_jiggling(void);
void oled_render_leader(void);
void oled_render_led_hue(void);
void oled_render_os_logo(void);
bool oled_task_user(void);

oled_rotation_t oled_init_user(oled_rotation_t rotation);
