// self
#include "LibraryViewWidget.h"

// qt
#include <QVBoxLayout>
#include <QMenu>
#include <QHeaderView>
#include <QTreeView>

nsSettingSpider::LibraryViewWidget::LibraryViewWidget(QWidget* parent)
: QTreeView(parent)  {

  //setHeaderLabel("Libraries");
  setContextMenuPolicy(Qt::CustomContextMenu);

  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
                SLOT(createMenuAt(const QPoint&)));
}

void nsSettingSpider::LibraryViewWidget::createMenuAt(const QPoint& pos) {

  QMenu* menu = new QMenu(this);
  QAction* addAction = new QAction("Add library folder", this);

  connect(addAction, SIGNAL(triggered()),
          this,      SIGNAL(onLibraryAddClicked()));

  menu->addAction(addAction);
  menu->popup(viewport()->mapToGlobal(pos));
}
