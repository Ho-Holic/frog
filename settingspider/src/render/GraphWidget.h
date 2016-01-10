#ifndef SETTINGSPIDER_GRAPHWIDGET_H
#define SETTINGSPIDER_GRAPHWIDGET_H

// qt
#include <QWidget>

// self
#include "world/Relation.h"

namespace nsSettingSpider {

  class Entity;
  class Connection;

  class GraphWidget : public QWidget {
    Q_OBJECT
  public:
    GraphWidget(QWidget* parent = 0);
  signals:
    void onSceneUpdate();
    void onDoubleClick(const QPoint&);    
    void onDrop(const QPoint&, const QString&);
    void onMouseMove(const QPoint&, const QPoint&);
    void onMousePress(const QPoint&);
    void onMouseRelease(const QPoint&);
    void onRelationTypeChange(const RelationType&);
    void onInDeleteArea(const QPoint&);
  public slots:
    void drawEntity(Entity* entity);
    void drawConnection(Connection* connection);
    void setOrigin(const QPoint& origin);
    void setAcceptDeletes(bool allow);
  public:
    virtual void resizeEvent(QResizeEvent* e);
    virtual void paintEvent(QPaintEvent* e);
    virtual void mouseDoubleClickEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void dragEnterEvent(QDragEnterEvent* e);
    virtual void dragLeaveEvent(QDragLeaveEvent* e);
    virtual void dragMoveEvent(QDragMoveEvent* e);
    virtual void dropEvent(QDropEvent* e);
  private:
    enum { DeleteRectHeight = 40 };
  private:
    void drawBackground();
    void drawDragArea();
    void drawDeleteArea();
    QRect withOrigin(const QRect& r) const;
    QPoint withOrigin(const QPoint& p) const;
  private:
    QPoint mOrigin;
    QPoint mMousePosition;
    bool mIsHolding;
    QPoint mDragPosition;
    bool mIsDragging;
    bool mIsDeleteAllowed;
  };
}

#endif // SETTINGSPIDER_GRAPHWIDGET_H
