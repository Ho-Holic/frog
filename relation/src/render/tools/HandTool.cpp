// self
#include "HandTool.h"

nsRelation::HandTool::HandTool(QObject* parent)
: Tool(parent) {

  // this stuff would be generic
  QString item1 = tr("Module");
  QString item2 = tr("Bridge");
  this->addToMarkingMenu(item1);
  this->addToMarkingMenu(item2);
}


void nsRelation::HandTool::move(const QPoint& from, const QPoint& to) {

  Tool::move(from, to);

  this->setOrigin(this->origin() + (to - from));

  emit onOriginChanged(this->origin()); // TODO: maybe no need for now?
}


