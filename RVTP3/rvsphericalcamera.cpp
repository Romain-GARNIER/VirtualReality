#include "rvsphericalcamera.h"

RVSphericalCamera::RVSphericalCamera()
{
    m_rho = 10;
    m_phi = 0;
    m_theta = 0;
}

float RVSphericalCamera::phi() const
{
    return m_phi;
}

void RVSphericalCamera::setPhi(float phi)
{
    if(phi > -M_PI_2 ||  phi < M_PI_2 ){
        m_phi = phi;
        update_position();
    }
}

float RVSphericalCamera::rho() const
{
    return m_rho;
}

void RVSphericalCamera::setRho(float rho)
{
    if(rho > 0){
        m_rho = rho;
        update_position();
    }
}

float RVSphericalCamera::theta() const
{
    return m_theta;
}

void RVSphericalCamera::setTheta(float theta)
{
    m_theta = theta;
    update_position();
}

void RVSphericalCamera::update_position(){
    float x,y,z;

    x = m_target.x() + m_rho*qCos(m_phi)*qCos(m_theta);
    y = m_target.y() + m_rho*qSin(m_phi);
    z = m_target.z() + m_rho*qCos(m_phi)*qSin(m_theta);

    m_position.setX(x);
    m_position.setY(y);
    m_position.setZ(z);
}
