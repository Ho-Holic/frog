#ifndef FROG_RELATION_MAINWINDOW_H
#define FROG_RELATION_MAINWINDOW_H

// qt
#include <QMainWindow>

// self
#include "world/World.h"

namespace nsRelation {

  class World;
  class GraphWidget;
  class LibraryImportWidget;
  class Convertor;

  class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    MainWindow(QWidget* parent = 0);
  signals:
    void onSaveTo(const QString&);
    void onLoadFrom(const QString&);
    void onSetWorldAcceptDeletes(bool);
  private slots:
    void onOpenClicked();
    void onSaveClicked();    
  private:
    void connectParts(World* world,
                      GraphWidget* graphWidget,
                      nsRelation::Convertor* convertor);
  };

}

#endif // FROG_RELATION_MAINWINDOW_H
