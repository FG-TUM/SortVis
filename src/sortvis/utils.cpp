#include "utils.h"

#include <QApplication>
#include <QScreen>
#include <iostream>

namespace utils {

double pixelToCentimeter(int pixel) {
  QScreen *screen = QApplication::primaryScreen();
  if (!screen) {
    throw std::runtime_error(std::string(__FILE__) + ":" + __func__ + ": No primary screen available.");
  }
  const double dpi = screen->logicalDotsPerInch();
  constexpr double cmToInch = 1. / 2.54;
  const double dpiInCm = dpi * cmToInch;
  return pixel / dpiInCm;
}

int centimeterToPixel(double cm) {
  QScreen *screen = QApplication::primaryScreen();
  if (!screen) {
    throw std::runtime_error(std::string(__FILE__) + ":" + __func__ + ": No primary screen available.");
  }
  const double dpi = screen->logicalDotsPerInch();
  constexpr double cmToInch = 1. / 2.54;
  const double dpiInCm = dpi * cmToInch;
  const auto pixel = static_cast<int>(std::round(cm * dpiInCm));
  return pixel;
}

QVector<int> generateValues(int n, int min, int max) {
  QVector<int> values;
  values.reserve(n);
  for (int j = 0; j < n; ++j) {
    values.append(QRandomGenerator::global()->bounded(min, max));
  }
  return values;
}
}  // namespace utils