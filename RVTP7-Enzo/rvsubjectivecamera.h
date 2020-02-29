#ifndef RVSUBJECTIVECAMERA_H
#define RVSUBJECTIVECAMERA_H

#include "rvstereocamera.h"

class RVSubjectiveCamera : public RVStereoCamera
{
public:
    RVSubjectiveCamera();

    float yaw() const;
    void setYaw(float yaw);

    float pitch() const;
    void setPitch(float pitch);

    void move(float d);
    void lateral(float d);
    void turn(float angle);
    void tilt(float angle);
    void crouch();
    void jump();

    void setPosition(const QVector3D &position) override;

    bool getCrouched() const;
    void setCrouched(bool value);

    bool getJumping() const;
    void setJumping(bool value);
    void update();

    float getOriginY() const;
    void setOriginY(float value);

protected:
    float m_yaw; //lacet
    float m_pitch; //tangage

private:
    void updateTarget();
    bool crouched;
    bool jumping;
    bool landing;
    float crouching_coeff;
    float jumping_coeff;
    float jumping_velocity;
    float originY;

};

#endif // RVSUBJECTIVECAMERA_H
