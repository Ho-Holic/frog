#ifndef FROG_RELATION_GRAPHWIDGET_H
#define FROG_RELATION_GRAPHWIDGET_H

// qt
#include <QWidget>

// self
#include "world/Relation.h"
#include "world/Connection.h"
#include "Tools.h"

namespace nsRelation {

  class Entity;
  class Connection;
  class WorldEvent;  

  class GraphWidget : public QWidget {
    Q_OBJECT
  public:
    typedef QList<Entity*> SelectionList;
    typedef void (GraphWidget::*TouchFunction)(const QPoint&);
    typedef void (GraphWidget::*MoveFunction)(const QPoint&, const QPoint&);
    typedef void (GraphWidget::*FinalizeFunction)(const QPoint&);

  public:
    GraphWidget(QWidget* parent = 0);
  signals:
    void onSceneUpdate(const QString&);
    void onMarkingMenuUpdate(const QString&);
    void onMousePress(const QPoint&);
    void onMouseRelease(const QPoint&);

    void onCreateRequest(const QString&);
    void onDestroyRequest(Entity*);

  public slots:
    void dispatchWorldEvent(WorldEvent* event);

    void drawEntity(const QString& replyId, Entity* entity);
    void drawConnection(const QString& replyId, Connection* connection);
    void drawMarkingMenuItem(const QString& replyId, MarkingMenuItem* item);
    void drawMarkingMenuSelection(const QPoint& center, const QPoint& edge);
  public slots:
    void entityIncomingSlotEvent(WorldEvent* event);
    void entityOutcomingSlotEvent(WorldEvent* event);
    void entityBodyEvent(WorldEvent* event);
    void entityNothingEvent(WorldEvent* event);
    void originChangeEvent(const QPoint& origin);
  public:    
    virtual void wheelEvent(QWheelEvent* e);
    virtual void paintEvent(QPaintEvent* e);
    virtual void resizeEvent(QResizeEvent* e);
    virtual void mouseDoubleClickEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void dragEnterEvent(QDragEnterEvent* e);
    virtual void dragLeaveEvent(QDragLeaveEvent* e);
    virtual void dragMoveEvent(QDragMoveEvent* e);
    virtual void dropEvent(QDropEvent* e);
  private:
    void drawBackground();
    void drawDragArea();
    void drawDeleteArea();
    void drawScene();
    void drawPendingConnection();
    void drawMarkingMenu();

    // TODO: replace withOrigin --> toGraphWidgetCoordinates
    // TODO: replace withoutOrigin --> toWorldCoordinates
    int withoutOriginY(int y) const;
    QRect withoutOrigin(const QRect& r) const;
    QPoint withoutOrigin(const QPoint& p) const;
    QRect withOrigin(const QRect& r) const;
    QPoint withOrigin(const QPoint& p) const;
  private:
    QString mId;

    // TODO: replace this bunch of variables with Cursor class
    QPoint mMousePosition;
    bool mIsHolding;
    QPoint mDragPosition;
    bool mIsDragging;
    // Cursor class allow to create different cursors
    // and you can check what type of cursor you have
    // cursor.type() == Cursor::Dragging

    Tools* mTools;
  };
}

#endif // FROG_RELATION_GRAPHWIDGET_H
