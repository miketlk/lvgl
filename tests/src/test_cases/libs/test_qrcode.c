#if LV_BUILD_TEST
#include "../lvgl.h"
#include "../../lvgl_private.h"

#include "unity/unity.h"

#if LV_USE_QRCODE
#include <string.h>

static lv_obj_t * active_screen = NULL;

void setUp(void)
{
    active_screen = lv_screen_active();
}

void tearDown(void)
{
    lv_obj_clean(active_screen);
}

void test_barcode_normal(void)
{
    lv_color_t bg_color = lv_palette_lighten(LV_PALETTE_LIGHT_BLUE, 5);
    lv_color_t fg_color = lv_palette_darken(LV_PALETTE_BLUE, 4);

    lv_obj_t * qr = lv_qrcode_create(active_screen);
    TEST_ASSERT_NOT_NULL(qr);
    lv_qrcode_set_size(qr, 150);
    lv_qrcode_set_dark_color(qr, fg_color);
    lv_qrcode_set_light_color(qr, bg_color);

    /*Set data*/
    const char * data = "https://lvgl.io";
    lv_result_t res = lv_qrcode_update(qr, data, strlen(data));
    TEST_ASSERT_EQUAL(res, LV_RESULT_OK);
    lv_obj_center(qr);

    /*Add a border with bg_color*/
    lv_obj_set_style_border_color(qr, bg_color, 0);
    lv_obj_set_style_border_width(qr, 5, 0);
    TEST_ASSERT_EQUAL_SCREENSHOT("libs/qrcode_1.png");
}

void test_qrcode_options(void)
{
    #define TEST_DEFAULTS() do {\
        TEST_ASSERT_EQUAL(lv_qrcode_update(qr, data, sizeof(data)),\
                          LV_RESULT_OK);\
        TEST_ASSERT_EQUAL_SCREENSHOT("libs/qrcode_def_options.png");\
    } while(0)

    static const char * text = "hello, LVGL";
    static const uint8_t data[] = { /* "hello, LVGL" fullwidth style */
        0xEF, 0xBD, 0x88, // h
        0xEF, 0xBD, 0x85, // e
        0xEF, 0xBD, 0x8C, // l
        0xEF, 0xBD, 0x8C, // l
        0xEF, 0xBD, 0x8F, // o
        0xEF, 0xBC, 0x8C, // ,
        0xE3, 0x80, 0x80, // ideographic space
        0xEF, 0xBC, 0xAC, // L
        0xEF, 0xBC, 0xB6, // V
        0xEF, 0xBC, 0xA7, // G
        0xEF, 0xBC, 0xAC, // L
    };

    /* Create QR code with default options */
    lv_obj_t * qr = lv_qrcode_create(active_screen);
    TEST_ASSERT_NOT_NULL(qr);
    lv_qrcode_set_size(qr, 400);
    lv_obj_center(qr);
    TEST_ASSERT_EQUAL(lv_qrcode_update(qr, data, sizeof(data)), LV_RESULT_OK);
    TEST_ASSERT_EQUAL_SCREENSHOT("libs/qrcode_def_options.png");

    /* Version range: 5-40 */
    lv_qrcode_set_version_range(qr, 5, 40);
    TEST_ASSERT_EQUAL(lv_qrcode_update(qr, data, sizeof(data)), LV_RESULT_OK);
    TEST_ASSERT_EQUAL_SCREENSHOT("libs/qrcode_versions_5-40.png");
    lv_qrcode_set_version_range(qr, 0, 0);
    TEST_DEFAULTS();

    /* Version range: 40-40 */
    lv_qrcode_set_version_range(qr, 40, 40);
    TEST_ASSERT_EQUAL(lv_qrcode_update(qr, data, sizeof(data)), LV_RESULT_OK);
    TEST_ASSERT_EQUAL_SCREENSHOT("libs/qrcode_versions_40-40.png");
    lv_qrcode_set_version_range(qr, 0, 0);
    TEST_DEFAULTS();

    /* Text mode */
    lv_qrcode_set_mode(qr, LV_QRCODE_MODE_TEXT);
    TEST_ASSERT_EQUAL(lv_qrcode_update(qr, text, strlen(text)), LV_RESULT_OK);
    TEST_ASSERT_EQUAL_SCREENSHOT("libs/qrcode_text.png");
    lv_qrcode_set_mode(qr, LV_QRCODE_MODE_BINARY);
    TEST_DEFAULTS();

    /* Fixed mask 7 */
    lv_qrcode_set_mask(qr, LV_QRCODE_MASK_7);
    TEST_ASSERT_EQUAL(lv_qrcode_update(qr, data, sizeof(data)), LV_RESULT_OK);
    TEST_ASSERT_EQUAL_SCREENSHOT("libs/qrcode_mask_7.png");
    lv_qrcode_set_mask(qr, LV_QRCODE_MASK_AUTO);
    TEST_DEFAULTS();

    /* ECC: L */
    lv_qrcode_set_ecc(qr, LV_QRCODE_ECC_L);
    lv_qrcode_set_boost_ecl(qr, false);
    TEST_ASSERT_EQUAL(lv_qrcode_update(qr, data, sizeof(data)), LV_RESULT_OK);
    TEST_ASSERT_EQUAL_SCREENSHOT("libs/qrcode_ecc_l.png");
    lv_qrcode_set_ecc(qr, LV_QRCODE_ECC_M);
    lv_qrcode_set_boost_ecl(qr, true);
    TEST_DEFAULTS();

    /* ECC: Q */
    lv_qrcode_set_ecc(qr, LV_QRCODE_ECC_Q);
    lv_qrcode_set_boost_ecl(qr, false);
    TEST_ASSERT_EQUAL(lv_qrcode_update(qr, data, sizeof(data)), LV_RESULT_OK);
    TEST_ASSERT_EQUAL_SCREENSHOT("libs/qrcode_ecc_q.png");
    lv_qrcode_set_ecc(qr, LV_QRCODE_ECC_M);
    lv_qrcode_set_boost_ecl(qr, true);
    TEST_DEFAULTS();

    /* ECC: H */
    lv_qrcode_set_ecc(qr, LV_QRCODE_ECC_H);
    lv_qrcode_set_boost_ecl(qr, false);
    TEST_ASSERT_EQUAL(lv_qrcode_update(qr, data, sizeof(data)), LV_RESULT_OK);
    TEST_ASSERT_EQUAL_SCREENSHOT("libs/qrcode_ecc_h.png");
    lv_qrcode_set_ecc(qr, LV_QRCODE_ECC_M);
    lv_qrcode_set_boost_ecl(qr, true);
    TEST_DEFAULTS();

    /* Disable boosting ECL */
    TEST_ASSERT_EQUAL(lv_qrcode_update(qr, text, 1), LV_RESULT_OK);
    TEST_ASSERT_EQUAL_SCREENSHOT("libs/qrcode_1byte_boost_ecl.png");
    lv_qrcode_set_boost_ecl(qr, false);
    TEST_ASSERT_EQUAL(lv_qrcode_update(qr, text, 1), LV_RESULT_OK);
    TEST_ASSERT_EQUAL_SCREENSHOT("libs/qrcode_1byte_no_boost_ecl.png");
    lv_qrcode_set_boost_ecl(qr, true);
    TEST_DEFAULTS();

    #undef TEST_DEFAULTS
}

#else

void setUp(void)
{
}

void tearDown(void)
{
}

void test_barcode_normal(void)
{
}

#endif

#endif
