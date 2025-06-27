#include "ControlsWidget.h"

#include <QHBoxLayout>
#include <QLabel>

#include "../utils.h"  // needs relative path to not confuse with system utils.h

ControlsWidget::ControlsWidget(QWidget *parent) : QWidget(parent) {
  // Layout
  controlsLayout = new QHBoxLayout();
  controlsLayout->setAlignment(Qt::AlignLeft);
  setLayout(controlsLayout);

  // Start button
  startButton = new QPushButton("Start!");
  startButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  controlsLayout->addWidget(startButton);

  // Animation speed slider (incl label)
  auto *speedLabel = new QLabel();
  controlsLayout->addWidget(speedLabel);
  speedSlider = new QSlider(Qt::Horizontal);
  speedSlider->setRange(1, 1000);  // speed in ms
  speedSlider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
  speedSlider->setMinimumWidth(utils::centimeterToPixel(2.0));
  controlsLayout->addWidget(speedSlider);
  constexpr auto speedLabelText = "Pace %1 ms/step";
  QObject::connect(speedSlider, &QSlider::valueChanged, [=](int value) {
    speedLabel->setText(QString(speedLabelText).arg(value, 3));
  });
  // Set value after connection to ensure the label is correct from the start
  constexpr int defaultSpeed = 10;  // default speed in ms
  // Set the label width to fit the widest possible text
  speedLabel->setFixedWidth(
      speedLabel->fontMetrics().horizontalAdvance(QString(speedLabelText).arg(speedSlider->maximum())));
  speedSlider->setValue(defaultSpeed);

  // Number of bars / array size
  auto *sizeLabel = new QLabel("Array size");
  controlsLayout->addWidget(sizeLabel);
  sizeBox = new QSpinBox();
  controlsLayout->addWidget(sizeBox);
  sizeBox->setRange(1, 100);
  sizeBox->setValue(10);
}

QHBoxLayout *ControlsWidget::getControlsLayout() const {
  return controlsLayout;
}

QPushButton *ControlsWidget::getStartButton() const {
  return startButton;
}

QSlider *ControlsWidget::getSpeedSlider() const {
  return speedSlider;
}

QSpinBox *ControlsWidget::getSizeBox() const {
  return sizeBox;
}
