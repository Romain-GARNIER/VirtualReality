#include "rvbb8.h"

RVBB8::RVBB8()
    :RVModel ("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/bb8.obj")
{
    m_meshes[0]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/HEAD diff MAP.jpg");
    m_meshes[1]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/Head ring diff MAP.jpg");
    m_meshes[2]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/Head ring diff MAP.jpg");
    m_meshes[3]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/Head ring MAP.jpg");
    m_meshes[4]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/Head top diff MAP.jpg");
    m_meshes[5]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/Head top diff MAP.jpg");
    m_meshes[6]->setTexture("/Users/garni/Documents/GitHub/VirtualReality/RVTP7/bb8/Body diff MAP.jpg");

    m_velocity = 0;
    m_lacet = 0.01;
}

void RVBB8::draw()
{
    m_meshes[0]->draw();
    m_meshes[1]->draw();
    m_meshes[2]->draw();
    m_meshes[3]->draw();
    m_meshes[4]->draw();
    m_meshes[5]->draw();
    m_meshes[6]->draw();
}

void RVBB8::update(float t)
{
    float distance = m_velocity*t;
    float dx = distance * qSin(qDegreesToRadians(m_lacet));
     float dz = distance *  qCos(qDegreesToRadians(m_lacet));
    QVector3D vec = QVector3D(-dz,0,dx);
    for(int i = 0; i < 6; i++){
        m_meshes[i]->setOrientation(m_lacet,0,0);
    }
    translate(vec);
    m_meshes[6]->rotate(t*m_velocity, QVector3D::crossProduct(QVector3D(0,1,0), vec));
}

float RVBB8::velocity() const
{
    return m_velocity;
}

void RVBB8::setVelocity(float velocity)
{
    m_velocity = velocity;
}

float RVBB8::lacet() const
{
    return m_lacet;
}

void RVBB8::setLacet(float lacet)
{
    m_lacet = lacet;
}
