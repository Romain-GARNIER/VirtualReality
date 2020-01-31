#ifndef RVSPHERICCAMERA_H
#define RVSPHERICCAMERA_H

#include <qmath.h>

#include "rvcamera.h"

class RVSphericalCamera : public RVCamera
{
public:
    RVSphericalCamera();

    float phi() const;
    void setPhi(float phi);

    float rho() const;
    void setRho(float rho);

    float theta() const;
    void setTheta(float theta);

protected:
    float m_phi;
    float m_theta;
    float m_rho;

private:
    void update_position();
};

#endif // RVSPHERICCAMERA_H
