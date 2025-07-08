#pragma once
#include <QRandomGenerator>
#include <QVector>

namespace utils {

/**
 * Convert pixel to centimeter on screen.
 *
 * @param pixel
 * @return Centimeter value
 */
double pixelToCentimeter(int pixel);

/**
 * Convert centimeter on screen to screen pixel.
 *
 * @param cm
 * @return Pixel value
 */
int centimeterToPixel(double cm);

/**
 * Generate a random integer in the range [min, max[.
 *
 * @param n Number of values to generate
 * @param min Minimum value (inclusive)
 * @param max Maximum value (exclusive)
 * @return QVector of random integers
 */
QVector<int> generateValues(int n, int min = 1, int max = 101);

}  // namespace utils
