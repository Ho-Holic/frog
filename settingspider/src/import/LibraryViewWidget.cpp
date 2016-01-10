// self
#include "LibraryViewWidget.h"

// qt
#include <QVBoxLayout>
#include <QMenu>
#include <QHeaderView>
#include <QTreeView>

nsSettingSpider::LibraryViewWidget::LibraryViewWidget(QWidget* parent)
: QTreeView(parent)  {

  setContextMenuPolicy(Qt::CustomContextMenu);

  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
                SLOT(createMenuAt(const QPoint&)));
}

void nsSettingSpider::LibraryViewWidget::createMenuAt(const QPoint& pos) {

  QMenu* menu = new QMenu(this);

  menu->addAction(tr("Add library folder"), this, SIGNAL(onLibraryAddClicked()));
  menu->popup(viewport()->mapToGlobal(pos));
}
