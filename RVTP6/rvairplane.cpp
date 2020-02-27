#include "rvairplane.h"

#include <qmath.h>

RVAirplane::RVAirplane()
    :RVModel("C:\\Users\\garni\\Documents\\GitHub\\VirtualReality\\RVTuto6\\model\\GeeBee2.x")//RVDice();
{
    m_acceleration = 0;
    m_tangage = 0;
    m_roulis = 0;
    m_lacet = 0;
    m_velocity = 0;
//    this->rotate(20,QVector3D(0,0,1));

}

void RVAirplane::update(float time){
    float x, y, z;
    float coeff = -1 * qCos(qDegreesToRadians(m_tangage));
    float angleAirplane = 9.0f;

    m_velocity = m_acceleration;//*time;

    x = m_velocity * qSin(qDegreesToRadians(m_lacet))* coeff;
    y = m_velocity * qSin(qDegreesToRadians(m_tangage));
    z = m_velocity * qCos(qDegreesToRadians(m_lacet)) * coeff;

    setOrientation(m_lacet, m_tangage, m_roulis);
    translate(QVector3D(x,y,z));

    m_meshes.at(2)->rotate(m_velocity*time, QVector3D(x, y, z));
}

float RVAirplane::tangage() const
{
    return m_tangage;
}

void RVAirplane::setTangage(float tangage)
{
    m_tangage = tangage;
    update(0);
}

float RVAirplane::roulis() const
{
    return m_roulis;
}

void RVAirplane::setRoulis(float roulis)
{
    m_roulis = roulis;
    update(0);
}

float RVAirplane::lacet() const
{
    return m_lacet;
}

void RVAirplane::setLacet(float lacet)
{
    m_lacet = lacet;
    update(0);
}

float RVAirplane::acceleration() const
{
    return m_acceleration;
}

void RVAirplane::setAcceleration(float acceleration)
{
    m_acceleration = acceleration;
}

void RVAirplane::accelere(float acceleration){
    m_acceleration += acceleration;
    update(0);
}

void RVAirplane::decelere(float deceleration){
    if(m_acceleration > 0){
        m_acceleration -= deceleration;
        update(0);
    }
}
