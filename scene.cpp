#include "scene.h"

Scene::Scene(QObject* parent): QGraphicsScene(parent)
{
    sceneMode = NoMode;
    lineToDraw = nullptr;
    circleToDraw=nullptr;    
    ejeX= new QGraphicsLineItem(0,300,800,300);
    ejeY=new QGraphicsLineItem(400,0,400,600);
    ejeX->setPen(QPen(Qt::white, 1, Qt::SolidLine));
    ejeY->setPen(QPen(Qt::white, 1, Qt::SolidLine));
    this->addItem(ejeX);
    this->addItem(ejeY);
    finalizar = true;
}

void Scene::setMode(Mode mode)
{
    sceneMode = mode;
    QGraphicsView::DragMode vMode =
            QGraphicsView::NoDrag;
    switch (mode)
    {
    case DrawLine:
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
        break;

    case SelectObject:
        makeItemsControllable(true);
        vMode = QGraphicsView::RubberBandDrag;
        break;

    default:
        break;

    }
    QGraphicsView* mView = this->views().at(0);
    if(mView)
        mView->setDragMode(vMode);
}

void Scene::makeItemsControllable(bool areControllable)
{
    foreach(QGraphicsItem* item, items()){
        item->setFlag(QGraphicsItem::ItemIsSelectable,
                      areControllable);
        item->setFlag(QGraphicsItem::ItemIsMovable,
                      areControllable);
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(sceneMode == DrawLine)
    {
        if (event->button()==Qt::RightButton && lineToDraw)
        {
            lineToDraw=nullptr;

        }
        else if(!lineToDraw)
        {
                origPoint = event->scenePos();
                lineToDraw = new QGraphicsLineItem;
                this->addItem(lineToDraw);
                lineToDraw->setPen(QPen(Qt::white, 2, Qt::SolidLine));
                lineToDraw->setPos(origPoint);
        }
        else
        {
            lineToDraw->setLine(0,0,
                                 event->scenePos().x() - origPoint.x(),
                                 event->scenePos().y() - origPoint.y());
            lineToDraw=nullptr;
            origPoint = event->scenePos();
            lineToDraw = new QGraphicsLineItem;
            this->addItem(lineToDraw);
            lineToDraw->setPen(QPen(Qt::white, 2, Qt::SolidLine));
            lineToDraw->setPos(origPoint);
        }
    }
    else if (sceneMode == DrawCircle)
    {
        if(!circleToDraw)
        {
            origCircle = event->scenePos();
            circleToDraw = new QGraphicsEllipseItem;
            this->addItem(circleToDraw);
            circleToDraw->setPen(QPen(Qt::white, 3, Qt::SolidLine));            
        }
        else
        {
            circleToDraw = nullptr;
        }
        origCircle = event->scenePos();
    }
    else
        QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    ejeX->setLine(0,event->scenePos().y(),800,event->scenePos().y());
    ejeY->setLine(event->scenePos().x(),0,event->scenePos().x(),600);
    if(sceneMode == DrawLine)
    {
        if (lineToDraw)
        {
            lineToDraw->setLine(0,0,
                                event->scenePos().x() - origPoint.x(),
                                event->scenePos().y() - origPoint.y());
        }
    }
    else if(sceneMode == DrawCircle)
    {
        if (circleToDraw)
        {
            qreal IncrementoX, IncrementoY;
            qreal radio;
            IncrementoX=event->scenePos().x()-origCircle.x();
            IncrementoY=event->scenePos().y()-origCircle.y();
            radio = sqrt(pow(IncrementoX,2)+pow(IncrementoY,2));
            qreal diametro = radio*2;
            circleToDraw->setRect(origCircle.x()-radio, origCircle.y()-radio, diametro,diametro);
        }
    }
        else
            QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(sceneMode == DrawLine)
    {
        if (lineToDraw)
        {
            /*lineToDraw->setLine(0,0,
                                 event->scenePos().x() - origPoint.x(),
                                 event->scenePos().y() - origPoint.y());*/
        }
        /*else
        {
            lineToDraw->setLine(0,0,
                                 event->scenePos().x() - origPoint.x(),
                                 event->scenePos().y() - origPoint.y());
            lineToDraw=nullptr;
        }*/
    }
    else if (sceneMode == DrawCircle)
    {

    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete)
        foreach(QGraphicsItem* item, selectedItems()){
            removeItem(item);
            delete item;
        }

    else
        QGraphicsScene::keyPressEvent(event);
}


