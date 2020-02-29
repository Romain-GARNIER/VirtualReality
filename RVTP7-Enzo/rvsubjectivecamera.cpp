#include "rvsubjectivecamera.h"

RVSubjectiveCamera::RVSubjectiveCamera()
        :RVStereoCamera()
{
    m_yaw = 0;
    m_pitch = 0;
    crouched = false;
    jumping = false;
    landing = false;
    crouching_coeff= 10.0f;
    jumping_coeff = 20.0f;
    jumping_velocity = 1.0f;
    originY = m_position.y();
}

void RVSubjectiveCamera::updateTarget()
{
    float x = qCos(m_pitch) * qCos(m_yaw);
    float y = qSin(m_pitch);
    float z = - qCos(m_pitch) * qSin(m_yaw);
    this->setTarget(m_position + QVector3D(x,y,z));
}

float RVSubjectiveCamera::getOriginY() const
{
    return originY;
}

void RVSubjectiveCamera::setOriginY(float value)
{
    originY = value;
}

bool RVSubjectiveCamera::getJumping() const
{
    return jumping;
}

void RVSubjectiveCamera::setJumping(bool value)
{
    jumping = value;
}

void RVSubjectiveCamera::update()
{
    if(jumping){
        if(m_position.y() + jumping_velocity > getOriginY() + jumping_coeff){
            m_position.setY(getOriginY() + jumping_coeff);
            jumping = false;
            landing = true;
        }
        else{
            m_position.setY(m_position.y() + jumping_velocity);
        }
    }
    else if(landing){
        if(m_position.y() - jumping_velocity < getOriginY()){
            m_position.setY(getOriginY());
            landing = false;
            jumping=false;
        }
        else{
            m_position.setY(m_position.y() - jumping_velocity);
        }
    }
    updateTarget();
}

bool RVSubjectiveCamera::getCrouched() const
{
    return crouched;
}

void RVSubjectiveCamera::setCrouched(bool value)
{
    crouched = value;
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

void RVSubjectiveCamera::move(float d)
{
    float ptx = m_target.x() - m_position.x();
    float pty = m_target.y() - m_position.y();
    float ptz = m_target.z() - m_position.z();

    QVector3D dpt = QVector3D(ptx,pty,ptz)*d;

    float newPx = m_position.x() + dpt.x();
    float newPz = m_position.z() + dpt.z();

    m_position.setX(newPx);
    m_position.setZ(newPz);
    updateTarget();

}

void RVSubjectiveCamera::lateral(float d)
{
    QVector3D rightVector = QVector3D::crossProduct(m_target, m_position);
    rightVector.normalize();
    float newX = d*rightVector.x() + m_position.x();
    float newZ = d*rightVector.z() + m_position.z();
    m_position.setX(newX);
    m_position.setZ(newZ);
    updateTarget();
}

void RVSubjectiveCamera::turn(float angle)
{
    setYaw(yaw() + qRadiansToDegrees(angle)/180); //to change
}

void RVSubjectiveCamera::tilt(float angle)
{
    setPitch(pitch() + qRadiansToDegrees(angle)/180); //to change
}

void RVSubjectiveCamera::crouch()
{
    if(crouched){
        m_position.setY(m_position.y() + crouching_coeff);
        crouched = false;
    }
    else{
        m_position.setY(m_position.y() - crouching_coeff);
        crouched = true;
    }
    updateTarget();
}

void RVSubjectiveCamera::jump()
{
    if(!landing && !jumping){
        this->jumping = true;
    }
}

void RVSubjectiveCamera::setPosition(const QVector3D &position)
{
    RVCamera::setPosition(position);
    updateTarget();
}
