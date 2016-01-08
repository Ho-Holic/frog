#include "MainWindow.h"

// qt
#include <QLayout>
#include <QTimer>
#include <QSplitter>

// self
#include "render/GraphWidget.h"
#include "world/World.h"
#include "import/LibraryImportWidget.h"

nsSettingSpider::MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent) {

  QWidget* widget = new QWidget(this);

  QHBoxLayout* layout = new QHBoxLayout(widget);
  QSplitter* splitter = new QSplitter(widget);

  World* world = new World(splitter);
  GraphWidget* graphWidget = new GraphWidget(splitter);
  graphWidget->setAcceptDrops(true);

  LibraryImportWidget* libraryImport = new LibraryImportWidget(splitter);

  splitter->addWidget(graphWidget);
  splitter->addWidget(libraryImport);
  splitter->setStretchFactor(0, 80);
  splitter->setStretchFactor(1, 20);
  layout->addWidget(splitter);

  setCentralWidget(widget);

  connectParts(world, graphWidget);
}

void nsSettingSpider::MainWindow::connectParts(nsSettingSpider::World* world,
                                               nsSettingSpider::GraphWidget* graphWidget) {
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

  connect(graphWidget, SIGNAL(onDrop(const QPoint&, const QString&)),
          world,       SLOT(createEntityAt(const QPoint&, const QString&)));

  connect(graphWidget, SIGNAL(onMousePress(const QPoint&)),
          world,       SLOT(activateMode(const QPoint&)));

  connect(graphWidget, SIGNAL(onMouseRelease(const QPoint&)),
          world,       SLOT(deactivateMode(const QPoint&)));

  connect(graphWidget, SIGNAL(onMouseMove(const QPoint&, const QPoint&)),
          world,       SLOT(moveInWorld(const QPoint&, const QPoint&)));

  connect(graphWidget, SIGNAL(onRelationTypeChange(const RelationType&)),
          world,       SLOT(changeRelationType(const RelationType&)));
}


