#ifndef SETTINGSPIDER_MAINWINDOW_H
#define SETTINGSPIDER_MAINWINDOW_H

// qt
#include <QMainWindow>

// self
#include "world/World.h"

namespace nsSettingSpider {

  class World;
  class GraphWidget;
  class LibraryImportWidget;

  class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    MainWindow(QWidget* parent = 0);
  signals:
    void onSaveTo(const QString&);
    void onSetWorldAcceptDeletes(bool);
  private slots:
    void onSaveClicked();
    void dispatchWorldMode(World::Mode mode);
  private:
    void connectParts(World* world,
                      GraphWidget* graphWidget);      
  };

}

#endif // SETTINGSPIDER_MAINWINDOW_H
