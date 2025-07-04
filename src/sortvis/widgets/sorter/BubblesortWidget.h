#pragma once

#include "sortvis/widgets/BarPlotWidget.h"

class BubblesortWidget : public BarPlotWidget {
  Q_OBJECT  // needed for signal/slot mechanism
 public : explicit BubblesortWidget(QWidget *parent = nullptr);

  ~BubblesortWidget() override = default;

 protected:
  void reset() override;
  QString statistics() const override;


 private:
  void sortStepImpl() override;

  // Bubblesort variables
  int iteration = 0;
  int i = 0;
  int swaps = 0;
};
