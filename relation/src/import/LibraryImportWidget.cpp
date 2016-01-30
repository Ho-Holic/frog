// self
#include "LibraryImportWidget.h"
#include "LibraryViewWidget.h"
#include "LibraryAddWidget.h"
#include "LibraryItemData.h"
#include "LibraryModel.h"

// tmp
#include <QDebug>

nsRelation::LibraryImportWidget::LibraryImportWidget(QWidget* parent)
: QStackedWidget(parent)
, mModel(new LibraryModel(this)) {

  LibraryViewWidget* libView = new LibraryViewWidget(this);
  libView->setModel(mModel);
  libView->setSelectionMode(QAbstractItemView::ExtendedSelection);
  libView->setDragEnabled(true);

  connect(libView, SIGNAL(onLibraryAddClicked()),
          this,    SLOT(switchToLibraryAddMode()));

  LibraryAddWidget* libAdd = new LibraryAddWidget(this);

  connect(libAdd, SIGNAL(onPathAddition(const LibraryItemData&)),
          mModel, SLOT(addPath(const LibraryItemData&)));

  connect(libAdd, SIGNAL(onCancelClicked()),
          this,   SLOT(switchToLibraryViewMode()));

  addWidget(libView);
  addWidget(libAdd);


}

void nsRelation::LibraryImportWidget::switchToLibraryViewMode() {
  setCurrentIndex(LibraryViewMode);  
}

void nsRelation::LibraryImportWidget::switchToLibraryAddMode() {
  setCurrentIndex(LibraryAddMode);
}


