// self
#include "GraphWidget.h"
#include "ColorScheme.h"
#include "tools/Tool.h"
#include "tools/HandTool.h"
#include "tools/ConnectTool.h"

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
// cursor
, mMousePosition(0, 0)
, mIsHolding(false)
, mDragPosition(0, 0)
, mIsDragging(false)
// other
, mTools()
, mMode(Idle) {

  connect(mTools.moveTool(), SIGNAL(onDestroyRequest(Entity*)),
          this,              SIGNAL(onDestroyRequest(Entity*)));

  connect(mTools.handTool(), SIGNAL(onOriginChanged(const QPoint&)),
          this,              SLOT  (originChangeEvent(const QPoint&)));

  // default tool is "hand tool"
  mTools.changeToolTo(HandType);
  originChangeEvent(mTools.handTool()->origin());
}

void nsRelation::GraphWidget::dispatchWorldEvent(WorldEvent* event) {
  switch (event->state()) {
  case WorldEvent::EntityIncomingSlot:  entityIncomingSlotEvent(event); break;
  case WorldEvent::EntityOutcomingSlot: entityOutcomingSlotEvent(event); break;
  case WorldEvent::EntityBody:          entityBodyEvent(event); break;
  case WorldEvent::Nothing:             entityNothingEvent(event); break;
  }
}

void nsRelation::GraphWidget::entityIncomingSlotEvent(WorldEvent* event) {
  // TODO: replace with `connectMode` and
  // move code from connectEditMode  
  nsRelation::Entity* entity = event->selectedEntity();
  if (entity->hasInRelations(mTools.connectTool()->relationType())) {
    mMode = EditConnection;
  }
  else {
    mMode = Idle;
  }
}

void nsRelation::GraphWidget::entityOutcomingSlotEvent(WorldEvent* event) {

  mMode = PendingConnection;

  mTools.changeToolTo(ConnectType);
  mTools.currentTool()->addToSelection(event->selectedEntity());
}

void nsRelation::GraphWidget::entityBodyEvent(WorldEvent* event) {

  if (mTools.currentToolType() == ConnectType) {
    mMode = Connect;

    mTools.currentTool()->addToSelection(event->selectedEntity());
  }
  else {

    mMode = EntityMove;

    mTools.changeToolTo(MoveType);
    mTools.currentTool()->addToSelection(event->selectedEntity());
  }
}

void nsRelation::GraphWidget::entityNothingEvent(WorldEvent* event) {

  mMode = OriginMove;

  Q_UNUSED(event);
  mTools.changeToolTo(HandType);
}

void nsRelation::GraphWidget::originChangeEvent(const QPoint& origin) {

  Q_UNUSED(origin);
  QRect deleteRect = withoutOrigin(QRect(QPoint(0,0),
                                         QSize(this->size().width(), MoveTool::DeleteRectHeight)));
  mTools.moveTool()->setDeleteArea(deleteRect);
}


int nsRelation::GraphWidget::withoutOriginY(int y) const {
  return y - mTools.origin().y();
}

QRect nsRelation::GraphWidget::withoutOrigin(const QRect& r) const {
  return QRect(r.topLeft() - mTools.origin(), r.size());
}

QPoint nsRelation::GraphWidget::withoutOrigin(const QPoint& p) const {
  return p - mTools.origin();
}

QRect nsRelation::GraphWidget::withOrigin(const QRect& r) const {
  return QRect(mTools.origin() + r.topLeft(), r.size());
}

QPoint nsRelation::GraphWidget::withOrigin(const QPoint& p) const {
  return mTools.origin() + p;
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

    QPoint from = withoutOrigin(mMousePosition);
    QPoint to = withoutOrigin(e->pos());
    mTools.move(from, to);

    mMousePosition = e->pos();    

    update();
  }
}

void nsRelation::GraphWidget::mousePressEvent(QMouseEvent* e) {


  mIsHolding = true;
  mMousePosition = e->pos();

  if (e->button() == Qt::RightButton) {
    // TODO: menu
#warning entityShapeMenuMode();
  }
  else if (e->button() == Qt::LeftButton) {

    QPoint p = withoutOrigin(mMousePosition);
    emit onMousePress(p);
    mTools.beginTouch(p);
  }

  update();
}

void nsRelation::GraphWidget::mouseReleaseEvent(QMouseEvent* e) {

  // TODO: remove candidate
  QPoint p = withoutOrigin(e->pos());
  emit onMouseRelease(p);

  mTools.endTouch(p);
  mTools.reset();
  // seems we can remove idleMode from here via clever tool deactivation
#warning idleMode();

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

  // TODO: temporary, take cyclic history collection from work project
  RelationType type = (mTools.connectTool()->relationType() == Relation::Needed)
                      ? Relation::Absorb
                      : Relation::Needed;

  mTools.connectTool()->setRelationType(type);

  QWidget::wheelEvent(e);
}

void nsRelation::GraphWidget::paintEvent(QPaintEvent* e) {

  QWidget::paintEvent(e);

  drawBackground();

  if (mIsDragging) drawDragArea();

  if (mMode == EntityShapeMenu) drawEntityShapeMenu();

  emit onSceneUpdate(mId);

  // send pending
  Connection pendingConnection = mTools.connectTool()->pendingConnection();
  if ((mMode == PendingConnection || mMode == EditConnection) && ! pendingConnection.isDisconnected()) {
    drawConnection(mId, &pendingConnection);
  }


  drawDeleteArea();
}

void nsRelation::GraphWidget::resizeEvent(QResizeEvent* e) {
  originChangeEvent(mTools.handTool()->origin());
}

void nsRelation::GraphWidget::drawEntityShapeMenu() {

  //QStringList mEntityShapes = (QStringList() << "Module" << "Bridge");

  QPainter p(this);

  // draw body
  QRect box = VectorMath::fromCenterPoint(mMousePosition, ColorScheme::boxForText(tr("Shape"), ColorScheme::itemTextFont()));
  p.setPen(Qt::NoPen);
  p.setBrush(ColorScheme::entity());
  p.drawRect(box);

  // draw text
  p.setPen(ColorScheme::entityText());
  p.drawText(box, Qt::AlignCenter, tr("Shape"));
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

  // TODO: рассмотреть возможность записи currentToolType() == MoveTool::Type или хотябы MoveToolType
  bool isDelete = (mTools.currentToolType() == MoveType) && (mMousePosition.y() < MoveTool::DeleteRectHeight);

  if ( ! isDelete) {
    return;
  }

  QPainter p(this);
  QRect rect(QPoint(0, 0), QSize(width(), MoveTool::DeleteRectHeight));

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
