// self
#include "GraphWidget.h"
#include "ColorScheme.h"

// qt
#include <QPainter>
#include <QMouseEvent>

// tmp
#include <QDebug>

nsSettingSpider::GraphWidget::GraphWidget(QWidget* parent)
: QWidget(parent)
, mOrigin(0, 0)
, mClickedPosition(0, 0)
, mIsHolding(false) {
  //
}

void nsSettingSpider::GraphWidget::resizeEvent(QResizeEvent* e) {
  QWidget::resizeEvent(e);
}

void nsSettingSpider::GraphWidget::paintEvent(QPaintEvent* e) {
  QWidget::paintEvent(e);
  QPainter p(this);
  p.setPen(Qt::NoPen);
  p.setBrush(ColorScheme::background());
  p.drawRect(this->rect());

  p.setBrush(QBrush(ColorScheme::backgroundDecoration(), Qt::BDiagPattern));
  p.drawRect(this->rect());

//  p.setPen(QColor(0, 0, 0));
//  for (int i = 0; i < height(); i += 20) {
//    p.drawText(QRect(0, i, 200, 200), QString::number(mOrigin.y() + i));
//  }
  emit updateScene();
}

void nsSettingSpider::GraphWidget::mouseDoubleClickEvent(QMouseEvent* e) {
  QWidget::mouseDoubleClickEvent(e);  
  emit onDoubleClick(e->pos());
  update();
}


void nsSettingSpider::GraphWidget::mouseMoveEvent(QMouseEvent* e) {
  if (mIsHolding) {    
    emit onMouseMove(mClickedPosition, e->pos());
    mClickedPosition = e->pos();
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
  mClickedPosition = e->pos();
  emit onMousePress(mClickedPosition);
  update();
}

void nsSettingSpider::GraphWidget::mouseReleaseEvent(QMouseEvent* e) {  
  emit onMouseRelease(e->pos());
  mIsHolding = false;
  update();
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

  //p.setPen(QPen(QColor(240, 173, 109), Qt::SolidLine));
  //p.drawText(QRect(withOrigin(connection->to() - QPoint(-20, 20)), QSize(20, 20)), "123");
}

void nsSettingSpider::GraphWidget::drawDeleteArea(bool enabled) {
  if ( ! enabled) return;


  QPainter p(this);
  QRect rect(QPoint(0, 0), QSize(width(), 40));

  p.setPen(Qt::NoPen);
  p.setBrush(ColorScheme::deleteArea());
  p.drawRect(rect);

  p.setPen(QPen(ColorScheme::deleteAreaText(), Qt::SolidLine));
  p.drawText(rect, Qt::AlignCenter, "Удалить");
}

void nsSettingSpider::GraphWidget::setOrigin(const QPoint& origin) {
  mOrigin = origin;
}


