#ifndef CURSOR_H
#define CURSOR_H

#include <QGraphicsLineItem>

class Cursor : public QGraphicsLineItem
{
public:
    Cursor();
    QGraphicsLineItem* LeeCursorHorizontal();
    QGraphicsLineItem* LeeCursorVertical();
//private:
    QGraphicsLineItem* Horizontal;
    QGraphicsLineItem* Vertical;
};

#endif // CURSOR_H
