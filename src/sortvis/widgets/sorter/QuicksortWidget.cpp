#include "QuicksortWidget.h"

QuicksortWidget::QuicksortWidget(QWidget *parent) : BarPlotWidget(parent) {}

void QuicksortWidget::reset() {
  BarPlotWidget::reset();

  right = values.size() - 1;
  left = 0;
  currentIdx = left;
}

QList<std::pair<QString, int>> QuicksortWidget::statistics() const {
  auto ret = BarPlotWidget::statistics();
  // Add more statistics as needed, e.g.:
  ret.append({"Swaps", swaps});
  ret.append({"Recursion Depth", recursionDepth});
  return ret;
}

void QuicksortWidget::sortStepImpl() {
  if (left < 0 or left >= right) {
    if (stack.empty()) {
      sortingCompleted();
      return;
    } else {
      std::tie(left, right) = stack.top();
      stack.pop();
      currentIdx = left;
      // going into a new "frame" is a new step
      return;
    }
  }

  // before a new recursion
  if (currentIdx <= left) {
    pivotVal = values[right];
    partitionIdx = left;
  }

  // partitioning
  if (currentIdx < right) {
    if (values[currentIdx] <= pivotVal) {
      ++swaps;
      std::swap(values[currentIdx], values[partitionIdx]);
      ++partitionIdx;
    }
    ++currentIdx;
  } else {
    ++swaps;
    std::swap(values[partitionIdx], values[right]);
    // return partitionIdx
    ++recursionDepth;
    stack.push({partitionIdx + 1, right});

    // directly initiate the next stack frame
    right = partitionIdx - 1;
    currentIdx = left;
  }
}