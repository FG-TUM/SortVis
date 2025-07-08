#include "BubblesortWidget.h"

BubblesortWidget::BubblesortWidget(QWidget *parent) : BarPlotWidget(parent) {}

void BubblesortWidget::reset() {
  BarPlotWidget::reset();
  iteration = 0;
  i = 0;
  swaps = 0;
}
QList<std::pair<QString, int>> BubblesortWidget::statistics() const {
  auto ret = BarPlotWidget::statistics();
  ret.append({"Swaps", swaps});
  return ret;
}

void BubblesortWidget::sortStepImpl() {
  // Optimized bubble sort: Elements > iteration are known to be sorted
  if (iteration < values.size() - 1) {
    if (i < values.size() - iteration - 1) {
      if (values[i] > values[i + 1]) {
        std::swap(values[i], values[i + 1]);
        ++swaps;
      }
      ++i;
    } else {
      i = 0;
      ++iteration;
    }
  } else {
    sortingCompleted();
  }
}