#include "rvsubjectivecamera.h"

RVSubjectiveCamera::RVSubjectiveCamera()
    :RVStereoCamera()
{
    m_yaw = 0;
    m_pitch = 0;
}

void RVSubjectiveCamera::updateTarget()
{
    float x = qCos(m_pitch) * qCos(m_yaw);
    float y = qSin(m_pitch);
    float z = - qCos(m_pitch) * qSin(m_yaw);
    this->setTarget(m_position + QVector3D(x,y,z));
}

void RVSubjectiveCamera::move(float d){
    m_position.setX(target().x() + d*(m_target.x() - m_position.x()));
    m_position.setZ(target().z() + d*(m_target.z() - m_position.z()));
    updateTarget();
}

void RVSubjectiveCamera::lateral(float d){
    QVector3D rightVector = QVector3D::crossProduct(m_target, m_position);
    rightVector.normalize();
    m_position.setX(target().x() + d*rightVector.x());
    m_position.setZ(target().z() + d*rightVector.z());
    updateTarget();
}

float RVSubjectiveCamera::yaw() const
{
    return m_yaw;
}

void RVSubjectiveCamera::setYaw(float yaw)
{
    m_yaw = yaw;
    updateTarget();
}

float RVSubjectiveCamera::pitch() const
{
    return m_pitch;
}

void RVSubjectiveCamera::setPitch(float pitch)
{
    m_pitch = pitch;
    updateTarget();
}

void RVSubjectiveCamera::turn(float angle){
    setYaw(yaw() + angle);
    updateTarget();
}

void RVSubjectiveCamera::tilt(float angle){
    setPitch(pitch() + angle);
    updateTarget();
}

void RVSubjectiveCamera::setPosition(const QVector3D &position)
{
    RVCamera::setPosition(position);
    updateTarget();
}
