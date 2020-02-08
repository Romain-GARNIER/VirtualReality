#ifndef RVSPHERE_H
#define RVSPHERE_H

/*!
  \file rvsphere.h
  \brief Déclaration de la classe RVSphere.
  \author  Leo Donati
  \date    2019-2020
  \version 5.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Utilise RVsurface avec l'équation paramétrée utilisant les coordonnées sphériques
*/

#include "rvsurface.h"
#include "rvcurve.h"

class RVSphere : public RVSurface
{
public:
    RVSphere(double radius = 1.0);
    ~RVSphere() override;

    double radius() const;
    void setRadius(double radius);

    void update(float time);

    RVCurve *trajectory() const;
    void setTrajectory(RVCurve *trajectory);

protected:
    float x(double s, double t) override;
    float y(double s, double t) override;
    float z(double s, double t) override;

    double m_radius;
    RVCurve *m_trajectory;
};

#endif // RVSPHERE_H
