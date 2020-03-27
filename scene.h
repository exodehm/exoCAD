#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QAction>
#include <QGraphicsView>
#include <QKeyEvent>
#include <cmath>
#include <QDebug>

#include "cursor.h"
<<<<<<< HEAD
<<<<<<< HEAD
//#include "circle.h"
#include "exoradiuscircle.h"
=======
#include "circle.h"
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
=======
#include "circle.h"
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3


class Scene : public QGraphicsScene
{
    //Q_OBJECT
public:
    enum Mode {NoMode, SelectObject, DrawLine, DrawRect, Draw3PointsRect, DrawEllipse, DrawRadiusCircle, DrawDiameterCircle, Draw3PointsCircle};
    Scene(QObject* parent = nullptr);
    Scene(const QRectF & sceneRect, QObject * parent = nullptr);
    void setMode(Mode mode);
    void setCursor();
    int getGridSize() const {return this->gridSize;}

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event);
    void drawBackground (QPainter* painter, const QRectF &rect);

private:
    Mode sceneMode;
    QPointF origPoint;
    QPointF D1;
    QPointF P1,P2;
    QGraphicsLineItem* lineToDraw;
    QGraphicsRectItem* rectToDraw;
    QGraphicsRectItem* rectForEllipse;
<<<<<<< HEAD
<<<<<<< HEAD
    QGraphicsLineItem* DiameterLine;    
=======
=======
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
    QGraphicsLineItem* DiameterLine;
    QGraphicsLineItem* RadiusLine;
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
    QGraphicsLineItem* ABLine;
    QGraphicsLineItem* BCLine;
    QGraphicsLineItem* ACLine;
    QLineF PerpAB;
    QLineF PerpAC;
    QGraphicsEllipseItem* circleToDraw;
    QGraphicsEllipseItem* ellipseToDraw;
<<<<<<< HEAD
<<<<<<< HEAD
    EXORadiusCircle* mycircle;
=======
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
=======
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
    void makeItemsControllable(bool areControllable);
    Cursor* Cruceta;
    bool primerpunto;
    bool segundopunto;
    bool tercerpunto;
    bool cuartopunto;
    int gridSize;
};

#endif // SCENE_H
