#ifndef RVPLANE_H
#define RVPLANE_H

#include "rvbody.h"

class RVPlane : public RVBody
{
public:
    RVPlane();
    RVPlane(int longX, int largZ);

    int longX() const;
    void setLongX(int longX);

    int largZ() const;
    void setLargZ(int largZ);

private:
    int m_longX;
    int m_largZ;

protected:
    void RVPlane::initializeBuffer() override;
    void RVPlane::draw() override;
};

#endif // RVPLANE_H
