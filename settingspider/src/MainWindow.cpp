#include "MainWindow.h"

// qt
#include <QLayout>
#include <QTimer>

// self
#include "GraphWidget.h"
#include "World.h"
#include "LibraryImportWidget.h"

nsSettingSpider::MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent) {

  QWidget* widget = new QWidget(this);

  World* world = new World(widget);
  GraphWidget* graphWidget = new GraphWidget(widget);
  LibraryImportWidget* libraryImport = new LibraryImportWidget(widget);

  QHBoxLayout* layout = new QHBoxLayout(widget);  
  layout->addWidget(graphWidget, 100);
  layout->addWidget(libraryImport, 30);

  setCentralWidget(widget);

  connectParts(world, graphWidget, libraryImport);
}

void nsSettingSpider::MainWindow::connectParts(nsSettingSpider::World* world,
                                               nsSettingSpider::GraphWidget* graphWidget,
                                               LibraryImportWidget* libraryImport) {
  connect(world,       SIGNAL(entityChanged(Entity*)),
          graphWidget, SLOT(drawEntity(Entity*)));

  connect(world,       SIGNAL(connectionChanged(Connection*)),
          graphWidget, SLOT(drawConnection(Connection*)));

  connect(world,       SIGNAL(deleteAreaChanged(bool)),
          graphWidget, SLOT(drawDeleteArea(bool)));

  connect(world,       SIGNAL(originChanged(const QPoint&)),
          graphWidget, SLOT(setOrigin(const QPoint&)));

  connect(graphWidget, SIGNAL(updateScene()),
          world,       SLOT(reportStatus()));

  connect(graphWidget, SIGNAL(onDoubleClick(const QPoint&)),
          world,       SLOT(createEntityAt(const QPoint&)));

  connect(graphWidget, SIGNAL(onMousePress(const QPoint&)),
          world,       SLOT(activateMode(const QPoint&)));

  connect(graphWidget, SIGNAL(onMouseRelease(const QPoint&)),
          world,       SLOT(deactivateMode(const QPoint&)));

  connect(graphWidget, SIGNAL(onMouseMove(const QPoint&, const QPoint&)),
          world,       SLOT(moveInWorld(const QPoint&, const QPoint&)));

  connect(graphWidget, SIGNAL(onRelationTypeChange(const RelationType&)),
          world,       SLOT(changeRelationType(const RelationType&)));
}


