#include "QuicksortWidget.h"

#include "QuicksortWidget.h"

QuicksortWidget::QuicksortWidget(QWidget *parent)
    : BarPlotWidget(parent) {}

void QuicksortWidget::reset() {
  BarPlotWidget::reset();

}

QList<std::pair<QString, int>> QuicksortWidget::statistics() const {
  auto ret = BarPlotWidget::statistics();
  // Add more statistics as needed, e.g.:
  ret.append({"Swaps", swaps});
  ret.append({"Recursion Depth", recursionDepth});
  return ret;
}

void QuicksortWidget::sortStepImpl() {

}