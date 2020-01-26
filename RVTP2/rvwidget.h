#ifndef RVWIDGET_H
#define RVWIDGET_H

#include "rvcamera.h"
#include "rvbody.h"
#include "rvpyramid.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>

class RVWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    RVWidget(QWidget *parent = nullptr);
    ~RVWidget() override;

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

protected:
    void initializeBuffer();
    void initializeShaders();
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

protected:
    QOpenGLBuffer m_vbo;
    QOpenGLBuffer m_ibo;
    QOpenGLShaderProgram m_program;
    float m_angleY;
    float m_angleX;
    QPoint m_oldPos;
    QTimer* m_timer;
    bool m_rotate;
    int m_angleProj;
    float m_aspetcRatio;
    RVCamera *m_camera;         //!<    Pointeur sur la caméra à utiliser lors du rendu
    RVCamera *m_camera2;
    RVBody   *m_body;           //!<    Pointeur sur l'objet 3D montré dans le widget
    RVBody   *m_plan;           //!<    Pointeur sur l'objet 3D montré dans le widget
    float m_angularVelocityX;   //!<    Vitesse angulaire autour de l'axe x
    float m_angularVelocityY;   //!<    Vitesse angulaire autour de l'axe y
    float m_angularVelocityZ;   //!<    Vitesse angulaire autour de l'axe z
    bool m_animation;           //!<    Booléen qui dit si l'animation est activée ou pas
    QVector3D m_vector1;
    QVector3D m_vector2;
    QVector3D m_vector3;
    QVector3D m_vector4;

    bool isOrtho;
    int zone;

private slots:
    void update();

protected slots:
    void startAnimation();
    void changeFov(int angle);
    void changeOpacity(int opacity);
    void changeWireframe(int);
    void changeCulling(int);
    void changeScale(int);
    void changeSaturation(int g);
    void setOrthogonale(bool ortho);
};
#endif // RVWIDGET_H
