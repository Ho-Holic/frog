// self
#include "MoveTool.h"
#include "world/Entity.h"

nsRelation::MoveTool::MoveTool(QObject* parent)
: Tool(parent)
, mIsDeleteAllowed(false) {
  //
}

void nsRelation::MoveTool::move(const QPoint& from, const QPoint& to) {
  Q_ASSERT( ! this->selection().empty());
  Entity* current = this->selection().front();

#warning "current->setTopLeft(withoutOrigin(to) - withoutOrigin(from) + current->rect().topLeft());"
  current->setTopLeft(to - from + current->rect().topLeft());
}

void nsRelation::MoveTool::endTouch(const QPoint& pos) {
  Q_ASSERT( ! this->selection().empty());
  Entity* current = this->selection().front();

#warning " && (current->rect().contains(withoutOrigin(pos)));"
  bool isDelete =  (mIsDeleteAllowed)
                && (pos.y() < DeleteRectHeight)
                && (current)
                && (current->rect().contains(pos));

  if (isDelete) {
    emit onDestroyRequest(current);
    //QString stringData = QString("removeById %1").arg(mActiveEntity->idString());
    //emit onDestroyRequest(stringData);
  }
}
