#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QAction>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDebug>

#include "cursor.h"

class Scene : public QGraphicsScene
{
public:
    enum Mode {NoMode, SelectObject, DrawLine, DrawCircle};
    Scene(QObject* parent = 0);
    void setMode(Mode mode);
    void setCursor();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    Mode sceneMode;
    QPointF origPoint;
    QPointF origCircle;
    QGraphicsLineItem* lineToDraw;
    QGraphicsEllipseItem* circleToDraw;    
    void makeItemsControllable(bool areControllable);
    QGraphicsLineItem* ejeX;
    QGraphicsLineItem* ejeY;
    bool finalizar;
};

#endif // SCENE_H
