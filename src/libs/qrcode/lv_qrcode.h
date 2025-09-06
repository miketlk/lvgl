/**
 * @file lv_qrcode.h
 *
 */

#ifndef LV_QRCODE_H
#define LV_QRCODE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"
#include "../../misc/lv_color.h"
#include "../../misc/lv_types.h"
#include "../../widgets/canvas/lv_canvas.h"
#include LV_STDBOOL_INCLUDE
#include LV_STDINT_INCLUDE
#if LV_USE_QRCODE

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

LV_ATTRIBUTE_EXTERN_DATA extern const lv_obj_class_t lv_qrcode_class;

/**
 * QR Code input modes.
 */
typedef enum {
    /** Binary mode accepting any binary data. */
    LV_QRCODE_MODE_BINARY = 0,

    /** Text mode with autodetection of numeric and alphanumeric strings. */
    LV_QRCODE_MODE_TEXT = 1
} lv_qrcode_mode_t;

/**
 * QR Code error-correction levels (ISO/IEC 18004).
 *
 * Values are intentionally identical to Nayuki's `qrcodegen_Ecc_*`
 * so they can be cast at zero cost. The typical fraction of
 * tolerable erroneous codewords is:
 * - L about 7%
 * - M about 15%
 * - Q about 25%
 * - H about 30%
 */
typedef enum {
    /** Low error correction (~7%). Matches qrcodegen_Ecc_LOW. */
    LV_QRCODE_ECC_L = 0,

    /** Medium error correction (~15%). Matches qrcodegen_Ecc_MEDIUM. */
    LV_QRCODE_ECC_M = 1,

    /** Quartile error correction (~25%). Matches qrcodegen_Ecc_QUARTILE. */
    LV_QRCODE_ECC_Q = 2,

    /** High error correction (~30%). Matches qrcodegen_Ecc_HIGH. */
    LV_QRCODE_ECC_H = 3
} lv_qrcode_ecc_t;

/**
 * QR Code mask pattern selector.
 *
 * Values mirror Nayuki's `qrcodegen_Mask_*`. `AUTO` requests the encoder
 * to choose the best mask; otherwise select an explicit mask 0..7.
 */
typedef enum {
    /** Let encoder choose the optimal mask. Matches qrcodegen_Mask_AUTO. */
    LV_QRCODE_MASK_AUTO = -1,

    /** Explicit mask 0. Matches qrcodegen_Mask_0. */
    LV_QRCODE_MASK_0    = 0,

    /** Explicit mask 1. Matches qrcodegen_Mask_1. */
    LV_QRCODE_MASK_1    = 1,

    /** Explicit mask 2. Matches qrcodegen_Mask_2. */
    LV_QRCODE_MASK_2    = 2,

    /** Explicit mask 3. Matches qrcodegen_Mask_3. */
    LV_QRCODE_MASK_3    = 3,

    /** Explicit mask 4. Matches qrcodegen_Mask_4. */
    LV_QRCODE_MASK_4    = 4,

    /** Explicit mask 5. Matches qrcodegen_Mask_5. */
    LV_QRCODE_MASK_5    = 5,

    /** Explicit mask 6. Matches qrcodegen_Mask_6. */
    LV_QRCODE_MASK_6    = 6,

    /** Explicit mask 7. Matches qrcodegen_Mask_7. */
    LV_QRCODE_MASK_7    = 7
} lv_qrcode_mask_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create an empty QR code (an `lv_canvas`) object.
 * @param parent point to an object where to create the QR code
 * @return pointer to the created QR code object
 */
lv_obj_t * lv_qrcode_create(lv_obj_t * parent);

/**
 * Set QR code size.
 * @param obj pointer to a QR code object
 * @param size width and height of the QR code
 */
void lv_qrcode_set_size(lv_obj_t * obj, int32_t size);

/**
 * Set QR code dark color.
 * @param obj pointer to a QR code object
 * @param color dark color of the QR code
 */
void lv_qrcode_set_dark_color(lv_obj_t * obj, lv_color_t color);

/**
 * Set QR code light color.
 * @param obj pointer to a QR code object
 * @param color light color of the QR code
 */
void lv_qrcode_set_light_color(lv_obj_t * obj, lv_color_t color);

/**
 * Set the preferred QR version range.
 * @param obj pointer to a QR code object
 * @param min_ver minimum version (0 for AUTO)
 * @param max_ver maximum version (0 for AUTO)
 */
void lv_qrcode_set_version_range(lv_obj_t * obj, int32_t min_ver, int32_t max_ver);

/**
 * Set the input mode (segment mode mirror).
 * @param obj pointer to a QR code object
 * @param mode one of LV_QRCODE_MODE_*
 */
void lv_qrcode_set_mode(lv_obj_t * obj, lv_qrcode_mode_t mode);

/**
 * Set the mask selection.
 * @param obj pointer to a QR code object
 * @param mask one of LV_QRCODE_MASK_*
 */
void lv_qrcode_set_mask(lv_obj_t * obj, lv_qrcode_mask_t mask);

/**
 * Set the ECC level.
 * @param obj pointer to a QR code object
 * @param ecc one of LV_QRCODE_ECC_*
 */
void lv_qrcode_set_ecc(lv_obj_t * obj, lv_qrcode_ecc_t ecc);

/**
 * Enable/disable boosting ECL when advantageous.
 * @param obj pointer to a QR code object
 * @param enable true to enable, false to disable
 */
void lv_qrcode_set_boost_ecl(lv_obj_t * obj, bool enable);

/**
 * Set the data of a QR code object
 * @param obj pointer to a QR code object
 * @param data data to display
 * @param data_len length of data in bytes
 * @return LV_RESULT_OK: if no error; LV_RESULT_INVALID: on error
 */
lv_result_t lv_qrcode_update(lv_obj_t * obj, const void * data, uint32_t data_len);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_QRCODE*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_QRCODE_H*/
