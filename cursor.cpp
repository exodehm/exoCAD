#include "cursor.h"

Cursor::Cursor(const QRectF &Window):ancho(Window.width()),alto(Window.height())
{
   EjeX.setLine(0,alto/2,ancho,alto/2);
   EjeY.setLine(ancho/2,0,ancho/2,alto);
   CursorDrawMode=true;
   qDebug()<<"Constructor de cursor en: "<<Window.width()<<" , "<<Window.height();
}

void Cursor::mover(QPointF punto)
{
    EjeX.setLine(0,punto.y(),ancho,punto.y());
    EjeY.setLine(punto.x(),0,punto.x(),alto);
    SquareSelect.setRect(punto.x()-4,punto.y()-4,8,8);
    update();
}

void Cursor::setMode(bool mode)
{
    CursorDrawMode = mode;
    if (mode==false)
    {
        qDebug()<<"Modo edicion: ";
    }
    else
    {
        qDebug()<<"Modo dibujo";
    }
}

QRectF Cursor::boundingRect() const
{
    return QRectF (0,0,ancho,alto);
}

void Cursor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::white);
    if (CursorDrawMode==true)
    {
        painter->drawLine(EjeX);
        painter->drawLine(EjeY);
    }
    else
    {
        painter->drawRect(SquareSelect);       
    }
}

void Cursor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{


}

void Cursor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    EjeX.setLine(0,event->pos().y(),ancho,event->pos().y());
    EjeY.setLine(event->pos().x(),0,event->pos().x(),alto);
    SquareSelect.setRect(event->pos().x()-5,event->pos().y()-5,10,10);
    qDebug()<<event->pos().x()<<"-"<<event->pos().y();
    update();
}

void Cursor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void Cursor::resize(QRectF rec)
{
    EjeX.setLine(0,rec.x()/2,rec.y(),rec.x()/2);
    EjeY.setLine(rec.x()/2,0,rec.x()/2,rec.y());
}
