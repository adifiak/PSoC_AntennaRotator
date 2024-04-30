/**
 * @file ssd1306.h
 * @brief Header file for SSD1306 OLED display driver. (Based on Adafruit driver.)
 */

#ifndef _SSD1306_H
#define _SSD1306_H

/**
 * @brief Color definitions for OLED display.
 */
#define BLACK 0
#define WHITE 1
#define INVERSE 2

/**
 * @brief Enumeration for scroll direction.
 */
typedef enum {
    SCROLL_RIGHT = 0x26, /**< Scroll to the right */
    SCROLL_LEFT = 0x2A   /**< Scroll to the left */
} SCROLL_DIR;

/**
 * @brief Enumeration for scroll speed.
 */
typedef enum {
    SCROLL_SPEED_0 = 0x03, /**< Slowest scroll speed */
    SCROLL_SPEED_1 = 0x02,
    SCROLL_SPEED_2 = 0x01,
    SCROLL_SPEED_3 = 0x06,
    SCROLL_SPEED_4 = 0x00,
    SCROLL_SPEED_5 = 0x05,
    SCROLL_SPEED_6 = 0x04,
    SCROLL_SPEED_7 = 0x07  /**< Fastest scroll speed */
} SCROLL_SPEED;

/**
 * @brief Enumeration for scroll area.
 */
typedef enum {
    SCROLL_PAGE_0 = 0,
    SCROLL_PAGE_1,
    SCROLL_PAGE_2,
    SCROLL_PAGE_3,
    SCROLL_PAGE_4,
    SCROLL_PAGE_5,
    SCROLL_PAGE_6,
    SCROLL_PAGE_7
} SCROLL_AREA;

/**
 * @brief Initialize the OLED display.
 * @param i2caddr The I2C address of the display.
 */
void display_init(uint8_t i2caddr);

/**
 * @brief Update the OLED display.
 */
void display_update(void);

/**
 * @brief Clear the OLED display.
 */
void display_clear(void);

/**
 * @brief Stop scrolling on the OLED display.
 */
void display_stopscroll(void);

/**
 * @brief Scroll the OLED display.
 * @param start The starting scroll area.
 * @param end The ending scroll area.
 * @param dir The scroll direction.
 * @param speed The scroll speed.
 */
void display_scroll(SCROLL_AREA start, SCROLL_AREA end, SCROLL_DIR dir, SCROLL_SPEED speed);

/**
 * @brief Set the contrast of the OLED display.
 * @param contrast The contrast value.
 */
void display_contrast(uint8_t contrast);

/**
 * @brief Invert the colors on the OLED display.
 * @param invert Set to 1 to invert, 0 to not invert.
 */
void display_invert(uint8_t invert);

/**
 * @brief Draw a pixel on the OLED display.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 */
void gfx_drawPixel(int16_t x, int16_t y, uint16_t color);

#endif // _SSD1306_H

/* [] END OF FILE */
