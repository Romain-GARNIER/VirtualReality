#include "rvterrain.h"

RVTerrain::RVTerrain()
    : RVSurface()
{
    double width = 100;
    m_minS = -width/2;
    m_maxS = +width/2;
    m_minT = -width/2;
    m_maxT = +width/2;
    m_numSegS = 50;
    m_numSegT = 50;

    m_VSFileName = ":/shaders/VS_heightmap.vsh";
}

RVTerrain::RVTerrain(double width)
:RVSurface()
{
    m_minS = -width/2;
    m_maxS = +width/2;
    m_minT = -width/2;
    m_maxT = +width/2;
    m_numSegS = 50;
    m_numSegT = 50;

    m_VSFileName = ":/shaders/VS_heightmap.vsh";
}

RVTerrain::~RVTerrain(){

}

QOpenGLTexture *RVTerrain::heightmap() const
{
    return m_heightmap;
}

void RVTerrain::setHeightmap(QString textureFilename)
{
   m_heightmap = new QOpenGLTexture(QImage(textureFilename).mirrored());
}

float RVTerrain::heightFactor() const
{
    return m_heightFactor;
}

void RVTerrain::setHeightFactor(float heightFactor)
{
    m_heightFactor = heightFactor;
}

float RVTerrain::x(double s, double t){
    return s;
}

float RVTerrain::y(double s, double t){
    return 0;
}
float RVTerrain::z(double s, double t){
    return t;
}
