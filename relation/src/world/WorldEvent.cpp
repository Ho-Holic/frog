// self
#include "WorldEvent.h"

// common
#include "cplusplus11.h"

nsRelation::WorldEvent::WorldEvent(nsRelation::WorldEvent::WorldState state)
: mState(state)
, mActiveEntity(nullptr) {
  //
}

nsRelation::WorldEvent::WorldEvent(nsRelation::WorldEvent::WorldState state,
                                        nsRelation::Entity* active)
: mState(state)
, mActiveEntity(active) {
  //
}

nsRelation::WorldEvent::WorldState nsRelation::WorldEvent::state() const {
  return mState;
}

nsRelation::Entity* nsRelation::WorldEvent::selectedEntity() const {
  return mActiveEntity;
}
