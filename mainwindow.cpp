#include "mainwindow.h"

MainWindow::MainWindow()
{
    WindowWidth=800;
    WindowHeight=600;
    QRectF InitialWindow(0,0,WindowWidth,WindowHeight);
    scene = new Scene(InitialWindow,this);    
    view = new QGraphicsView(scene);
    view->setRenderHints(QPainter::Antialiasing);
    view->setMouseTracking(true);

    //view->setBackgroundBrush(Qt::black);

    setCentralWidget(view);
    resize(WindowWidth,WindowHeight);
    view->resize(this->width(),this->height());
    view->setCursor(Qt::CrossCursor);
    qDebug()<<view->width();
    qDebug()<<view->height();

    createActions();
    createConnections();
    createToolBar();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    scene->setSceneRect(0,0,this->width(),this->height());
    QRectF rec(0,0,this->x(),this->y());
    scene->sceneRectChanged(rec);
    qDebug()<<scene->sceneRect().x()<<"-"<<scene->sceneRect().y();
}

void MainWindow::createActions(){
    lineAction = new QAction("Draw line", this);
    lineAction->setData(int(Scene::DrawLine));
    lineAction->setIcon(QIcon(":/icons/line.png"));
    lineAction->setCheckable(true);

    rectAction = new QAction("Draw rectangle", this);
    rectAction->setData(int(Scene::DrawRect));
    rectAction->setIcon(QIcon(":/icons/rectangle.png"));
    rectAction->setCheckable(true);

    rect3PointsAction = new QAction("Draw rectangle by 3 points", this);
    rect3PointsAction->setData(int(Scene::Draw3PointsRect));
    rect3PointsAction->setIcon(QIcon(":/icons/rectangle_3_points.png"));
    rect3PointsAction->setCheckable(true);

    ellipseAction = new QAction("Draw ellipse", this);
    ellipseAction->setData(int(Scene::DrawEllipse));
    ellipseAction->setIcon(QIcon(":/icons/ellipse.png"));
    ellipseAction->setCheckable(true);

    circleRadiusAction = new QAction("Draw circle by radius", this);
    circleRadiusAction->setData(int(Scene::DrawRadiusCircle));
    circleRadiusAction->setIcon(QIcon(":/icons/circle_radius.png"));
    circleRadiusAction->setCheckable(true);

    circleDiameterAction = new QAction("Draw circle by diameter", this);
    circleDiameterAction->setData(int(Scene::DrawDiameterCircle));
    circleDiameterAction->setIcon(QIcon(":/icons/circle_diameter.png"));
    circleDiameterAction->setCheckable(true);

    circle3PointsAction = new QAction("Draw circle by 3 points", this);
    circle3PointsAction->setData(int(Scene::Draw3PointsCircle));
    circle3PointsAction->setIcon(QIcon(":/icons/circle_3_points.png"));
    circle3PointsAction->setCheckable(true);

    selectAction = new QAction("Select object", this);
    selectAction->setData(int(Scene::SelectObject));
    selectAction->setIcon(QIcon(":/icons/select.png"));
    selectAction->setCheckable(true);

    actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);
    actionGroup->addAction(lineAction);
    actionGroup->addAction(rectAction);
    actionGroup->addAction(rect3PointsAction);
    actionGroup->addAction(ellipseAction);
    actionGroup->addAction(circleRadiusAction);
    actionGroup->addAction(circleDiameterAction);
    actionGroup->addAction(circle3PointsAction);
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
    drawingToolBar->addAction(rectAction);
    drawingToolBar->addAction(rect3PointsAction);
    drawingToolBar->addAction(ellipseAction);
    drawingToolBar->addAction(circleRadiusAction);
    drawingToolBar->addAction(circleDiameterAction);
    drawingToolBar->addAction(circle3PointsAction);
}
