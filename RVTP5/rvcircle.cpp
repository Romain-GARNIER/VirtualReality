#include "rvcircle.h"
#include "math.h"

RVCircle::RVCircle()
    :RVCurve()
{    
    m_rayon = 10;
    m_periode = 5;
}

RVCircle::RVCircle(double rayon, double periode)
    :RVCurve()
{
    m_rayon = rayon;
    m_periode = periode;

}

//void RVBounce::update(float time){
//    float y = pow(m_hMax,2)*time + m_tMax*time;
//    QVector3D position = this->position();
//    position.setY(y);

//    setPosition(position);
//}

float RVCircle::x(double t)
{
    m_omega = 2 * M_PI/m_periode;
    return m_rayon * qCos(m_omega * t);
}

float RVCircle::y(double t)
{

    return position().y();
}

float RVCircle::z(double t)
{
    m_omega = 2 * M_PI/m_periode;
    return m_rayon * qSin(m_omega * t);
}

double RVCircle::periode() const
{
    return m_periode;
}

void RVCircle::setPeriode(double periode)
{
    m_periode = periode;
}

double RVCircle::rayon() const
{
    return m_rayon;
}

void RVCircle::setRayon(double rayon)
{
    m_rayon = rayon;
}
