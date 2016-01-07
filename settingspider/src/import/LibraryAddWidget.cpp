// self
#include "LibraryAddWidget.h"
#include "LibraryItemData.h"

// qt
#include <QTreeView>
#include <QFileSystemModel>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QSlider>

// common
#include "cplusplus11.h"

// tmp
#include <QDebug>

nsSettingSpider::LibraryAddWidget::LibraryAddWidget(QWidget* parent)
: QWidget(parent)
, mFileSystemModel(nullptr)
, mPathLabel(nullptr)
, mPathSlider(nullptr)
, mPath()
, mPathForAddition(mPath) {

  QGridLayout* layout = new QGridLayout(this);
  layout->setMargin(0);

  QFileSystemModel* model = new QFileSystemModel(this);
  model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Drives | QDir::AllDirs);
  QModelIndex index = model->setRootPath(mPath);

  QTreeView* tree = new QTreeView(this);
  tree->setModel(model);
  tree->setRootIndex(index);

  // hide columns
  for (int i = 1; i < model->columnCount(); ++i) {
    tree->hideColumn(i);
  }

  QLabel* pathCaption = new QLabel("<b>Part of the path:</b>", this);
  QLabel* pathText = new QLabel(mPath, this);

  QPushButton* add = new QPushButton("Add", this);
  QPushButton* cancel = new QPushButton("Cancel", this);
  QSlider* slider = new QSlider(Qt::Horizontal, this);
  slider->setRange(0, 0);

  layout->addWidget(tree,        0, 0, 1, 2);
  layout->addWidget(pathCaption, 1, 0, 1, 2);
  layout->addWidget(pathText,    2, 0, 1, 2);
  layout->addWidget(slider,      3, 0, 1, 2);
  layout->addWidget(add,         4, 0);
  layout->addWidget(cancel,      4, 1);

  connect(add,    SIGNAL(clicked()),
          this,   SLOT(addLibrary()));

  connect(cancel, SIGNAL(clicked()),
          this,   SIGNAL(onCancelClicked()));

  connect(tree,   SIGNAL(clicked(const QModelIndex&)),
          this,   SLOT(libraryPathChanged(const QModelIndex&)));

  connect(slider, SIGNAL(sliderMoved(int)),
          this,   SLOT(dividePathAt(int)));

  mFileSystemModel = model;
  mPathLabel = pathText;
  mPathSlider = slider;
}

void nsSettingSpider::LibraryAddWidget::libraryPathChanged(const QModelIndex& index) {

  mPath = QDir::fromNativeSeparators(QDir(mFileSystemModel->filePath(index)).absolutePath());

  // we can cache old slider position, if it resets
  int parts = mPath.split("/", QString::SkipEmptyParts).size();

  if (mPath.startsWith('/')) {
    // unix hack, sorry ((
    // try to find other solution
    // problem is:
    // "C:/test/123" (win) has "parts = 3" with SkipEmptyParts mode
    // "/test/123"   (nix) has "parts = 2", but we need 3 with SkipEmptyParts mode

    parts += 1;
  }

  // don't use "parts - 1", because we need extra state
  // see LibraryAddWidget::dividePathAt
  mPathSlider->setRange(0, parts);

  dividePathAt(mPathSlider->value());
}

void nsSettingSpider::LibraryAddWidget::addLibrary() {

  if (mPath.isEmpty()) return;

  emit onPathAddition(LibraryItemData(mPath, mPathForAddition));
  emit onCancelClicked();
}

void nsSettingSpider::LibraryAddWidget::dividePathAt(int pos) {

  // Some explanations:
  //
  //    C:/123/cat (win path)
  //      /123/cat (nix path)

  //    | 0  |  1  |  2   |  3  |  <- pos variable
  //    |    | C:/ | 123/ | cat |  <- what part of path to exclude
  //    |    |   / | 123/ | cat |

  //    0 - use full path     e.g. C:/123/cat
  //    1 - path without root e.g. 123/cat
  //    2 - path w/o 123      e.g. cat
  //    3 - only file name, path = ""

  // windows path don't start with "/", so need generic workaround

  if (pos > 0) {

    int sectionsLeft = pos;
    int splitPos = mPath.size();
    for (int strPos = 0; strPos < mPath.size(); ++strPos) {
      if (mPath.at(strPos) == '/') {
        sectionsLeft -= 1;
      }
      if (sectionsLeft == 0) {
        splitPos = strPos;
        break;
      }
    }

    QString left = mPath.left(splitPos + 1);
    QString right = mPath.mid(splitPos + 1);


    QColor rightColor = mPathLabel->palette().color(QPalette::Text);
    QColor leftColor((rightColor.red()   + 255) / 1.5,
                     (rightColor.green() + 255) / 1.5,
                     (rightColor.blue()  + 255) / 1.5);

    QString coloredPath = QString("<font color=\"%1\">%2</font><font color=\"%3\">%4</font>")
                          .arg(leftColor.name())
                          .arg(left)
                          .arg(rightColor.name())
                          .arg(right);

    mPathForAddition = right;
    mPathLabel->setText(coloredPath);

  }
  else {
    mPathForAddition = mPath;
    mPathLabel->setText(mPath);
  }


}
