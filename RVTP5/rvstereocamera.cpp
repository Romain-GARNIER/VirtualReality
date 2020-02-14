#include "rvstereocamera.h"
#include <qmath.h>

RVStereoCamera::RVStereoCamera()
    :RVCamera()
{
    m_eyeDistance = 4;
    m_focalDistance = 60;
    m_cameraType = RV_CAMERA_MONO;
}

int RVStereoCamera::cameraType() const
{
    return m_cameraType;
}

void RVStereoCamera::setCameraType(int cameraType)
{
    m_cameraType = cameraType;
}

float RVStereoCamera::eyeDistance() const
{
    return m_eyeDistance;
}

void RVStereoCamera::setEyeDistance(float eyeDistance)
{
    m_eyeDistance = eyeDistance;
}

float RVStereoCamera::focalDistance() const
{
    return m_focalDistance;
}

void RVStereoCamera::setFocalDistance(float focalDistance)
{
    m_focalDistance = focalDistance;
}

QMatrix4x4 RVStereoCamera::viewMatrix(){
    if(m_cameraType == RV_CAMERA_MONO)
        return RVCamera::viewMatrix();
    if(m_cameraType == RV_CAMERA_LEFT)
        return leftViewMatrix();
    if(m_cameraType == RV_CAMERA_RIGHT)
        return rightViewMatrix();
}

QMatrix4x4 RVStereoCamera::projectionMatrix(){
    if(m_cameraType == RV_CAMERA_MONO)
        return RVCamera::projectionMatrix();
    if(m_cameraType == RV_CAMERA_LEFT)
        return leftProjectionMatrix();
    if(m_cameraType == RV_CAMERA_RIGHT)
        return rightProjectionMatrix();
}

QMatrix4x4 RVStereoCamera::leftViewMatrix()
{
    QVector3D visee = m_target - m_position;
    QVector3D interOeil = QVector3D::crossProduct(visee, m_up);
    interOeil.normalize();
    QVector3D posOeilGauche = m_position + (interOeil * (-m_eyeDistance/2));
    QVector3D cibleGauche = m_target + (interOeil * (-m_eyeDistance/2));

    QMatrix4x4 vue;
    vue.lookAt(posOeilGauche, cibleGauche, m_up);
    return vue;
}

QMatrix4x4 RVStereoCamera::rightViewMatrix()
{
    QVector3D visee = m_target - m_position;
    QVector3D interOeil = QVector3D::crossProduct(visee, m_up);
    interOeil.normalize();
    QVector3D posOeilDroite = m_position + interOeil * (m_eyeDistance/2);
    QVector3D cibleDroite = m_target + interOeil * (+m_eyeDistance/2);

    QMatrix4x4 vue;
    vue.lookAt(posOeilDroite, cibleDroite, m_up);
    return vue;
}

QMatrix4x4 RVStereoCamera::leftProjectionMatrix()
{
    float top, bottom, left, right;
    float tanFovOver2 = qTan(qDegreesToRadians(m_fov/2));

    top = m_zMin * tanFovOver2;
    bottom = - top;

    float a = m_aspect * tanFovOver2 * m_focalDistance;
    float b = a - m_eyeDistance/2;
    float c = a + m_eyeDistance/2;

    left = -b * m_zMin / m_focalDistance;
    right = c * m_zMin / m_focalDistance;

    QMatrix4x4 proj;
    proj.frustum(left, right, bottom, top, m_zMin, m_zMax);
    return proj;
}

QMatrix4x4 RVStereoCamera::rightProjectionMatrix()
{
    float top, bottom, left, right;
    float tanFovOver2 = qTan(qDegreesToRadians(m_fov/2));

    top = m_zMin * tanFovOver2;
    bottom = - top;

    float a = m_aspect * tanFovOver2 * m_focalDistance;
    float b = a - m_eyeDistance/2;
    float c = a + m_eyeDistance/2;

    left = -c * m_zMin / m_focalDistance;
    right = b * m_zMin / m_focalDistance;

    QMatrix4x4 proj;
    proj.frustum(left, right, bottom, top, m_zMin, m_zMax);
    return proj;
}
