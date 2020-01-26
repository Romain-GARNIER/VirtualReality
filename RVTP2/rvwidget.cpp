#include "rvwidget.h"
#include "rvcube.h"
#include "rvplane.h"

#include <QMessageBox>
#include <QKeyEvent>

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    m_angularVelocityX = 0;
    m_angularVelocityY = 3;
    m_angularVelocityZ = 0;
    m_timer = new QTimer(this);
    m_animation = false;

    isOrtho = false;

    zone = 0;

    grabKeyboard();
}

RVWidget::~RVWidget()
{
    delete m_timer;
    delete m_camera;
    delete m_body;
    delete m_plan;
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    m_camera = new RVCamera();
    m_camera2 = new RVCamera();
    m_body = new RVCube();
    m_plan = new RVPlane();

    m_vector1 = QVector3D(2, 7, 4);
    m_vector2 = QVector3D(-7,0,0);
    m_vector3 = QVector3D(7,0,0);
    m_vector4 =  QVector3D(0.5,7,0);

    m_camera->setTarget(QVector3D(0, 0, 0));

    m_body->setCamera(m_camera);
    m_body->initialize();

    m_plan->setCamera(m_camera);
    m_plan->setPosition(QVector3D(0, 0, 0));
    m_plan->initialize();


    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));

    m_timer->start(10);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




//    for(int i=-10;i<10;i+=2){
//        for(int j=-10;j<10;j+=2){
//            m_body->setPosition(QVector3D(i, 0, j));
//            m_body->draw();
//        }
//    }

    int width = this->width();
    int height = this->height();

    m_camera->setIsOrthogonal(isOrtho);
    m_camera->setPosition(m_vector1);
    glViewport(0,0,width/2,height/2);
    for(int i=-9;i < 10; i+=2){
        for(int j=-9;j < 10; j+=2){
            m_body->setPosition(QVector3D(i, 0, j));
            m_body->draw();
        }
    }
    m_plan->draw();

    m_camera->setIsOrthogonal(!isOrtho);
    m_camera->setPosition(m_vector2);
    glViewport(width/2,0,width/2,height/2);
    for(int i=-9;i < 10; i+=2){
        for(int j=-9;j < 10; j+=2){
            m_body->setPosition(QVector3D(i, 0, j));
            m_body->draw();
        }
    }
    m_plan->draw();

    m_camera->setIsOrthogonal(!isOrtho);
    m_camera->setPosition(m_vector3);
    glViewport(0,height/2,width/2,height/2);
    for(int i=-9;i < 10; i+=2){
        for(int j=-9;j < 10; j+=2){
            m_body->setPosition(QVector3D(i, 0, j));
            m_body->draw();
        }
    }
    m_plan->draw();

    m_camera->setIsOrthogonal(!isOrtho);
    m_camera->setPosition(m_vector4);
    glViewport(width/2,height/2,width/2,height/2);
    for(int i=-9;i < 10; i+=2){
        for(int j=-9;j < 10; j+=2){
            m_body->setPosition(QVector3D(i, 0, j));
            m_body->draw();
        }
    }
    m_plan->draw();
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
    m_camera2->setAspect(aspect);
    //transformation de viewport
    glViewport(0, 0, w, h);
}

void RVWidget::mousePressEvent(QMouseEvent* event){
    m_oldPos = event->pos();
    if(m_oldPos.x() < this->width()/2){
        if(m_oldPos.y() > this->height()/2)
            zone = 1;
        else
            zone = 3;
    }else{
        if(m_oldPos.y() > this->height()/2)
            zone = 2;
        else
            zone = 4;
    }
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
    m_camera2->setFov(newFov);
    this->update();
}


void RVWidget::changeOpacity(int opacity){
//    m_body->setOpacity(opacity*0.01f);
    m_plan->setOpacity(opacity*0.01f);
    this->update();
}

void RVWidget::changeWireframe(int wireframe){
    m_body->setWireframe(wireframe);
    this->update();
}

void RVWidget::changeCulling(int culling){
    m_body->setCulling(culling);
    this->update();
}

void RVWidget::changeScale(int scale){
    m_plan->setScale(scale*0.1f);
    this->update();
}

void RVWidget::changeSaturation(int g){
    float color = g*0.01f;
    m_body->setGlobalColor(QVector3D(color,color,color));
    this->update();
}

void RVWidget::keyPressEvent(QKeyEvent *event){

    int x = 0;
    int y = 0;
    int z = 0;

    if(event->key() == Qt::Key_Down){
        QVector3D vector = m_camera->position();
        vector.setY(vector.y()-1.0f);
        m_camera->setPosition(vector);
        y--;
    }
    if(event->key() == Qt::Key_Up){
        QVector3D vector = m_camera->position();
        vector.setY(vector.y()+1.0f);
        m_camera->setPosition(vector);
        y++;
    }
    if(event->key() == Qt::Key_Left){
        QVector3D vector = m_camera->position();
        vector.setX(vector.x()-1.0f);
        m_camera->setPosition(vector);
        x--;
    }
    if(event->key() == Qt::Key_Right){
        QVector3D vector = m_camera->position();
        vector.setX(vector.x()+1.0f);
        m_camera->setPosition(vector);
        x++;
    }

    if(zone == 0){
        m_vector1 = QVector3D(m_vector1.x()+x,m_vector1.y()+y,m_vector1.z()+z);
        m_vector2 = QVector3D(m_vector2.x()+x,m_vector2.y()+y,m_vector2.z()+z);
        m_vector3 = QVector3D(m_vector3.x()+x,m_vector3.y()+y,m_vector3.z()+z);
        m_vector4 = QVector3D(m_vector4.x()+x,m_vector4.y()+y,m_vector4.z()+z);
    }else {
        switch (zone) {
            case 1:
                m_vector1 = QVector3D(m_vector1.x()+x,m_vector1.y()+y,m_vector1.z()+z);
                break;
            case 2:
                m_vector2 = QVector3D(m_vector2.x()+x,m_vector2.y()+y,m_vector2.z()+z);
                break;
            case 3:
                m_vector3 = QVector3D(m_vector3.x()+x,m_vector3.y()+y,m_vector3.z()+z);
                break;
            case 4:
                m_vector4 = QVector3D(m_vector4.x()+x,m_vector4.y()+y,m_vector4.z()+z);
                break;
        }
    }
    this->update();
}

void RVWidget::setOrthogonale(bool ortho){
    m_camera->setIsOrthogonal(ortho);
    isOrtho = ortho;
    this->update();
}
