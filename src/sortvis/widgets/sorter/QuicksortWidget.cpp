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
  // Implements one step of quicksort
  // Check if the range is valid
  if (left >= right) {
    // If the stack is empty, we are done
    if (stack.empty()) {
      sortingCompleted();
      return;
    } else {
      // More stack frames mean there are more partitions to process
      std::tie(left, right) = stack.top();
      stack.pop();
      currentIdx = left;
      // Going into a new partition is a new step
      return;
    }
  }

  // Initialize for new recursion
  if (currentIdx <= left) {
    pivotVal = values[right];
    partitionIdx = left;
  }

  // Partitioning
  if (currentIdx < right) {
    if (values[currentIdx] <= pivotVal) {
      ++swaps;
      std::swap(values[currentIdx], values[partitionIdx]);
      ++partitionIdx;
    }
    ++currentIdx;
  } else {
    // Finalize partition. Swap pivot to its correct position
    ++swaps;
    std::swap(values[partitionIdx], values[right]);
    // Queue up the right partition for later
    ++recursionDepth;
    stack.push({partitionIdx + 1, right});

    // Continue with left partition immediately
    right = partitionIdx - 1;
    currentIdx = left;
  }
}