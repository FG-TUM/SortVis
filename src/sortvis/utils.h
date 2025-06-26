#pragma once

namespace utils {

/**
 * Convert pixel to centimeter on screen.
 * @param pixel
 * @return Centimeter value
 */
double pixelToCentimeter(int pixel);

/**
 * Convert centimeter on screen to screen pixel.
 * @param cm
 * @return Pixel value
 */
int centimeterToPixel(double cm);

}  // namespace utils
