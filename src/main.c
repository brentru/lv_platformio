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

extern lv_font_t circle_30px;
#define SYMBOL_CHECKMARK "\xEF\x81\x98"

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

void setBackgroundBlack(lv_obj_t *screen) {
  lv_obj_set_style_bg_color(screen, lv_color_black(), LV_STATE_DEFAULT);
}

// Styles used by the loading screen, need to be global or static
static lv_style_t styleIconFile, styleIconWiFi, styleIconTurtle30px, styleIconCloud, styleIconCheckmark;

void buildScreenLoad() {
  lv_obj_t * scrLoad = lv_obj_create(NULL);

  setBackgroundBlack(scrLoad);

  // TODO: This should be replaced by Image/Bruce's logo
  // add project label to screen
  lv_obj_t *labelWS = lv_label_create(scrLoad);
  lv_label_set_text(labelWS, "WipperSnapper");

  static lv_style_t styleText;
  lv_style_init(&styleText);
  lv_style_set_text_color(&styleText, lv_color_white());
  lv_style_set_text_font(&styleText, &lv_font_montserrat_20); 
  lv_obj_add_style(labelWS, &styleText, LV_PART_MAIN);
  lv_obj_align(labelWS, LV_ALIGN_CENTER, 0, 0);

  // Icon bar offset and spacing
  lv_coord_t iconBarXStart = 28;
  lv_coord_t iconBarYOffset = -66;
  int iconBarXSpaces = 33; // +10 exactly between icons

  // add symbol_code (30px) to represent settings.json
  lv_obj_t *labelIconFile = lv_label_create(scrLoad);
  lv_label_set_text(labelIconFile, SYMBOL_CODE);
  // formatting
  lv_style_init(&styleIconFile);
  lv_style_set_text_color(&styleIconFile, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconFile, &file_code);   
  lv_obj_add_style(labelIconFile, &styleIconFile, LV_PART_MAIN);
  lv_obj_align(labelIconFile, LV_ALIGN_BOTTOM_LEFT, iconBarXStart, iconBarYOffset);


  // add symbol_wifi (30px) to represent wifi connect
  lv_obj_t *labelWiFi = lv_label_create(scrLoad);
  lv_label_set_text(labelWiFi, SYMBOL_WIFI);
  lv_style_init(&styleIconWiFi);
  lv_style_set_text_color(&styleIconWiFi, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconWiFi, &wifi_30px); 
  lv_obj_add_style(labelWiFi, &styleIconWiFi, LV_PART_MAIN);
  lv_obj_align(labelWiFi, LV_ALIGN_BOTTOM_LEFT, iconBarXStart+(iconBarXSpaces*1), iconBarYOffset);

  // Add symbol turtle 30px
  lv_obj_t *labelTurtleBar = lv_label_create(scrLoad);
  lv_label_set_text(labelTurtleBar, SYMBOL_TURTLE30PX);

  lv_style_init(&styleIconTurtle30px);
  lv_style_set_text_color(&styleIconTurtle30px, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconTurtle30px, &turtle_30px); 
  lv_obj_add_style(labelTurtleBar, &styleIconTurtle30px, LV_PART_MAIN); //28+(33*2) = 94
  lv_obj_align(labelTurtleBar, LV_ALIGN_BOTTOM_LEFT, 106, iconBarYOffset);

  // Add cloud
  lv_obj_t *labelCloudBar = lv_label_create(scrLoad);
  lv_label_set_text(labelCloudBar, SYMBOL_CLOUD);

  lv_style_init(&styleIconCloud);
  lv_style_set_text_color(&styleIconCloud, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconCloud, &cloud_30px); 
  lv_obj_add_style(labelCloudBar, &styleIconCloud, LV_PART_MAIN);
  lv_obj_align(labelCloudBar, LV_ALIGN_BOTTOM_LEFT, iconBarXStart+(106+13), iconBarYOffset);

  // Add circle checkmark
  lv_obj_t *labelCircleBar = lv_label_create(scrLoad);
  lv_label_set_text(labelCircleBar, SYMBOL_CHECKMARK);

  lv_style_init(&styleIconCheckmark);
  lv_style_set_text_color(&styleIconCheckmark, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconCheckmark, &circle_30px); 
  lv_obj_add_style(labelCircleBar, &styleIconCheckmark, LV_PART_MAIN);
  lv_obj_align(labelCircleBar, LV_ALIGN_BOTTOM_LEFT, 160+33, iconBarYOffset);

  lv_scr_load(scrLoad);
}

// Changes a symbol's color to the "task complete" color
void setIconComplete(lv_style_t *iconStyle) {
  lv_style_set_text_color(iconStyle, lv_palette_main(LV_PALETTE_GREEN));
}

// Clear all properties from the icon bar styles and free all allocated memories
void resetIconBarStyles() {
  lv_style_reset(&styleIconFile);
  lv_style_reset(&styleIconWiFi);
  lv_style_reset(&styleIconTurtle30px);
  lv_style_reset(&styleIconCloud);
  lv_style_reset(&styleIconCheckmark);
}

void testScreens() {
//  printf("Creating Splash Screen...\n");
//  lv_obj_t * scrSplash = lv_obj_create(NULL);
//  createSplashScreen(scrSplash);

  printf("Building Load Screen...\n");
  buildScreenLoad();

  // Can pass in each icon style to transform it as the loading screen
  // progresses
  setIconComplete(&styleIconFile);
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