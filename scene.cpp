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
    segundopunto = false;
    //prueba para git
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
    else if (sceneMode == DrawRadiusCircle)
    {
        if(!circleToDraw)
        {
            origCircle = event->scenePos();
            circleToDraw = new QGraphicsEllipseItem;
            RadiusLine = new QGraphicsLineItem;
            this->addItem(RadiusLine);
            RadiusLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
            RadiusLine->setPos(origCircle);
            this->addItem(circleToDraw);
            circleToDraw->setPen(QPen(Qt::white, 3, Qt::SolidLine));            
        }
        else
        {
            circleToDraw = nullptr;
            RadiusLine = nullptr;
        }
        origCircle = event->scenePos();
    }
    else if (sceneMode==DrawDiameterCircle)
    {
        if (!circleToDraw)
        {
            D1 = event->scenePos();
            circleToDraw = new QGraphicsEllipseItem;
            DiameterLine = new QGraphicsLineItem;
            this->addItem(DiameterLine);
            DiameterLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
            DiameterLine->setPos(D1);
            this->addItem(circleToDraw);
            circleToDraw->setPen(QPen(Qt::white, 3, Qt::SolidLine));
        }
        else
        {
            circleToDraw = nullptr;
            DiameterLine = nullptr;
        }
        D1 = event->scenePos();
    }
    else if (sceneMode==Draw3PointsCircle)
    {
        if (!circleToDraw)
        {
            if (!segundopunto)
            {
                P1 = event->scenePos();
                segundopunto=true;
                qDebug()<<"Punto P1: X= "<<P1.x()<<"Y= "<<P1.y();
            }
            else
            {
                P2 = event->scenePos();                
                qDebug()<<"Punto P2: X= "<<P2.x()<<"Y= "<<P2.y();
                circleToDraw = new QGraphicsEllipseItem;
                ABLine = new QGraphicsLineItem;
                BCLine = new QGraphicsLineItem;
                ACLine = new QGraphicsLineItem;

                ABLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
                BCLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
                ACLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));

                this->addItem(ABLine);
                this->addItem(BCLine);
                this->addItem(ACLine);

                ABLine->setLine(P1.x(),P1.y(),P2.x(),P2.y());
                PerpAB=ABLine->line().normalVector();
                PerpAB.translate((P2.x()-P1.x())/2,(P2.y()-P1.y())/2);
                this->addItem(circleToDraw);
                circleToDraw->setPen(QPen(Qt::white, 3, Qt::SolidLine));
            }
        }
        else
        {
            circleToDraw = nullptr;
            DiameterLine = nullptr;
            segundopunto = false;
        }
        //D1 = event->scenePos();
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
    else if(sceneMode == DrawRadiusCircle)
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
            RadiusLine->setLine(0,0, IncrementoX,IncrementoY);
        }
    }
    else if(sceneMode == DrawDiameterCircle)
    {
        if (circleToDraw)
        {
            qreal IncrementoX=event->scenePos().x()-D1.x();
            qreal IncrementoY=event->scenePos().y()-D1.y();
            qreal radio = sqrt(pow(IncrementoX,2)+pow(IncrementoY,2))/2;
            QPointF centro((D1.x()+IncrementoX/2),(D1.y()+IncrementoY/2));
            circleToDraw->setRect(centro.x()-radio,centro.y()-radio, radio*2,radio*2);
            DiameterLine->setLine(0,0, IncrementoX,IncrementoY);
        }
    }
    else if(sceneMode == Draw3PointsCircle)
    {
        if (circleToDraw)
        {
            ACLine->setLine(P1.x(),P1.y(),event->scenePos().x(),event->scenePos().y());
            BCLine->setLine(P2.x(),P2.y(),event->scenePos().x(),event->scenePos().y());
            PerpAC=ACLine->line().normalVector();
            PerpAC.translate((event->scenePos().x()-P1.x())/2,(event->scenePos().y()-P1.y())/2);

            QPointF* pIntersectionPoint= new QPointF;
            int tipointerseccion = PerpAB.intersect(PerpAC, pIntersectionPoint);
            if (tipointerseccion==1 || tipointerseccion==2)
            {
                qreal radio = sqrt(pow(pIntersectionPoint->x()-P1.x(),2)+pow(pIntersectionPoint->y()-P1.y(),2));
                circleToDraw->setRect(pIntersectionPoint->x()-radio,pIntersectionPoint->y()-radio,radio*2,radio*2);
            }
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
    else if (sceneMode == DrawRadiusCircle)
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


