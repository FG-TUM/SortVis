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
  sorting = false;
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

  // Write the current step number
  QString stats = statistics();
  QRect textRect = painter.fontMetrics().boundingRect(QRect(10, 10, width() - 20, height() - 20),
                                                      Qt::AlignLeft | Qt::TextWordWrap,
                                                      stats);
  painter.drawText(textRect, Qt::AlignLeft | Qt::TextWordWrap, stats);
}

QString BarPlotWidget::statistics() const {
  return QString("%1: %2").arg("Step").arg(steps);
}
