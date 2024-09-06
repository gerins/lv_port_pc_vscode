
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_display_t *hal_init(int32_t w, int32_t h);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
// LV_FONT_DECLARE(custom_symbol_16)

/**********************
 *      VARIABLES
 **********************/
// const char *tempLogo = "\xEF\x8B\x88";
// const char *lightingBoltLogo = "\xEF\x83\xA7";

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
lv_obj_t *CreateBaseArc(uint32_t indicatorColour, uint32_t backgroundColour, int arcSize, int minRange, int maxrange)
{

  // Background arc, solid color
  lv_obj_t *backgroundArc = lv_arc_create(lv_screen_active());
  lv_arc_set_value(backgroundArc, 0);
  lv_arc_set_bg_angles(backgroundArc, 90, 270);                // Arc length, 90 start at 6 o'clock
  lv_obj_center(backgroundArc);                                // Middle position
  lv_obj_set_size(backgroundArc, arcSize + 5, arcSize + 5);    // Set width and height
  lv_obj_set_style_arc_width(backgroundArc, 20, LV_PART_MAIN); // Ketebalan arc
  lv_obj_remove_style(backgroundArc, NULL, LV_PART_KNOB);      // Remove knob
  lv_obj_remove_flag(backgroundArc, LV_OBJ_FLAG_CLICKABLE);    // Static arc
  lv_obj_set_style_arc_color(backgroundArc, lv_color_hex(indicatorColour), LV_PART_MAIN);
  lv_obj_set_style_arc_width(backgroundArc, 20, LV_PART_MAIN);

  // Main arc
  lv_obj_t *newArc = lv_arc_create(lv_screen_active());

  // Spec
  lv_arc_set_range(newArc, minRange, maxrange); // Value range
  lv_arc_set_bg_angles(newArc, 90, 270);        // Arc length, start at 6 o clock end at 12 o clock
  // Style
  lv_obj_center(newArc);                                                                // Middle position
  lv_obj_set_size(newArc, arcSize, arcSize);                                            // Set width and height
  lv_obj_remove_style(newArc, NULL, LV_PART_KNOB);                                      // Remove knob
  lv_obj_remove_flag(newArc, LV_OBJ_FLAG_CLICKABLE);                                    // Static arc
  lv_obj_set_style_arc_color(newArc, lv_color_hex(backgroundColour), LV_PART_MAIN);     // LV_PART_MAIN = Glass
  lv_obj_set_style_arc_color(newArc, lv_color_hex(indicatorColour), LV_PART_INDICATOR); // LV_PART_INDICATOR = Water
  lv_obj_set_style_arc_width(newArc, 15, LV_PART_MAIN);
  lv_obj_set_style_arc_width(newArc, 15, LV_PART_INDICATOR);

  return newArc;
}

int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init(240, 240);

  /******************************************************************
   *                      START CODING HERE
   ******************************************************************/
  // ARC 1
  lv_obj_t *rpmArc = CreateBaseArc(0xFF34A5F1, 0xFF183C52, 220, 0, 7000);
  lv_arc_set_value(rpmArc, 3000);
  lv_obj_t *rpmLabel = lv_label_create(lv_screen_active());           // Create text
  lv_obj_align(rpmLabel, LV_ALIGN_TOP_MID, 29, 9);                    // Position
  lv_obj_set_style_text_color(rpmLabel, lv_color_hex(0xFF34A5F1), 0); // Change text color
  lv_label_set_text(rpmLabel, "max");

  // ARC 2
  lv_obj_t *engineTempArc = CreateBaseArc(0xFF7D1716, 0xFF311410, 170, 0, 120);
  lv_arc_set_value(engineTempArc, 90);
  lv_obj_t *tempLabel = lv_label_create(lv_screen_active());           // Create text
  lv_obj_align(tempLabel, LV_ALIGN_TOP_MID, 30, 35);                   // Position
  lv_obj_set_style_text_color(tempLabel, lv_color_hex(0xFF7D1716), 0); // Change text color
  lv_label_set_text(tempLabel, "90 c");
  // lv_obj_t *tempSymbol = lv_label_create(lv_scr_act());                 //
  // lv_obj_align(tempSymbol, LV_ALIGN_CENTER, 0, -108);                   // Center position
  // lv_obj_set_style_text_font(tempSymbol, &custom_symbol_16, 0);         // Change font style
  // lv_obj_set_style_text_color(tempSymbol, lv_color_hex(0xFFD72749), 0); // Change text color
  // lv_label_set_text(tempSymbol, tempLogo);                              // Set logo symbol

  // ARC 3
  lv_obj_t *voltArc = CreateBaseArc(0xFFFFC848, 0xFF524C20, 120, 0, 16);
  lv_arc_set_value(voltArc, 12);
  lv_obj_t *voltLabel = lv_label_create(lv_screen_active());           // Create text
  lv_obj_align(voltLabel, LV_ALIGN_TOP_MID, 30, 60);                   // Position
  lv_obj_set_style_text_color(voltLabel, lv_color_hex(0xFFFFC848), 0); // Change text color
  lv_label_set_text(voltLabel, "13.2v");

  lv_obj_t *label = lv_label_create(lv_screen_active());           // Create text
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);                      // Center
  lv_obj_set_style_text_color(label, lv_color_hex(0xFF1E2021), 0); // Change text color
  lv_label_set_text(label, "3000");

  while (1)
  {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_timer_handler();
    usleep(5 * 1000);
  }

  return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static lv_display_t *hal_init(int32_t w, int32_t h)
{

  lv_group_set_default(lv_group_create());

  lv_display_t *disp = lv_sdl_window_create(w, h);

  lv_indev_t *mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse, lv_group_get_default());
  lv_indev_set_display(mouse, disp);
  lv_display_set_default(disp);

  LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  lv_obj_t *cursor_obj;
  cursor_obj = lv_image_create(lv_screen_active()); /*Create an image object for the cursor */
  lv_image_set_src(cursor_obj, &mouse_cursor_icon); /*Set the image source*/
  lv_indev_set_cursor(mouse, cursor_obj);           /*Connect the image  object to the driver*/

  lv_indev_t *mousewheel = lv_sdl_mousewheel_create();
  lv_indev_set_display(mousewheel, disp);
  lv_indev_set_group(mousewheel, lv_group_get_default());

  lv_indev_t *kb = lv_sdl_keyboard_create();
  lv_indev_set_display(kb, disp);
  lv_indev_set_group(kb, lv_group_get_default());

  return disp;
}
