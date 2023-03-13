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

void loadBootScreen(lv_timer_t * timer) {
  // delete the splash screen
  lv_obj_del(timer->user_data);

  // create the boot screen, TODO: maybe do this in another function?
  lv_obj_t * scr2 = lv_obj_create(NULL);
  lv_scr_load(scr2);

}

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

  // transition to loadBootScreen after 2500ms delay
  lv_timer_t * timer = lv_timer_create(loadBootScreen, 2500,  &scrSplash);
}

void testScreens() {

  createSplashScreen();

}

int main(void)
{
  lv_init();
  hal_setup();

  // Step through the boot sequence
  testScreens();

  // Mock checking provisioning status
  // checkCredentials();

  // HAL loop
  hal_loop();
}