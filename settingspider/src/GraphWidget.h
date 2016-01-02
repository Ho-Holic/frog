#ifndef SETTINGSPIDER_GRAPHWIDGET_HPP
#define SETTINGSPIDER_GRAPHWIDGET_HPP

// qt
#include <QWidget>

// self
#include "Entity.h"
#include "Connection.h"

namespace nsSettingSpider {

  // сделать удаление в самой верхушке графа

  class GraphWidget : public QWidget {
    Q_OBJECT
  public:
    GraphWidget(QWidget* parent = 0);
  signals:
    void updateScene();
    void onDoubleClick(const QPoint&);    
    void onMouseMove(const QPoint&, const QPoint&);
    void onMousePress(const QPoint&);
    void onMouseRelease(const QPoint&);
    void onRelationTypeChange(const RelationType&);
  public slots:
    void drawEntity(Entity* entity);
    void drawConnection(Connection* connection);
    void drawDeleteArea(bool enabled);
    void setOrigin(const QPoint& origin);
  public:
    virtual void resizeEvent(QResizeEvent* e);
    virtual void paintEvent(QPaintEvent* e);
    virtual void mouseDoubleClickEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
  private:
    QRect withOrigin(const QRect& r) const;
    QPoint withOrigin(const QPoint& p) const;
  private:
    QPoint mOrigin;
    QPoint mClickedPosition;
    bool mIsHolding;
  };
}

#endif // SETTINGSPIDER_GRAPHWIDGET_HPP
