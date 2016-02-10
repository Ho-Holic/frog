// self
#include "Entity.h"
#include "VectorMath.h"

// qt
#include <QRect>
#include <QFontMetrics>

nsRelation::IntegerIdGenerator
nsRelation::Entity::s_idGenerator = nsRelation::IntegerIdGenerator();

nsRelation::Entity::Entity(const QPoint& center, const QString& shortPath)
: mId(s_idGenerator.next())
, mLibraryName(shortPath)
, mFont()
, mRect(VectorMath::fromCenterPoint(center, fromName(mLibraryName, mFont)))
, mInRelation()
, mOutRelation() {
  //
}

nsRelation::IntegerIdGenerator::id_type nsRelation::Entity::sequentialId() const {
  return mId;
}

void nsRelation::Entity::inAttach(const nsRelation::RelationType& type,
                                       nsRelation::Entity* from) {
  mInRelation[type].push_front(from);
}

void nsRelation::Entity::outAttach(const nsRelation::RelationType& type,
                                        nsRelation::Entity* to) {
  mOutRelation[type].push_front(to);
}

void nsRelation::Entity::inDetach(const nsRelation::RelationType& type, nsRelation::Entity* from) {
  int removed = mInRelation[type].removeAll(from);
  Q_ASSERT(removed == 1 || removed == 0);
  Q_UNUSED(removed);
}

void nsRelation::Entity::outDetach(const nsRelation::RelationType& type, nsRelation::Entity* to) {
  int removed = mOutRelation[type].removeAll(to);
  Q_ASSERT(removed == 1 || removed == 0);
  Q_UNUSED(removed);
}

const nsRelation::Entity::RelationBinding&
nsRelation::Entity::outRelations() const {
  return mOutRelation;
}

const nsRelation::Entity::RelationList&
nsRelation::Entity::inRelations(const nsRelation::RelationType& type) const {

  RelationBinding::const_iterator found = mInRelation.find(type);
  Q_ASSERT(found != mInRelation.end());
  return found.value();
}

const nsRelation::Entity::RelationList&
nsRelation::Entity::outRelations(const nsRelation::RelationType& type) const {

  RelationBinding::const_iterator found = mOutRelation.find(type);
  Q_ASSERT(found != mOutRelation.end());
  return found.value();
}

bool nsRelation::Entity::hasInRelations(const nsRelation::RelationType& type) const {

  RelationBinding::const_iterator found = mInRelation.find(type);
  return found != mInRelation.end() && ( ! found->empty());
}

bool nsRelation::Entity::hasOutRelations(const nsRelation::RelationType& type) const {

  RelationBinding::const_iterator found = mOutRelation.find(type);
  return found != mOutRelation.end() && ( ! found->empty());
}

const nsRelation::Entity::RelationBinding&
nsRelation::Entity::inRelations() const {
  return mInRelation;
}

const QRect& nsRelation::Entity::rect() const {
  return mRect;
}

QString nsRelation::Entity::idString() const {
  return QString::number(mId);
}

QRect nsRelation::Entity::connectionRect() const {
  QPoint topLeft = mRect.center() - QPoint(mRect.width() / 2, -(mRect.height() / 4));
  QPoint fixedTopLeft = QPoint(mRect.topLeft().x(), topLeft.y());
  return QRect(fixedTopLeft, mRect.bottomRight());
}

QRect nsRelation::Entity::connectionSlotRect() const {

  //QFontMetrics metrics(mFont);
  // QSize(metrics.height(), metrics.height())
  QSize circle(10, 10);
  return QRect(mRect.topLeft() + QPoint(mRect.width()/2, 0) - QPoint(circle.width()/2, circle.height()/2),
               circle);
}

QRect nsRelation::Entity::captionRect() const {
  QFontMetrics metrics(mFont);
  return QRect(mRect.topLeft(), QSize(mRect.width(), metrics.height() * 2));
}

const QString& nsRelation::Entity::libraryName() const {
  return mLibraryName;
}

const QFont& nsRelation::Entity::font() const {
  return mFont;
}

void nsRelation::Entity::setTopLeft(const QPoint& pos) {
  mRect = QRect(pos, mRect.size());
}

QSize nsRelation::Entity::fromName(const QString& name, const QFont& usedFont) {
  QFontMetrics metrics(usedFont);
  int w = metrics.boundingRect(name).width() + (metrics.averageCharWidth() * 4);
  return QSize(w, 50);
}