#include "rvstereocamera.h"
#include <qmath.h>

RVStereoCamera::RVStereoCamera()
    :RVCamera()
{
    m_eyeDistance = 4;
    m_focalDistance = 100;
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

QMatrix4x4 RVStereoCamera::leftViewMatrix(){
    QVector3D PT;
    QVector3D v;
    QVector3D position;
    QVector3D target;
    float norme_v;
    float vX, vY, vZ;

    PT = QVector3D();
    PT.setX(m_target.x() - m_position.x());
    PT.setY(m_target.y() - m_position.y());
    PT.setZ(m_target.z() - m_position.z());

    v = PT.operator*=(m_up);

    norme_v = sqrt(pow(v.x(),2) + pow(v.y(),2) + pow(v.z(),2));
    vX = v.x()/norme_v;
    vY = v.y()/norme_v;
    vZ = v.z()/norme_v;

    position = QVector3D();
    position.setX(m_position.x() - m_eyeDistance/2*vX);
    position.setY(m_position.y() - m_eyeDistance/2*vY);
    position.setZ(m_position.z() - m_eyeDistance/2*vZ);


    target = QVector3D();
    target.setX(m_target.x() - m_eyeDistance/2*vX);
    target.setY(m_target.y() - m_eyeDistance/2*vY);
    target.setZ(m_target.z() - m_eyeDistance/2*vZ);


    QMatrix4x4 view;
    view.lookAt(m_position, m_target, m_up);
    return view;
}


QMatrix4x4 RVStereoCamera::leftProjectionMatrix()
{
    QMatrix4x4 proj;
    if (m_isOrthogonal) {
        proj.ortho(-m_fov * m_aspect/10, m_fov * m_aspect/10, -m_fov/10, m_fov/10, m_zMin, m_zMax);
    }
    else {
        float top, bottom, left, right, a, b, c;

        top = m_zMin * qTan((m_fov * M_PI / 180.0f)/2);
        bottom = top * -1;

        a = m_focalDistance*top/m_zMin;
        b = a - m_eyeDistance/2;
        c = a + m_eyeDistance/2;

        left = (m_zMin*b/m_focalDistance)*-1;
        right = m_zMin*c/m_focalDistance;

        proj.frustum(left, right, bottom, top, m_zMin, m_zMax);
    }
    return proj;
}


QMatrix4x4 RVStereoCamera::rightViewMatrix(){
    QVector3D PT;
    QVector3D v;
    QVector3D position;
    QVector3D target;
    float norme_v;
    float vX, vY, vZ;

    PT = QVector3D();
    PT.setX(m_target.x() + m_position.x());
    PT.setY(m_target.y() + m_position.y());
    PT.setZ(m_target.z() + m_position.z());

    v = PT.operator*=(m_up);

    norme_v = sqrt(pow(v.x(),2) + pow(v.y(),2) + pow(v.z(),2));
    vX = v.x()/norme_v;
    vY = v.y()/norme_v;
    vZ = v.z()/norme_v;

    position = QVector3D();
    position.setX(m_position.x() - m_eyeDistance/2*vX);
    position.setY(m_position.y() - m_eyeDistance/2*vY);
    position.setZ(m_position.z() - m_eyeDistance/2*vZ);


    target = QVector3D();
    target.setX(m_target.x() - m_eyeDistance/2*vX);
    target.setY(m_target.y() - m_eyeDistance/2*vY);
    target.setZ(m_target.z() - m_eyeDistance/2*vZ);


    QMatrix4x4 view;
    view.lookAt(m_position, m_target, m_up);
    return view;
}


QMatrix4x4 RVStereoCamera::rightProjectionMatrix()
{
    QMatrix4x4 proj;
    if (m_isOrthogonal) {
        proj.ortho(-m_fov * m_aspect/10, m_fov * m_aspect/10, -m_fov/10, m_fov/10, m_zMin, m_zMax);
    }
    else {
        float top, bottom, left, right, a, b, c;

        top = m_zMin * qTan((m_fov * M_PI/180.0f)/2);
        bottom = top * -1;

        a = m_focalDistance*top/m_zMin;
        b = a - m_eyeDistance/2;
        c = a + m_eyeDistance/2;

        left = (m_zMin*c/m_focalDistance)*-1;
        right = m_zMin*b/m_focalDistance;

        proj.frustum(left, right, bottom, top, m_zMin, m_zMax);
    }
    return proj;
}
