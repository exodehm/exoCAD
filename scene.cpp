#include "scene.h"


Scene::Scene(QObject* parent): QGraphicsScene(parent), gridSize(20){}

Scene::Scene(const QRectF & sceneRect, QObject * parent) : QGraphicsScene(parent), gridSize(20)
{
    Q_ASSERT(gridSize > 0);
    sceneMode = NoMode;
    lineToDraw = nullptr;
    rectToDraw = nullptr;
    rectForEllipse=nullptr;
    circleToDraw = nullptr;
<<<<<<< HEAD
    mycircle = nullptr;
    ellipseToDraw = nullptr;
    //Cruceta =  new Cursor(sceneRect);
    //this->addItem(Cruceta);
=======
    ellipseToDraw = nullptr;
    Cruceta =  new Cursor(sceneRect);
    this->addItem(Cruceta);
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
    primerpunto =  false;
    segundopunto = false;
    tercerpunto = false;
    cuartopunto = false;
    ABLine = nullptr;
    BCLine = nullptr;
    ACLine = nullptr;

    //QObject::connect(this,SIGNAL(sceneRectChanged(QRectF)),Cruceta,SLOT(resize(QRectF)));
}

void Scene::setMode(Mode mode)
{
    sceneMode = mode;
    QGraphicsView::DragMode vMode = QGraphicsView::NoDrag;
    if (mode==SelectObject || mode==NoMode)
    {
        makeItemsControllable(true);
        vMode = QGraphicsView::RubberBandDrag;
<<<<<<< HEAD
        //Cruceta->setMode(false);
=======
        Cruceta->setMode(false);
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
    }
    else
    {
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
<<<<<<< HEAD
        //Cruceta->setMode(true);
=======
        Cruceta->setMode(true);
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
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
    switch(sceneMode)
    {
    case DrawLine:

        if (event->button()==Qt::RightButton && lineToDraw)
        {
            this->removeItem(lineToDraw);
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
        break;

    case DrawRect:

        if (!rectToDraw)
<<<<<<< HEAD
        {
            origPoint = event->scenePos();
            rectToDraw = new QGraphicsRectItem;
            this->addItem(rectToDraw);
            rectToDraw->setPen(QPen(Qt::white, 2, Qt::SolidLine));
            rectToDraw->setPos(origPoint);
=======
        {
            origPoint = event->scenePos();
            rectToDraw = new QGraphicsRectItem;
            this->addItem(rectToDraw);
            rectToDraw->setPen(QPen(Qt::white, 2, Qt::SolidLine));
            rectToDraw->setPos(origPoint);
        }
        else
        {
            rectToDraw->setRect(0,0, event->scenePos().x() - origPoint.x(), event->scenePos().y() - origPoint.y());
            rectToDraw=nullptr;
        }
        break;

    case Draw3PointsRect:
        if (!rectToDraw)
        {
            if (!primerpunto && !segundopunto)
            {
                primerpunto=true;                
                P1 = event->scenePos();
                ABLine = new QGraphicsLineItem;
                ABLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
                ABLine->setPos(P1);
                this->addItem(ABLine);
            }
            else if (primerpunto && !segundopunto)
            {

                segundopunto = true;                
                ACLine = new QGraphicsLineItem;
                ACLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
                ACLine->setPos(P1);                
                this->addItem(ACLine);
            }
        }
        else
        {
            ABLine = nullptr;
            BCLine = nullptr;
            ACLine = nullptr;
            primerpunto=false;
            segundopunto=false;
            rectToDraw=nullptr;
            sceneMode = NoMode;
        }
        break;

    case DrawEllipse://¡¡¡no funciona!!!

        if(!ellipseToDraw)
        {
            if (!primerpunto)
            {
                P1 = event->scenePos();
                primerpunto=true;
                ABLine = new QGraphicsLineItem;
                this->addItem(ABLine);
                ABLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
            }
            else if (primerpunto && !segundopunto && !tercerpunto && !cuartopunto)
            {
                //primerpunto = false;
                segundopunto = true;
                ABLine->setLine(P1.x(),P1.y(),event->scenePos().x(),event->scenePos().y());
                //rectForEllipse = new QGraphicsRectItem;
                //this->addItem(ABLine);
                qreal xmedio,ymedio;
                xmedio = (ABLine->line().p1().x() + ABLine->line().p2().x())/2;
                ymedio = (ABLine->line().p1().y() + ABLine->line().p2().y())/2;
                P2.setX(xmedio);
                P2.setY(ymedio);
                qDebug()<<ABLine->line().p1().x()<<"-"<<ABLine->line().p1().y()
                       <<"-"<<ABLine->line().p2().x()<<"-"<<ABLine->line().p2().y();
                qDebug()<<xmedio<<"-"<<ymedio;
                BCLine = new QGraphicsLineItem;
                this->addItem(BCLine);
                BCLine->setPen(QPen(Qt::red, 1, Qt::DashLine));
                PerpAB=ABLine->line().normalVector();
                //PerpAB.translate((P2.x()-P1.x())/2,(P2.y()-P1.y())/2);
                //ACLine = new QGraphicsLineItem (PerpAB);
                ACLine = new QGraphicsLineItem;
                ACLine->setPen(QPen(Qt::cyan, 1, Qt::DashLine));
                this->addItem(ACLine);

            }
            else if (primerpunto && segundopunto && !tercerpunto && !cuartopunto)
            {
                tercerpunto = true;
                /*rectForEllipse =  new QGraphicsRectItem;
                rectForEllipse->setRotation(ABLine->line().angle());
                this->addItem(rectForEllipse);*/
                qDebug()<<"anguloAB"<<ABLine->line().angle()<<"anguloBC"<<BCLine->line().angle();
            }
            else
            {
                qDebug()<<"Acabada la elise";
            }
        }
        else
        {
            //ellipseToDraw = nullptr;
            ABLine = nullptr;
            BCLine = nullptr;
            primerpunto=false;
            segundopunto = false;
            tercerpunto = false;
        }
        break;

    case DrawRadiusCircle:

        if(!circleToDraw)
        {
            origCircle = event->scenePos();
            circleToDraw = new QGraphicsEllipseItem;
            RadiusLine = new QGraphicsLineItem;
            RadiusLine->setParentItem(circleToDraw);
            RadiusLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
            RadiusLine->setPos(origCircle);
            this->addItem(circleToDraw);
            circleToDraw->setPen(QPen(Qt::green, 3, Qt::SolidLine));
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
        }
        else
        {
            rectToDraw->setRect(0,0, event->scenePos().x() - origPoint.x(), event->scenePos().y() - origPoint.y());
            rectToDraw=nullptr;
        }
<<<<<<< HEAD
        break;

    case Draw3PointsRect:
        if (!rectToDraw)
        {
            if (!primerpunto && !segundopunto)
            {
                primerpunto=true;                
                P1 = event->scenePos();
                ABLine = new QGraphicsLineItem;
                ABLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
                ABLine->setPos(P1);
                this->addItem(ABLine);
            }
            else if (primerpunto && !segundopunto)
            {

                segundopunto = true;                
                ACLine = new QGraphicsLineItem;
                ACLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
                ACLine->setPos(P1);                
                this->addItem(ACLine);
            }
        }
        else
        {
            ABLine = nullptr;
            BCLine = nullptr;
            ACLine = nullptr;
            primerpunto=false;
            segundopunto=false;
            rectToDraw=nullptr;
            sceneMode = NoMode;
        }
        break;

    case DrawEllipse:

        if(!ellipseToDraw)
        {
            if (!primerpunto && !segundopunto)
            {
                primerpunto=true;
                P1 = event->scenePos();
                ABLine = new QGraphicsLineItem;
                ABLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
                ABLine->setPos(P1);
                this->addItem(ABLine);
            }
            else if (primerpunto && !segundopunto)
            {

                segundopunto = true;
                ACLine = new QGraphicsLineItem;
                ACLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
                ACLine->setPos(P1);
                this->addItem(ACLine);
            }
        }
        else
        {
            qDebug()<<"Acabada la elipse";
            ABLine = nullptr;
            BCLine = nullptr;
            ACLine = nullptr;
            primerpunto = false;
            segundopunto = false;
            rectToDraw = nullptr;
            ellipseToDraw = nullptr;
            sceneMode = NoMode;
        }
        break;

    case DrawRadiusCircle:      
        if (!mycircle)
        {
            mycircle =  new EXORadiusCircle(event->scenePos());
            this->addItem(mycircle);
        }
        else
        {
            mycircle->finish();
            mycircle = nullptr;
        }
=======
        origCircle = event->scenePos();
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
        break;

    case DrawDiameterCircle:

        if (!circleToDraw)
        {
            D1 = event->scenePos();
            circleToDraw = new QGraphicsEllipseItem;
            DiameterLine = new QGraphicsLineItem;
            DiameterLine->setParentItem(circleToDraw);
            DiameterLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
            DiameterLine->setPos(D1);
            this->addItem(circleToDraw);
            circleToDraw->setPen(QPen(Qt::cyan, 3, Qt::SolidLine));
        }
        else
        {
            circleToDraw = nullptr;
            DiameterLine = nullptr;
        }
        D1 = event->scenePos();
        break;

    case Draw3PointsCircle:

        if (!circleToDraw)
        {
            if (!primerpunto)
            {
                P1 = event->scenePos();
                primerpunto=true;
                ABLine = new QGraphicsLineItem;
                ABLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
                this->addItem(ABLine);
                qDebug()<<"Punto P1: X= "<<P1.x()<<"Y= "<<P1.y();
            }
            else if (primerpunto && !segundopunto)
            {
                P2 = event->scenePos();
                qDebug()<<"Punto P2: X= "<<P2.x()<<"Y= "<<P2.y();
                circleToDraw = new QGraphicsEllipseItem;
                //ABLine = new QGraphicsLineItem;
                BCLine = new QGraphicsLineItem;
                ACLine = new QGraphicsLineItem;

                ABLine->setParentItem(circleToDraw);
                BCLine->setParentItem(circleToDraw);
                ACLine->setParentItem(circleToDraw);

                BCLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));
                ACLine->setPen(QPen(Qt::gray, 1, Qt::DashLine));

                ABLine->setLine(P1.x(),P1.y(),P2.x(),P2.y());
                PerpAB=ABLine->line().normalVector();
                PerpAB.translate((P2.x()-P1.x())/2,(P2.y()-P1.y())/2);
                this->addItem(circleToDraw);
                circleToDraw->setPen(QPen(Qt::red, 3, Qt::SolidLine));
                primerpunto=false;
                segundopunto=true;
            }
        }
        else
        {
            circleToDraw = nullptr;
            segundopunto = false;
        }
        break;

    default:
        QGraphicsScene::mousePressEvent(event);
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
<<<<<<< HEAD
    //Cruceta->mover(event->scenePos());
=======
    Cruceta->mover(event->scenePos());
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
    if(sceneMode == DrawLine)
    {
        if (lineToDraw)
        {
            lineToDraw->setLine(0,0,
                                event->scenePos().x() - origPoint.x(),
                                event->scenePos().y() - origPoint.y());
        }
    }
    else if(sceneMode == DrawRect)
<<<<<<< HEAD
=======
    {
        if (rectToDraw)
        {
            rectToDraw->setRect(0,0,
                                event->scenePos().x() - origPoint.x(),
                                event->scenePos().y() - origPoint.y());
        }
    }
    else if(sceneMode == Draw3PointsRect)
    {
        if (primerpunto && !segundopunto)
        {
            ABLine->setLine(0,0,event->scenePos().x() - P1.x(), event->scenePos().y() - P1.y());
        }
        else if (primerpunto && segundopunto)
        {
            ACLine->setLine(0,0,event->scenePos().x() - P1.x(), event->scenePos().y() - P1.y());
            qreal BC;
            qreal IncrementoX=ABLine->line().dx()-ACLine->line().dx();
            qreal IncrementoY=ABLine->line().dy()-ACLine->line().dy();
            BC = sqrt(pow(IncrementoX,2)+pow(IncrementoY,2));
            qreal ss = (ABLine->line().length()+ACLine->line().length()+BC)/2;
            qreal altura = 2/ABLine->line().length()*sqrt(ss*(ss-BC)*(ss-ABLine->line().length())*(ss-ACLine->line().length()));            
            if (!rectToDraw)
            {
                rectToDraw = new QGraphicsRectItem;
                rectToDraw->setPen(QPen(Qt::yellow, 2, Qt::SolidLine));
                rectToDraw->setPos(P1);
                rectToDraw->setRotation(-ABLine->line().angle());
                this->addItem(rectToDraw);
            }
            else
            {
                //if (ABLine->line().dy()-ACLine->line().dy()>0)
                if (ABLine->line().angle()<ACLine->line().angle() && ACLine->line().angle()<180)
                {
                    rectToDraw->setRect(0,0,ABLine->line().length(),-altura);
                }
                else
                {
                    rectToDraw->setRect(0,0,ABLine->line().length(),altura);
                }
            }
            qDebug()<<ACLine->line().angle();
        }
    }
    else if(sceneMode == DrawRadiusCircle)
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
    {
        if (rectToDraw)
        {
            rectToDraw->setRect(0,0,
                                event->scenePos().x() - origPoint.x(),
                                event->scenePos().y() - origPoint.y());
        }
    }
    else if(sceneMode == Draw3PointsRect)
    {
        if (primerpunto && !segundopunto)
        {
            ABLine->setLine(0,0,event->scenePos().x() - P1.x(), event->scenePos().y() - P1.y());
        }
        else if (primerpunto && segundopunto)
        {
            ACLine->setLine(0,0,event->scenePos().x() - P1.x(), event->scenePos().y() - P1.y());
            qreal BC;
            qreal IncrementoX=ABLine->line().dx()-ACLine->line().dx();
            qreal IncrementoY=ABLine->line().dy()-ACLine->line().dy();
            BC = sqrt(pow(IncrementoX,2)+pow(IncrementoY,2));
            qreal ss = (ABLine->line().length()+ACLine->line().length()+BC)/2;
            qreal altura = 2/ABLine->line().length()*sqrt(ss*(ss-BC)*(ss-ABLine->line().length())*(ss-ACLine->line().length()));            
            if (!rectToDraw)
            {
                rectToDraw = new QGraphicsRectItem;
                rectToDraw->setPen(QPen(Qt::yellow, 2, Qt::SolidLine));
                rectToDraw->setPos(P1);
                rectToDraw->setRotation(-ABLine->line().angle());
                this->addItem(rectToDraw);
            }
            else
            {
                //if (ABLine->line().dy()-ACLine->line().dy()>0)
                if (ABLine->line().angle()<ACLine->line().angle() && ACLine->line().angle()<180)
                {
                    rectToDraw->setRect(0,0,ABLine->line().length(),-altura);
                }
                else
                {
                    rectToDraw->setRect(0,0,ABLine->line().length(),altura);
                }
            }
            qDebug()<<ACLine->line().angle();
        }
    }
    else if(sceneMode == DrawRadiusCircle)
    {       
        if (mycircle)
        {
            mycircle->changeSize(event->scenePos());
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
        if (primerpunto)
        {
            ABLine->setLine(P1.x(),P1.y(),event->scenePos().x(),event->scenePos().y());
        }
        else if (!primerpunto && segundopunto)
        {
            ACLine->setLine(P1.x(),P1.y(),event->scenePos().x(),event->scenePos().y());
            BCLine->setLine(P2.x(),P2.y(),event->scenePos().x(),event->scenePos().y());
            PerpAC=ACLine->line().normalVector();
            PerpAC.translate((event->scenePos().x()-P1.x())/2,(event->scenePos().y()-P1.y())/2);

            QPointF* pIntersectionPoint= new QPointF;
            int tipointerseccion = PerpAB.intersect(PerpAC, pIntersectionPoint);
            if (tipointerseccion== 1 || tipointerseccion==2)
            {
                qreal radio = sqrt(pow(pIntersectionPoint->x()-P1.x(),2)+pow(pIntersectionPoint->y()-P1.y(),2));
                circleToDraw->setRect(pIntersectionPoint->x()-radio,pIntersectionPoint->y()-radio,radio*2,radio*2);
            }
        }
    }

    else if(sceneMode == DrawEllipse)
    {
<<<<<<< HEAD
        if (primerpunto && !segundopunto)
        {
            ABLine->setLine(0,0,event->scenePos().x() - P1.x(), event->scenePos().y() - P1.y());
        }
        else if (primerpunto && segundopunto)
        {
            ACLine->setLine(0,0,event->scenePos().x() - P1.x(), event->scenePos().y() - P1.y());
            qreal BC;
            qreal IncrementoX=ABLine->line().dx()-ACLine->line().dx();
            qreal IncrementoY=ABLine->line().dy()-ACLine->line().dy();
            BC = sqrt(pow(IncrementoX,2)+pow(IncrementoY,2));
            qreal ss = (ABLine->line().length()+ACLine->line().length()+BC)/2;
            qreal altura = 2/ABLine->line().length()*sqrt(ss*(ss-BC)*(ss-ABLine->line().length())*(ss-ACLine->line().length()));
            if (!rectToDraw)
            {
                rectToDraw = new QGraphicsRectItem;
                rectToDraw->setPen(QPen(Qt::darkGreen, 2, Qt::SolidLine));
                rectToDraw->setPos(P1);
                rectToDraw->setRotation(-ABLine->line().angle());
                this->addItem(rectToDraw);
                ellipseToDraw = new QGraphicsEllipseItem;
                ellipseToDraw->setPen(QPen(Qt::yellow, 2, Qt::SolidLine));
                ellipseToDraw->setPos(P1);
                ellipseToDraw->setRotation(-ABLine->line().angle());
                this->addItem(ellipseToDraw);
            }
            else
            {
                //if (ABLine->line().dy()-ACLine->line().dy()>0)
                if (ABLine->line().angle()<ACLine->line().angle() && ACLine->line().angle()<180)
                {
                    rectToDraw->setRect(0,0,ABLine->line().length(),-altura);
                    ellipseToDraw->setRect(0,0,ABLine->line().length(),-altura);
                }
                else
                {
                    rectToDraw->setRect(0,0,ABLine->line().length(),altura);
                    ellipseToDraw->setRect(0,0,ABLine->line().length(),altura);
                }
            }
            qDebug()<<ACLine->line().angle();
        }       
    }
    if (itemAt(event->scenePos(),QTransform()))
    {
        int dist=8;
        QGraphicsItem *item = itemAt(event->scenePos(),QTransform());
        if (qgraphicsitem_cast<EXORadiusCircle *>(item))
        {
            EXORadiusCircle *Circle = qgraphicsitem_cast<EXORadiusCircle *>(item);
            for (int i=0;i<Circle->getPoints().size();i++)
            {
                if ((fabs(event->scenePos().x()-Circle->getPoints().at(i).x())<dist)
                        && (fabs(event->scenePos().y()-Circle->getPoints().at(i).y())<dist))
                {
                    qDebug()<<"I: "<<i;
                    QCursor::setPos((int)Circle->getPoints().at(i).x(),(int)Circle->getPoints().at(i).y()+100);
                    //event->setPos(Circle->getPoints().at(i));
                    //this->setCursor();
                }
            }
        }
        QGraphicsScene::mouseMoveEvent(event);
=======
        if (primerpunto && !segundopunto && !tercerpunto)
        {
            ABLine->setLine(P1.x(),P1.y(),event->scenePos().x(),event->scenePos().y());
        }
        else if (primerpunto && segundopunto && !tercerpunto)
        {
            BCLine->setLine(P2.x(),P2.y(), event->scenePos().x(),event->scenePos().y());
            //qDebug()<< ACLine->line().p1().x()<<","<<ACLine->line().p1().y()<<" - "<<ACLine->line().p2().x()<<","<<ACLine->line().p2().y();
            qreal angulo = BCLine->line().angle()- ABLine->line().angle();
            if (angulo>90)
            {
                angulo = 180-angulo;
            }
            qreal dist = BCLine->line().length() * sin(angulo);
            qDebug()<<"Distancia: "<<BCLine->line().length();
            qDebug()<<"Distancia corregida: "<<dist;
            qDebug()<<"Seno "<< sin(angulo);
            PerpAB.setLength(dist);
            ACLine->setLine(P1.x(),P1.y(),PerpAB.p2().x(),PerpAB.p2().y());
            qDebug()<<"anguloAB"<<ABLine->line().angle()<<"anguloBC"<<BCLine->line().angle();
            qDebug()<<"angulo"<<angulo;
            //qDebug()<<BCLine->line().length();

            if (!rectForEllipse)
            {
                rectForEllipse =  new QGraphicsRectItem;
                rectForEllipse->setPos(P1.x(),P1.y());
                rectForEllipse->setRotation(-ABLine->line().angle());
                rectForEllipse->setPen(QPen(Qt::green, 3, Qt::SolidLine));
                this->addItem(rectForEllipse);
                ellipseToDraw = new QGraphicsEllipseItem(rectForEllipse->rect());
                //ellipseToDraw = new QGraphicsEllipseItem;
                ellipseToDraw->setPos(P1.x(),P1.y());
                ellipseToDraw->setTransformOriginPoint(P1.x(),P1.y());
                rectForEllipse->setRotation(-ABLine->line().angle());
                ellipseToDraw->setPen(QPen(Qt::darkGreen, 3, Qt::SolidLine));
                this->addItem(ellipseToDraw);
            }
            else
            {
                rectForEllipse->setRect(0,0,ABLine->line().length(),PerpAB.length());
                ellipseToDraw->setRect(rectForEllipse->rect());
                rectForEllipse->setRotation(ABLine->line().angle());
                //rectForEllipse->setRotation(-90);
            }
        }
>>>>>>> 0b6a00ddb75af76847c98083e2adf0d6e4be75d3
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

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QPen pen(Qt::white);
    QBrush brocha(Qt::black);
    painter->setPen(pen);
    painter->setBrush(brocha);
    painter->fillRect(rect,brocha);

    qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
    qreal top = int(rect.top()) - (int(rect.top()) % gridSize);
    QVector<QPointF> points;
    for (qreal x = left; x < rect.right(); x += gridSize){
        for (qreal y = top; y < rect.bottom(); y += gridSize){
            points.append(QPointF(x,y));
        }
    }
    painter->drawPoints(points.data(), points.size());
}


