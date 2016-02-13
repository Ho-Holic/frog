// self
#include "GraphWidget.h"
#include "ColorScheme.h"
#include "world/Entity.h"
#include "world/Connection.h"
#include "world/VectorMath.h"
#include "world/WorldEvent.h"
#include "world/Header.h"

// qt
#include <QPainter>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QWheelEvent>
#include <QMimeData>
#include <QUuid>

// tmp
#include <QDebug>

// common
#include <cplusplus11.h>

nsRelation::GraphWidget::GraphWidget(QWidget* parent)
: QWidget(parent)
, mId(QUuid::createUuid().toString())
, mOrigin(0, 0)
, mMousePosition(0, 0)
, mIsHolding(false)
, mDragPosition(0, 0)
, mIsDragging(false)
, mIsDeleteAllowed(false)

, mRelationType(Relation::Needed)
, mMode(Idle)
, mTouchFunction(&emptyTouch)
, mMoveFunction(&emptyMove)
, mFinalizeFunction(&emptyFinalize)
, mSelectedEntities()
, mPendingConnection() {
  //
}

void nsRelation::GraphWidget::setModeDependOn(WorldEvent* event) {
  switch (event->state()) {
  case WorldEvent::EntityIncomingSlot:  connectEditMode(event->selectedEntity()); break;
  case WorldEvent::EntityOutcomingSlot: connectMode(event->selectedEntity()); break;
  case WorldEvent::EntityBody:          moveMode(event->selectedEntity()); break;
  case WorldEvent::Nothing:             originMode(); break;
  }
}

void nsRelation::GraphWidget::moveMode(Entity* entity) {
  if (mMode == PendingConnection) {
    mMode = Connect;
    mTouchFunction = &emptyTouch;
    mMoveFunction = &emptyMove;
    mFinalizeFunction = &connectFinalize;
    mSelectedEntities.push_back(entity);
    mPendingConnection = Connection();
    mIsDeleteAllowed = false;
  }
  else {
    mMode = EntityMove;
    mTouchFunction = &emptyTouch;
    mMoveFunction = &moveEntity;
    mFinalizeFunction = &moveFinalize;
    mSelectedEntities.push_back(entity);
    mPendingConnection = Connection();
    mIsDeleteAllowed = true;
  }
}

void nsRelation::GraphWidget::connectMode(Entity* entity) {
  mMode = PendingConnection;
  mTouchFunction = &emptyTouch;
  mMoveFunction = &connectEntity;
  mFinalizeFunction = &connectFinalize;
  mSelectedEntities.push_back(entity);
  mPendingConnection = Connection();
  mIsDeleteAllowed = false;
}

void nsRelation::GraphWidget::connectEditMode(nsRelation::Entity* entity) {
  if (entity->hasInRelations(mRelationType)) {
    mMode = EditConnection;
    mTouchFunction = &emptyTouch;
    mMoveFunction = &moveConnectEdit;
    mFinalizeFunction = &emptyFinalize;
    mSelectedEntities.push_back(entity);
    mPendingConnection = Connection();
    mIsDeleteAllowed = false;
  }
  else {
    idleMode();
  }
}

void nsRelation::GraphWidget::idleMode() {
  mMode = Idle;
  mTouchFunction = &emptyTouch;
  mMoveFunction = &emptyMove;
  mFinalizeFunction = &emptyFinalize;
  mSelectedEntities.clear();
  mPendingConnection = Connection();
  mIsDeleteAllowed = false;
}

void nsRelation::GraphWidget::originMode() {
  mMode = OriginMove;
  mTouchFunction = &emptyTouch;
  mMoveFunction = &moveOrigin;
  mFinalizeFunction = &emptyFinalize;
  mSelectedEntities.clear();
  mPendingConnection = Connection();
  mIsDeleteAllowed = false;
}

void nsRelation::GraphWidget::touchCall(const QPoint& pos) {
  (*this.*mTouchFunction)(pos);
}

void nsRelation::GraphWidget::moveCall(const QPoint& from, const QPoint& to) {
  (*this.*mMoveFunction)(from,to);
}


void nsRelation::GraphWidget::finalizeCall(const QPoint& pos) {
  (*this.*mFinalizeFunction)(pos);
}

void nsRelation::GraphWidget::emptyTouch(const QPoint& pos) {
  // TODO: class with interface: touch, move, finalize. Finalize or better concept???
  // maybe enter, move, leave ?
  Q_UNUSED(pos);
}

void nsRelation::GraphWidget::emptyMove(const QPoint& from, const QPoint& to) {
  Q_UNUSED(from);
  Q_UNUSED(to);
}

void nsRelation::GraphWidget::emptyFinalize(const QPoint& pos) {
  Q_UNUSED(pos);
}


void nsRelation::GraphWidget::moveOrigin(const QPoint& from, const QPoint& to) {
  mOrigin += to - from;  
}

void nsRelation::GraphWidget::moveEntity(const QPoint& from, const QPoint& to) {
  Q_ASSERT( ! mSelectedEntities.empty());
  Entity* current = mSelectedEntities.front();
  current->setTopLeft(withoutOrigin(to) - withoutOrigin(from) + current->rect().topLeft());
}

void nsRelation::GraphWidget::moveFinalize(const QPoint& pos) {

  Q_ASSERT( ! mSelectedEntities.empty());
  Entity* current = mSelectedEntities.front();

  bool isDelete =  (mIsDeleteAllowed)
                && (pos.y() < DeleteRectHeight)
                && (current)
                && (current->rect().contains(withoutOrigin(pos)));

  if (isDelete) {    
    emit onDestroyRequest(current);
    //QString stringData = QString("removeById %1").arg(mActiveEntity->idString());
    //emit onDestroyRequest(stringData);
  }
}


void nsRelation::GraphWidget::connectFinalize(const QPoint& pos) {

  Q_ASSERT(mSelectedEntities.size() > 1); // we need two to perform connection

  Entity* parent = mSelectedEntities.at(0);
  Entity* child = mSelectedEntities.at(1);

  if (parent == child) return; // skip self

  if (child->rect().contains(withoutOrigin(pos))) {
    child->inAttach(mRelationType, parent);
    parent->outAttach(mRelationType, child);
  }

}

void nsRelation::GraphWidget::connectEntity(const QPoint& from, const QPoint& to) {

  Q_UNUSED(from);
  Q_UNUSED(to);

  Q_ASSERT( ! mSelectedEntities.empty());

  Entity* current = mSelectedEntities.front();  
  mPendingConnection = Connection(mRelationType, current);
}

void nsRelation::GraphWidget::moveConnectEdit(const QPoint& from, const QPoint& to) {
  Q_UNUSED(to);
  Q_UNUSED(from);

  Q_ASSERT( ! mSelectedEntities.empty());
  Entity* current = mSelectedEntities.front();

  Q_ASSERT( ! current->inRelations(mRelationType).empty());

  Entity* entity = current->inRelations(mRelationType).front();
  current->inDetach(mRelationType, entity);
  entity->outDetach(mRelationType, current);

  idleMode(); // clean up and go as if we just connect entities

  connectMode(entity);

}

int nsRelation::GraphWidget::withoutOriginY(int y) const {
  return y - mOrigin.y();
}

QRect nsRelation::GraphWidget::withoutOrigin(const QRect& r) const {
  return QRect(r.topLeft() - mOrigin, r.size());
}

QPoint nsRelation::GraphWidget::withoutOrigin(const QPoint& p) const {
  return p - mOrigin;
}

QRect nsRelation::GraphWidget::withOrigin(const QRect& r) const {
  return QRect(mOrigin + r.topLeft(), r.size());
}

QPoint nsRelation::GraphWidget::withOrigin(const QPoint& p) const {
  return mOrigin + p;
}

void nsRelation::GraphWidget::mouseDoubleClickEvent(QMouseEvent* e) {

  QPoint p = withoutOrigin(e->pos());
  QString name = tr("unnamed");
  QString dataString = QString("%1 %2 %3 %4 \"%5\"")
                       .arg(Header::entity)
                       .arg(Header::generate)
                       .arg(p.x())
                       .arg(p.y())
                       .arg(name);

  emit onCreateRequest(dataString);
  // TODO: start event own loop with timer to call update with some rate and remove update calls?
  update();
}

void nsRelation::GraphWidget::mouseMoveEvent(QMouseEvent* e) {

  if (mIsHolding) {

    QPoint from = mMousePosition;
    QPoint to = e->pos();
    moveCall(from, to);

    mMousePosition = e->pos();
    update();
  }
}

void nsRelation::GraphWidget::mousePressEvent(QMouseEvent* e) {

  if (e->button() == Qt::RightButton) {
    // TODO: menu
    return;
  }

  mIsHolding = true;
  mMousePosition = e->pos();

  emit onMousePress(withoutOrigin(mMousePosition));

  touchCall(mMousePosition);

  update();
}

void nsRelation::GraphWidget::mouseReleaseEvent(QMouseEvent* e) {

  // TODO: remove candidate
  emit onMouseRelease(withoutOrigin(e->pos()));

  finalizeCall(e->pos());
  idleMode();  

  mIsHolding = false;
  update();
}

void nsRelation::GraphWidget::dragMoveEvent(QDragMoveEvent* e) {
  if (mIsDragging) {
    mDragPosition = e->pos();
    update();
  }
}

void nsRelation::GraphWidget::dragEnterEvent(QDragEnterEvent* e) {
  if (e->mimeData()->hasText()) {
    mIsDragging = true;
    mDragPosition = e->pos();
    e->acceptProposedAction();
    update();
  }
}

void nsRelation::GraphWidget::dragLeaveEvent(QDragLeaveEvent* e) {
  Q_UNUSED(e);
  mIsDragging = false;
  update();
}

void nsRelation::GraphWidget::dropEvent(QDropEvent* e) {

  mIsDragging = false;

  if (e->mimeData()->hasText()) {

    QStringList list = e->mimeData()->text().split(";", QString::SkipEmptyParts);

    foreach(const QString& path, list) {

      QString dataString = QString("%1 %2 %3 %4 \"%5\"")
                           .arg(Header::entity)
                           .arg(Header::generate)
                           // TODO: calculate correct positions
                           .arg(e->pos().x())
                           .arg(e->pos().y())
                           .arg(path);

      emit onCreateRequest(dataString);
    }

    update();
  }
}


void nsRelation::GraphWidget::wheelEvent(QWheelEvent* e) {

  // TODO: temporary, take cyclic history collection from work
  mRelationType = (mRelationType == Relation::Needed) ? Relation::Absorb
                                                      : Relation::Needed;
  QWidget::wheelEvent(e);
}

void nsRelation::GraphWidget::paintEvent(QPaintEvent* e) {

  QWidget::paintEvent(e);

  drawBackground();

  if (mIsDragging) drawDragArea();

  emit onSceneUpdate(mId);

  // send pending
  if ((mMode == PendingConnection || mMode == EditConnection) && ! mPendingConnection.isDisconnected()) {
    drawConnection(mId, &mPendingConnection);
  }


  bool isDelete = mIsDeleteAllowed && (mMousePosition.y() < DeleteRectHeight);
  if (isDelete) drawDeleteArea();
}

void nsRelation::GraphWidget::drawBackground() {
  QPainter p(this);
  p.setPen(Qt::NoPen);
  p.setBrush(ColorScheme::background());
  p.drawRect(this->rect());

  p.setBrush(QBrush(ColorScheme::backgroundDecoration(), Qt::BDiagPattern));
  p.drawRect(this->rect());
}

void nsRelation::GraphWidget::drawDragArea() {
  QPainter p(this);
  p.setPen(QPen(ColorScheme::entity(), 1, Qt::DashLine));
  p.setBrush(Qt::NoBrush);
  p.drawRect(VectorMath::fromCenterPoint(mDragPosition, QSize(100, 100))); // TODO: calculate normal size
}

void nsRelation::GraphWidget::drawDeleteArea() {

  QPainter p(this);
  QRect rect(QPoint(0, 0), QSize(width(), DeleteRectHeight));

  p.setPen(Qt::NoPen);
  p.setBrush(ColorScheme::deleteArea());
  p.drawRect(rect);

  p.setPen(QPen(ColorScheme::deleteAreaText(), Qt::SolidLine));
  p.drawText(rect, Qt::AlignCenter, tr("Delete"));
}

void nsRelation::GraphWidget::drawEntity(const QString& replyId, nsRelation::Entity* entity) {

  if (replyId != mId) return;

  QPainter p(this);
  p.setPen(Qt::NoPen);
  p.setBrush(ColorScheme::entity());
  p.drawRect(withOrigin(entity->rect()));

  p.setBrush(ColorScheme::connection());
  p.drawRect(withOrigin(entity->connectionRect()));

  p.setPen(ColorScheme::entityText());
  p.drawText(withOrigin(entity->captionRect()), Qt::AlignCenter, entity->libraryName());
}

void nsRelation::GraphWidget::drawConnection(const QString& replyId, nsRelation::Connection* connection) {

  if (connection->isDisconnected()) return;
  if (replyId != mId) return;

  QPainter p(this);

  if (connection->relationType() == Relation::Needed) {
    p.setPen(QPen(ColorScheme::connection(), Qt::SolidLine));
  }
  else if (connection->relationType() == Relation::Absorb) {
    p.setPen(QPen(ColorScheme::connection(), 1, Qt::DashLine));
  } 

  QPoint fromPos = connection->from()->rect().bottomLeft() + QPoint(connection->from()->rect().width()/2, 0);
  QPoint toPos = connection->isPending() ? withoutOrigin(mMousePosition)
                                         : connection->to()->connectionSlotRect().center();

  p.drawLine(withOrigin(fromPos), withOrigin(toPos));

  p.setPen(QPen(ColorScheme::connection(), Qt::SolidLine));
  p.setBrush(ColorScheme::connection());

  // TODO: draw connection pot for pending connection, maybe arrow?
  if ( ! connection->isPending()) {
    p.drawEllipse(withOrigin(connection->to()->connectionSlotRect()));
  }

  // TODO: draw some text
  //p.setPen(QPen(QColor(240, 173, 109), Qt::SolidLine));
  //p.drawText(QRect(withOrigin(connection->to() - QPoint(-20, 20)), QSize(20, 20)), "123");
}
