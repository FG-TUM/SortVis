#include <QApplication>
#include <QScreen>
#include <QShortcut>

#include "sortvis/utils.h"
#include "sortvis/widgets/BarPlotWidget.h"
#include "sortvis/widgets/ControlsWidget.h"
#include "sortvis/widgets/sorter/BubblesortWidget.h"
#include "widgets/sorter/QuicksortWidget.h"

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
  QVector<BarPlotWidget *> barWidgets;
  barWidgets.reserve(3);
  auto values = utils::generateValues(controlsWidget->getSizeBox()->value());
  for (int i = 0; i < barWidgets.capacity(); ++i) {
    BarPlotWidget *barWidget;
    if (i <= 1) {
      barWidget = new BubblesortWidget();
    } else {
      barWidget = new QuicksortWidget();
    }

    // Set initial values and animation speed
    barWidget->setValues(values);
    barWidget->setAnimationSpeed(controlsWidget->getSpeedSlider()->value());
    plotsLayout->addWidget(barWidget);
    barWidgets.append(barWidget);

    // Connect UI
    QObject::connect(controlsWidget->getSpeedSlider(),
                     &QSlider::valueChanged,
                     barWidget,
                     &BarPlotWidget::setAnimationSpeed);
  }

  // On "Start", reset all to new common values and start animation
  QObject::connect(controlsWidget->getStartButton(), &QPushButton::clicked, [&]() {
    auto newValues = utils::generateValues(controlsWidget->getSizeBox()->value());
    for (auto *barWidget : barWidgets) {
      barWidget->setValues(newValues);
      barWidget->startSortAnimation();
    }
  });

  window.show();
  return QApplication::exec();
}
