#ifndef SETTINGSPIDER_WORLD_H
#define SETTINGSPIDER_WORLD_H

// qt
#include <QObject>
#include <QList>

// self
#include "Entity.h"
#include "Connection.h"
#include "Relation.h"

namespace nsSettingSpider {
  class World : public QObject {
    Q_OBJECT
  private:
    Q_DISABLE_COPY(World)
  public:
    typedef QList<Entity*> EntityList;

    enum Mode {
      Idle,
      OriginMove,
      EntityMove,
      PendingConnection,
      EditConnection
    };

    typedef void (World::*TouchFunction)(const QPoint&);
    typedef void (World::*MoveFunction)(const QPoint&, const QPoint&);
    typedef void (World::*FinalizeFunction)(const QPoint&);
  public:
    World(QObject* parent = 0);
    ~World();
  signals:
    void entityChanged(Entity*);
    void connectionChanged(Connection*);    
    void originChanged(const QPoint& origin);
    void modeChanged(World::Mode);
  public slots:
    void createEntityAt(const QPoint& center);
    void createEntityAt(const QPoint& center, const QString& data);
    void destroyActiveEntity(const QPoint& pos);
    void activateMode(const QPoint& pos);
    void deactivateMode(const QPoint& pos);    
    void moveInWorld(const QPoint& from, const QPoint& to);
    void changeRelationType(const RelationType& relationType);
    void reportStatus();    
    void saveTo(const QString& path) const;
    void loadFrom(const QString& path);
  public:
    EntityList::size_type entityCount() const;
    Entity* entityAt(EntityList::size_type index) const;
  private:
    void touchCall(const QPoint& pos);
    void moveCall(const QPoint& from, const QPoint& to);
    void finalizeCall(const QPoint& pos);

    void moveMode(Entity* entity);
    void connectMode(Entity* entity);
    void connectEditMode(Entity* entity);
    void idleMode();
    void originMode();

    void reportRelations(const Entity* from);
  private:
    void emptyTouch(const QPoint& pos);
    void emptyMove(const QPoint& from, const QPoint& to);
    void emptyFinalize(const QPoint& pos);
    void moveOrigin(const QPoint& from, const QPoint& to);
    void moveEntity(const QPoint& from, const QPoint& to);    
    void connectEntity(const QPoint& from, const QPoint& to);
    void connectFinalize(const QPoint& pos);
    void moveConnectEdit(const QPoint& from, const QPoint& to);
  private:
    void destroyEntity(Entity* entity);
    int withoutOriginY(int y) const;
    QRect withoutOrigin(const QRect& r) const;
    QPoint withoutOrigin(const QPoint& p) const;
  private:
    QPoint mOrigin;
    RelationType mRelationType;
    Mode mMode;
  private:
    EntityList mEntityList;
    TouchFunction mTouchFunction;
    MoveFunction mMoveFunction;
    FinalizeFunction mFinalizeFunction;
    Entity* mActiveEntity;
    Connection mPendingConnection;
  };    
}



#endif // SETTINGSPIDER_WORLD_H
