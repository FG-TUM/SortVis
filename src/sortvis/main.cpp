#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QShortcut>
#include <QSlider>

#include "utils.h"
#include "widgets/BarPlotWidget.h"
#include "widgets/ControlsWidget.h"

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
  auto *controlsWidget = new ControlsWidget();
  mainLayout->addWidget(controlsWidget, 0);

  // Create plots
  auto *plotsLayout = new QHBoxLayout();
  mainLayout->addLayout(plotsLayout, 1);

  // Create a simple bar plot using QWidgets
  for (int i = 0; i < 3; ++i) {
    auto *barWidget = new BarPlotWidget();
    barWidget->generateValues(controlsWidget->getSizeBox()->value());
    // FIXME: Debug
    if (i == 0) {
      barWidget->setValues({10, 20, 30, 40, 50, 60, 70, 80, 90, 100});
    }
    // Set initial animation speed
    barWidget->setAnimationSpeed(controlsWidget->getSpeedSlider()->value());
    plotsLayout->addWidget(barWidget);

    // Connect UI
    QObject::connect(controlsWidget->getStartButton(), &QPushButton::clicked, barWidget, [=]() {
      barWidget->startSortAnimation(controlsWidget->getSizeBox()->value());
    });
    QObject::connect(controlsWidget->getSpeedSlider(),
                     &QSlider::valueChanged,
                     barWidget,
                     &BarPlotWidget::setAnimationSpeed);
  }

  window.show();
  return QApplication::exec();
}
