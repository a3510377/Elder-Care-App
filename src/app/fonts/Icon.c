#include "app/ui.h"

/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 ******************************************************************************/

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E3F7 "" */
    0x0, 0x20, 0x0, 0x1c, 0x0, 0x7, 0x80, 0x23, 0x70, 0xc, 0x8e, 0x7, 0x81,
    0x83, 0x60, 0x31, 0xcc, 0xe, 0xff, 0xff, 0xc0,

    /* U+E63E "" */
    0x3, 0xfc, 0x0, 0xff, 0xf0, 0x3e, 0x7, 0xc7, 0x80, 0x1e, 0x60, 0x0, 0x60,
    0x1f, 0x80, 0x7, 0xfe, 0x0, 0xf0, 0x70, 0x4, 0x0, 0x0, 0x6, 0x0, 0x0, 0xf0,
    0x0, 0xf, 0x0, 0x0, 0x60, 0x0,

    /* U+EA0B "" */
    0x0, 0x80, 0x6, 0x0, 0x38, 0x1, 0xe0, 0x7, 0x80, 0x36, 0x1, 0x98, 0xe, 0x7e,
    0x70, 0x31, 0xf1, 0x80, 0xcc, 0x3, 0x60, 0xf, 0x0, 0x3c, 0x0, 0xe0, 0x3,
    0x0,

    /* U+EB31 "" */
    0x3, 0xfc, 0x0, 0x70, 0x1c, 0xe, 0x0, 0x38, 0xc0, 0x0, 0xe6, 0x0, 0x1, 0x18,
    0x3, 0x80, 0x60, 0x76, 0x1, 0x83, 0x18, 0x6, 0x18, 0xc0, 0x18, 0xee, 0x0,
    0x63, 0xf0, 0x1, 0xc0, 0xe0, 0x6, 0x2, 0x0, 0x0, 0x0,

    /* U+F076 "" */
    0x8, 0x0, 0x3e, 0x0, 0x36, 0x7f, 0x36, 0x0, 0x36, 0x0, 0x36, 0x0, 0x36,
    0x78, 0x36, 0x0, 0x77, 0x0, 0xe3, 0x80, 0xc1, 0x80, 0xff, 0x80, 0xff, 0x80,
    0x7f, 0x0, 0x3e, 0x0,

    /* U+F87D "" */
    0x3c, 0x0, 0x33, 0x0, 0x30, 0x80, 0x18, 0x60, 0xc, 0x31, 0xe6, 0x19, 0x9b,
    0xc, 0x85, 0xcc, 0xc2, 0x7e, 0x61, 0xbf, 0x30, 0xcc, 0xd8, 0x66, 0x6e, 0x61,
    0x33, 0xf0, 0xf1, 0xf8, 0x1, 0x98, 0x0, 0xcc, 0x0, 0x64, 0x0, 0x1c, 0x0};

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
     .adv_w = 320,
     .box_w = 18,
     .box_h = 9,
     .ofs_x = 1,
     .ofs_y = 5},
    {.bitmap_index = 21,
     .adv_w = 320,
     .box_w = 20,
     .box_h = 13,
     .ofs_x = 0,
     .ofs_y = 3},
    {.bitmap_index = 54,
     .adv_w = 320,
     .box_w = 14,
     .box_h = 16,
     .ofs_x = 3,
     .ofs_y = 2},
    {.bitmap_index = 82,
     .adv_w = 320,
     .box_w = 21,
     .box_h = 14,
     .ofs_x = 0,
     .ofs_y = 2},
    {.bitmap_index = 119,
     .adv_w = 320,
     .box_w = 16,
     .box_h = 15,
     .ofs_x = 2,
     .ofs_y = 3},
    {.bitmap_index = 149,
     .adv_w = 320,
     .box_w = 17,
     .box_h = 18,
     .ofs_x = 1,
     .ofs_y = 1}};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {0x0,   0x247, 0x614,
                                          0x73a, 0xc7f, 0x1486};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {.range_start = 58359,
     .range_length = 5255,
     .glyph_id_start = 1,
     .unicode_list = unicode_list_0,
     .glyph_id_ofs_list = NULL,
     .list_length = 6,
     .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY}};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static lv_font_fmt_txt_glyph_cache_t cache;
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
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};

/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t fontIcon = {
#else
lv_font_t fontIcon = {
#endif
    .get_glyph_dsc =
        lv_font_get_glyph_dsc_fmt_txt, /*Function pointer to get glyph's data*/
    .get_glyph_bitmap =
        lv_font_get_bitmap_fmt_txt, /*Function pointer to get glyph's bitmap*/
    .line_height = 18, /*The maximum line height required by the font*/
    .base_line = -1,   /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc /*The custom font data. Will be accessed by
                        `get_glyph_bitmap/dsc` */
};
