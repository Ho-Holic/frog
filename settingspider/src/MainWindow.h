#ifndef SETTINGSPIDER_MAINWINDOW_H
#define SETTINGSPIDER_MAINWINDOW_H

// qt
#include <QMainWindow>

// self
#include "GraphWidget.h"
#include "World.h"

namespace nsSettingSpider {

  class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    MainWindow(QWidget* parent = 0);
  };

}

#endif // SETTINGSPIDER_MAINWINDOW_H
