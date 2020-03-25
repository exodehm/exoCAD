#ifndef EXORADIUSCIRCLE_H
#define EXORADIUSCIRCLE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPointF>
#include <QPen>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "exocontrolpoint.h"

class EXORadiusCircle : public QGraphicsEllipseItem
{
public:

    enum { Type = UserType + 10 };

    explicit EXORadiusCircle(QPointF center, QGraphicsItem* parent = nullptr);
    ~EXORadiusCircle();

    void changeSize(QPointF P);
    void fixControlPoints();
    void finish();
    QList<EXO_ControlPoint>& getPoints();
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){}
    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event){}
    virtual void mousePressEvent (QGraphicsSceneMouseEvent * event ){}
    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event){}
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event ){}
    virtual bool sceneEventFilter ( QGraphicsItem * watched, QEvent * event ) ;

    int type() const
      {
          // Enable the use of qgraphicsitem_cast with this item.
          return Type;
      }

private:
    QPointF centerPoint;
    QGraphicsEllipseItem centerCircle;
    //QList<QPointF> quadrantPoints;
    QList<EXO_ControlPoint> quadrantPoints;
    QGraphicsEllipseItem quadrantCircle[4];
    QGraphicsLineItem* RadiusLine;
    qreal radius;
    qreal increaseX, increaseY;
};

#endif // EXORADIUSCIRCLE_H
