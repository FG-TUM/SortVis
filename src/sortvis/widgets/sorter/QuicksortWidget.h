#pragma once

#include <QStack>
#include "sortvis/widgets/BarPlotWidget.h"

class QuicksortWidget : public BarPlotWidget {
  Q_OBJECT  // needed for signal/slot mechanism
 public:
  explicit QuicksortWidget(QWidget *parent = nullptr);

  ~QuicksortWidget() override = default;

 protected:
  void reset() override;
  QList<std::pair<QString, int>> statistics() const override;

 private:
  void sortStepImpl() override;

  // Quicksort variables


  // statistics
  int swaps = 0;
  int recursionDepth = 0;
};
