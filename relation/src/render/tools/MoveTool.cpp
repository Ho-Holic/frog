// self
#include "MoveTool.h"

nsRelation::MoveTool::MoveTool(QObject* parent)
: Tool(parent) {
  //
}

void nsRelation::MoveTool::move(const QPoint& from, const QPoint& to) {
  Q_ASSERT( ! mSelectedEntities.empty());
  Entity* current = mSelectedEntities.front();
  current->setTopLeft(withoutOrigin(to) - withoutOrigin(from) + current->rect().topLeft());
}

void nsRelation::MoveTool::endTouch(const QPoint& pos) {
  Q_ASSERT( ! mSelectedEntities.empty());
  Entity* current = mSelectedEntities.front();

  bool isDelete =  (mIsDeleteAllowed)
                && (pos.y() < DeleteRectHeight)
                && (current)
                && (current->rect().contains(withoutOrigin(pos)));

  if (isDelete) {
    emit onDestroyRequest(current);
    //QString stringData = QString("removeById %1").arg(mActiveEntity->idString());
    //emit onDestroyRequest(stringData);
  }
}
