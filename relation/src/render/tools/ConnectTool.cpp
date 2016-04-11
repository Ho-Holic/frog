// self
#include "ConnectTool.h"
#include "world/Entity.h"

nsRelation::ConnectTool::ConnectTool(QObject* parent)
: Tool(parent)
, mRelationType(Relation::Needed)
, mPendingConnection() {
  //
}

nsRelation::RelationType nsRelation::ConnectTool::relationType() const {
  return mRelationType;
}

void nsRelation::ConnectTool::setRelationType(const nsRelation::RelationType& type) {
  mRelationType = type;
}

nsRelation::Connection nsRelation::ConnectTool::pendingConnection() const {
  return mPendingConnection;
}

void nsRelation::ConnectTool::beginTouch(const QPoint& pos) {
  Q_UNUSED(pos);

  Q_ASSERT( ! selection().empty());
  Entity* current = selection().front();

  Q_ASSERT( ! current->inRelations(mRelationType).empty());

  Entity* entity = current->inRelations(mRelationType).front();
  current->inDetach(mRelationType, entity);
  entity->outDetach(mRelationType, current);

#warning idleMode(); // clean up and go as if we just connect entities
#warning connectMode(entity);
  emit changeTool(ConnectType, entity);
}

void nsRelation::ConnectTool::move(const QPoint& from, const QPoint& to) {
  Q_UNUSED(from);
  Q_UNUSED(to);

  Q_ASSERT( ! selection().empty());

  Entity* current = selection().front();
  mPendingConnection = Connection(mRelationType, current);
}

void nsRelation::ConnectTool::endTouch(const QPoint& pos) {
  Q_ASSERT(selection().size() > 1); // we need two to perform connection

  Entity* parent = selection().at(0);
  Entity* child = selection().at(1);

  if (parent == child) return; // skip self  

#warning "if (child->rect().contains(withoutOrigin(pos))) {"
  if (child->rect().contains(pos)) {
    child->inAttach(mRelationType, parent);
    parent->outAttach(mRelationType, child);
  }
}
