#ifndef RVAIRPLANE_H
#define RVAIRPLANE_H

#include "rvmodel.h"

class RVAirplane : public RVModel
{
public:
    RVAirplane();

    void update(float time) override;

    float tangage() const;
    void setTangage(float tangage);

    float roulis() const;
    void setRoulis(float roulis);

    float lacet() const;
    void setLacet(float lacet);

    float acceleration() const;
    void setAcceleration(float acceleration);

    void accelere(float acceleration);
    void decelere(float deceleration);

protected:
    float m_velocity;
    float m_acceleration;

    float m_tangage;
    float m_roulis;
    float m_lacet;
};

#endif // RVAIRPLANE_H
