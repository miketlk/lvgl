/**
 * @file lv_qrcode_private.h
 *
 */

#ifndef LV_QRCODE_PRIVATE_H
#define LV_QRCODE_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../../widgets/canvas/lv_canvas_private.h"
#include "lv_qrcode.h"

#if LV_USE_QRCODE

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Options of the QR code generator*/
struct _lv_qrcode_opts_t {
    uint8_t min_version : 6;  // default 0 => AUTO
    uint8_t max_version : 6;  // default 0 => AUTO
    uint8_t mode : 1;         // default 0 => BINARY
    int8_t  mask : 4;         // default -1 => AUTO
    uint8_t ecc : 2;          // default M
    uint8_t boost_ecl : 1;    // default 1
};

/*Data of qrcode*/
struct _lv_qrcode_t {
    lv_canvas_t canvas;
    lv_color_t dark_color;
    lv_color_t light_color;
    struct _lv_qrcode_opts_t opts;
};


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#endif /* LV_USE_QRCODE */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_QRCODE_PRIVATE_H*/
