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
  //lv_obj_del_delayed(labelWS, 1500);
  lv_obj_del_delayed(labelWS, 5000);

  printf("exit splash screen\n");
}

void buildScreenLoad() {
  lv_obj_t * scrLoad = lv_obj_create(NULL);

  lv_obj_set_style_bg_color(scrLoad, lv_color_black(), LV_STATE_DEFAULT);

  static lv_style_t styleText;
  lv_style_init(&styleText);
  lv_style_set_text_color(&styleText, lv_color_white());
  lv_style_set_text_font(&styleText, &lv_font_montserrat_20); 

  // add project label to screen
  lv_obj_t *labelWS = lv_label_create(scrLoad);
  lv_obj_add_style(labelWS, &styleText, LV_PART_MAIN);
  lv_label_set_text(labelWS, "WipperSnapper");
  lv_obj_align(labelWS, LV_ALIGN_CENTER, 0, 0);

  // Icon bar
  lv_coord_t iconBarXStart = 28;
  lv_coord_t iconBarYOffset = -66;
  int iconBarXSpaces = 40; // +40 between icons

  // add symbol_code (30px) to represent settings.json
  // TODO :see how to inline define a style?
  static lv_style_t styleIcon;
  lv_style_init(&styleIcon);
  lv_style_set_text_color(&styleIcon, lv_palette_main(LV_PALETTE_GREY));

  lv_obj_t *labelIconFile = lv_label_create(scrLoad);
  lv_style_set_text_font(&styleIcon, &file_code); 
  lv_label_set_text(labelIconFile, SYMBOL_CODE);
  lv_obj_add_style(labelIconFile, &styleIcon, LV_PART_MAIN);
  lv_obj_align(labelIconFile, LV_ALIGN_BOTTOM_LEFT, iconBarXStart, iconBarYOffset);
  lv_scr_load(scrLoad);


  // add symbol_wifi (30px) to represent wifi connect
  static lv_style_t styleIconWiFi;
  lv_style_init(&styleIconWiFi);
  lv_style_set_text_color(&styleIconWiFi, lv_palette_main(LV_PALETTE_GREY));
  lv_obj_t *labelWiFi = lv_label_create(scrLoad);
  lv_style_set_text_font(&styleIconWiFi, &wifi_30px); 
  lv_label_set_text(labelWiFi, SYMBOL_WIFI);
  lv_obj_add_style(labelWiFi, &styleIconWiFi, LV_PART_MAIN);
  lv_obj_align(labelWiFi, LV_ALIGN_BOTTOM_LEFT, iconBarXStart+iconBarXSpaces, iconBarYOffset);

  // Add symbol turtle 30px
  static lv_style_t styleIconTurtle30;
  lv_style_init(&styleIconTurtle30);
  lv_style_set_text_color(&styleIconTurtle30, lv_palette_main(LV_PALETTE_GREY));
  lv_obj_t *labelTurtleBar = lv_label_create(scrLoad);
  lv_style_set_text_font(&styleIconTurtle30, &turtle_30px); 
  lv_label_set_text(labelTurtleBar, SYMBOL_TURTLE30PX);
  lv_obj_add_style(labelTurtleBar, &styleIconTurtle30, LV_PART_MAIN);
  lv_obj_align(labelTurtleBar, LV_ALIGN_BOTTOM_LEFT, iconBarXStart+(iconBarXSpaces*2), iconBarYOffset);

  // Add cloud
  static lv_style_t styleIconCloud;
  lv_style_init(&styleIconCloud);
  lv_style_set_text_color(&styleIconCloud, lv_palette_main(LV_PALETTE_GREY));
  lv_obj_t *labelCloudBar = lv_label_create(scrLoad);
  lv_style_set_text_font(&styleIconCloud, &cloud_30px); 
  lv_label_set_text(labelCloudBar, SYMBOL_CLOUD);
  lv_obj_add_style(labelCloudBar, &styleIconCloud, LV_PART_MAIN);
  lv_obj_align(labelCloudBar, LV_ALIGN_BOTTOM_LEFT, iconBarXStart+(iconBarXSpaces*3), iconBarYOffset);


  // TODO: Move fonts into folder!

  // TODO: add symbol circle-check 30px

  lv_scr_load(scrLoad);

}

void testScreens() {
  printf("Creating Splash Screen...\n");
  lv_obj_t * scrSplash = lv_obj_create(NULL);
  createSplashScreen(scrSplash);

  //lv_obj_t * scrLoad = lv_obj_create(NULL);
  // maybe we are having issues bc we dont call timer handler/lv_task_handler
  printf("Building Load Screen...\n");
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