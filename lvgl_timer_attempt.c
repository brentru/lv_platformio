/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "lvgl.h"
#include "app_hal.h"
#include <stdio.h>
#include <unistd.h>


extern lv_font_t turtle2;
#define TURTLE_SYMBOL "\xEF\x9C\xA6"

extern lv_font_t file_code;
#define SYMBOL_CODE "\xEF\x87\x89"

extern lv_font_t wifi_30px;
#define SYMBOL_WIFI "\xEF\x87\xAB"

// Mock credentials
#define AIO_USERNAME "aioUser"
#define AIO_KEY "aioKey"
#define SSID "mySSID"
#define SSID_PASS "SSIDPass"

// TODO: Mock secrets.json file not able to be deserialized
// TODO: Mock a filesystem with AIO credentials
// TODO: Mock a filesystem without AIO credentials
// TODO: Mock a filesystem with WiFi credentials
// TODO: Mock a filesystem without WiFi credentials


void screen2() {
  lv_obj_t * scr2 = lv_obj_create(NULL);

  lv_obj_set_style_bg_color(scr2, lv_color_black(), LV_STATE_DEFAULT);

  static lv_style_t styleText;
  lv_style_init(&styleText);
  lv_style_set_text_color(&styleText, lv_color_white());
  lv_style_set_text_font(&styleText, &lv_font_montserrat_20); 

  // add project label to screen
  lv_obj_t *labelWS = lv_label_create(scr2);
  lv_obj_add_style(labelWS, &styleText, LV_PART_MAIN);
  lv_label_set_text(labelWS, "WS Screen 2");
  lv_obj_align(labelWS, LV_ALIGN_CENTER, 0, 0);

  lv_scr_load(scr2);
}

void cleanup_screen1(lv_timer_t * timer) {
  printf("cleanup_screen1()\n");
}


void screen1() {
  lv_obj_t * scr1 = lv_obj_create(NULL);

  lv_obj_set_style_bg_color(scr1, lv_color_black(), LV_STATE_DEFAULT);

  static lv_style_t styleText;
  lv_style_init(&styleText);
  lv_style_set_text_color(&styleText, lv_color_white());
  lv_style_set_text_font(&styleText, &lv_font_montserrat_20); 

  // add project label to screen
  lv_obj_t *labelWS = lv_label_create(scr1);
  lv_obj_add_style(labelWS, &styleText, LV_PART_MAIN);
  lv_label_set_text(labelWS, "WS Screen 1");
  lv_obj_align(labelWS, LV_ALIGN_CENTER, 0, 0);
  lv_scr_load(scr1);

  lv_obj_del_delayed(labelWS, 2500);
}

void testScreens() {
  printf("Creating screen 1...\n");
  screen1();
  printf("Done! Screen2 time...\n");
  screen2();

}

int main(void)
{
  lv_init();
  hal_setup();

  // Step through the boot sequence
  testScreens();

  // HAL loop
  hal_loop();
}