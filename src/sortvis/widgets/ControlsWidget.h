#pragma once
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QWidget>

class ControlsWidget : public QWidget {
 public:
  /**
   * Constructor for the ControlsWidget.
   * Initializes the layout and controls.
   *
   * @param parent The parent widget, defaults to nullptr.
   */
  explicit ControlsWidget(QWidget *parent = nullptr);

  /**
   * Getter for the controls layout.
   */
  [[nodiscard]] QHBoxLayout *getControlsLayout() const;

  /**
   * Getter for the start button.
   */
  [[nodiscard]] QPushButton *getStartButton() const;

  /**
   * Getter for the speed slider.
   */
  [[nodiscard]] QSlider *getSpeedSlider() const;

  /**
   * Getter for the size spin box.
   */
  [[nodiscard]] QSpinBox *getSizeBox() const;

 private:
  QHBoxLayout *controlsLayout;
  QPushButton *startButton;
  QSlider *speedSlider;
  QSpinBox *sizeBox;
};
