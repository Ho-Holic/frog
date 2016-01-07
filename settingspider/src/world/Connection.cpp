// self
#include "Connection.h"
#include "Relation.h"

nsSettingSpider::Connection::Connection()
: mRelationType(Relation::Needed)
, mFrom(0, 0)
, mTo(0, 0, 0, 0) {
  //
}

nsSettingSpider::Connection::Connection(const QString& relationType, const QPoint& from, const QRect& to)
: mRelationType(relationType)
, mFrom(from)
, mTo(to) {
  //
}

bool nsSettingSpider::Connection::isNull() const {
  return mFrom.isNull() && mTo.isNull();
}

const QString& nsSettingSpider::Connection::relationType() const {
  return mRelationType;
}

const QPoint& nsSettingSpider::Connection::from() const {
  return mFrom;
}

const QRect& nsSettingSpider::Connection::to() const {
  return mTo;
}
