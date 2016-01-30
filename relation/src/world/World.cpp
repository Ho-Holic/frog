// self
#include "World.h"
#include "WorldEvent.h"

// qt
#include <QRect>
#include <QtAlgorithms>

// common
#include "cplusplus11.h"

nsRelation::World::World(QObject* parent)
: QObject(parent)
, mEntityList() {
  //
}

nsRelation::World::~World() {

  qDeleteAll(mEntityList);
}

void nsRelation::World::inspectWorldAt(const QPoint& pos) {

  QScopedPointer<WorldEvent> event(selectApropriateEventFor(pos));
  emit onWorldInspectEvent(event.data()); 
}

nsRelation::WorldEvent* nsRelation::World::selectApropriateEventFor(const QPoint& pos) {

  // TODO: create generate_if(mEntityList.begin(), mEntityList.end(), DefaultSpawnedValue, &predicate);
  // where predicate is  "pair<SpawnedValue, bool> predicate(CollectionElement e) {...}
  // pair<SpawnedValue, true> if bool = true then  SpawnedValue returned from "generate_if"
  // otherwise pair<???, false> and search continues
  // if no match then find return DefaultSpawnedValue

  // improve API ^

  for (EntityList::iterator i = mEntityList.begin(); i != mEntityList.end(); ++i) {

    Entity* entity = *i;    

    if (entity->connectionSlotRect().contains(pos)) {
      return new WorldEvent(WorldEvent::EntityIncomingSlot, entity);
      break;
    }
    else if (entity->connectionRect().contains(pos)) {
      return new WorldEvent(WorldEvent::EntityOutcomingSlot, entity);
      break;
    }
    else if (entity->rect().contains(pos)) {
      return new WorldEvent(WorldEvent::EntityBody, entity);
      break;
    }
  }

  return new WorldEvent(WorldEvent::Nothing);
}

void nsRelation::World::reportStatus(const QString& replyId) {

  // send entities
  for (EntityList::const_iterator i = mEntityList.begin(); i != mEntityList.end(); ++i) {
    Entity* entity = *i;
    emit onEntityChanged(replyId, entity);
  }

  // send connections. must be after entities or draw would paint block over connections
  // also this separeta processing of entities and connections
  for (EntityList::const_iterator i = mEntityList.begin(); i != mEntityList.end(); ++i) {
    Entity* entity = *i;
    reportRelations(replyId, entity);
  }


}


void nsRelation::World::reportRelations(const QString& replyId, const nsRelation::Entity* from) {

  // TODO: add foreach

  const Entity::RelationBinding& allRelations = from->outRelations();

  for (Entity::RelationBinding::const_iterator relation = allRelations.begin(); relation != allRelations.end(); ++relation) {

    const Entity::RelationList& list = relation.value();

    for (Entity::RelationList::const_iterator i = list.begin(); i != list.end(); ++i) {
      const Entity* to = *i;
      Connection connection = Connection(relation.key(),
                                         from->rect().bottomLeft() + QPoint(from->rect().width()/2, 0),
                                         to->connectionSlotRect());
      emit onConnectionChanged(replyId, &connection);
    }
  }

}

void nsRelation::World::createEntityAt(const QPoint& center) {
  Entity* entity = new Entity(center, tr("unnamed"));
  mEntityList.push_front(entity);
}

void nsRelation::World::createEntityAt(const QPoint& center, const QString& data) {

  QStringList list = data.split(";", QString::SkipEmptyParts);

  foreach(const QString& path, list) {
    Entity* entity = new Entity(center, path);
    mEntityList.push_front(entity);
  }
}

void nsRelation::World::destroyEntity(nsRelation::Entity* entity) {

  const nsRelation::Entity::RelationBinding& inRelations = entity->inRelations();
  for (Entity::RelationBinding::const_iterator relation = inRelations.begin(); relation != inRelations.end(); ++relation) {

    const Entity::RelationList& list = relation.value();

    for (Entity::RelationList::const_iterator i = list.begin(); i != list.end(); ++i) {
      Entity* parent = *i;
      parent->outDetach(relation.key(), entity);
    }
  }

  const nsRelation::Entity::RelationBinding& outRelations = entity->outRelations();
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

nsRelation::World::EntityList::size_type
nsRelation::World::entityCount() const {
  return mEntityList.size();
}

nsRelation::Entity* nsRelation::World::entityAt(EntityList::size_type index) const {
  return mEntityList.at(index);
}
