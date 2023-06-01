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
#include <stdlib.h>
#include <time.h>

/**********************
 *      MACROS
 **********************/
#define SYMBOL_TURTLE "\xEF\x9C\xA6"

/**********************
 *      FONTS
 **********************/
extern lv_font_t turtle_20;



static lv_obj_t * consoleLabel;

#define MAX_TEXT_BUFFER_SZ 430
static char textBuffer[MAX_TEXT_BUFFER_SZ + 1]; // + '\0'

static char txtBuffer[256];

/** Sensor types */
typedef enum {
  SENSOR_TYPE_ACCELEROMETER = (1), /**< Gravity + linear acceleration */
  SENSOR_TYPE_MAGNETIC_FIELD = (2),
  SENSOR_TYPE_ORIENTATION = (3),
  SENSOR_TYPE_GYROSCOPE = (4),
  SENSOR_TYPE_LIGHT = (5),
  SENSOR_TYPE_PRESSURE = (6),
  SENSOR_TYPE_PROXIMITY = (8),
  SENSOR_TYPE_GRAVITY = (9),
  SENSOR_TYPE_LINEAR_ACCELERATION =
      (10), /**< Acceleration not including gravity */
  SENSOR_TYPE_ROTATION_VECTOR = (11),
  SENSOR_TYPE_RELATIVE_HUMIDITY = (12),
  SENSOR_TYPE_AMBIENT_TEMPERATURE = (13),
  SENSOR_TYPE_OBJECT_TEMPERATURE = (14),
  SENSOR_TYPE_VOLTAGE = (15),
  SENSOR_TYPE_CURRENT = (16),
  SENSOR_TYPE_COLOR = (17),
  SENSOR_TYPE_TVOC = (18),
  SENSOR_TYPE_VOC_INDEX = (19),
  SENSOR_TYPE_NOX_INDEX = (20),
  SENSOR_TYPE_CO2 = (21),
  SENSOR_TYPE_ECO2 = (22),
  SENSOR_TYPE_PM10_STD = (23),
  SENSOR_TYPE_PM25_STD = (24),
  SENSOR_TYPE_PM100_STD = (25),
  SENSOR_TYPE_PM10_ENV = (26),
  SENSOR_TYPE_PM25_ENV = (27),
  SENSOR_TYPE_PM100_ENV = (28),
  SENSOR_TYPE_GAS_RESISTANCE = (29),
  SENSOR_TYPE_UNITLESS_PERCENT = (30)
} sensors_type_t;


/* Sensor event (36 bytes) */
/** struct sensor_event_s is used to provide a single sensor event in a common
 * format. */
typedef struct {
  int32_t version;   /**< must be sizeof(struct sensors_event_t) */
  int32_t sensor_id; /**< unique sensor identifier */
  int32_t type;      /**< sensor type */
  int32_t reserved0; /**< reserved */
  int32_t timestamp; /**< time is in milliseconds */
  union {
    float data[4];              ///< Raw Data
    float temperature; /**< temperature is in degrees centigrade (Celsius) */
    float distance;    /**< distance in centimeters */
    float light;       /**< light in SI lux units */
    float pressure;    /**< pressure in hectopascal (hPa) */
    float relative_humidity; /**< relative humidity in percent */
    float current;           /**< current in milliamps (mA) */
    float voltage;           /**< voltage in volts (V) */
    float tvoc;              /**< Total Volatile Organic Compounds, in ppb */
    float voc_index; /**< VOC (Volatile Organic Compound) index where 100 is
                          normal (unitless) */
    float nox_index; /**< NOx (Nitrogen Oxides) index where 100 is normal
                          (unitless) */
    float CO2;       /**< Measured CO2 in parts per million (ppm) */
    float eCO2;      /**< equivalent/estimated CO2 in parts per million (ppm
                        estimated from some other measurement) */
    float pm10_std;  /**< Standard Particulate Matter <=1.0 in parts per million
                        (ppm) */
    float pm25_std;  /**< Standard Particulate Matter <=2.5 in parts per million
                        (ppm) */
    float pm100_std; /**< Standard Particulate Matter <=10.0 in parts per
                        million (ppm) */
    float pm10_env;  /**< Environmental Particulate Matter <=1.0 in parts per
                        million (ppm) */
    float pm25_env;  /**< Environmental Particulate Matter <=2.5 in parts per
                        million (ppm) */
    float pm100_env; /**< Environmental Particulate Matter <=10.0 in parts per
                        million (ppm) */
    float gas_resistance;   /**< Proportional to the amount of VOC particles in
                               the air (Ohms) */
    float unitless_percent; /**<Percentage, unit-less (%) */
  };                        ///< Union for the wide ranges of data we can carry
} sensors_event_t;


// Adds data to the monitor
// Referenced: https://github.com/lvgl/lv_demos/blob/release/v6/lv_apps/terminal/terminal.c
void monitor_add(const char * txt_in)
{
    // Calculate text size
    size_t txt_len = strlen(txt_in);
    size_t old_len = strlen(textBuffer);

    // If the data is longer then the terminal ax size show the last part of data
    if(txt_len > MAX_TEXT_BUFFER_SZ) {
        txt_in += (txt_len - MAX_TEXT_BUFFER_SZ);
        txt_len = MAX_TEXT_BUFFER_SZ;
        old_len = 0;
    }

    // If the text become too long 'forget' the oldest lines
    else if(old_len + txt_len > MAX_TEXT_BUFFER_SZ) {
        uint16_t new_start;
        for(new_start = 0; new_start < old_len; new_start++) {
            if(textBuffer[new_start] == '\n') {
                if(new_start >= txt_len) {
                    while(textBuffer[new_start] == '\n' || textBuffer[new_start] == '\r') new_start++;
                    break;
                }
            }
        }

        // If it wasn't able to make enough space on line breaks simply forget the oldest characters
        if(new_start == old_len) {
            new_start = old_len - (MAX_TEXT_BUFFER_SZ - txt_len);
        }

        // Move the remaining text to the beginning
        uint16_t j;
        for(j = new_start; j < old_len; j++) {
            textBuffer[j - new_start] = textBuffer[j];
        }
        old_len = old_len - new_start;
        textBuffer[old_len] = '\0';

    }

    // Copy new text to the text buffer
    memcpy(&textBuffer[old_len], txt_in, txt_len);
    textBuffer[old_len + txt_len] = '\0';

    // Update label
    lv_label_set_text_static(consoleLabel, textBuffer);
}


// sensor event api handling
void add_to_console_sensor_event(int16_t i2c_address, sensors_event_t sensor_event) {
  // TODO: maybe a memset to clear buffer first?
  // Only handling temperature and humidity types for now...
  if (sensor_event.type == SENSOR_TYPE_AMBIENT_TEMPERATURE) {
    snprintf(txtBuffer, 256, "[I2C, 0x%x] Temp.: %0.2f *F\n", i2c_address, sensor_event.temperature);
  } else if (sensor_event.type == SENSOR_TYPE_RELATIVE_HUMIDITY) {
    snprintf(txtBuffer, 256, "[I2C, 0x%x] Humid.: %0.2f RH\n", i2c_address, sensor_event.relative_humidity);
  }

  monitor_add(txtBuffer);
}

// Generate a mock sensor value between 1 and 100
int16_t generate_value() {
    return rand() % 101;
}

// Mock a MCP9808 Temperature Sensor
void read_mcp9808() {
    // Create a new sensor event
    sensors_event_t sensorEvent;

    // Mock: MCP9808 Temperature-only sensor
    int16_t i2c_address = 0x18;
    sensorEvent.type = SENSOR_TYPE_AMBIENT_TEMPERATURE;
    sensorEvent.temperature = (float) generate_value();

    // Add a sensor_event to the console
    add_to_console_sensor_event(i2c_address, sensorEvent);
}

// Mock a AHT20 Temperature Sensor
void read_aht20() {
    int16_t i2c_address = 0x38;
    // Create a new sensor event
    sensors_event_t sensorEvent;
    // Add temperature event
    sensorEvent.type = SENSOR_TYPE_AMBIENT_TEMPERATURE;
    sensorEvent.temperature = (float) generate_value();
    add_to_console_sensor_event(i2c_address, sensorEvent);

    // Add humidity event
    sensorEvent.type = SENSOR_TYPE_RELATIVE_HUMIDITY;
    sensorEvent.temperature = (float) generate_value();
    add_to_console_sensor_event(i2c_address, sensorEvent);
}

void add_to_console_digital_io(uint8_t pinName, int pinValue, bool isInput) {
  if (isInput)
    snprintf(txtBuffer, 256, "[Pin] D%u Read: %d\n", pinName, pinValue);
  else
    snprintf(txtBuffer, 256, "[Pin] Set D%u to %d\n", pinName, pinValue);
  monitor_add(txtBuffer);
}

void add_to_console_analog_in(uint8_t pinName, float pinValue, bool isRawMode) {
  if (isRawMode)
    snprintf(txtBuffer, 256, "[Pin] A%u Read: %0.3f\n", pinName, pinValue);
  else
    snprintf(txtBuffer, 256, "[Pin] A%u Read: %0.3fv\n", pinName, pinValue);
  monitor_add(txtBuffer);
}

void add_to_console_ping() {
    snprintf(txtBuffer, 256, "[Net] Ping IO\n");
}

void add_to_console_pwm_tone(uint8_t pin, uint32_t freq) {
  snprintf(txtBuffer, 256, "[PWM] Writing %uHz to pin %u\n", freq, pin);
  monitor_add(txtBuffer);
}

void add_to_console_pwm_dc(uint8_t pin, uint32_t duty_cycle) {
  snprintf(txtBuffer, 256, "[PWM] Writing duty cycle of %u to pin %u\n", duty_cycle, pin);
  monitor_add(txtBuffer);
}

void add_to_console_servo_write(int pin, int value) {
  snprintf(txtBuffer, 256, "[Servo] Writing value %d to pin %d\n", value, pin);
  monitor_add(txtBuffer);
}

void add_to_console_strand_write(int strandIdx, uint32_t rgbColor) {
  snprintf(txtBuffer, 256, "[Pixel] Writing color %u to strand # %d\n", rgbColor, strandIdx);
  monitor_add(txtBuffer);
}


void add_to_console_component_init() {
  snprintf(txtBuffer, 256, "[Pin] Configured analog output A%u\n", 0);
  monitor_add(txtBuffer);

  snprintf(txtBuffer, 256, "[Pin] Configured digital input D%u\n", 10);
  monitor_add(txtBuffer);

  snprintf(txtBuffer, 256, "[I2C] Configured sensor at 0x%x\n", 0x40);
  monitor_add(txtBuffer);

  snprintf(txtBuffer, 256, "[NeoPixel] Configured strand on D%d\n", 5);
  monitor_add(txtBuffer);

  snprintf(txtBuffer, 256, "[Servo] Configured servo on pin %d with min. pulse width of %duS and a max. pulse width of %duS\n", 12, 0, 1500);
  monitor_add(txtBuffer);

  snprintf(txtBuffer, 256, "[PWM] Configured PWM output on pin %d with freq. of %d Hz\n", 7, 300);
  monitor_add(txtBuffer);
}

void cb_add_to_console(lv_timer_t * timer) {
    int r = rand() % 12; // generate a random function callback

    switch (r)
    {
    // I2C
    case 0:
        read_aht20();
        break;
    case 1:
        read_mcp9808();
        break;
    // Digital IO
    case 2:
        add_to_console_digital_io(4, r, 0);
        break;
    case 3:
        add_to_console_digital_io(5, r, 1);
        break;
    // Analog IO
    case 4:
        add_to_console_analog_in(0, 0.052, 0);
        break;
    case 5:
        add_to_console_analog_in(1, 0.3, 1);
        break;
    // PWM
    case 6:
        add_to_console_pwm_tone(0, 400);
        break;
    case 7:
        add_to_console_pwm_dc(0, 20);
        break;
    case 8:
        add_to_console_servo_write(3, 256);
        break;
    // NeoPixel
    case 9:
        add_to_console_strand_write(1, 0xFFFF);
        break;
    case 10:
        add_to_console_ping();
    default:
        break;
    }
}





void load_task() {
  srand(time(NULL));
  printf("in load_task\n");
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_STATE_DEFAULT);

  // Create a status bar
  lv_obj_t * canvas = lv_canvas_create(lv_scr_act());
  static uint8_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR(240, 25)];
  lv_canvas_set_buffer(canvas, buffer, 240, 25, LV_IMG_CF_TRUE_COLOR);
  lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_COVER);
  lv_draw_rect_dsc_t rect_dsc;
  rect_dsc.bg_color = lv_palette_main(LV_PALETTE_GREY);
  rect_dsc.bg_opa = LV_OPA_COVER;
  lv_draw_rect_dsc_init(&rect_dsc);
  lv_canvas_draw_rect(canvas, 0, 0, 240, 25, &rect_dsc);

  // Add battery icon to status bar
  // TODO: Optional timer to check battery level on some boards
  // Note: FunHouse won't require this and should always be have a full battery displayed
  lv_obj_t * statusbar_icon_bat = lv_label_create(lv_scr_act());
  lv_label_set_text(statusbar_icon_bat, LV_SYMBOL_BATTERY_FULL);
  lv_obj_align(statusbar_icon_bat, LV_ALIGN_TOP_RIGHT, -5, 6);

  // Add WiFi icon to status bar
  // TODO: Timer to check if we are still connected to WiFi levels every 2000ms
  lv_obj_t * statusbar_icon_wifi = lv_label_create(lv_scr_act());
  lv_label_set_text(statusbar_icon_wifi, LV_SYMBOL_WIFI);
  lv_obj_align(statusbar_icon_wifi, LV_ALIGN_TOP_RIGHT, -30, 5);

  // Add Turtle icon to status bar
  lv_obj_t *labelTurtleBar = lv_label_create(lv_scr_act());
  lv_label_set_text(labelTurtleBar, SYMBOL_TURTLE);
  static lv_style_t styleIconTurtle30px;
  lv_style_init(&styleIconTurtle30px);
  lv_style_set_text_color(&styleIconTurtle30px,
                          lv_palette_main(LV_PALETTE_GREEN));
  lv_style_set_text_font(&styleIconTurtle30px, &turtle_20);
  lv_obj_add_style(labelTurtleBar, &styleIconTurtle30px,
                   LV_PART_MAIN);
  lv_obj_align(labelTurtleBar, LV_ALIGN_TOP_LEFT, 5, 5);


  // Add a label to hold console text
  // TODO: Speed this up via https://docs.lvgl.io/8.2/widgets/core/label.html#very-long-texts
  consoleLabel = lv_label_create(lv_scr_act());
  lv_obj_align(consoleLabel, LV_ALIGN_BOTTOM_LEFT, 5, -5);
  // TODO: Test long-mode...
  //lv_label_set_long_mode(consoleLabel, LV_LABEL_LONG_WRAP);
  lv_obj_set_width(consoleLabel, 240);
  static lv_style_t styleConsoleLabel;
  lv_style_init(&styleConsoleLabel);
  lv_style_set_text_color(&styleConsoleLabel, lv_color_white());
  lv_obj_add_style(consoleLabel, &styleConsoleLabel, LV_PART_MAIN);
  lv_label_set_text_static(consoleLabel, textBuffer);
  lv_obj_move_background(consoleLabel);
  lv_timer_t * timer_cb_console = lv_timer_create(cb_add_to_console, 7500,  NULL);

  add_to_console_component_init();

}



int main(void) {
  lv_init();
  hal_setup();

  printf("call load_task\n");
  load_task();

  lv_event_send(consoleLabel, LV_EVENT_REFRESH, "data");

  // printf("task handler\n");
  // lv_task_handler();

  printf("going into hal_loop...\n");
  hal_loop();
}