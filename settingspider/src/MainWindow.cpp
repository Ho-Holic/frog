#include "MainWindow.h"

// qt
#include <QLayout>
#include <QTimer>
#include <QSplitter>
#include <QMenuBar>
#include <QFileDialog>

// self
#include "render/GraphWidget.h"
#include "import/LibraryImportWidget.h"

// tmp
#include <QDebug>

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

  QMenuBar* menu = new QMenuBar(this);
  QMenu* fileMenu = menu->addMenu(tr("&File"));
  fileMenu->addAction(tr("&Save As..."), this, SLOT(onSaveClicked()), QKeySequence(Qt::CTRL + Qt::Key_S));

  QMenu* exportMenu = fileMenu->addMenu(tr("&Export"));
  exportMenu->addAction(tr("&Graphviz"), this, SLOT(onSaveClicked()), QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_G));
  exportMenu->addAction(tr("&PostgreSQL"), this, SLOT(onSaveClicked()), QKeySequence(Qt::CTRL + Qt::SHIFT +  Qt::Key_Q));

  QMenu* libraryMenu = menu->addMenu(tr("&Library"));
  libraryMenu->addAction(tr("&Add library folder"), libraryImport, SLOT(switchToLibraryAddMode()), QKeySequence(Qt::CTRL + Qt::Key_L));

  setMenuBar(menu);

  connectParts(world, graphWidget);
}

void nsSettingSpider::MainWindow::onSaveClicked() {

  QString path = QFileDialog::getSaveFileName(this, tr("Save As"), QString(), tr("Relation Files (*.rel)"));
  if ( ! path.isEmpty()) {
    emit onSaveTo(path);
  }
}

void nsSettingSpider::MainWindow::onModeChange(World::Mode mode) {

  emit onSetWorldAcceptDeletes(mode == World::EntityMove);
}

void nsSettingSpider::MainWindow::connectParts(nsSettingSpider::World* world,
                                               nsSettingSpider::GraphWidget* graphWidget) {
  connect(world,       SIGNAL(entityChanged(Entity*)),
          graphWidget, SLOT(drawEntity(Entity*)));

  connect(world,       SIGNAL(connectionChanged(Connection*)),
          graphWidget, SLOT(drawConnection(Connection*)));  

  connect(world,       SIGNAL(originChanged(const QPoint&)),
          graphWidget, SLOT(setOrigin(const QPoint&)));    

  connect(graphWidget, SIGNAL(updateScene()),
          world,       SLOT(reportStatus()));

  connect(graphWidget, SIGNAL(onDoubleClick(const QPoint&)),
          world,       SLOT(createEntityAt(const QPoint&)));

  connect(graphWidget, SIGNAL(onInDeleteArea(const QPoint&)),
          world,       SLOT(destroyActiveEntity(const QPoint&)));

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

//  connect(this,  SIGNAL(onSaveTo(const QString&)),
//          world, SLOT());

  connect(world, SIGNAL(modeChanged(World::Mode)),
          this,  SLOT(onModeChange(World::Mode)));

  connect(this,        SIGNAL(onSetWorldAcceptDeletes(bool)),
          graphWidget, SLOT(setAcceptDeletes(bool)));
}


