#ifndef RVBOUNCE_H
#define RVBOUNCE_H

#include "rvcurve.h"
#include <QTime>

class RVBounce : public RVCurve
{
public:
    RVBounce();

    RVBounce(double hMax, double tMax);

protected:
    float x(double t) override;
    float y(double t) override;
    float z(double t) override;

    double m_hMax;
    double m_tMax;
    double m_a;
    double m_b;
};

#endif // RVBOUNCE_H
