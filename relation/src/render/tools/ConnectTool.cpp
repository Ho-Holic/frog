// self
#include "ConnectTool.h"
#include "world/Entity.h"

// tmp
#include <QDebug>

nsRelation::ConnectTool::ConnectTool(QObject* parent)
: Tool(parent)
, mRelationType(Relation::Needed)
, mPendingConnection()
, mConnectMode (Idle) {
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

void nsRelation::ConnectTool::setConnectMode(nsRelation::ConnectTool::ConnectMode mode) {
  mConnectMode = mode;
}

void nsRelation::ConnectTool::beginTouch(const QPoint& pos) {  

  Tool::beginTouch(pos);

  if (mConnectMode == AboutToDisconnect) {

    Q_ASSERT( ! selection().empty());
    Entity* current = selection().front();

    Q_ASSERT( ! current->inRelations(mRelationType).empty());

    Entity* entity = current->inRelations(mRelationType).front();
    current->inDetach(mRelationType, entity);
    entity->outDetach(mRelationType, current);

    this->reset();
    this->addToSelection(entity);

  }
}

void nsRelation::ConnectTool::move(const QPoint& from, const QPoint& to) {

  Tool::move(from, to);

  Q_ASSERT( ! selection().empty());

  Entity* current = selection().front();
  mPendingConnection = Connection(mRelationType, current);
}

void nsRelation::ConnectTool::endTouch(const QPoint& pos) {

  Tool::endTouch(pos);

  if (mConnectMode == AboutToConnect) {

    Q_ASSERT(selection().size() > 1); // we need two to perform connection

    Entity* parent = selection().at(0);
    Entity* child = selection().at(1);

    if (parent == child) return; // skip self

    if (child->rect().contains(pos)) {
      child->inAttach(mRelationType, parent);
      parent->outAttach(mRelationType, child);
    }

    this->reset();
    this->addToSelection(parent);
    this->addToSelection(child);
  }
}

void nsRelation::ConnectTool::reset() {  

  Tool::reset();
  mConnectMode = Idle;
  mPendingConnection = Connection(); // remove extra draw of edge on graph
}
