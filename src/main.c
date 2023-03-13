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


void createSplashScreen(lv_obj_t * scr) {
  lv_obj_set_style_bg_color(scr, lv_color_black(), LV_STATE_DEFAULT);
  // Generate a splash screen
  // TODO: Waiting for bruce, using splash text instead
  static lv_style_t styleText;
  lv_style_init(&styleText);
  lv_style_set_text_color(&styleText, lv_color_white());
  lv_style_set_text_font(&styleText, &lv_font_montserrat_20); 
  // add project label to screen
  lv_obj_t *labelWS = lv_label_create(scr);
  lv_obj_add_style(labelWS, &styleText, LV_PART_MAIN);
  lv_label_set_text(labelWS, "WipperSnapper");
  lv_obj_align(labelWS, LV_ALIGN_CENTER, 0, 0);
  // load splash screen
  lv_scr_load(scr);
  // transition to loadBootScreen after 1sec delay
  lv_obj_del_delayed(labelWS, 1000);
  printf("exit splash screen\n");
}

void buildScreenLoad() {
  printf("buildScreenLoad()\n");
  lv_obj_t * scrLoad = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(scrLoad, lv_color_black(), LV_STATE_DEFAULT);

  // TODO: Add logo
  // Add logo text (TODO: Remove when we have bruce logo)
  static lv_style_t styleText;
  lv_style_init(&styleText);
  lv_style_set_text_color(&styleText, lv_color_white());
  lv_style_set_text_font(&styleText, &lv_font_montserrat_20); 

  // add project label to screen
  lv_obj_t *labelWS = lv_label_create(scrLoad);
  lv_obj_add_style(labelWS, &styleText, LV_PART_MAIN);
  lv_label_set_text(labelWS, "WipperSnapper");
  lv_obj_align(labelWS, LV_ALIGN_CENTER, 0, 0);
  
  // Add new style for grayed-out icons
  static lv_style_t styleIconsGray;
  lv_style_init(&styleIconsGray);
  lv_style_set_text_color(&styleIconsGray, lv_color_hex(0x4D4A4A));

  lv_obj_t *labelFile = lv_label_create(scrLoad);
  lv_label_set_text(labelFile, LV_SYMBOL_FILE);
  lv_obj_align(labelFile, LV_ALIGN_BOTTOM_LEFT, 0, 0);

  lv_scr_load(scrLoad);

}

void testScreens() {
  printf("Creating Splash Screen...");
  lv_obj_t * scrSplash = lv_obj_create(NULL);
  createSplashScreen(scrSplash);

  
  printf("Generate Load Screen");
  buildScreenLoad();
  // TODO: call generate load
  // TODO: Delete splash screen after load screen is active?

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