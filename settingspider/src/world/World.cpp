// self
#include "World.h"

// qt
#include <QRect>

// common
#include "cplusplus11.h"

nsSettingSpider::World::World(QObject* parent)
: QObject(parent)
, mOrigin(0, 0)
, mRelationType(Relation::Needed)
, mMode(Idle)
, mEntityList()
, mTouchFunction(&emptyTouch)
, mMoveFunction(&emptyMove)
, mFinalizeFunction(&emptyFinalize)
, mActiveEntity(nullptr)
, mPendingConnection() {
  //
}

nsSettingSpider::World::~World() {
  for (EntityList::Iterator i = mEntityList.begin(); i != mEntityList.end(); ++i) {
    Entity* entity = (*i);
    delete entity;
    (*i) = nullptr;
  }
  mEntityList.clear();
}

void nsSettingSpider::World::reportStatus() {

  // send entities
  for (EntityList::const_iterator i = mEntityList.begin(); i != mEntityList.end(); ++i) {
    Entity* entity = *i;
    emit onEntityChanged(entity);
  }

  // send connections. must be after entities or draw would paint block over connections
  // also this separeta processing of entities and connections
  for (EntityList::const_iterator i = mEntityList.begin(); i != mEntityList.end(); ++i) {
    Entity* entity = *i;
    reportRelations(entity);
  }

  // send pending
  if ((mMode == PendingConnection || mMode == EditConnection) && ! mPendingConnection.isNull()) {
    emit onConnectionChanged(&mPendingConnection);
  }
}

void nsSettingSpider::World::saveTo(const QString& path) const {
  //
}

void nsSettingSpider::World::loadFrom(const QString& path) {
  //
}

void nsSettingSpider::World::reportRelations(const nsSettingSpider::Entity* from) {

  const Entity::RelationBinding& allRelations = from->outRelations();

  for (Entity::RelationBinding::const_iterator relation = allRelations.begin(); relation != allRelations.end(); ++relation) {

    const Entity::RelationList& list = relation.value();

    for (Entity::RelationList::const_iterator i = list.begin(); i != list.end(); ++i) {
      const Entity* to = *i;
      Connection connection = Connection(relation.key(),
                                         from->rect().bottomLeft() + QPoint(from->rect().width()/2, 0),
                                         to->connectionSlotRect());
      emit onConnectionChanged(&connection);
    }
  }

}

void nsSettingSpider::World::emptyTouch(const QPoint& pos) {
  Q_UNUSED(pos);
}

void nsSettingSpider::World::createEntityAt(const QPoint& center) {
  Entity* entity = new Entity(withoutOrigin(center), tr("unnamed"));
  mEntityList.push_front(entity);
}

void nsSettingSpider::World::createEntityAt(const QPoint& center, const QString& data) {

  QStringList list = data.split(";", QString::SkipEmptyParts);

  foreach(const QString& path, list) {
    Entity* entity = new Entity(withoutOrigin(center), path);
    mEntityList.push_front(entity);
  }
}

void nsSettingSpider::World::destroyActiveEntity(const QPoint& pos) {

  bool isDelete = mActiveEntity && mActiveEntity->rect().contains(withoutOrigin(pos));
  if (isDelete) {
    destroyEntity(mActiveEntity);
  }
}

void nsSettingSpider::World::destroyEntity(nsSettingSpider::Entity* entity) {

  const nsSettingSpider::Entity::RelationBinding& inRelations = entity->inRelations();
  for (Entity::RelationBinding::const_iterator relation = inRelations.begin(); relation != inRelations.end(); ++relation) {

    const Entity::RelationList& list = relation.value();

    for (Entity::RelationList::const_iterator i = list.begin(); i != list.end(); ++i) {
      Entity* parent = *i;
      parent->outDetach(relation.key(), entity);
    }
  }

  const nsSettingSpider::Entity::RelationBinding& outRelations = entity->outRelations();
  for (Entity::RelationBinding::const_iterator relation = outRelations.begin(); relation != outRelations.end(); ++relation) {

    const Entity::RelationList& list = relation.value();

    for (Entity::RelationList::const_iterator i = list.begin(); i != list.end(); ++i) {
      Entity* child = *i;
      child->inDetach(relation.key(), entity);
    }
  }

  int removed = mEntityList.removeAll(entity);
  Q_ASSERT(removed == 1 || removed == 0);
  Q_UNUSED(removed);
}

void nsSettingSpider::World::activateMode(const QPoint& pos) {
  for (EntityList::iterator i = mEntityList.begin(); i != mEntityList.end(); ++i) {
    Entity* entity = *i;
    if ( entity->hasInRelations(mRelationType) && entity->connectionSlotRect().contains(withoutOrigin(pos))) {
      connectEditMode(entity);
      break;
    }
    else if (entity->connectionRect().contains(withoutOrigin(pos))) {
      connectMode(entity);
      break;
    }
    else if (entity->rect().contains(withoutOrigin(pos))) {
      moveMode(entity);
      break;
    }
  }
  if (mMode == Idle) { // if no other mode was selected use move origin
    originMode();
  }

  emit onModeChange(mMode);

  touchCall(withoutOrigin(pos));
}

void nsSettingSpider::World::deactivateMode(const QPoint& pos) {
  finalizeCall(withoutOrigin(pos));
  idleMode();
  emit onModeChange(mMode);
}

void nsSettingSpider::World::moveInWorld(const QPoint& from, const QPoint& to) {
  moveCall(withoutOrigin(from), withoutOrigin(to));
}

void nsSettingSpider::World::moveMode(Entity* entity) {
  mMode = EntityMove;
  mTouchFunction = &emptyTouch;
  mMoveFunction = &moveEntity;
  mFinalizeFunction = &emptyFinalize;
  mActiveEntity = entity;
  mPendingConnection = Connection();
}

void nsSettingSpider::World::connectMode(Entity* entity) {
  mMode = PendingConnection;
  mTouchFunction = &emptyTouch;
  mMoveFunction = &connectEntity;
  mFinalizeFunction = &connectFinalize;
  mActiveEntity = entity;
  mPendingConnection = Connection();
}

void nsSettingSpider::World::connectEditMode(nsSettingSpider::Entity* entity) {
  mMode = EditConnection;
  mTouchFunction = &emptyTouch;
  mMoveFunction = &moveConnectEdit;
  mFinalizeFunction = &emptyFinalize;
  mActiveEntity = entity;
  mPendingConnection = Connection();
}

void nsSettingSpider::World::idleMode() {  
  mMode = Idle;
  mTouchFunction = &emptyTouch;
  mMoveFunction = &emptyMove;
  mFinalizeFunction = &emptyFinalize;
  mActiveEntity = nullptr;
  mPendingConnection = Connection();
}

void nsSettingSpider::World::originMode() {
  mMode = OriginMove;
  mTouchFunction = &emptyTouch;
  mMoveFunction = &moveOrigin;
  mFinalizeFunction = &emptyFinalize;
  mActiveEntity = nullptr;
  mPendingConnection = Connection();
}




void nsSettingSpider::World::touchCall(const QPoint& pos) {
  (*this.*mTouchFunction)(pos);
}

void nsSettingSpider::World::moveCall(const QPoint& from, const QPoint& to) {
  (*this.*mMoveFunction)(from,to);
}


void nsSettingSpider::World::finalizeCall(const QPoint& pos) {
  (*this.*mFinalizeFunction)(pos);
}

void nsSettingSpider::World::changeRelationType(const nsSettingSpider::RelationType& relationType) {
  mRelationType = relationType;
}

void nsSettingSpider::World::emptyMove(const QPoint& from, const QPoint& to) {
  Q_UNUSED(from);
  Q_UNUSED(to);
}

void nsSettingSpider::World::moveOrigin(const QPoint& from, const QPoint& to) {
  mOrigin += to - from;
  emit onOriginChanged(mOrigin);
}

void nsSettingSpider::World::moveEntity(const QPoint& from, const QPoint& to) {
  Q_ASSERT(mActiveEntity != nullptr);
  mActiveEntity->setTopLeft(to - from + mActiveEntity->rect().topLeft());
}

void nsSettingSpider::World::connectEntity(const QPoint& from, const QPoint& to) {
  Q_UNUSED(from);
  QRect connectionRect = mActiveEntity->connectionRect();
  mPendingConnection = Connection(mRelationType,
                                  connectionRect.bottomLeft() + QPoint(connectionRect.width() / 2, 0),
                                  QRect(to, QSize(10, 10)));
}

void nsSettingSpider::World::emptyFinalize(const QPoint& pos) {
  Q_UNUSED(pos);
}

void nsSettingSpider::World::connectFinalize(const QPoint& pos) {

  for (EntityList::iterator i = mEntityList.begin(); i != mEntityList.end(); ++i) {
    Entity* entity = *i;
    if (entity == mActiveEntity) continue; // skip self
    if (entity->rect().contains(pos)) {
      entity->inAttach(mRelationType, mActiveEntity);
      mActiveEntity->outAttach(mRelationType, entity);
    }
  }
}

void nsSettingSpider::World::moveConnectEdit(const QPoint& from, const QPoint& to) {
  Q_UNUSED(to);
  Q_UNUSED(from);
  Q_ASSERT( ! mActiveEntity->inRelations(mRelationType).empty());

  Entity* entity = mActiveEntity->inRelations(mRelationType).front();
  mActiveEntity->inDetach(mRelationType, entity);
  entity->outDetach(mRelationType, mActiveEntity);

  connectMode(entity);
  emit onModeChange(mMode);
}

int nsSettingSpider::World::withoutOriginY(int y) const {
  return y - mOrigin.y();
}

QRect nsSettingSpider::World::withoutOrigin(const QRect& r) const {
  return QRect(r.topLeft() - mOrigin, r.size());
}

QPoint nsSettingSpider::World::withoutOrigin(const QPoint& p) const {
  return p - mOrigin;
}

nsSettingSpider::World::EntityList::size_type
nsSettingSpider::World::entityCount() const {
  return mEntityList.size();
}

nsSettingSpider::Entity* nsSettingSpider::World::entityAt(EntityList::size_type index) const {
  return mEntityList.at(index);
}


