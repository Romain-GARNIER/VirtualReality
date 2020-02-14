#ifndef RVAIRPLANE_H
#define RVAIRPLANE_H

#include "rvmodel.h"

class RVAirplane : public RVModel
{
public:
    RVAirplane();

protected:
    float m_velocity;
    float m_accelerationpour;
};

#endif // RVAIRPLANE_H
