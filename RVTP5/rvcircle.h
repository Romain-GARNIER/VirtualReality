#ifndef RVCIRCLE_H
#define RVCIRCLE_H

#include "rvcurve.h"
#include <QTime>

class RVCircle : public RVCurve
{
public:
    RVCircle();

    RVCircle(double hMax, double tMax);

    double rayon() const;
    void setRayon(double rayon);

    double periode() const;
    void setPeriode(double periode);

protected:
    float x(double t) override;
    float y(double t) override;
    float z(double t) override;

    double m_rayon;
    double m_periode;
    double m_omega;
};

#endif // RVCIRCLE_H
