#include "rvbounce.h"
#include "math.h"

RVBounce::RVBounce()
    :RVCurve()
{    
    m_hMax = 0;
    m_tMax = 0;
}

RVBounce::RVBounce(double hMax, double tMax)
    :RVCurve()
{
    m_hMax = hMax;
    m_tMax = tMax;
    m_a = -2*(hMax)/tMax;
    m_b = 2*hMax;
}

//void RVBounce::update(float time){
//    float y = pow(m_hMax,2)*time + m_tMax*time;
//    QVector3D position = this->position();
//    position.setY(y);

//    setPosition(position);
//}

float RVBounce::x(double t)
{
    return position().x();
}

float RVBounce::y(double t)
{
    t = fmod(t,m_tMax);
    float yValue = float(m_a*pow(t,2) + m_b*t);
    return yValue;
}

float RVBounce::z(double t)
{
    return position().z();
}
