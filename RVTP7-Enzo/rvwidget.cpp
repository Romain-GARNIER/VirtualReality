/*!
  \file rvwidget.cpp
  \brief Définition de la classe RVWidget.
  \author  Leo Donati
  \date    2019-2020
  \version 3.0 (tutoriel n°3)

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/
#include "rvwidget.h"

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    m_angularVelocityX = 0;
    m_angularVelocityY = 3;
    m_angularVelocityZ = 0;
    m_timer = new QTimer(this);
    m_animation = false;

    grabKeyboard();
    m_time = QTime();
    m_time.start();
    m_nbOfPaint = 0;
    subjView = false;
}

RVWidget::~RVWidget()
{
    makeCurrent();
    delete m_camera;
    delete m_batiment;
    delete m_sphere;
    delete m_torus;
    delete m_timer;
    delete m_trajectory;
    delete m_bb8;
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    float scale = float(this->width())/this->height();

    m_camera = new RVSphericalCamera();
    m_camera->setAspect(scale);
    m_camera->setIsOrthogonal(false);
    m_camera->setTarget(QVector3D(0, 50, -100));
    m_camera->setZMin(2);
    m_camera->setZMax(500);
    static_cast<RVSphericalCamera*>(m_camera)->setRho(70);

    m_camera2 = new RVSubjectiveCamera();
    m_camera2->setZMax(2000);
    m_camera2->setPosition(QVector3D(0,50,-100));
    m_camera2->setOriginY(m_camera2->position().y());
    m_camera2->setFov(45);

    m_light = new RVLight();
    m_light->setAmbient(QColor(80, 80, 80));
    m_light->setPosition(QVector3D(0, 150, -100));

    m_batiment = new RVModel("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/model/IUT_INFO.X");
    m_batiment->setCamera(m_camera2);
    m_batiment->setLight(m_light);
    m_batiment->initialize();

    m_sphere = new RVSphere(5.0);
    m_sphere->setCamera(m_camera2);
    m_sphere->setPosition(QVector3D(0, 50, -50));
    m_sphere->setTexture(":/textures/wood.png");
    m_sphere->setLight(m_light);
    m_sphere->initialize();

    m_torus = new RVTorus(1.0, 10.0);
    m_torus->setCamera(m_camera2);
    m_torus->setPosition(QVector3D(200, 50, -100));
    m_torus->setFS(":/shaders/FS_lit_damier.fsh");
    m_torus->setLight(m_light);
    m_torus->initialize();

    m_bb8 = new RVBB8();
    m_bb8->setCamera(m_camera);
    m_bb8->setPosition(QVector3D(0, 20, -100));
    m_bb8->setLight(m_light);
    m_bb8->setScale(0.4f);
    m_bb8->setOrigin(QVector3D(-10.5,50,0));
    m_bb8->initialize();
    m_bb8->setCamera(m_camera);

    m_camera->setTarget(m_bb8->position());
    static_cast<RVSphericalCamera*>(m_camera)->setPhi(0.50);
    static_cast<RVSphericalCamera*>(m_camera)->setRho(150);
    m_scene.append(m_batiment);
    m_scene.append(m_sphere);
    m_scene.append(m_torus);
    m_scene.append(m_bb8);
    m_scene.setCamera(m_camera);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(10);
}

void RVWidget::paintGL()
{

    QPainter p(this);

    //début du code OpenGL
    p.beginNativePainting();
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_camera->setCameraType(RV_CAMERA_MONO);
        m_scene.draw();
        glDisable(GL_DEPTH_TEST);
    p.endNativePainting();
    //fin du code OpenGL

    //Calcul du fps
    m_nbOfPaint ++;
    float fps = m_nbOfPaint/(m_time.elapsed() * 0.001f);

    p.setPen(Qt::yellow);
    p.setFont(QFont("Arial", 12));
    p.drawText(5, 5, width(), height(), Qt::AlignLeft, "Fps = " + QString::number(fps, 'f',2) );
}

void RVWidget::resizeGL(int w, int h)
{
    float aspect = float(w)/h;
    m_camera->setAspect(aspect);

    //transformation de viewport
    glViewport(0, 0, w, h);
}

void RVWidget::update()
{
    int t = m_time.elapsed();
    //qDebug("temps qui passe = %d ms", t);

    if (m_animation) {
        m_scene.update(float(t));
    }
    if(!subjView){
        m_bb8->update(float(t*0.01));
        m_camera->setTarget(m_bb8->position());
    }
    else{
      m_camera2->update();
    }

    QOpenGLWidget::update();
}

void RVWidget::startAnimation()
{
    m_animation = ! m_animation;
    this->update();
}

void RVWidget::changeFov(int newFov)
{
    m_camera->setFov(newFov);
    this->update();
}

void RVWidget::changeOpacity(int newOpacity)
{
    //m_body->setOpacity(newOpacity * 0.01f);
    m_sphere->setOpacity(newOpacity * 0.01f);
}

void RVWidget::changeWireFrame(bool b)
{
    m_sphere->setWireFrame(b);
}

void RVWidget::changeCulling(bool b)
{
    m_batiment->setCulling(b);
}

void RVWidget::changeScale(int s)
{
    m_sphere->setScale(s*0.01f);
}

void RVWidget::changeSaturation(int s)
{
    m_batiment->setGlobalColor(QColor(s, s, s));
}

void RVWidget::changeCameraType(bool b)
{
    m_camera->setIsOrthogonal(!b);
}

void RVWidget::mousePressEvent(QMouseEvent *event)
{
    m_oldPos = event->pos();
}

void RVWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = float(event->x() - m_oldPos.x()) / width();
    float dy = float(event->y() - m_oldPos.y()) / height();
    float angleX = 180 * dy;
    float angleY = 180 * dx;
    //m_body->rotate(angleX, QVector3D(1, 0, 0));
    //m_body->rotate(angleY, QVector3D(0, 1, 0));
    float oldPhi = static_cast<RVSphericalCamera*>(m_camera)->phi();
    float oldTheta = static_cast<RVSphericalCamera*>(m_camera)->theta();

    if(!subjView){
        static_cast<RVSphericalCamera*>(m_camera)->setPhi(oldPhi+qDegreesToRadians(angleX));
        static_cast<RVSphericalCamera*>(m_camera)->setTheta(oldTheta+qDegreesToRadians(angleY));
    }
    else{
        m_camera2->turn(dx);
        m_camera2->tilt(dy);
    }



    m_oldPos = event->pos();

    update();
    //QOpenGLWidget::update();
}

void RVWidget::keyPressEvent(QKeyEvent *event)
{
    QVector3D camPos = m_camera->position();
    float oldPhi = static_cast<RVSphericalCamera*>(m_camera)->phi();
    float oldTheta = static_cast<RVSphericalCamera*>(m_camera)->theta();
    float deltamove = 3.0f;
    float deltaturn = 0.4f;
    switch (event->key())
    {
    case Qt::Key_Left:
        m_camera2->turn(deltaturn);
        break;
    case Qt::Key_Right:
        m_camera2->turn(-deltaturn);
        break;
    case Qt::Key_Up:
        m_camera2->tilt(deltaturn);
        break;
    case Qt::Key_Down:
        m_camera2->tilt(-deltaturn);
        break;
    case Qt::Key_Z:
        if(subjView){
          m_camera2->move(deltamove);
        }
        else{
           m_bb8->setVelocity(m_bb8->velocity()+0.0005f);
        }
        break;
    case Qt::Key_S:
        if(subjView){
          m_camera2->move(-deltamove);
        }
        else{
            if(m_bb8->velocity() - 0.0005 >= 0){
               m_bb8->setVelocity(m_bb8->velocity()-0.0005f);
            }
            else{
              m_bb8->setVelocity(0);
            }
        }
        break;
    case Qt::Key_Q:
        if(subjView){
           m_camera2->lateral(-deltamove);
        }
        else{
            m_bb8->setLacet(m_bb8->lacet()+2);
            static_cast<RVSphericalCamera*>(m_camera)->setTheta(oldTheta-qDegreesToRadians(2.0));
        }
        break;
    case Qt::Key_D:
        if(subjView){
            m_camera2->lateral(deltamove);
        }
        else{
            m_bb8->setLacet(m_bb8->lacet()-2);
            static_cast<RVSphericalCamera*>(m_camera)->setTheta(oldTheta+qDegreesToRadians(2.0));
        }
        break;
    case Qt::Key_Control:
        if(subjView){
           m_camera2->crouch();
        }
        break;
    case Qt::Key_Space:
        if(subjView){
          m_camera2->jump();
        }
        break;
    case Qt::Key_C:
        if(subjView){
            subjView = false;
            m_scene.setCamera(m_camera);
        }
        else{
            subjView = true;
            m_scene.setCamera(m_camera2);
        }
        break;
    }
    m_camera->setPosition(camPos);
}
