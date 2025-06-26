#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QShortcut>
#include <QSlider>

#include "utils.h"
#include "widgets/BarPlotWidget.h"

int main(int argc, char *argv[]) {
  // Global application object
  QApplication app(argc, argv);

  QWidget window;
  auto *quitShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q), &window);
  QObject::connect(quitShortcut, &QShortcut::activated, &app, &QApplication::quit);

  window.setWindowTitle("Sorting Visualizer");
  // resize window to half the screen size
  const auto screenGeometry = QApplication::primaryScreen()->geometry();
  const int windowHeight = screenGeometry.height() * 0.8;
  const int windowWidth = windowHeight * (16. / 9.);
  window.resize(windowWidth, windowHeight);
  // Center the window on the screen
  window.move((screenGeometry.width() - windowWidth) / 2, (screenGeometry.height() - windowHeight) / 2);

  auto *mainLayout = new QVBoxLayout(&window);

  // Controls
  auto *controlsLayout = new QHBoxLayout();
  mainLayout->addLayout(controlsLayout);
  controlsLayout->setAlignment(Qt::AlignLeft);

  // Start button
  auto *button = new QPushButton("Start!");
  button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  controlsLayout->addWidget(button);

  // Animation speed slider (incl label)
  auto *speedLabel = new QLabel();
  controlsLayout->addWidget(speedLabel);
  auto *speedSlider = new QSlider(Qt::Horizontal);
  speedSlider->setRange(1, 1000);  // speed in ms
  speedSlider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
  speedSlider->setMinimumWidth(utils::centimeterToPixel(2.0));  // 5 cm wide
  controlsLayout->addWidget(speedSlider);
  constexpr auto speedLabelText = "Pace %1 ms/step";
  QObject::connect(speedSlider, &QSlider::valueChanged,
                   [&](int value) { speedLabel->setText(QString(speedLabelText).arg(value, 3)); });
  // Set value after connection to ensure the label is correct from the start
  constexpr int defaultSpeed = 10;  // default speed in ms
  // Set the label width to fit the widest possible text
  speedLabel->setFixedWidth(
      speedLabel->fontMetrics().horizontalAdvance(QString(speedLabelText).arg(speedSlider->maximum())));
  speedSlider->setValue(defaultSpeed);

  // Create plots
  auto *plotsLayout = new QHBoxLayout();
  mainLayout->addLayout(plotsLayout);

  // Create a simple bar plot using QWidgets
  // FIXME: Don't limit plots
  for (int i = 2; i < 3; ++i) {
    auto *barWidget = new BarPlotWidget();
    barWidget->generateValues(100);
    // FIXME: Debug
    if (i == 0) {
      barWidget->setValues({10, 20, 30, 40, 50, 60, 70, 80, 90, 100});
    }
    // Set initial animation speed
    barWidget->setAnimationSpeed(speedSlider->value());
    plotsLayout->addWidget(barWidget);

    // Connect UI
    QObject::connect(button, &QPushButton::clicked, barWidget, &BarPlotWidget::startSortAnimation);
    QObject::connect(speedSlider, &QSlider::valueChanged, barWidget, &BarPlotWidget::setAnimationSpeed);
  }

  window.show();
  return QApplication::exec();
}
