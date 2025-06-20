#pragma once

#include <QTimer>
#include <QVector>
#include <QWidget>

// Custom paint event for bar plot
class BarPlotWidget : public QWidget {
  Q_OBJECT
 public:
  explicit BarPlotWidget(QWidget *parent = nullptr);

  [[nodiscard]] const QVector<int> &getValues() const;

  /**
   * Set the values for the bar plot and reset sorting state.
   *
   * @param values The new values to be displayed in the bar plot.
   */
  void setValues(const QVector<int> &values);

  void startSortAnimation();

  /**
   * Reset algorithm, animation and sorting state.
   */
  void reset();

  void generateValues(int n);

  [[nodiscard]] int getAnimationSpeed() const;

  void setAnimationSpeed(int animation_speed);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private slots:
  void sortStep();

 private:
  QVector<int> values{};

  // Widget State
  QTimer timer;
  bool sorting = false;
  bool sorted = false;

  // Quicksort variables
  int iteration = 0;
  int i = 0;

  // Statistics
  int steps = 0;
  int swaps = 0;
  /**
   * Animation speed in milliseconds per step.
   */
  int animationSpeed = 1;
};
