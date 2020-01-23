#include "rvwidget.h"
#include <QMessageBox>

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    m_angularVelocityX = 0;
    m_angularVelocityY = 3;
    m_angularVelocityZ = 0;
    m_timer = new QTimer(this);
    m_animation = false;
}

RVWidget::~RVWidget()
{
    delete m_timer;
    delete m_camera;
    delete m_body;
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();
//    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);

    m_camera = new RVCamera();
    m_body = new RVPyramid();
    m_body->setCamera(m_camera);
    m_body->setPosition(QVector3D(0, -0.5f, -4));
    m_body->initialize();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));

    m_timer->start(10);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_body->draw();
}

void RVWidget::update(){
    if (m_animation) {
        float angularVelocity = 3.0f;
        m_body->rotate(angularVelocity, QVector3D(0, 1, 0));
    }
    QOpenGLWidget::update();
}


void RVWidget::resizeGL(int w, int h)
{
    //Pour tenir compte du changement de format du widget
    float aspect = float(w)/h;
    m_camera->setAspect(aspect);
    //transformation de viewport
    glViewport(0, 0, w, h);
}

void RVWidget::mousePressEvent(QMouseEvent* event){
    m_oldPos = event->pos();
}

void RVWidget::mouseMoveEvent(QMouseEvent* event){
    float dx, dy;

    dx = (event->pos().x() - m_oldPos.x());
    dy = (event->pos().y() - m_oldPos.y());

    dx = dx/width();
    dy = dy/height();

    float angleX = 180 * dy;
    float angleY = 180 * dx;

    m_body->rotate(angleX, QVector3D(1, 0, 0));
    m_body->rotate(angleY, QVector3D(0, 1, 0));

    m_oldPos = event->pos();
    QOpenGLWidget::update();
}


void RVWidget::startAnimation(){
    m_animation = ! m_animation;
    this->update();
}

void RVWidget::changeFov(int newFov){
    m_camera->setFov(newFov);
    this->update();
}
