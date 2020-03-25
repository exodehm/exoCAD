#include "exoradiuscircle.h"
#include <cmath>

EXORadiusCircle::EXORadiusCircle(QPointF center, QGraphicsItem *parent):QGraphicsEllipseItem(parent)
{
    RadiusLine = new QGraphicsLineItem(this);
    RadiusLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
    RadiusLine->setPos(center);
    centerPoint = center;
    this->setPen(QPen(Qt::green, 3, Qt::SolidLine));
    setAcceptHoverEvents(true);
    setData(0,"Circulo chachi");
}

EXORadiusCircle::~EXORadiusCircle()
{

}

void EXORadiusCircle::changeSize(QPointF P)
{
    increaseX=P.x()-centerPoint.x();
    increaseY=P.y()-centerPoint.y();
    radius = sqrt(pow(increaseX,2)+pow(increaseY,2));
    this->setRect(centerPoint.x()-radius, centerPoint.y()-radius, radius*2,radius*2);
    RadiusLine->setLine(0,0, increaseX,increaseY);
}

void EXORadiusCircle::fixControlPoints()
{
    //Center
    centerCircle.setRect(centerPoint.x()-5.0f,centerPoint.y()-5.0f,10.0f,10.0f);
    centerCircle.setParentItem(this);
    centerCircle.setPen(QPen(Qt::red, 1, Qt::SolidLine));
    centerCircle.setVisible(false);
    //quadrants
    EXO_ControlPoint P;
    P.setX(centerPoint.x());
    P.setY(centerPoint.y()-radius);
    P.setParentItem(this);
    P.installSceneEventFilter(this);
    quadrantPoints.push_back(P);

    P.setX(centerPoint.x()+radius);
    P.setY(centerPoint.y());
    P.setParentItem(this);
    P.installSceneEventFilter(this);
    quadrantPoints.push_back(P);

    P.setX(centerPoint.x());
    P.setY(centerPoint.y()+radius);
    P.setParentItem(this);
    P.installSceneEventFilter(this);
    quadrantPoints.push_back(P);

    P.setX(centerPoint.x()-radius);
    P.setY(centerPoint.y());
    P.setParentItem(this);
    P.installSceneEventFilter(this);
    quadrantPoints.push_back(P);

    P.setX(centerPoint.x());
    P.setY(centerPoint.y());
    P.setParentItem(this);
    P.installSceneEventFilter(this);
    quadrantPoints.push_back(P);

    for (int i=0;i<4;i++)
    {
        quadrantCircle[i].setRect(quadrantPoints.at(i).x()-5,quadrantPoints.at(i).y()-5,10,10);
        quadrantCircle[i].setParentItem(this);
        quadrantCircle[i].setPen(QPen(Qt::red, 1, Qt::SolidLine));
        quadrantCircle[i].setVisible(false);
    }
}

void EXORadiusCircle::finish()
{
    fixControlPoints();
    RadiusLine->setParentItem(nullptr);
    delete RadiusLine;
}

QList<EXO_ControlPoint> &EXORadiusCircle::getPoints()
{
    return quadrantPoints;
}

void EXORadiusCircle::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    this->setPen(QPen(Qt::yellow, 3, Qt::SolidLine));
    //qDebug()<<"Cambio a amarillo";
    QGraphicsItem::hoverEnterEvent(event);
    for (int i=0;i<4;i++)
    {
       quadrantCircle[i].setVisible(true);
    }
    centerCircle.setVisible(true);
}

void EXORadiusCircle::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setPen(QPen(Qt::magenta, 3, Qt::SolidLine));
    //qDebug()<<"Cambio a rosa";
    QGraphicsItem::hoverMoveEvent(event);

}

void EXORadiusCircle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setPen(QPen(Qt::green, 3, Qt::SolidLine));
    qDebug()<<"Cambio a verde";
    QGraphicsItem::hoverLeaveEvent(event);
    for (int i=0;i<4;i++)
    {
       quadrantCircle[i].setVisible(false);
    }
    centerCircle.setVisible(false);
}

bool EXORadiusCircle::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    qDebug() << " QEvent == " + QString::number(event->type());

    EXO_ControlPoint * point = dynamic_cast<EXO_ControlPoint *>(watched);
    if ( point == NULL) return false; // not expected to get here

    QGraphicsSceneMouseEvent * mevent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
    if ( mevent == NULL)
    {
        // this is not one of the mouse events we are interrested in
        return false;
    }

    switch (event->type() )
    {
            // if the mouse went down, record the x,y coords of the press, record it inside the corner object
        case QEvent::GraphicsSceneMousePress:
            {
                point->setMouseState(EXO_ControlPoint::kMouseDown);
                point->mouseDownX = mevent->pos().x();
                point->mouseDownY = mevent->pos().y();
                qDebug()<<"presimanando!!";
            }
            break;

        case QEvent::GraphicsSceneMouseRelease:
            {
                point->setMouseState(EXO_ControlPoint::kMouseReleased);

            }
            break;

        case QEvent::GraphicsSceneMouseMove:
            {
                point->setMouseState(EXO_ControlPoint::kMouseMoving );
            }
            break;

        default:
            // we dont care about the rest of the events
            return false;
            break;
    }


    if ( point->getMouseState() == EXO_ControlPoint::kMouseMoving )
    {

        qreal x = mevent->pos().x(), y = mevent->pos().y();

        // depending on which corner has been grabbed, we want to move the position
        // of the item as it grows/shrinks accordingly. so we need to eitehr add
        // or subtract the offsets based on which corner this is.

        int XaxisSign = 0;
        int YaxisSign = 0;
        switch( point->getCorner() )
        {
        case 0:
            {
                XaxisSign = +1;
                YaxisSign = +1;
            }
            break;

        case 1:
            {
                XaxisSign = -1;
                YaxisSign = +1;
            }
            break;

        case 2:
            {
                XaxisSign = -1;
                YaxisSign = -1;
            }
            break;

        case 3:
            {
                XaxisSign = +1;
                YaxisSign = -1;
            }
            break;

        }

        // if the mouse is being dragged, calculate a new size and also re-position
        // the box to give the appearance of dragging the corner out/in to resize the box

        int xMoved = point->mouseDownX - x;
        int yMoved = point->mouseDownY - y;

       /* int newWidth = _width + ( XaxisSign * xMoved);
        if ( newWidth < 40 ) newWidth  = 40;

        int newHeight = _height + (YaxisSign * yMoved) ;
        if ( newHeight < 40 ) newHeight = 40;

        int deltaWidth  =   newWidth - _width ;
        int deltaHeight =   newHeight - _height ;

        adjustSize(  deltaWidth ,   deltaHeight);

        deltaWidth *= (-1);
        deltaHeight *= (-1);

        if ( point->getCorner() == 0 )
        {
            int newXpos = this->pos().x() + deltaWidth;
            int newYpos = this->pos().y() + deltaHeight;
            this->setPos(newXpos, newYpos);
        }
        else   if ( point->getCorner() == 1 )
        {
            int newYpos = this->pos().y() + deltaHeight;
            this->setPos(this->pos().x(), newYpos);
        }
        else   if ( point->getCorner() == 3 )
        {
            int newXpos = this->pos().x() + deltaWidth;
            this->setPos(newXpos,this->pos().y());
        }

        setCornerPositions();*/

        this->update();
    }

    return true;// true => do not send event to watched - we are finished with this event
}
