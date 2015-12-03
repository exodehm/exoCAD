#include "mainwindow.h"

MainWindow::MainWindow()
{
    scene = new Scene(this);
    scene->setSceneRect(0,0,800,600);
    view = new QGraphicsView(scene);
    view->setRenderHints(QPainter::Antialiasing);
    view->setMouseTracking(true);
    view->setBackgroundBrush(Qt::black);

    setCentralWidget(view);
    resize(800,600);
    view->resize(this->width(),this->height());
    qDebug()<<view->width();
    qDebug()<<view->height();

    createActions();
    createConnections();
    createToolBar();
}

void MainWindow::createActions(){
    lineAction = new QAction("Draw line", this);
    lineAction->setData(int(Scene::DrawLine));
    lineAction->setIcon(QIcon(":/icons/line.png"));
    lineAction->setCheckable(true);

    circleAction = new QAction("Draw circle", this);
    circleAction->setData(int(Scene::DrawCircle));
    circleAction->setIcon(QIcon(":/icons/circle.png"));
    circleAction->setCheckable(true);

    selectAction = new QAction("Select object", this);
    selectAction->setData(int(Scene::SelectObject));
    selectAction->setIcon(QIcon(":/icons/select.png"));
    selectAction->setCheckable(true);

    actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);
    actionGroup->addAction(lineAction);
    actionGroup->addAction(circleAction);
    actionGroup->addAction(selectAction);
}

void MainWindow::createConnections(){
    connect(actionGroup, SIGNAL(triggered(QAction*)),
            this, SLOT(actionGroupClicked(QAction*)));
}

void MainWindow::actionGroupClicked(QAction *action){
    scene->setMode(Scene::Mode(action->data().toInt()));
}

void MainWindow::createToolBar(){
    drawingToolBar = new QToolBar;
    addToolBar(Qt::TopToolBarArea, drawingToolBar);
    drawingToolBar->addAction(selectAction);
    drawingToolBar->addAction(lineAction);
    drawingToolBar->addAction(circleAction);
}
