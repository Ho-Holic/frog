// self
#include "GraphWidget.h"
#include "ColorScheme.h"
#include "world/Entity.h"
#include "world/Connection.h"
#include "world/VectorMath.h"
#include "world/WorldEvent.h"

// qt
#include <QPainter>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QUuid>

// tmp
#include <QDebug>

// common
#include <cplusplus11.h>

nsSettingSpider::GraphWidget::GraphWidget(QWidget* parent)
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

void nsSettingSpider::GraphWidget::setModeDependOn(WorldEvent* event) {
  switch (event->state()) {
  case WorldEvent::EntityIncomingSlot:  connectEditMode(event->selectedEntity()); break;
  case WorldEvent::EntityOutcomingSlot: connectMode(event->selectedEntity()); break;
  case WorldEvent::EntityBody:          moveMode(event->selectedEntity()); break;
  case WorldEvent::Nothing:             originMode(); break;
  }
}

//----------------------------------------------------------

void nsSettingSpider::GraphWidget::moveMode(Entity* entity) {
  if (mMode == PendingConnection) {
    mMode = Connect;
    mTouchFunction = &emptyTouch;
    mMoveFunction = &emptyMove;
    mFinalizeFunction = &connectFinalize;
    mSelectedEntities.push_back(entity);
    mPendingConnection = Connection();
  }
  else {
    mMode = EntityMove;
    mTouchFunction = &emptyTouch;
    mMoveFunction = &moveEntity;
    mFinalizeFunction = &moveFinalize;
    mSelectedEntities.push_back(entity);
    mPendingConnection = Connection();
  }
}

void nsSettingSpider::GraphWidget::connectMode(Entity* entity) {
  mMode = PendingConnection;
  mTouchFunction = &emptyTouch;
  mMoveFunction = &connectEntity;
  mFinalizeFunction = &connectFinalize;
  mSelectedEntities.push_back(entity);
  mPendingConnection = Connection();
}

void nsSettingSpider::GraphWidget::connectEditMode(nsSettingSpider::Entity* entity) {
  if (entity->hasInRelations(mRelationType)) {
    mMode = EditConnection;
    mTouchFunction = &emptyTouch;
    mMoveFunction = &moveConnectEdit;
    mFinalizeFunction = &emptyFinalize;
    mSelectedEntities.push_back(entity);
    mPendingConnection = Connection();
  }
  else {
    idleMode();
  }
}

void nsSettingSpider::GraphWidget::idleMode() {
  mMode = Idle;
  mTouchFunction = &emptyTouch;
  mMoveFunction = &emptyMove;
  mFinalizeFunction = &emptyFinalize;
  mSelectedEntities.clear();
  mPendingConnection = Connection();
}

void nsSettingSpider::GraphWidget::originMode() {
  mMode = OriginMove;
  mTouchFunction = &emptyTouch;
  mMoveFunction = &moveOrigin;
  mFinalizeFunction = &emptyFinalize;
  mSelectedEntities.clear();
  mPendingConnection = Connection();
}

void nsSettingSpider::GraphWidget::touchCall(const QPoint& pos) {
  (*this.*mTouchFunction)(pos);
}

void nsSettingSpider::GraphWidget::moveCall(const QPoint& from, const QPoint& to) {
  (*this.*mMoveFunction)(from,to);
}


void nsSettingSpider::GraphWidget::finalizeCall(const QPoint& pos) {
  (*this.*mFinalizeFunction)(pos);
}


//---------------------------------------------------------------------------

void nsSettingSpider::GraphWidget::emptyTouch(const QPoint& pos) {
  // TODO: class with interface: touch, move, finalize. Finalize or better concept???
  // maybe enter, move, leave ?
  Q_UNUSED(pos);
}

void nsSettingSpider::GraphWidget::emptyMove(const QPoint& from, const QPoint& to) {
  Q_UNUSED(from);
  Q_UNUSED(to);
}

void nsSettingSpider::GraphWidget::emptyFinalize(const QPoint& pos) {
  Q_UNUSED(pos);
}


void nsSettingSpider::GraphWidget::moveOrigin(const QPoint& from, const QPoint& to) {
  mOrigin += to - from;  
}

void nsSettingSpider::GraphWidget::moveEntity(const QPoint& from, const QPoint& to) {
  Q_ASSERT( ! mSelectedEntities.empty());
  Entity* current = mSelectedEntities.front();
  current->setTopLeft(to - from + current->rect().topLeft());
}

void nsSettingSpider::GraphWidget::moveFinalize(const QPoint& pos) {

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


void nsSettingSpider::GraphWidget::connectFinalize(const QPoint& pos) {

  Q_ASSERT(mSelectedEntities.size() > 1); // we need two to perform connection

  Entity* parent = mSelectedEntities.at(0);
  Entity* child = mSelectedEntities.at(1);

  if (parent == child) return; // skip self

  if (child->rect().contains(pos)) {
    child->inAttach(mRelationType, parent);
    parent->outAttach(mRelationType, child);
  }

}

void nsSettingSpider::GraphWidget::connectEntity(const QPoint& from, const QPoint& to) {

  Q_ASSERT( ! mSelectedEntities.empty());
  Entity* current = mSelectedEntities.front();

  Q_UNUSED(from);
  QRect connectionRect = current->connectionRect();
  mPendingConnection = Connection(mRelationType,
                                  connectionRect.bottomLeft() + QPoint(connectionRect.width() / 2, 0),
                                  QRect(to, QSize(10, 10)));
}

void nsSettingSpider::GraphWidget::moveConnectEdit(const QPoint& from, const QPoint& to) {
  Q_UNUSED(to);
  Q_UNUSED(from);

  Q_ASSERT( ! mSelectedEntities.empty());
  Entity* current = mSelectedEntities.front();

  Q_ASSERT( ! current->inRelations(mRelationType).empty());

  Entity* entity = current->inRelations(mRelationType).front();
  current->inDetach(mRelationType, entity);
  entity->outDetach(mRelationType, current);

  connectMode(entity);

}

int nsSettingSpider::GraphWidget::withoutOriginY(int y) const {
  return y - mOrigin.y();
}

QRect nsSettingSpider::GraphWidget::withoutOrigin(const QRect& r) const {
  return QRect(r.topLeft() - mOrigin, r.size());
}

QPoint nsSettingSpider::GraphWidget::withoutOrigin(const QPoint& p) const {
  return p - mOrigin;
}

QRect nsSettingSpider::GraphWidget::withOrigin(const QRect& r) const {
  return QRect(mOrigin + r.topLeft(), r.size());
}

QPoint nsSettingSpider::GraphWidget::withOrigin(const QPoint& p) const {
  return mOrigin + p;
}

//----------------------------------------------------------



void nsSettingSpider::GraphWidget::mouseDoubleClickEvent(QMouseEvent* e) {      

  emit onDoubleClick(withoutOrigin(e->pos()));
  // TODO: later update w/ dataString algo
//  QString dataString = QString("entity %1 %2 unnamed")
//                       .arg(e->pos().x())
//                       .arg(e->pos.y());

//  emit onCreateRequest(dataString);
  // TODO: start event own loop with timer to call update with some rate and remove update calls?
  update();
}

void nsSettingSpider::GraphWidget::mouseMoveEvent(QMouseEvent* e) {

  if (mIsHolding) {

    QPoint from = mMousePosition;
    QPoint to = e->pos();
    moveCall(withoutOrigin(from), withoutOrigin(to));

    mMousePosition = e->pos();
    update();
  }
}

void nsSettingSpider::GraphWidget::mousePressEvent(QMouseEvent* e) {

  if (e->button() == Qt::LeftButton) {
    mRelationType = Relation::Needed;
  }
  else if (e->button() == Qt::RightButton) {    
    mRelationType = Relation::Absorb;
  }

  mIsHolding = true;
  mMousePosition = e->pos();

  emit onMousePress(withoutOrigin(mMousePosition));

  touchCall(withoutOrigin(mMousePosition));

  update();
}

void nsSettingSpider::GraphWidget::mouseReleaseEvent(QMouseEvent* e) {    

  emit onMouseRelease(withoutOrigin(e->pos()));

  finalizeCall(withoutOrigin(e->pos()));
  idleMode();  

  mIsHolding = false;
  update();
}

void nsSettingSpider::GraphWidget::dragMoveEvent(QDragMoveEvent* e) {
  if (mIsDragging) {
    mDragPosition = e->pos();
    update();
  }
}

void nsSettingSpider::GraphWidget::dragEnterEvent(QDragEnterEvent* e) {
  if (e->mimeData()->hasText()) {
    mIsDragging = true;
    mDragPosition = e->pos();
    e->acceptProposedAction();
    update();
  }
}

void nsSettingSpider::GraphWidget::dragLeaveEvent(QDragLeaveEvent* e) {
  Q_UNUSED(e);
  mIsDragging = false;
  update();
}

void nsSettingSpider::GraphWidget::dropEvent(QDropEvent* e) {
  mIsDragging = false;
  if (e->mimeData()->hasText()) {
    emit onDrop(withoutOrigin(e->pos()), e->mimeData()->text());
    update();
  }
}


void nsSettingSpider::GraphWidget::resizeEvent(QResizeEvent* e) {
  QWidget::resizeEvent(e);
}

void nsSettingSpider::GraphWidget::paintEvent(QPaintEvent* e) {

  QWidget::paintEvent(e);

  drawBackground();

  if (mIsDragging) drawDragArea();

  emit onSceneUpdate(mId);

  // send pending
  if ((mMode == PendingConnection || mMode == EditConnection) && ! mPendingConnection.isNull()) {
    drawConnection(mId, &mPendingConnection);
  }


  bool isDelete = mIsDeleteAllowed && (mMousePosition.y() < DeleteRectHeight);
  if (isDelete) drawDeleteArea();
}

void nsSettingSpider::GraphWidget::drawBackground() {
  QPainter p(this);
  p.setPen(Qt::NoPen);
  p.setBrush(ColorScheme::background());
  p.drawRect(this->rect());

  p.setBrush(QBrush(ColorScheme::backgroundDecoration(), Qt::BDiagPattern));
  p.drawRect(this->rect());
}

void nsSettingSpider::GraphWidget::drawDragArea() {
  QPainter p(this);
  p.setPen(QPen(ColorScheme::entity(), 1, Qt::DashLine));
  p.setBrush(Qt::NoBrush);
  p.drawRect(VectorMath::fromCenterPoint(mDragPosition, QSize(100, 100))); // TODO: calculate normal size
}

void nsSettingSpider::GraphWidget::drawDeleteArea() {

  QPainter p(this);
  QRect rect(QPoint(0, 0), QSize(width(), DeleteRectHeight));

  p.setPen(Qt::NoPen);
  p.setBrush(ColorScheme::deleteArea());
  p.drawRect(rect);

  p.setPen(QPen(ColorScheme::deleteAreaText(), Qt::SolidLine));
  p.drawText(rect, Qt::AlignCenter, tr("Delete"));
}

void nsSettingSpider::GraphWidget::drawEntity(const QString& replyId, nsSettingSpider::Entity* entity) {

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

void nsSettingSpider::GraphWidget::drawConnection(const QString& replyId, nsSettingSpider::Connection* connection) {

  if (replyId != mId) return;

  QPainter p(this);

  if (connection->relationType() == Relation::Needed) {
    p.setPen(QPen(ColorScheme::connection(), Qt::SolidLine));
  }
  else if (connection->relationType() == Relation::Absorb) {
    p.setPen(QPen(ColorScheme::connection(), 1, Qt::DashLine));
  }
  p.drawLine(withOrigin(connection->from()), withOrigin(connection->to().center()));

  p.setPen(QPen(ColorScheme::connection(), Qt::SolidLine));
  p.setBrush(ColorScheme::connection());
  p.drawEllipse(withOrigin(connection->to()));

  // TODO: draw some text
  //p.setPen(QPen(QColor(240, 173, 109), Qt::SolidLine));
  //p.drawText(QRect(withOrigin(connection->to() - QPoint(-20, 20)), QSize(20, 20)), "123");
}
