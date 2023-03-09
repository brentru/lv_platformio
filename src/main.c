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
// Function to check if provisioning (FS or Web-based) was successful
void checkCredentials() {
  // TODO: this should be implemented with ArduinoJSON
  // error check against default values [ArduinoJSON, 3.3.3]
/*   if (io_username == nullptr) {
    WS_DEBUG_PRINTLN("ERROR: io_username not set!");
    fsHalt();
  } */
}

// Dynamically create and load a new status bar, provided a screen
void createStatusbar(struct _lv_obj_t *screen) {
  // use a black background
  lv_obj_set_style_bg_color(screen, lv_color_black(), LV_STATE_DEFAULT);

  // turtle font label
  lv_obj_t *label = lv_label_create(screen);
  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_text_font(&style, &turtle2);
  lv_style_set_text_color(&style, lv_color_white());
  lv_obj_add_style(label, &style, LV_PART_MAIN);
  // set turtle font label
  lv_label_set_text(label, TURTLE_SYMBOL);
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, 5, 5);

  
  static lv_style_t style2;
  lv_style_init(&style2);
  lv_style_set_text_color(&style2, lv_color_white());
  // Battery Icon
  lv_obj_t *labelBattery = lv_label_create(screen);
  lv_obj_add_style(labelBattery, &style2, LV_PART_MAIN);
  lv_label_set_text(labelBattery, LV_SYMBOL_BATTERY_FULL);
  lv_obj_align(labelBattery, LV_ALIGN_TOP_RIGHT, 0, 0);
  // WiFi Icon

  // load screen
  lv_scr_load(screen);
}

void testScreens() {
  // Create new screen
  lv_obj_t * scr1 = lv_obj_create(NULL);
  // Create and append status bar onto screen
  createStatusbar(scr1);
  // Display the splash icon
  // TODO: Waiting for bruce, using splash text instead

  lv_obj_t *labelWS = lv_label_create(scr1);
  static lv_style_t styleText;
  lv_style_init(&styleText);
  lv_style_set_text_color(&styleText, lv_color_white());

  // This is casuing an issue, why?
  lv_style_set_text_font(&styleText, &lv_font_montserrat_20); 


  lv_obj_add_style(labelWS, &styleText, LV_PART_MAIN);


  lv_label_set_text(labelWS, "WipperSnapper");
  lv_obj_align(labelWS, LV_ALIGN_CENTER, 0, 0);

}

int main(void)
{
  lv_init();
  hal_setup();

  // TODO: Splash

  // TODO: Add function within actual LVGL glue to
  // read the display config & settings from display.json file

  //createStatusbar();
  testScreens();

  // Mock checking provisioning status
  // checkCredentials();

  // HAL loop
  hal_loop();
}