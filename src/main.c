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

void createSplashScreen(lv_obj_t *scr) {
  lv_obj_set_style_bg_color(scr, lv_color_black(), LV_STATE_DEFAULT);

  // create and center the full logo (200px)
  lv_obj_t *icon = lv_img_create(scr);
  lv_img_set_src(icon, &ws_logo_200px);
  lv_obj_align(icon, LV_ALIGN_CENTER, 0, 0);
}

void setBackgroundBlack(lv_obj_t *screen) {
  lv_obj_set_style_bg_color(screen, lv_color_black(), LV_STATE_DEFAULT);
}

// Styles used by the loading screen, need to be global or static
static lv_style_t styleIconFile, styleIconWiFi, styleIconTurtle30px,
    styleIconCloud, styleIconCheckmark;

void buildScreenLoad(lv_obj_t *scr) {

  lv_obj_set_style_bg_color(scr, lv_color_black(), LV_STATE_DEFAULT);

  lv_obj_t *icon = lv_img_create(scr);
  lv_img_set_src(icon, &ws_icon_100px);
  lv_obj_align(icon, LV_ALIGN_TOP_MID, 0, 5);

  // Icon bar offset and spacing
  const lv_coord_t iconBarXStart = 28;
  const lv_coord_t iconBarYOffset = -45; // gives us room for text, too
  const int iconBarXSpaces = 33;         // +10 exactly between icons

  // add symbol_code (30px) to represent settings.json
  lv_obj_t *labelIconFile = lv_label_create(scr);
  lv_label_set_text(labelIconFile, SYMBOL_CODE);
  // formatting
  lv_style_init(&styleIconFile);
  lv_style_set_text_color(&styleIconFile, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconFile, &file_code);
  lv_obj_add_style(labelIconFile, &styleIconFile, LV_PART_MAIN);
  lv_obj_align(labelIconFile, LV_ALIGN_BOTTOM_LEFT, iconBarXStart,
               iconBarYOffset);

  // add symbol_wifi (30px) to represent wifi connect
  lv_obj_t *labelWiFi = lv_label_create(scr);
  lv_label_set_text(labelWiFi, SYMBOL_WIFI);
  lv_style_init(&styleIconWiFi);
  lv_style_set_text_color(&styleIconWiFi, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconWiFi, &wifi_30px);
  lv_obj_add_style(labelWiFi, &styleIconWiFi, LV_PART_MAIN);
  lv_obj_align(labelWiFi, LV_ALIGN_BOTTOM_LEFT,
               iconBarXStart + (iconBarXSpaces * 1), iconBarYOffset);

  // Add symbol turtle 30px
  lv_obj_t *labelTurtleBar = lv_label_create(scr);
  lv_label_set_text(labelTurtleBar, SYMBOL_TURTLE30PX);

  lv_style_init(&styleIconTurtle30px);
  lv_style_set_text_color(&styleIconTurtle30px,
                          lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconTurtle30px, &turtle_30px);
  lv_obj_add_style(labelTurtleBar, &styleIconTurtle30px,
                   LV_PART_MAIN); // 28+(33*2) = 94
  lv_obj_align(labelTurtleBar, LV_ALIGN_BOTTOM_LEFT, 106, iconBarYOffset);

  // Add cloud
  lv_obj_t *labelCloudBar = lv_label_create(scr);
  lv_label_set_text(labelCloudBar, SYMBOL_CLOUD);

  lv_style_init(&styleIconCloud);
  lv_style_set_text_color(&styleIconCloud, lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconCloud, &cloud_30px);
  lv_obj_add_style(labelCloudBar, &styleIconCloud, LV_PART_MAIN);
  lv_obj_align(labelCloudBar, LV_ALIGN_BOTTOM_LEFT, iconBarXStart + (106 + 13),
               iconBarYOffset);

  // Add circle checkmark
  lv_obj_t *labelCircleBar = lv_label_create(scr);
  lv_label_set_text(labelCircleBar, SYMBOL_CHECKMARK);

  lv_style_init(&styleIconCheckmark);
  lv_style_set_text_color(&styleIconCheckmark,
                          lv_palette_main(LV_PALETTE_GREY));
  lv_style_set_text_font(&styleIconCheckmark, &circle_30px);
  lv_obj_add_style(labelCircleBar, &styleIconCheckmark, LV_PART_MAIN);
  lv_obj_align(labelCircleBar, LV_ALIGN_BOTTOM_LEFT, 160 + 33, iconBarYOffset);
}

// Clear all properties from the icon bar styles and free all allocated memories
void resetIconBarStyles() {
  lv_style_reset(&styleIconFile);
  lv_style_reset(&styleIconWiFi);
  lv_style_reset(&styleIconTurtle30px);
  lv_style_reset(&styleIconCloud);
  lv_style_reset(&styleIconCheckmark);
}

// Changes a symbol's color to the "task complete" color
void setIconComplete(lv_style_t *iconStyle) {
  lv_style_set_text_color(iconStyle, lv_palette_main(LV_PALETTE_GREEN));
}

// TODO: Can we make this type of thing reusable whenever we need to set up an
// error?
lv_obj_t *buildScreenError(char *errorHeader, char *errorInstructions) {
  lv_obj_t *scrError = lv_obj_create(NULL);
  setBackgroundBlack(scrError);

  // Add circle checkmark
  // TODO: Allow other icons to be set within this function
  lv_obj_t *labelErrorTriangle = lv_label_create(scrError);
  lv_label_set_text(labelErrorTriangle, SYMBOL_ERROR_TRIANGLE);

  static lv_style_t styleErrorTriangle;
  lv_style_init(&styleErrorTriangle);
  lv_style_set_text_color(&styleErrorTriangle, lv_color_white());
  lv_style_set_text_font(&styleErrorTriangle, &errorTriangle);
  lv_obj_add_style(labelErrorTriangle, &styleErrorTriangle, LV_PART_MAIN);
  lv_obj_align(labelErrorTriangle, LV_ALIGN_TOP_MID, 0, 30);

  // Label (error heading)
  lv_obj_t *labelErrorHeader = lv_label_create(scrError);
  lv_label_set_text(labelErrorHeader, errorHeader);

  static lv_style_t styleTextBig;
  lv_style_init(&styleTextBig);
  lv_style_set_text_color(&styleTextBig, lv_color_white());
  lv_style_set_text_font(&styleTextBig, &lv_font_montserrat_16);
  lv_obj_add_style(labelErrorHeader, &styleTextBig, LV_PART_MAIN);
  lv_obj_align(labelErrorHeader, LV_ALIGN_CENTER, 0, 10);

  // Label (error text box)
  lv_obj_t *labelErrorBody = lv_label_create(scrError);
  lv_label_set_long_mode(labelErrorBody, LV_LABEL_LONG_WRAP);
  lv_label_set_text(labelErrorBody, errorInstructions);

  static lv_style_t styleErrorText;
  lv_style_init(&styleErrorText);
  lv_style_set_text_color(&styleErrorText, lv_color_white());
  lv_style_set_text_font(&styleErrorText, &lv_font_montserrat_12);
  lv_obj_add_style(labelErrorBody, &styleErrorText, LV_PART_MAIN);
  // small width to allow LABEL_LONG_WRAP
  lv_obj_set_width(labelErrorBody, 220);
  lv_obj_align(labelErrorBody, LV_ALIGN_CENTER, 0, 65);

  return scrError;
}

void testScreens() {
  // Build splash screen
  lv_obj_t *scrSplash = lv_obj_create(NULL);
  createSplashScreen(scrSplash);
  // Load splash screen
  lv_scr_load(scrSplash);

  // Build loading screen
  lv_obj_t *scrLoading = lv_obj_create(NULL);
  buildScreenLoad(scrLoading);
  // Switch from Splash screen to the Loading screen and delete Splash screen
  lv_scr_load_anim(scrLoading, LV_SCR_LOAD_ANIM_NONE, 100, 2500, true);

  // Generate an error screen
  // lv_obj_t * scrError = buildScreenError(ERR_NO_JSON_HEADER,
  // ERR_NO_JSON_INSTRUCTIONS);
}

int main(void) {
  lv_init();
  hal_setup();

  // Step through the boot sequence
  testScreens();

  // HAL loop
  hal_loop();
}