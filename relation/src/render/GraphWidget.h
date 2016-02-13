#ifndef FROG_RELATION_GRAPHWIDGET_H
#define FROG_RELATION_GRAPHWIDGET_H

// qt
#include <QWidget>

// self
#include "world/Relation.h"
#include "world/Connection.h"

namespace nsRelation {

  class Entity;
  class Connection;
  class WorldEvent;  

  class GraphWidget : public QWidget {
    Q_OBJECT
  public:
    enum Mode {
      Idle,
      OriginMove,
      EntityMove,
      PendingConnection,
      Connect,
      EditConnection
    };

    typedef QList<Entity*> SelectionList;
    typedef void (GraphWidget::*TouchFunction)(const QPoint&);
    typedef void (GraphWidget::*MoveFunction)(const QPoint&, const QPoint&);
    typedef void (GraphWidget::*FinalizeFunction)(const QPoint&);

  public:
    GraphWidget(QWidget* parent = 0);
  signals:
    void onSceneUpdate(const QString&);
    void onMousePress(const QPoint&);
    void onMouseRelease(const QPoint&);

    void onCreateRequest(const QString&);
    void onDestroyRequest(Entity*);

  public slots:
    void setModeDependOn(WorldEvent* event);
    void moveMode(Entity* entity);
    void connectMode(Entity* entity);
    void connectEditMode(Entity* entity);
    void idleMode();
    void originMode();

    void drawEntity(const QString& replyId, Entity* entity);
    void drawConnection(const QString& replyId, Connection* connection);

  public:    
    virtual void wheelEvent(QWheelEvent* e);
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
    void touchCall(const QPoint& pos);
    void moveCall(const QPoint& from, const QPoint& to);
    void finalizeCall(const QPoint& pos);

    void emptyTouch(const QPoint& pos);
    void emptyMove(const QPoint& from, const QPoint& to);
    void emptyFinalize(const QPoint& pos);
    void moveOrigin(const QPoint& from, const QPoint& to);
    void moveEntity(const QPoint& from, const QPoint& to);
    void moveFinalize(const QPoint& pos);
    void connectEntity(const QPoint& from, const QPoint& to);
    void connectFinalize(const QPoint& pos);
    void moveConnectEdit(const QPoint& from, const QPoint& to);    
  private:
    void drawBackground();
    void drawDragArea();
    void drawDeleteArea();

    // TODO: replace withOrigin --> toGraphWidgetCoordinates
    // TODO: replace withoutOrigin --> toWorldCoordinates
    int withoutOriginY(int y) const;
    QRect withoutOrigin(const QRect& r) const;
    QPoint withoutOrigin(const QPoint& p) const;
    QRect withOrigin(const QRect& r) const;
    QPoint withOrigin(const QPoint& p) const;
  private:
    QString mId;
    QPoint mOrigin;
    QPoint mMousePosition; // TODO: replace this bunch of variables with Cursor class
    bool mIsHolding;
    QPoint mDragPosition;
    bool mIsDragging;
    bool mIsDeleteAllowed;

    RelationType mRelationType;

    Mode mMode;
    TouchFunction mTouchFunction;
    MoveFunction mMoveFunction;
    FinalizeFunction mFinalizeFunction;
    SelectionList mSelectedEntities;
    Connection mPendingConnection;
  };
}

#endif // FROG_RELATION_GRAPHWIDGET_H
