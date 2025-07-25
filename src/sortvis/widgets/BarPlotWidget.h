#pragma once

#include <QTimer>
#include <QVector>
#include <QWidget>

class BarPlotWidget : public QWidget {
  Q_OBJECT  // needed for signal/slot mechanism
 public : explicit BarPlotWidget(QWidget *parent = nullptr);

  ~BarPlotWidget() override = default;

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
  virtual void reset();

  void generateValues(int n);

  [[nodiscard]] int getAnimationSpeed() const;

  void setAnimationSpeed(int animation_speed);

 private slots:
  void sortStep();

 private:
  void paintStatistics(QPainter &painter) const;

 protected:
  void paintEvent(QPaintEvent *event) override;

  virtual QList<std::pair<QString, int>> statistics() const;

  virtual void sortStepImpl() = 0;

  void sortingCompleted();

  QVector<int> values{};

  // Widget State
  QTimer timer;
  bool sorted = false;

  // Statistics
  constexpr static int statisticsKeyWidth = -10;  // px width of the key in the statistics text
  int steps = 0;
  /**
   * Animation speed in milliseconds per step.
   */
  int animationSpeed = 1;
};
