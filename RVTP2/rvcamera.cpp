#include "rvcamera.h"

RVCamera::RVCamera()
{
    m_position = QVector3D(0, 0, 0);
    m_target = QVector3D(0, 0, -1);
    m_up = QVector3D(0, 1, 0);
    m_fov  = 40;
    m_aspect = 1.33f;
    m_zMax = 100;
    m_zMin  = 2;
    m_isOrthogonal = false;
}

QMatrix4x4 RVCamera::viewMatrix()
{
    QMatrix4x4 view;
    view.lookAt(m_position, m_target, m_up);
    return view;
}

QMatrix4x4 RVCamera::projectionMatrix()
{
    QMatrix4x4 proj;
    if(!m_isOrthogonal)
        proj.perspective(m_fov, m_aspect, m_zMin, m_zMax);
    else{
        float nearPlane = m_zMin;
        float farPlane = m_zMax;
        int bottom = -m_fov/4;
        int top = m_fov/4;
        int left = bottom*m_aspect;
        int right = top*m_aspect;
        proj.ortho(left,right,bottom,top,nearPlane,farPlane);
    }
    return proj;
}


QVector3D RVCamera::position() const
{
    return m_position;
}

void RVCamera::setPosition(const QVector3D &position)
{
    m_position = position;
}

QVector3D RVCamera::target() const
{
    return m_target;
}

void RVCamera::setTarget(const QVector3D &target)
{
    m_target = target;
}

QVector3D RVCamera::up() const
{
    return m_up;
}

void RVCamera::setUp(const QVector3D &up)
{
    m_up = up;
}

float RVCamera::zMin() const
{
    return m_zMin;
}

void RVCamera::setZMin(float zMin)
{
    m_zMin = zMin;
}

float RVCamera::zMax() const
{
    return m_zMax;
}

void RVCamera::setZMax(float zMax)
{
    m_zMax = zMax;
}

bool RVCamera::isOrthogonal() const
{
    return m_isOrthogonal;
}

void RVCamera::setIsOrthogonal(bool isOrthogonal)
{
    m_isOrthogonal = isOrthogonal;
}

float RVCamera::fov() const
{
    return m_fov;
}

void RVCamera::setFov(float fov)
{
    m_fov = fov;
}

float RVCamera::aspect() const
{
    return m_aspect;
}

void RVCamera::setAspect(float aspect)
{
    m_aspect = aspect;
}

