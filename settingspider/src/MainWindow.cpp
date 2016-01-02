#include "MainWindow.h"

// qt
#include <QLayout>
#include <QTimer>

nsSettingSpider::MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent) {
  QWidget* widget = new QWidget(this);
  nsSettingSpider::World* world = new nsSettingSpider::World(widget);
  nsSettingSpider::GraphWidget* graphWidget = new nsSettingSpider::GraphWidget(widget);

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

  QHBoxLayout* layout = new QHBoxLayout(widget);  
  layout->addWidget(graphWidget);

  setCentralWidget(widget);
}


