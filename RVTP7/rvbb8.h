#ifndef RVBB8_H
#define RVBB8_H

#include "rvmodel.h"

class RVBB8 : public RVModel
{
public:
    RVBB8();

    void draw() override;
    void update(float t) override;

    float velocity() const;
    void setVelocity(float velocity);

    float lacet() const;
    void setLacet(float lacet);

private:
    float m_velocity;
    float m_lacet;
};

#endif // RVBB8_H
