// self
#include "Connection.h"
#include "Relation.h"

nsRelation::Connection::Connection()
: mRelationType(Relation::Needed)
, mFrom(0, 0)
, mTo(0, 0, 0, 0) {
  //
}

nsRelation::Connection::Connection(const QString& relationType, const QPoint& from, const QRect& to)
: mRelationType(relationType)
, mFrom(from)
, mTo(to) {
  //
}

bool nsRelation::Connection::isNull() const {
  return mFrom.isNull() && mTo.isNull();
}

const QString& nsRelation::Connection::relationType() const {
  return mRelationType;
}

const QPoint& nsRelation::Connection::from() const {
  return mFrom;
}

const QRect& nsRelation::Connection::to() const {
  return mTo;
}
