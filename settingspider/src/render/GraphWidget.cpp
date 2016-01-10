// self
#include "GraphWidget.h"
#include "ColorScheme.h"
#include "world/Entity.h"
#include "world/Connection.h"
#include "world/VectorMath.h"

// qt
#include <QPainter>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

// tmp
#include <QDebug>

nsSettingSpider::GraphWidget::GraphWidget(QWidget* parent)
: QWidget(parent)
, mOrigin(0, 0)
, mMousePosition(0, 0)
, mIsHolding(false)
, mDragPosition(0, 0)
, mIsDragging(false)
, mIsDeleteAllowed(false) {
  //
}

void nsSettingSpider::GraphWidget::resizeEvent(QResizeEvent* e) {
  QWidget::resizeEvent(e);
}

void nsSettingSpider::GraphWidget::paintEvent(QPaintEvent* e) {

  QWidget::paintEvent(e);

  drawBackground();

  if (mIsDragging) drawDragArea();

  bool isDelete = mIsDeleteAllowed && (mMousePosition.y() < DeleteRectHeight);
  if (isDelete) drawDeleteArea();

  emit updateScene();
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

void nsSettingSpider::GraphWidget::mouseDoubleClickEvent(QMouseEvent* e) {  
  emit onDoubleClick(e->pos());
  // TODO: start event own loop with timer to call update with some rate and remove update calls?
  update();
}

void nsSettingSpider::GraphWidget::mouseMoveEvent(QMouseEvent* e) {
  if (mIsHolding) {
    emit onMouseMove(mMousePosition, e->pos());
    mMousePosition = e->pos();
    update();
  }
}

void nsSettingSpider::GraphWidget::mousePressEvent(QMouseEvent* e) {

  if (e->button() == Qt::LeftButton) {
    emit onRelationTypeChange(Relation::Needed);
  }
  else if (e->button() == Qt::RightButton) {
    emit onRelationTypeChange(Relation::Absorb);
  }

  mIsHolding = true;
  mMousePosition = e->pos();
  emit onMousePress(mMousePosition);
  update();
}

void nsSettingSpider::GraphWidget::mouseReleaseEvent(QMouseEvent* e) {    

  bool isDelete = mIsDeleteAllowed && (e->pos().y() < DeleteRectHeight);

  if (isDelete) {
    emit onInDeleteArea(e->pos());
  }

  emit onMouseRelease(e->pos());
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
    emit onDrop(e->pos(), e->mimeData()->text());
    update();
  }
}

QRect nsSettingSpider::GraphWidget::withOrigin(const QRect& r) const {
  return QRect(mOrigin + r.topLeft(), r.size());
}

QPoint nsSettingSpider::GraphWidget::withOrigin(const QPoint& p) const {
  return mOrigin + p;
}

void nsSettingSpider::GraphWidget::drawEntity(nsSettingSpider::Entity* entity) {
  QPainter p(this);
  p.setPen(Qt::NoPen);
  p.setBrush(ColorScheme::entity());
  p.drawRect(withOrigin(entity->rect()));

  p.setBrush(ColorScheme::connection());
  p.drawRect(withOrigin(entity->connectionRect()));

  p.setPen(ColorScheme::entityText());
  p.drawText(withOrigin(entity->captionRect()), Qt::AlignCenter, entity->libraryName());
}

void nsSettingSpider::GraphWidget::drawConnection(nsSettingSpider::Connection* connection) {
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

void nsSettingSpider::GraphWidget::setOrigin(const QPoint& origin) {
  mOrigin = origin;
}

void nsSettingSpider::GraphWidget::setAcceptDeletes(bool allow) {
  mIsDeleteAllowed = allow;
}


