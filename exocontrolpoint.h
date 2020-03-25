#ifndef EXOCONTROLPOINT_H
#define EXOCONTROLPOINT_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QDebug>


class EXO_ControlPoint : public QGraphicsRectItem
{    
public:
    explicit EXO_ControlPoint(QGraphicsItem *parent = nullptr);
    EXO_ControlPoint (const EXO_ControlPoint& P);
    EXO_ControlPoint& operator=(const EXO_ControlPoint& P);

    int  getCorner(); ///< allows the owner to find out which coner this is
    void setMouseState(int state); ///< allows the owner to record the current mouse state
    int  getMouseState() const; ///< allows the owner to get the current mouse state

    qreal mouseDownX;
    qreal mouseDownY;

    enum {kMouseReleased=0, kMouseDown, kMouseMoving}; ///< define the mouse states

private:

    virtual QRectF boundingRect() const; ///< must be re-implemented in this class to provide the diminsions of the box to the QGraphicsView
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); ///< must be re-implemented here to pain the box on the paint-event
    virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover enter events
    virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover leave events

    // once the hover event handlers are implemented in this class,
    // the mouse events must allow be implemented because of
    // some linkage issue - apparrently there is some connection
    // between the hover events and mouseMove/Press/Release
    // events which triggers a vtable issue
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );
    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );

    QColor _outterborderColor; ///< the hover event handlers will toggle this between red and black
    QPen _outterborderPen; ///< the pen is used to paint the red/black border

    qreal   _width;
    qreal   _height;
    int _corner;// 0,1,2,3  - starting at x=0,y=0 and moving clockwise around the box
    int _mouseButtonState;
};

#endif // EXOCONTROLPOINT_H
