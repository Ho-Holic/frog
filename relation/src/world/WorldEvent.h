#ifndef FROG_RELATION_WORLDEVENT_H
#define FROG_RELATION_WORLDEVENT_H

namespace nsRelation {

  class Entity;


  class WorldEvent {
  public:
    enum WorldState {
      Nothing,
      EntityBody,
      EntityOutcomingSlot,
      EntityIncomingSlot
    };
  public:
    WorldEvent(WorldState state);
    WorldEvent(WorldState state, Entity* active);
  public:
    WorldState state() const;
    Entity* selectedEntity() const;
  private:
    WorldState mState;
    Entity* mActiveEntity;
  };

}
#endif // FROG_RELATION_WORLDEVENT_H
