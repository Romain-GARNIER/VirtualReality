#ifndef RVSUBJECTIVECAMERA_H
#define RVSUBJECTIVECAMERA_H

#include "rvstereocamera.h"

class RVSubjectiveCamera : public RVStereoCamera
{
public:
    RVSubjectiveCamera();

    void updateTarget();

    float yaw() const;
    void setYaw(float yaw);

    float pitch() const;
    void setPitch(float pitch);

    void move(float d);
    void lateral(float d);
    void turn(float angle);
    void tilt(float angle);

    void setPosition(const QVector3D &position) override;

protected:
    float m_yaw;
    float m_pitch;
};

#endif // RVSUBJECTIVECAMERA_H
