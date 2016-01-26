#ifndef SETTINGSPIDER_WORLDEVENT_H
#define SETTINGSPIDER_WORLDEVENT_H

namespace nsSettingSpider {

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
#endif // SETTINGSPIDER_WORLDEVENT_H
