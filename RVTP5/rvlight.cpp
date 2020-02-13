#include "rvlight.h"
#include <QtMath>

RVLight::RVLight()
{
    m_position = QVector3D(10, 0, 10);
    m_ambient = QColor(100, 100, 100);
    m_diffuse = QColor(255, 255, 255);
    m_specular = QColor(255, 255, 255);
}

QVector3D RVLight::position() const
{
    return m_position;
}

void RVLight::setPosition(const QVector3D &position)
{
    m_position = position;
}

QColor RVLight::ambient() const
{
    return m_ambient;
}

void RVLight::setAmbient(const QColor &ambient)
{
    m_ambient = ambient;
}

QColor RVLight::diffuse() const
{
    return m_diffuse;
}

void RVLight::setDiffuse(const QColor &diffuse)
{
    m_diffuse = diffuse;
}

QColor RVLight::specular() const
{
    return m_specular;
}

void RVLight::setSpecular(const QColor &specular)
{
    m_specular = specular;
}

void RVLight::update(float time){
    float x, y, z, t;

    //Bounce
//    float hMax, tMax, a, b;

//    hMax = 20;
//    tMax = 10;
//    a = -2*(hMax)/tMax;
//    b = 2*hMax;

//    t = fmod(time*0.001,tMax);

//    x = position().x();
//    y = float(a*pow(t,2) + b*t);
//    z = position().y();

    //Cirlce
    float m_rayon = 100;
    float m_periode = 10;
    float m_omega = (2 * M_PI) / m_periode;

    time = time*0.001;

    x = m_rayon * qCos(m_omega * time);
    y = m_rayon * qSin(m_omega * time);
    z = m_rayon * qSin(m_omega * time);

    setPosition(QVector3D(x,y,z));
}
