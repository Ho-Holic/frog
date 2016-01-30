#ifndef FROG_RELATION_WORLD_H
#define FROG_RELATION_WORLD_H

// qt
#include <QObject>
#include <QList>

// self
#include "Entity.h"
#include "Connection.h"
#include "Relation.h"

namespace nsRelation {

  class WorldEvent;

  class World : public QObject {
    Q_OBJECT
  private:
    Q_DISABLE_COPY(World)
  public:
    typedef QList<Entity*> EntityList;
  public:
    World(QObject* parent = 0);
    ~World();
  signals:
    void onWorldInspectEvent(WorldEvent*);
    void onEntityChanged(const QString&, Entity*);
    void onConnectionChanged(const QString&, Connection*);
  public slots:
    void inspectWorldAt(const QPoint& pos);
    void createEntityAt(const QPoint& center);
    void createEntityAt(const QPoint& center, const QString& data);    
    void destroyEntity(Entity* entity);

    void reportStatus(const QString& replyId);
    void reportRelations(const QString& replyId, const Entity* from);
  public:
    EntityList::size_type entityCount() const;
    Entity* entityAt(EntityList::size_type index) const;
  private:
    WorldEvent* selectApropriateEventFor(const QPoint& pos);
  private:
  private:
    EntityList mEntityList;
  };    
}



#endif // FROG_RELATION_WORLD_H
