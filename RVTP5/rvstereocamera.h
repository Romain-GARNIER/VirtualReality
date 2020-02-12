#ifndef RVSTEREOCAMERA_H
#define RVSTEREOCAMERA_H

#include "rvcamera.h"

#define RV_CAMERA_MONO 0
#define RV_CAMERA_LEFT 1
#define RV_CAMERA_RIGHT 2

class RVStereoCamera : public RVCamera
{
public:

    RVStereoCamera();

    int cameraType() const;
    void setCameraType(int cameraType);

    float eyeDistance() const;
    void setEyeDistance(float eyeDistance);

    float focalDistance() const;
    void setFocalDistance(float focalDistance);

    QMatrix4x4 leftViewMatrix();
    QMatrix4x4 leftProjectionMatrix();
    QMatrix4x4 rightViewMatrix();
    QMatrix4x4 rightProjectionMatrix();

    QMatrix4x4 viewMatrix() override;
    QMatrix4x4 projectionMatrix() override;

protected:
    float m_eyeDistance;
    float m_focalDistance;
    int m_cameraType;
};

#endif // RVSTEREOCAMERA_H
