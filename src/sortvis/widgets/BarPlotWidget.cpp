#include "BarPlotWidget.h"

#include <QPainter>
#include <QRandomGenerator>

BarPlotWidget::BarPlotWidget(QWidget *parent) : QWidget(parent) {
  // On every timeout, call sortStep
  connect(&timer, &QTimer::timeout, this, &BarPlotWidget::sortStep);
}

const QVector<int> &BarPlotWidget::getValues() const {
  return values;
}

void BarPlotWidget::setValues(const QVector<int> &values) {
  this->values = values;
  reset();
}

void BarPlotWidget::startSortAnimation(int numberOfValues) {
  if (values.isEmpty() or sorting) {
    return;
  }

  // restart with new values
  if (sorted) {
    generateValues(numberOfValues);
    reset();
  }

  sorting = true;
  timer.start();
}
void BarPlotWidget::reset() {
  iteration = 0;
  i = 0;
  sorting = false;
  steps = 0;
  swaps = 0;
  timer.stop();
  update();
}
void BarPlotWidget::generateValues(int n) {
  values.clear();
  values.reserve(n);
  for (int j = 0; j < n; ++j) {
    values.append(QRandomGenerator::global()->bounded(1, 101));
  }
  sorted = false;
  update();
}

int BarPlotWidget::getAnimationSpeed() const {
  return timer.interval();
}

void BarPlotWidget::sortStep() {
  // Implements one step of bubble sort
  ++steps;
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
    timer.stop();
    sorting = false;
    sorted = true;
  }
  update();
}

void BarPlotWidget::setAnimationSpeed(int animationSpeed) {
  timer.setInterval(animationSpeed);
}

void BarPlotWidget::paintEvent(QPaintEvent *paint_event) {
  QPainter painter(this);
  const int barWidth = width() / values.size();
  const int barWidthHalf = barWidth * 0.5;
  painter.setBrush(Qt::blue);
  const auto fontMetrics = painter.fontMetrics();

  for (int i = 0; i < values.size(); ++i) {
    const int barHeight = height() * values[i] * 0.01;
    painter.drawRect(i * barWidth, height() - barHeight, barWidth - 4, barHeight);
    QString label = QString::number(values[i]);
    const int labelWidth = fontMetrics.horizontalAdvance(label);
    painter.drawText(i * barWidth + barWidthHalf - labelWidth * 0.5, height() - 10, label);
  }

  // Write the current step number
  int textX = 10;  // px from the left
  int textY = 20;  // px above the bottom

  QString stepText = QString("Step : %1\tSwaps: %2").arg(steps).arg(swaps);
  painter.drawText(textX, textY, stepText);
}
