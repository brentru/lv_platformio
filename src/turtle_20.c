/*******************************************************************************
 * Size: 20 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include <lvgl.h>
#endif

#ifndef TURTLE_20
#define TURTLE_20 1
#endif

#if TURTLE_20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+F726 "" */
    0x0, 0xff, 0xe8, 0x3e, 0xff, 0xba, 0x44, 0x3,
    0xff, 0x84, 0x7b, 0x4, 0x0, 0x16, 0xf5, 0x0,
    0xff, 0xe0, 0x16, 0x10, 0x7, 0x86, 0x94, 0x3,
    0xfe, 0xe0, 0xf, 0xf5, 0x88, 0xc, 0xee, 0x30,
    0x4, 0xa6, 0x1, 0xfe, 0x19, 0xb, 0x62, 0x39,
    0x90, 0x3, 0x0, 0x3f, 0xf8, 0xa, 0x8, 0x1,
    0x98, 0xc0, 0x80, 0x3f, 0xf8, 0x4, 0x1, 0x1d,
    0x0, 0x14, 0x1c, 0x3, 0xff, 0x88, 0x5c, 0x0,
    0x10, 0x70, 0xf, 0xfe, 0x10, 0x80, 0xa0, 0x1,
    0x2, 0x8, 0x3, 0xfc, 0x32, 0x80, 0x18, 0xa8,
    0xc0, 0xf7, 0xff, 0xfd, 0xc7, 0x40, 0xe, 0xfd,
    0x50, 0x9f, 0xff, 0xfe, 0xd, 0x8, 0x40, 0x80,
    0x64, 0x0, 0xff, 0xe1, 0xc3, 0x80, 0x77, 0xc1,
    0x80, 0x63, 0x50, 0xc, 0x55, 0xce, 0x1, 0xe2,
    0x74, 0x0, 0xc9, 0xc0, 0x18, 0x54, 0x40, 0x3f,
    0xbc, 0x3, 0x7b, 0x80, 0x67, 0x0, 0xff, 0x94,
    0x3, 0x29, 0x90, 0x5, 0xa0, 0x1f, 0xf1, 0x76,
    0x63, 0x88, 0x37, 0x2f, 0x98, 0x3, 0xf8
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 360, .box_w = 23, .box_h = 19, .ofs_x = 0, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 63270, .range_length = 1, .glyph_id_start = 1,
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
const lv_font_t turtle_20 = {
#else
lv_font_t turtle_20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if TURTLE_20*/

