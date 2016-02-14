// self
#include "ConnectTool.h"

nsRelation::ConnectTool::ConnectTool()
: Tool() {
  //
}

void nsRelation::ConnectTool::beginTouch(const QPoint& pos) {
  Q_UNUSED(pos);

  Q_ASSERT( ! mSelectedEntities.empty());
  Entity* current = mSelectedEntities.front();

  Q_ASSERT( ! current->inRelations(mRelationType).empty());

  Entity* entity = current->inRelations(mRelationType).front();
  current->inDetach(mRelationType, entity);
  entity->outDetach(mRelationType, current);

  idleMode(); // clean up and go as if we just connect entities

  connectMode(entity);
}

void nsRelation::ConnectTool::move(const QPoint& from, const QPoint& to) {
  Q_UNUSED(from);
  Q_UNUSED(to);

  Q_ASSERT( ! mSelectedEntities.empty());

  Entity* current = mSelectedEntities.front();
  mPendingConnection = Connection(mRelationType, current);
}

void nsRelation::ConnectTool::endTouch(const QPoint& pos) {
  Q_ASSERT(mSelectedEntities.size() > 1); // we need two to perform connection

  Entity* parent = mSelectedEntities.at(0);
  Entity* child = mSelectedEntities.at(1);

  if (parent == child) return; // skip self

  if (child->rect().contains(withoutOrigin(pos))) {
    child->inAttach(mRelationType, parent);
    parent->outAttach(mRelationType, child);
  }
}
