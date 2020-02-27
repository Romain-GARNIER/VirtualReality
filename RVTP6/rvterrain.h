#ifndef RVTERRAIN_H
#define RVTERRAIN_H

#include "rvsurface.h"

class RVTerrain : public RVSurface
{
public:
    RVTerrain();
    RVTerrain(double width);
    ~RVTerrain();

    QOpenGLTexture *heightmap() const;
    void setHeightmap(QString textureFilename);

    float heightFactor() const;
    void setHeightFactor(float heightFactor);

protected:
    float x(double s, double t) override;
    float y(double s, double t) override;
    float z(double s, double t) override;

    QOpenGLTexture* m_heightmap;
    float m_heightFactor;
};

#endif // RVTERRAIN_H
