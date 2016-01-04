// self
#include "LibraryImportWidget.h"
#include "LibraryAddWidget.h"

// qt
#include <QVBoxLayout>
#include <QMenu>
#include <QHeaderView>
#include <QTreeWidget>

// common
#include "cplusplus11.h"

// tmp
#include <QDebug>

#warning write my model for libView

nsSettingSpider::LibraryImportWidget::LibraryImportWidget(QWidget* parent)
: QStackedWidget(parent)
, mLibraryView(nullptr) {

  QTreeWidget* libView = createLibraryViewWidget(this);
  LibraryAddWidget* libAdd = createLibraryAddWidget(this);

  addWidget(libView);
  addWidget(libAdd);

  mLibraryView = libView;
}

QTreeWidget* nsSettingSpider::LibraryImportWidget::createLibraryViewWidget(QWidget* parent) {
  QTreeWidget* tree = new QTreeWidget(parent);
  tree->setHeaderLabel("Libraries");
  tree->setContextMenuPolicy(Qt::CustomContextMenu);

  connect(tree,   SIGNAL(customContextMenuRequested(const QPoint&)),
          parent, SLOT(createMenuAt(const QPoint&)));

  return tree;
}

nsSettingSpider::LibraryAddWidget* nsSettingSpider::LibraryImportWidget::createLibraryAddWidget(QWidget* parent) {
  LibraryAddWidget* tree = new LibraryAddWidget(parent);

  connect(tree,   SIGNAL(onCancelClicked()),
          parent, SLOT(switchToLibraryViewMode()));

  return tree;
}

void nsSettingSpider::LibraryImportWidget::createMenuAt(const QPoint& pos) {

  QMenu* menu = new QMenu(this);
  QAction* addAction = new QAction("Add library folder", this);

  connect(addAction, SIGNAL(triggered()),
          this,      SLOT(switchToLibraryAddMode()));

  menu->addAction(addAction);
  menu->popup(mLibraryView->viewport()->mapToGlobal(pos));
}

void nsSettingSpider::LibraryImportWidget::switchToLibraryViewMode() {
  setCurrentIndex(LibraryViewMode);
}

void nsSettingSpider::LibraryImportWidget::switchToLibraryAddMode() {
  setCurrentIndex(LibraryAddMode);
}


