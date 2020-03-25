#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QToolBar>
#include "scene.h"
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    void resizeEvent(QResizeEvent *e);
public slots:
    void actionGroupClicked(QAction*);
private:
    qreal WindowWidth;
    qreal WindowHeight;
    QGraphicsView* view;
    Scene* scene;

    void createActions();
    void createConnections();
    void createToolBar();

    QAction* lineAction;
    QAction* rectAction;
    QAction* rect3PointsAction;
    QAction* ellipseAction;
    QAction* circleRadiusAction;
    QAction* circleDiameterAction;
    QAction* circle3PointsAction;
    QAction* selectAction;
    QActionGroup *actionGroup;
    QToolBar* drawingToolBar;
};

#endif // MAINWINDOW_H
