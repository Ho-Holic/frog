// self
#include "Connection.h"
#include "Relation.h"

// common
#include "cplusplus11.h"

nsRelation::Connection::Connection()
: mRelationType()
, mFrom(nullptr)
, mTo(nullptr) {
  //
}

nsRelation::Connection::Connection(const QString& relationType, const nsRelation::Entity* from)
: mRelationType(relationType)
, mFrom(from)
, mTo(nullptr) {
  //
}

nsRelation::Connection::Connection(const QString& relationType, const Entity* from, const Entity* to)
: mRelationType(relationType)
, mFrom(from)
, mTo(to) {
  //
}

bool nsRelation::Connection::isDisconnected() const {
  return mFrom == nullptr && mTo == nullptr;
}

bool nsRelation::Connection::isPending() const {
  return mFrom != nullptr && mTo == nullptr;
}

const QString& nsRelation::Connection::relationType() const {
  return mRelationType;
}

const nsRelation::Entity* nsRelation::Connection::from() const {
  return mFrom;
}

const nsRelation::Entity* nsRelation::Connection::to() const {
  return mTo;
}
