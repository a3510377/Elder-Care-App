/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts:
 ******************************************************************************/

#include "app/ui.h"

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0021 "!" */
    0xfe, 0x40,

    /* U+4E86 "了" */
    0xff, 0xf0, 0x2, 0x0, 0x40, 0x8, 0x3, 0x0, 0x20, 0x2, 0x0, 0x20, 0x2, 0x0,
    0x20, 0x2, 0x0, 0x20, 0x2, 0x0, 0xa0, 0x4, 0x0,

    /* U+4F60 "你" */
    0x8, 0x80, 0x11, 0x0, 0x22, 0x0, 0x8f, 0xf1, 0x10, 0x26, 0x40, 0x8d, 0x8,
    0x28, 0x10, 0x91, 0x28, 0x22, 0x48, 0x48, 0x90, 0x91, 0x11, 0x42, 0x22, 0x4,
    0x4, 0x28, 0x8, 0x20,

    /* U+5012 "倒" */
    0x10, 0x4, 0x40, 0x11, 0xfc, 0x48, 0x85, 0x22, 0x15, 0x92, 0x56, 0x7d, 0x68,
    0x45, 0x21, 0x14, 0x9f, 0x52, 0x11, 0x48, 0x45, 0x21, 0xc4, 0xb8, 0x12,
    0x41, 0x48, 0x2,

    /* U+8DCC "跌" */
    0x0, 0x20, 0xf8, 0x41, 0x14, 0x82, 0x29, 0x4, 0x5f, 0xcf, 0xa4, 0x4, 0x88,
    0x8, 0x10, 0x11, 0xfe, 0xb8, 0x41, 0x41, 0x42, 0x82, 0x85, 0x8, 0x8b, 0x91,
    0x38, 0x41, 0x1, 0x1};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0,
     .adv_w = 0,
     .box_w = 0,
     .box_h = 0,
     .ofs_x = 0,
     .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0,
     .adv_w = 128,
     .box_w = 1,
     .box_h = 10,
     .ofs_x = 4,
     .ofs_y = 1},
    {.bitmap_index = 2,
     .adv_w = 256,
     .box_w = 12,
     .box_h = 15,
     .ofs_x = 2,
     .ofs_y = -2},
    {.bitmap_index = 25,
     .adv_w = 256,
     .box_w = 15,
     .box_h = 16,
     .ofs_x = 1,
     .ofs_y = -2},
    {.bitmap_index = 55,
     .adv_w = 256,
     .box_w = 14,
     .box_h = 16,
     .ofs_x = 1,
     .ofs_y = -2},
    {.bitmap_index = 83,
     .adv_w = 256,
     .box_w = 15,
     .box_h = 16,
     .ofs_x = 1,
     .ofs_y = -2}};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {0x0, 0x4e65, 0x4f3f, 0x4ff1, 0x8dab};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {.range_start = 33,
     .range_length = 36268,
     .glyph_id_start = 1,
     .unicode_list = unicode_list_0,
     .glyph_id_ofs_list = NULL,
     .list_length = 5,
     .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY}};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
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
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};

/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t fontChinese = {
#else
lv_font_t chinese = {
#endif
    .get_glyph_dsc =
        lv_font_get_glyph_dsc_fmt_txt, /*Function pointer to get glyph's data*/
    .get_glyph_bitmap =
        lv_font_get_bitmap_fmt_txt, /*Function pointer to get glyph's bitmap*/
    .line_height = 16, /*The maximum line height required by the font*/
    .base_line = 2,    /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc, /*The custom font data. Will be accessed by
                         `get_glyph_bitmap/dsc` */
    .fallback = NULL,
    .user_data = NULL};
