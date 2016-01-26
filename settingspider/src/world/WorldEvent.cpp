// self
#include "WorldEvent.h"

// common
#include "cplusplus11.h"

nsSettingSpider::WorldEvent::WorldEvent(nsSettingSpider::WorldEvent::WorldState state)
: mState(state)
, mActiveEntity(nullptr) {
  //
}

nsSettingSpider::WorldEvent::WorldEvent(nsSettingSpider::WorldEvent::WorldState state,
                                        nsSettingSpider::Entity* active)
: mState(state)
, mActiveEntity(active) {
  //
}

nsSettingSpider::WorldEvent::WorldState nsSettingSpider::WorldEvent::state() const {
  return mState;
}

nsSettingSpider::Entity* nsSettingSpider::WorldEvent::selectedEntity() const {
  return mActiveEntity;
}
