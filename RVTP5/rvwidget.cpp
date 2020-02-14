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

#include "rvhelix.h"
#include "rvbounce.h"
#include "rvcircle.h"

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
}

RVWidget::~RVWidget()
{
    makeCurrent();
    delete m_camera;
    delete m_body;
    delete m_plane;
    delete m_sun;
    delete m_torus;
    delete m_skybox;
    delete m_timer;
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
    m_camera->setTarget(QVector3D(0, 0, 0));
    m_camera->setZMin(2);
    m_camera->setZMax(500);
    static_cast<RVSphericalCamera*>(m_camera)->setRho(60);

    m_light = new RVLight();
    m_light->setPosition(QVector3D(-10,20,20));

    m_cameraTrajectory = new RVCircle(100,120);
    m_cameraTrajectory->setCamera(m_camera);
    m_cameraTrajectory->setPosition(QVector3D(0, 0, 0));
    m_cameraTrajectory->setScale(1);
    m_cameraTrajectory->initialize();

    m_lightTrajectory = new RVCircle(100,30);
    m_lightTrajectory->setCamera(m_camera);
    m_lightTrajectory->setPosition(QVector3D(0, 0, 0));
    m_lightTrajectory->setScale(1);
    m_lightTrajectory->initialize();

    RVCircle *sunTrajectory = new RVCircle(0,1);
    sunTrajectory->setCamera(m_camera);
    sunTrajectory->setPosition(QVector3D(0, 0, 0));
    sunTrajectory->setScale(1);
    sunTrajectory->initialize();

    RVCircle *mercuryTrajectory = new RVCircle(15,7);
    mercuryTrajectory->setCamera(m_camera);
    mercuryTrajectory->setPosition(QVector3D(0, 0, 0));
    mercuryTrajectory->setScale(1);
    mercuryTrajectory->initialize();

    RVCircle *venusTrajectory = new RVCircle(35,10);
    venusTrajectory->setCamera(m_camera);
    venusTrajectory->setPosition(QVector3D(0, 0, 0));
    venusTrajectory->setScale(1);
    venusTrajectory->initialize();

    RVCircle *earthTrajectory = new RVCircle(50,20);
    earthTrajectory->setCamera(m_camera);
    earthTrajectory->setPosition(QVector3D(0, 0, 0));
    earthTrajectory->setScale(1);
    earthTrajectory->initialize();

//    m_body = new RVDice();
//    m_body->setCamera(m_camera);
//    m_body->setPosition(QVector3D(0,10,10));
//    m_body->setScale(5);
//    m_body->setTexture(":/textures/dice_texture.jpg", false);
//    m_body->setLight(m_light);
//    m_body->initialize();

//    m_plane = new RVPlane();
//    m_plane->setScale(3);
//    m_plane->setPosition(QVector3D(0, -5, 0));
//    m_plane->setCamera(m_camera);
//    m_plane->setTexture(":/textures/wood.png");
//    m_plane->setLight(m_light);
//    m_plane->initialize();

    m_sun = new RVSphere(10.0);
    m_sun->setCamera(m_camera);
    m_sun->setPosition(QVector3D(0, 0, 0));
    m_sun->setTexture(":/textures/2k_sun.jpg");
    m_sun->setLight(m_light);
    m_sun->setTrajectory(sunTrajectory);
    m_sun->initialize();

    m_mercury = new RVSphere(1.0);
    m_mercury->setCamera(m_camera);
    m_mercury->setPosition(QVector3D(0, 0, -15));
    m_mercury->setTexture(":/textures/2k_mercury.jpg");
    m_mercury->setLight(m_light);
    m_mercury->setTrajectory(mercuryTrajectory);
    m_mercury->initialize();

    m_venus = new RVSphere(2.0);
    m_venus->setCamera(m_camera);
    m_venus->setPosition(QVector3D(0, 0, 35));
    m_venus->setTexture(":/textures/2k_venus_atmosphere.jpg");
    m_venus->setLight(m_light);
    m_venus->setTrajectory(venusTrajectory);
    m_venus->initialize();

    m_earth = new RVSphere(2.0);
    m_earth->setCamera(m_camera);
    m_earth->setPosition(QVector3D(0, 0, 50));
    m_earth->setTexture(":/textures/2k_earth_daymap.jpg");
    m_earth->setLight(m_light);
    m_earth->setTrajectory(earthTrajectory);
    m_earth->initialize();

    m_torus = new RVTorus(1.0, 10.0);
    m_torus->setCamera(m_camera);
    m_torus->setPosition(QVector3D(0, 10, 0));
    m_torus->setFS(":/shaders/FS_lit_damier.fsh");
    m_torus->setLight(m_light);
    m_torus->initialize();

    m_skybox = new RVSkyBox();
    m_skybox->setCamera(m_camera);
    m_skybox->setPosition(QVector3D());
    m_skybox->setCubeTexture(":/textures/stars.jpg",      //left
                             ":/textures/stars.jpg",     //right
                             ":/textures/stars.jpg",     //front
                             ":/textures/stars.jpg",         //back
                             ":/textures/stars.jpg",         //top
                             ":/textures/stars.jpg");   //bottom
    m_skybox->setScale(100.0);
    m_skybox->initialize();

//    m_scene.append(m_body);
//    m_scene.append(m_plane);
    m_scene.append(m_sun);
    m_scene.append(m_mercury);
    m_scene.append(m_venus);
    m_scene.append(m_earth);
//    m_scene.append(m_torus);
    m_scene.setCamera(m_camera);

    m_scene.append(m_cameraTrajectory);
    m_scene.append(m_lightTrajectory);
    m_scene.append(sunTrajectory);
    m_scene.append(mercuryTrajectory);
    m_scene.append(venusTrajectory);
    m_scene.append(earthTrajectory);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(10);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_skybox->setPosition(m_camera->position());
    m_skybox->draw();

    glColorMask(true, false, false, false);
    m_camera->setCameraType(RV_CAMERA_LEFT);
    m_scene.draw();

    glClear(GL_DEPTH_BUFFER_BIT) ;
    glColorMask(true, true, false, false);
    m_camera->setCameraType(RV_CAMERA_RIGHT);
    m_scene.draw();

    glColorMask(true, true, true, true);
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

   if (m_animation) {
//       m_scene.update(float(t));
       m_camera->setPosition(m_cameraTrajectory->pos(t*0.001));
       m_light->setPosition(m_lightTrajectory->pos(t*0.001));
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
    m_plane->setOpacity(newOpacity * 0.01f);
    m_sun->setOpacity(newOpacity * 0.01f);
}

void RVWidget::changeWireFrame(bool b)
{
    m_sun->setWireFrame(b);
}

void RVWidget::changeCulling(bool b)
{
    m_body->setCulling(b);
}

void RVWidget::changeScale(int s)
{
    m_sun->setScale(s*0.01f);
}

void RVWidget::changeSaturation(int s)
{
    m_body->setGlobalColor(QColor(s, s, s));
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

    static_cast<RVSphericalCamera*>(m_camera)->setPhi(oldPhi+qDegreesToRadians(angleX));
    static_cast<RVSphericalCamera*>(m_camera)->setTheta(oldTheta+qDegreesToRadians(angleY));

    m_oldPos = event->pos();

    QOpenGLWidget::update();
}

void RVWidget::keyPressEvent(QKeyEvent *event)
{
    QVector3D camPos = m_camera->position();
    float deltaX = 0.2f;
    float deltaY = 0.2f;
    switch (event->key())
    {
    case Qt::Key_Left:
        camPos.setX(camPos.x() - deltaX);
        break;
    case Qt::Key_Right:
        camPos.setX(camPos.x() + deltaX);
        break;
    case Qt::Key_Up:
        camPos.setY(camPos.y() + deltaY);
        break;
    case Qt::Key_Down:
        camPos.setY(camPos.y() - deltaY);
        break;
    }
    m_camera->setPosition(camPos);
}

