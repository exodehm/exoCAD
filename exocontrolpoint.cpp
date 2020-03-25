#include "exocontrolpoint.h"

EXO_ControlPoint::EXO_ControlPoint(QGraphicsItem *parent) : QGraphicsRectItem(parent),

    mouseDownX(0),
    mouseDownY(0),
    _outterborderColor(Qt::black),
    _outterborderPen(),
    _width(6),
    _height(6),
    _mouseButtonState(kMouseReleased)
{
    setParentItem(parent);
    _outterborderPen.setWidth(2);
    _outterborderPen.setColor(_outterborderColor);
    this->setAcceptHoverEvents(true);
}

EXO_ControlPoint::EXO_ControlPoint(const EXO_ControlPoint &P)
{
    mouseDownX= P.mouseDownX;
    mouseDownY = P.mouseDownY;
    _outterborderColor = P._outterborderColor;
    _outterborderPen = P._outterborderPen;
    _width = P._width;
    _height = P._height;
    setMouseState(P.getMouseState());
    _outterborderPen.setWidth(2);
    _outterborderPen.setColor(_outterborderColor);
    setAcceptHoverEvents(true);
}

EXO_ControlPoint &EXO_ControlPoint :: operator=(const EXO_ControlPoint& P)
{
    if (this != &P)
    {
        this->mouseDownX= P.mouseDownX;
        this->mouseDownY = P.mouseDownY;
        this->_outterborderColor = P._outterborderColor;
        this->_outterborderPen = P._outterborderPen;
        this->_width = P._width;
        this->_height = P._height;
        this->setMouseState(P.getMouseState());
        this->_outterborderPen.setWidth(2);
        this->_outterborderPen.setColor(_outterborderColor);
        this->setAcceptHoverEvents(true);
        }
    return *this;
}

int EXO_ControlPoint::getCorner()
{
    return 0;
}

void EXO_ControlPoint::setMouseState(int state)
{
    _mouseButtonState = state;
}

int EXO_ControlPoint::getMouseState() const
{
    return _mouseButtonState;
}

// we have to implement the mouse events to keep the linker happy,
// but just set accepted to false since are not actually handling them

void EXO_ControlPoint::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void EXO_ControlPoint::mousePressEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void EXO_ControlPoint::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    event->setAccepted(true);
}

void EXO_ControlPoint::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    event->setAccepted(false);
}

void EXO_ControlPoint::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    event->setAccepted(false);
}


// change the color on hover events to indicate to the use the object has
// been captured by the mouse

void EXO_ControlPoint::hoverLeaveEvent ( QGraphicsSceneHoverEvent * )
{
    _outterborderColor = Qt::black;
    this->update(0,0,_width,_height);
}

void EXO_ControlPoint::hoverEnterEvent ( QGraphicsSceneHoverEvent * )
{
    _outterborderColor = Qt::red;
    this->update(0,0,_width,_height);
    qDebug()<<"Rojooo";
}

QRectF EXO_ControlPoint::boundingRect() const
{
    return QRectF(0,0,_width,_height);
}

void EXO_ControlPoint::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // fill the box with solid color, use sharp corners

    _outterborderPen.setCapStyle(Qt::SquareCap);
    _outterborderPen.setStyle(Qt::SolidLine);
    painter->setPen(_outterborderPen);

    QPointF topLeft (0, 0);
    QPointF bottomRight ( _width, _height);

    QRectF rect (topLeft, bottomRight);

    QBrush brush (Qt::SolidPattern);
    brush.setColor (_outterborderColor);
    painter->fillRect(rect,brush);

}
