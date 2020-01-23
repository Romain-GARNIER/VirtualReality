#ifndef RVWIDGET_H
#define RVWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QTimer>
#include <QMouseEvent>

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

protected:
    QOpenGLBuffer m_vbo;
    QOpenGLBuffer m_ibo;
    QOpenGLShaderProgram m_program;
    float m_angleY;
    float m_angleX;
    QPoint m_oldPos;
    QTimer* m_timer;
    boolean m_rotate;
    int m_angleProj;
    float m_aspetcRatio;
    int m_opacity;

private slots:
    void update();

protected slots:
    void startAnimation();
    void changeFov(int angle);    
    void changeOpacity(int opacity);
};
#endif // RVWIDGET_H
