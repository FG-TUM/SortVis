#include "BarPlotWidget.h"

#include <qgridlayout.h>

#include <QLabel>
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
  if (values.isEmpty() or timer.isActive()) {
    return;
  }

  // restart with new values
  if (sorted) {
    generateValues(numberOfValues);
    reset();
  }

  timer.start();
}
void BarPlotWidget::reset() {
  steps = 0;
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
  reset();
  update();
}

int BarPlotWidget::getAnimationSpeed() const {
  return timer.interval();
}

void BarPlotWidget::sortStep() {
  // Implements one step of bubble sort
  ++steps;
  sortStepImpl();
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

  // Draw statistics
  paintStatistics(painter);
}

void BarPlotWidget::paintStatistics(QPainter &painter) const {
  const auto fontMetrics = painter.fontMetrics();

  const auto keyValueList = statistics();
  const int colonWidth = fontMetrics.horizontalAdvance(" : ");
  constexpr int paddingFromLeft = 0;
  constexpr int paddingFromTop = 0;
  constexpr int lineSeparation = 2;

  // Measure max widths for alignment
  int maxKeyWidth = 0;
  int maxValueWidth = 0;
  for (const auto &[key, value] : keyValueList) {
    maxKeyWidth = std::max(maxKeyWidth, fontMetrics.horizontalAdvance(key));
    maxValueWidth = std::max(maxValueWidth, fontMetrics.horizontalAdvance(QString::number(value)));
  }

  // Draw each stat line
  int posY = paddingFromTop;
  const int lineHeight = fontMetrics.height();
  for (const auto &[key, value] : keyValueList) {
    int keyX = paddingFromLeft;
    int colonX = keyX + maxKeyWidth;
    int valueX = colonX + colonWidth;
    int baselineY = posY + lineHeight;

    painter.drawText(keyX, baselineY, key);
    painter.drawText(colonX, baselineY, " : ");
    painter.drawText(valueX, baselineY, QString::number(value));

    posY += lineHeight + lineSeparation;
  }
}

QList<std::pair<QString, int>> BarPlotWidget::statistics() const {
  return QList<std::pair<QString, int>>{
      {"Steps", steps},
  };
}
void BarPlotWidget::sortingCompleted() {
  sorted = true;
  timer.stop();
}
