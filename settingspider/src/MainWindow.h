#ifndef SETTINGSPIDER_MAINWINDOW_H
#define SETTINGSPIDER_MAINWINDOW_H

// qt
#include <QMainWindow>

namespace nsSettingSpider {

  class World;
  class GraphWidget;
  class LibraryImportWidget;

  class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    MainWindow(QWidget* parent = 0);
  private:
    void connectParts(World* world,
                      GraphWidget* graphWidget,
                      LibraryImportWidget* libraryImport);
  };

}

#endif // SETTINGSPIDER_MAINWINDOW_H
