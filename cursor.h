#ifndef CURSOR_H
#define CURSOR_H

#include <QGraphicsItem>
#include <QPen>
#include <QDebug>
#include <QLineF>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class Cursor : public QGraphicsItem
{
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Cursor(const QRectF& Window);   
    void mover(QPointF punto);
    void setMode (bool mode);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void resize (QRectF rec);

private:
    qreal ancho;
    qreal alto;
    QLineF EjeX;
    QLineF EjeY;
    QRectF SquareSelect;
    QPointF posicionActual;
    bool CursorDrawMode;
};

#endif // CURSOR_H
