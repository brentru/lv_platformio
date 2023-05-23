/*******************************************************************************
 * Size: 20 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef WIFI_20PX
#define WIFI_20PX 1
#endif

#if WIFI_20PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+F1EB "" */
    0x0, 0xff, 0x11, 0xa1, 0x90, 0x7, 0xff, 0x10,
    0xe3, 0x3f, 0x72, 0xf3, 0x7f, 0x20, 0xc0, 0x3f,
    0xcd, 0xb8, 0xe6, 0x1, 0xf1, 0xbe, 0x6b, 0x0,
    0x78, 0xf6, 0x48, 0x3, 0xc2, 0x1, 0xe2, 0x9d,
    0x30, 0xa, 0x30, 0x80, 0x24, 0x8d, 0xff, 0x77,
    0xfb, 0x61, 0x0, 0x22, 0xc8, 0xa, 0x70, 0x9,
    0x76, 0xdc, 0x80, 0x38, 0x9e, 0xf5, 0x40, 0x27,
    0xa1, 0x0, 0x16, 0x51, 0x0, 0x7f, 0xc5, 0x58,
    0x40, 0x1, 0xb4, 0x5c, 0x30, 0x9, 0x67, 0x7b,
    0xfb, 0x65, 0x40, 0x23, 0xc5, 0x4b, 0xb, 0xa1,
    0x0, 0x36, 0xd3, 0x10, 0x80, 0x93, 0x56, 0xb0,
    0x0, 0x6a, 0xc0, 0x38, 0x6e, 0x48, 0x3, 0xf8,
    0xa6, 0xc4, 0x3, 0xf4, 0xa0, 0x4, 0xb5, 0x9b,
    0x94, 0xa0, 0x12, 0x48, 0x7, 0xe8, 0x30, 0x4e,
    0xa5, 0x32, 0x35, 0xae, 0x40, 0x38, 0x0, 0xfe,
    0xcb, 0xb0, 0x80, 0x7c, 0x37, 0x6c, 0x0, 0xff,
    0x90, 0x2, 0x19, 0xd9, 0x10, 0x9, 0x0, 0x3f,
    0xf8, 0x96, 0xc4, 0xd6, 0x1, 0xff, 0xc8, 0x50,
    0x9, 0x40, 0x3f, 0xf9, 0x6, 0x1, 0x18, 0x7,
    0xff, 0x23, 0xc4, 0x7, 0xc0, 0x3f, 0xf9, 0x7,
    0xdd, 0x18, 0x7, 0xf8
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 400, .box_w = 25, .box_h = 19, .ofs_x = 0, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 61931, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 1,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t wifi_20px = {
#else
lv_font_t wifi_20px = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -7,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if WIFI_20PX*/

