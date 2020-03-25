#ifndef CIRCLE_H
#define CIRCLE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPen>
#include <QDebug>

/*********************************************/
/************Interfaz*************************/
/*********************************************/

class Circle : public QGraphicsEllipseItem
{
public:
    Circle(QGraphicsScene* S);
    virtual void Place();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);


protected:
    QGraphicsScene* Scene;
    QPointF origCircle;

};

/*********************************************/
/************A partir del radio***************/
/*********************************************/

class RadiusCircle : public Circle
{
public:
    RadiusCircle(QGraphicsScene* Scene, QPointF Point);
    void Place();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsLineItem* RadiusLine;
    QPointF CenterCircle;
};

#endif // CIRCLE_H
