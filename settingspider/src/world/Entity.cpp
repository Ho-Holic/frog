// self
#include "Entity.h"
#include "VectorMath.h"

// qt
#include <QRect>
#include <QFontMetrics>

nsSettingSpider::IntegerIdGenerator
nsSettingSpider::Entity::s_idGenerator = nsSettingSpider::IntegerIdGenerator();

nsSettingSpider::Entity::Entity(const QPoint& center, const QString& shortPath)
: mId(s_idGenerator.next())
, mLibraryName(shortPath)
, mFont()
, mRect(VectorMath::fromCenterPoint(center, fromName(mLibraryName, mFont)))
, mInRelation()
, mOutRelation() {
  //
}

nsSettingSpider::IntegerIdGenerator::id_type nsSettingSpider::Entity::sequentialId() const {
  return mId;
}

void nsSettingSpider::Entity::inAttach(const nsSettingSpider::RelationType& type,
                                       nsSettingSpider::Entity* from) {
  mInRelation[type].push_front(from);
}

void nsSettingSpider::Entity::outAttach(const nsSettingSpider::RelationType& type,
                                        nsSettingSpider::Entity* to) {
  mOutRelation[type].push_front(to);
}

void nsSettingSpider::Entity::inDetach(const nsSettingSpider::RelationType& type, nsSettingSpider::Entity* from) {
  int removed = mInRelation[type].removeAll(from);
  Q_ASSERT(removed == 1 || removed == 0);
  Q_UNUSED(removed);
}

void nsSettingSpider::Entity::outDetach(const nsSettingSpider::RelationType& type, nsSettingSpider::Entity* to) {
  int removed = mOutRelation[type].removeAll(to);
  Q_ASSERT(removed == 1 || removed == 0);
  Q_UNUSED(removed);
}

const nsSettingSpider::Entity::RelationBinding&
nsSettingSpider::Entity::outRelations() const {
  return mOutRelation;
}

const nsSettingSpider::Entity::RelationList&
nsSettingSpider::Entity::inRelations(const nsSettingSpider::RelationType& type) const {

  RelationBinding::const_iterator found = mInRelation.find(type);
  Q_ASSERT(found != mInRelation.end());
  return found.value();
}

const nsSettingSpider::Entity::RelationList&
nsSettingSpider::Entity::outRelations(const nsSettingSpider::RelationType& type) const {

  RelationBinding::const_iterator found = mOutRelation.find(type);
  Q_ASSERT(found != mOutRelation.end());
  return found.value();
}

bool nsSettingSpider::Entity::hasInRelations(const nsSettingSpider::RelationType& type) const {

  RelationBinding::const_iterator found = mInRelation.find(type);
  return found != mInRelation.end() && ( ! found->empty());
}

bool nsSettingSpider::Entity::hasOutRelations(const nsSettingSpider::RelationType& type) const {

  RelationBinding::const_iterator found = mOutRelation.find(type);
  return found != mOutRelation.end() && ( ! found->empty());
}

const nsSettingSpider::Entity::RelationBinding&
nsSettingSpider::Entity::inRelations() const {
  return mInRelation;
}

const QRect& nsSettingSpider::Entity::rect() const {
  return mRect;
}

QRect nsSettingSpider::Entity::connectionRect() const {
  QPoint topLeft = mRect.center() - QPoint(mRect.width() / 2, -(mRect.height() / 4));
  QPoint fixedTopLeft = QPoint(mRect.topLeft().x(), topLeft.y());
  return QRect(fixedTopLeft, mRect.bottomRight());
}

QRect nsSettingSpider::Entity::connectionSlotRect() const {

  //QFontMetrics metrics(mFont);
  // QSize(metrics.height(), metrics.height())
  QSize circle(10, 10);
  return QRect(mRect.topLeft() + QPoint(mRect.width()/2, 0) - QPoint(circle.width()/2, circle.height()/2),
               circle);
}

QRect nsSettingSpider::Entity::captionRect() const {
  QFontMetrics metrics(mFont);
  return QRect(mRect.topLeft(), QSize(mRect.width(), metrics.height() * 2));
}

const QString& nsSettingSpider::Entity::libraryName() const {
  return mLibraryName;
}

const QFont& nsSettingSpider::Entity::font() const {
  return mFont;
}

void nsSettingSpider::Entity::setTopLeft(const QPoint& pos) {
  mRect = QRect(pos, mRect.size());
}

QSize nsSettingSpider::Entity::fromName(const QString& name, const QFont& usedFont) {
  QFontMetrics metrics(usedFont);
  int w = metrics.boundingRect(name).width() + (metrics.averageCharWidth() * 4);
  return QSize(w, 50);
}
