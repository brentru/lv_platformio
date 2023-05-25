/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "app_hal.h"
#include "lvgl.h"
#include <stdio.h>

/**********************
 *      MACROS
 **********************/
#define SYMBOL_TURTLE "\xEF\x9C\xA6"

/**********************
 *      FONTS
 **********************/
extern lv_font_t turtle_20;



static lv_obj_t * consoleLabel;

#define MAX_TEXT_BUFFER_SZ 215
static char textBuffer[MAX_TEXT_BUFFER_SZ + 1]; // + '\0'

#define DISPLAY_WIDTH 240

int i = 0;

// Adds data to the monitor
// Referenced: https://github.com/lvgl/lv_demos/blob/release/v6/lv_apps/terminal/terminal.c
void monitor_add(const char * txt_in)
{
    size_t txt_len = strlen(txt_in);
    size_t old_len = strlen(textBuffer);

    /*If the data is longer then the terminal ax size show the last part of data*/
    if(txt_len > MAX_TEXT_BUFFER_SZ) {
        txt_in += (txt_len - MAX_TEXT_BUFFER_SZ);
        txt_len = MAX_TEXT_BUFFER_SZ;
        old_len = 0;
    }
    /*If the text become too long 'forget' the oldest lines*/
    else if(old_len + txt_len > MAX_TEXT_BUFFER_SZ) {
        uint16_t new_start;
        for(new_start = 0; new_start < old_len; new_start++) {
            if(textBuffer[new_start] == '\n') {
                /*If there is enough space break*/
                if(new_start >= txt_len) {
                    /*Ignore line breaks*/
                    while(textBuffer[new_start] == '\n' || textBuffer[new_start] == '\r') new_start++;
                    break;
                }
            }
        }

        /* If it wasn't able to make enough space on line breaks
         * simply forget the oldest characters*/
        if(new_start == old_len) {
            new_start = old_len - (MAX_TEXT_BUFFER_SZ - txt_len);
        }
        /*Move the remaining text to the beginning*/
        uint16_t j;
        for(j = new_start; j < old_len; j++) {
            textBuffer[j - new_start] = textBuffer[j];
        }
        old_len = old_len - new_start;
        textBuffer[old_len] = '\0';

    }

    memcpy(&textBuffer[old_len], txt_in, txt_len);
    textBuffer[old_len + txt_len] = '\0';
}

void cb_add_to_console(lv_timer_t * timer) {
  // append to the buffer
  static char txt[340];
  snprintf(txt, 340, "%d - test\n", i);
  monitor_add(txt);
  // set label
  lv_label_set_text_static(consoleLabel, textBuffer);
  
  i++;
}

void load_task() {
  printf("in load_task\n");
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_STATE_DEFAULT);

  // Create a status bar
  lv_obj_t * canvas = lv_canvas_create(lv_scr_act());
  static uint8_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR(240, 25)];
  lv_canvas_set_buffer(canvas, buffer, 240, 25, LV_IMG_CF_TRUE_COLOR);
  lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_COVER);
  lv_draw_rect_dsc_t rect_dsc;
  rect_dsc.bg_color = lv_palette_main(LV_PALETTE_GREY);
  rect_dsc.bg_opa = LV_OPA_COVER;
  lv_draw_rect_dsc_init(&rect_dsc);
  lv_canvas_draw_rect(canvas, 0, 0, 240, 25, &rect_dsc);

  // Add battery icon to status bar
  // TODO: Optional timer to check battery level on some boards
  // Note: FunHouse won't require this and should always be have a full battery displayed
  lv_obj_t * statusbar_icon_bat = lv_label_create(lv_scr_act());
  lv_label_set_text(statusbar_icon_bat, LV_SYMBOL_BATTERY_FULL);
  lv_obj_align(statusbar_icon_bat, LV_ALIGN_TOP_RIGHT, -5, 6);

  // Add WiFi icon to status bar
  // TODO: Timer to check if we are still connected to WiFi levels every 2000ms
  lv_obj_t * statusbar_icon_wifi = lv_label_create(lv_scr_act());
  lv_label_set_text(statusbar_icon_wifi, LV_SYMBOL_WIFI);
  lv_obj_align(statusbar_icon_wifi, LV_ALIGN_TOP_RIGHT, -30, 5);

  // Add Turtle icon to status bar
  lv_obj_t *labelTurtleBar = lv_label_create(lv_scr_act());
  lv_label_set_text(labelTurtleBar, SYMBOL_TURTLE);
  static lv_style_t styleIconTurtle30px;
  lv_style_init(&styleIconTurtle30px);
  lv_style_set_text_color(&styleIconTurtle30px,
                          lv_palette_main(LV_PALETTE_GREEN));
  lv_style_set_text_font(&styleIconTurtle30px, &turtle_20);
  lv_obj_add_style(labelTurtleBar, &styleIconTurtle30px,
                   LV_PART_MAIN);
  lv_obj_align(labelTurtleBar, LV_ALIGN_TOP_LEFT, 5, 5);


  // Add a label to hold console text
  // TODO: Speed this up via https://docs.lvgl.io/8.2/widgets/core/label.html#very-long-texts
  consoleLabel = lv_label_create(lv_scr_act());
  lv_obj_align(consoleLabel, LV_ALIGN_BOTTOM_LEFT, 5, -5);
  // TODO: Test long-mode...
  //lv_label_set_long_mode(consoleLabel, LV_LABEL_LONG_WRAP);
  lv_obj_set_width(consoleLabel, 240);
  static lv_style_t styleConsoleLabel;
  lv_style_init(&styleConsoleLabel);
  lv_style_set_text_color(&styleConsoleLabel, lv_color_white());
  lv_obj_add_style(consoleLabel, &styleConsoleLabel, LV_PART_MAIN);
  lv_label_set_text_static(consoleLabel, textBuffer);
  lv_obj_move_background(consoleLabel);
  lv_timer_t * timer_cb_console = lv_timer_create(cb_add_to_console, 500,  NULL);

}



int main(void) {
  lv_init();
  hal_setup();

  printf("call load_task\n");
  load_task();

  // printf("task handler\n");
  // lv_task_handler();

  printf("going into hal_loop...\n");
  hal_loop();
}