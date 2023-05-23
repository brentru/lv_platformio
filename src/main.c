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
#define SYMBOL_WIFI_30PX "\xEF\x87\xAB"
#define SYMBOL_CLOUD "\xEF\x83\x82"

/**********************
 *      FONTS
 **********************/
LV_FONT_DECLARE(wifi_30px);
LV_FONT_DECLARE(cloud_30px);

void cb_check_wifi_connection(lv_timer_t * timer) {
  bool stillConnected = true; // TODO: This will be replaced w/a call to networkStatus()

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
  lv_draw_rect_dsc_init(&rect_dsc);
  rect_dsc.bg_color = lv_palette_main(LV_PALETTE_GREY);
  lv_canvas_draw_rect(canvas, 0, 0, 240, 25, &rect_dsc);

  // TODO
  // Add an icon showing wiFi RSSI levels
  // Timer to check if we are still connected to WiFi levels every 2000ms
  lv_timer_t * timer = lv_timer_create(cb_check_wifi_connection, 2000, NULL);
  lv_obj_t * statusbar_icon_wifi = lv_label_create(lv_scr_act());
  lv_label_set_text(statusbar_icon_wifi, SYMBOL_WIFI_30PX);
  lv_obj_align(statusbar_icon_wifi, LV_ALIGN_TOP_RIGHT, -5, 5);

  // Add cloud
  // TODO: The cloud is too large, try a 20px version instead
/*   lv_obj_t * labelCloudBar = lv_label_create(lv_scr_act());
  lv_label_set_text(labelCloudBar, SYMBOL_CLOUD);
  static lv_style_t styleIconCloud;
  lv_style_init(&styleIconCloud);
  lv_style_set_text_color(&styleIconCloud, lv_color_black());
  lv_style_set_text_font(&styleIconCloud, &cloud_30px);
  lv_obj_add_style(labelCloudBar, &styleIconCloud, LV_PART_MAIN);
  lv_obj_align(labelCloudBar, LV_ALIGN_TOP_RIGHT, -25, 0); */


  // Add a label to hold console text
  // TODO: Speed this up via https://docs.lvgl.io/8.2/widgets/core/label.html#very-long-texts
  lv_obj_t * labelConsoleText = lv_label_create(lv_scr_act());
  lv_label_set_long_mode(labelConsoleText, LV_LABEL_LONG_WRAP);
  lv_obj_align(labelConsoleText, LV_ALIGN_BOTTOM_LEFT, 5, 0);  
  static lv_style_t styleConsoleText;
  lv_style_init(&styleConsoleText);
  lv_style_set_text_color(&styleConsoleText, lv_color_white());
  lv_obj_add_style(labelConsoleText, &styleConsoleText, LV_PART_MAIN);
  lv_label_set_text(labelConsoleText, "hello"); // TODO: may want to delete and only use when required
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