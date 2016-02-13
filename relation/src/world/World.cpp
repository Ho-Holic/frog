// self
#include "World.h"
#include "WorldEvent.h"
#include "Header.h"

// qt
#include <QRect>
#include <QtAlgorithms>

// common
#include "cplusplus11.h"

// tmp
#include <QDebug>

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

void nsRelation::World::morphWorld(const QString& transformation) {

    // TODO: read to first space, Header::getHeader()
    QStringList list = transformation.split(" ", QString::SkipEmptyParts);

    if (list.isEmpty()) return;

    if (list.at(0) == Header::entity)          createEntity(transformation);
    else if (list.at(0) == Header::connection) createConnection(transformation);
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
  foreach (Entity* entity, mEntityList) {
    emit onEntityChanged(replyId, entity);
  }

  // send connections. must be after entities or draw would paint block over connections
  // also this separeta processing of entities and connections
  foreach (Entity* entity, mEntityList) {
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
      Connection connection = Connection(relation.key(), from, to);
      emit onConnectionChanged(replyId, &connection);
    }
  }

}

void nsRelation::World::createEntity(const QString& data) {

#warning bug with spilt, when any arg like path contain spaces, replace with ArgumentList algo

  QStringList list = data.split(" ", QString::SkipEmptyParts);
  enum { command_index, id_index, x_index, y_index, name_index, elements_size };

  if (list.size() < elements_size || list.at(command_index) != Header::entity) return;

  IntegerId::id_type id = list.at(id_index) == Header::generate ? IntegerId::id_type()
                                                                : IntegerId::id_type(list.at(id_index).toInt());

  QPoint center(list.at(x_index).toInt(), list.at(y_index).toInt());
  Entity* entity = Entity::create(center, list.at(name_index), id);

  if (entity != nullptr) {

    mEntityList.push_front(entity);
  }
  else {

    emit onErrorMessage(tr("Can't create entity with id = %1. Id already taken."));
  }
}

void nsRelation::World::createConnection(const QString& data) {

#warning bug with spilt, when any arg like path contain spaces, replace with ArgumentList algo
  QStringList list = data.split(" ", QString::SkipEmptyParts);
  enum { command_index, relation_type_index, id_from_index, id_to_index, elements_size };

  if (list.size() < elements_size || list.at(command_index) != Header::connection) return;

  QString relationType = list.at(relation_type_index);
  QString parentId = list.at(id_from_index);
  QString childId = list.at(id_to_index);  

    foreach (Entity* parent, mEntityList) {

      if (parent->idString() == parentId) {

        foreach (Entity* child, mEntityList) {

          if (child->idString() == childId) {

            child->inAttach(relationType, parent);
            parent->outAttach(relationType, child);
            break;
          }
        }

        break;
      }
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
