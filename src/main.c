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

extern lv_font_t turtle2;
#define SYMBOL_TURTLE "\xEF\x9C\xA6"

extern lv_font_t file_code;
#define SYMBOL_CODE "\xEF\x87\x89"

extern lv_font_t wifi_30px;
#define SYMBOL_WIFI "\xEF\x87\xAB"

extern lv_font_t turtle_30px;
#define SYMBOL_TURTLE30PX "\xEF\x9C\xA6"

extern lv_font_t cloud_30px;
#define SYMBOL_CLOUD "\xEF\x83\x82"

extern lv_font_t circle_30px;
#define SYMBOL_CHECKMARK "\xEF\x81\x98"

extern lv_font_t errorTriangle;
#define SYMBOL_ERROR_TRIANGLE "\xEF\x81\xB1"

LV_IMG_DECLARE(ws_icon_100px);
LV_IMG_DECLARE(ws_logo_200px);

// Error strings
#define ERR_NO_JSON_HEADER "Secrets.json file not found!"
#define ERR_NO_JSON_INSTRUCTIONS                                               \
  "1. Visit adafru.it/123456 to generate a settings.json file.\n2.Drag and "   \
  "drop the secrets.json file to the WIPPER drive.\n3. Press RESET on your "   \
  "board."


lv_timer_t* splashTask;
lv_obj_t *splashImg;

lv_obj_t *labelIconFile, *labelWiFi;

// Styles used by the loading screen, need to be global or static
static lv_style_t styleIconFile, styleIconWiFi, styleIconTurtle30px, styleIconCloud, styleIconCheckmark;

// Icon bar offset and spacing
const lv_coord_t iconBarXStart = 28;
const lv_coord_t iconBarYOffset = -45; // gives us room for text, too
const int iconBarXSpaces = 33;         // +10 exactly between icons

void make_wifi_green(lv_timer_t * timer) {
    lv_style_set_text_color(&styleIconWiFi, lv_palette_main(LV_PALETTE_GREEN));
    lv_obj_add_style(labelWiFi, &styleIconWiFi, LV_PART_MAIN);
    lv_timer_del(timer);
}

void make_file_green(lv_timer_t * timer) {
    lv_style_set_text_color(&styleIconFile, lv_palette_main(LV_PALETTE_GREEN));
    lv_obj_add_style(labelIconFile, &styleIconFile, LV_PART_MAIN);
    lv_timer_del(timer);

    lv_timer_create(make_wifi_green, 1000, NULL);
}

void load_task(lv_timer_t * timer) {
  // remove the splash screen (TODO: do this in another func.)
  lv_obj_del(splashImg);

  // adding loading screen image
  lv_obj_t *icon = lv_img_create(lv_scr_act());
  lv_img_set_src(icon, &ws_icon_100px);
  lv_obj_align(icon, LV_ALIGN_TOP_MID, 0, 5);

  // add symbol_code (30px) to represent settings.json
  labelIconFile = lv_label_create(lv_scr_act());
  lv_label_set_text(labelIconFile, SYMBOL_CODE);
  // formatting
  lv_style_init(&styleIconFile);
  lv_style_set_text_color(&styleIconFile, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconFile, &file_code);
  lv_obj_add_style(labelIconFile, &styleIconFile, LV_PART_MAIN);
  lv_obj_align(labelIconFile, LV_ALIGN_BOTTOM_LEFT, iconBarXStart,
               iconBarYOffset);

  // add symbol_wifi (30px) to represent wifi connect
  labelWiFi = lv_label_create(lv_scr_act());
  lv_label_set_text(labelWiFi, SYMBOL_WIFI);
  lv_style_init(&styleIconWiFi);
  lv_style_set_text_color(&styleIconWiFi, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconWiFi, &wifi_30px);
  lv_obj_add_style(labelWiFi, &styleIconWiFi, LV_PART_MAIN);
  lv_obj_align(labelWiFi, LV_ALIGN_BOTTOM_LEFT,
               iconBarXStart + (iconBarXSpaces * 1), iconBarYOffset);

  // Add symbol turtle 30px
  lv_obj_t *labelTurtleBar = lv_label_create(lv_scr_act());
  lv_label_set_text(labelTurtleBar, SYMBOL_TURTLE30PX);

  lv_style_init(&styleIconTurtle30px);
  lv_style_set_text_color(&styleIconTurtle30px,
                          lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconTurtle30px, &turtle_30px);
  lv_obj_add_style(labelTurtleBar, &styleIconTurtle30px,
                   LV_PART_MAIN); // 28+(33*2) = 94
  lv_obj_align(labelTurtleBar, LV_ALIGN_BOTTOM_LEFT, 106, iconBarYOffset);

  // Add cloud
  lv_obj_t *labelCloudBar = lv_label_create(lv_scr_act());
  lv_label_set_text(labelCloudBar, SYMBOL_CLOUD);

  lv_style_init(&styleIconCloud);
  lv_style_set_text_color(&styleIconCloud, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconCloud, &cloud_30px);
  lv_obj_add_style(labelCloudBar, &styleIconCloud, LV_PART_MAIN);
  lv_obj_align(labelCloudBar, LV_ALIGN_BOTTOM_LEFT, iconBarXStart + (106 + 13),
               iconBarYOffset);

  // Add circle checkmark
  lv_obj_t *labelCircleBar = lv_label_create(lv_scr_act());
  lv_label_set_text(labelCircleBar, SYMBOL_CHECKMARK);

  lv_style_init(&styleIconCheckmark);
  lv_style_set_text_color(&styleIconCheckmark,
                          lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconCheckmark, &circle_30px);
  lv_obj_add_style(labelCircleBar, &styleIconCheckmark, LV_PART_MAIN);
  lv_obj_align(labelCircleBar, LV_ALIGN_BOTTOM_LEFT, 160 + 33, iconBarYOffset);

  lv_timer_del(timer);

  // simulate event loop
  lv_timer_create(make_file_green, 2500, NULL);
}

void splash_task(lv_timer_t * timer) {
  // create and load splash screen 
  
  // create and center the full logo (200px
  splashImg = lv_img_create(lv_scr_act());
  lv_img_set_src(splashImg, &ws_logo_200px);
  lv_obj_align(splashImg, LV_ALIGN_CENTER, 0, 0);

  lv_timer_del(timer); // one-shot task, delete

  // add load_task to timer handler
  lv_timer_create(load_task, 2500, NULL);
}


int main(void) {
  lv_init();
  hal_setup();

  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_STATE_DEFAULT);
  
  splashTask = lv_timer_create(splash_task, 0, NULL);

  // HAL loop
  hal_loop();
}