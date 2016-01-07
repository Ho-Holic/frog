// self
#include "LibraryImportWidget.h"
#include "LibraryViewWidget.h"
#include "LibraryAddWidget.h"
#include "LibraryItemData.h"
#include "LibraryModel.h"

// tmp
#include <QDebug>

nsSettingSpider::LibraryImportWidget::LibraryImportWidget(QWidget* parent)
: QStackedWidget(parent)
, mModel(new LibraryModel(this)) {

  LibraryViewWidget* libView = new LibraryViewWidget(this);
  libView->setModel(mModel);

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

void nsSettingSpider::LibraryImportWidget::switchToLibraryViewMode() {
  setCurrentIndex(LibraryViewMode);  
}

void nsSettingSpider::LibraryImportWidget::switchToLibraryAddMode() {
  setCurrentIndex(LibraryAddMode);
}


