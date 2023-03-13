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

//extern lv_font_t turtle;
extern lv_font_t turtle2;
#define TURTLE_SYMBOL "\xEF\x9C\xA6"

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


void createSplashScreen() {
  // Create new screen
  lv_obj_t * scrSplash = lv_obj_create(NULL);

  lv_obj_set_style_bg_color(scrSplash, lv_color_black(), LV_STATE_DEFAULT);
  // Generate a splash screen
  // TODO: Waiting for bruce, using splash text instead
  static lv_style_t styleText;
  lv_style_init(&styleText);
  lv_style_set_text_color(&styleText, lv_color_white());
  lv_style_set_text_font(&styleText, &lv_font_montserrat_20); 
  // add project label to screen
  lv_obj_t *labelWS = lv_label_create(scrSplash);
  lv_obj_add_style(labelWS, &styleText, LV_PART_MAIN);
  lv_label_set_text(labelWS, "WipperSnapper");
  lv_obj_align(labelWS, LV_ALIGN_CENTER, 0, 0);
  // load splash screen
  lv_scr_load(scrSplash);
  // transition to loadBootScreen after 1sec delay

  // TODO: Simulator hardfaults with lv_timer callbacks, this will need to be
  // set up on-hardware instead
  //lv_timer_t * timer = lv_timer_create(cleanSplashScreen, 2500,  &scrSplash);
}

void testScreens() {
  printf("Creating Splash Screen...");
  // TODO: Simulator hardfaults with lv_timer callbacks, this will need to be
  // set up on-hardware using delay() instead of timer cb
  // createSplashScreen();
  printf("Generate Load Screen");


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