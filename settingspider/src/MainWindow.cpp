#include "MainWindow.h"

// qt
#include <QLayout>
#include <QTimer>
#include <QSplitter>
#include <QMenuBar>
#include <QFileDialog>

// self
#include "world/World.h"
#include "render/GraphWidget.h"
#include "import/LibraryImportWidget.h"
#include "convert/Convertor.h"

// tmp
#include <QDebug>

nsSettingSpider::MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent) {

  QWidget* widget = new QWidget(this);

  QHBoxLayout* layout = new QHBoxLayout(widget);
  QSplitter* splitter = new QSplitter(widget);

  World* world = new World(splitter);
  Convertor* convertor = new Convertor(splitter);
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

  fileMenu->addAction(tr("&Save As..."),
                      this, SLOT(onSaveClicked()),
                      QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));

  QMenu* exportMenu = fileMenu->addMenu(tr("&Export"));

  exportMenu->addAction(tr("&Graphviz"),
                        this, SLOT(onSaveClicked()),
                        QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_G));

  exportMenu->addAction(tr("&PostgreSQL"),
                        this, SLOT(onSaveClicked()),
                        QKeySequence(Qt::CTRL + Qt::SHIFT +  Qt::Key_Q));

  QMenu* libraryMenu = menu->addMenu(tr("&Library"));

  libraryMenu->addAction(tr("&Add library folder"),
                         libraryImport, SLOT(switchToLibraryAddMode()),
                         QKeySequence(Qt::CTRL + Qt::Key_L));

  setMenuBar(menu);

  connectParts(world, graphWidget, convertor);
}

void nsSettingSpider::MainWindow::onSaveClicked() {

  QString path = QFileDialog::getSaveFileName(this, tr("Save As"), QString(), tr("Relation Files (*.rel)"));
  if ( ! path.isEmpty()) {
    emit onSaveTo(path);
  }
}

void nsSettingSpider::MainWindow::connectParts(nsSettingSpider::World* world,
                                               nsSettingSpider::GraphWidget* graphWidget,
                                               nsSettingSpider::Convertor* convertor) {

  connect(world,       SIGNAL(onEntityChanged(const QString&, Entity*)),
          graphWidget, SLOT(drawEntity(const QString&, Entity*)));

  connect(world,       SIGNAL(onConnectionChanged(const QString&, Connection*)),
          graphWidget, SLOT(drawConnection(const QString&, Connection*)));

  connect(world,       SIGNAL(onWorldInspectEvent(WorldEvent*)),
          graphWidget, SLOT(setModeDependOn(WorldEvent*)));

  connect(graphWidget, SIGNAL(onSceneUpdate(const QString&)),
          world,       SLOT(reportStatus(const QString&)));

  connect(graphWidget, SIGNAL(onDoubleClick(const QPoint&)),
          world,       SLOT(createEntityAt(const QPoint&)));

  connect(graphWidget, SIGNAL(onDrop(const QPoint&, const QString&)),
          world,       SLOT(createEntityAt(const QPoint&, const QString&)));

  connect(graphWidget, SIGNAL(onDestroyRequest(Entity*)),
          world,       SLOT(destroyEntity(Entity*)));

  connect(graphWidget, SIGNAL(onMousePress(const QPoint&)),
          world,       SLOT(inspectWorldAt(const QPoint&)));

  connect(graphWidget, SIGNAL(onMouseRelease(const QPoint&)),
          world,       SLOT(inspectWorldAt(const QPoint&)));

  connect(this,      SIGNAL(onSaveTo(const QString&)),
          convertor, SLOT(saveTo(const QString&)));

  connect(convertor, SIGNAL(onSaveRequestInformation(const QString&)),
          world,     SLOT(reportStatus(const QString&)));

  connect(world,     SIGNAL(onEntityChanged(const QString&, Entity*)),
          convertor, SLOT(saveEntity(const QString&, Entity*)));

  connect(world,     SIGNAL(onConnectionChanged(const QString&, Connection*)),
          convertor, SLOT(saveConnection(const QString&, Connection*)));

}


