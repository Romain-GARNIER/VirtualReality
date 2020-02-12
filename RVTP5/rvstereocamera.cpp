#include "rvstereocamera.h"

RVStereoCamera::RVStereoCamera()
    :RVCamera()
{
    m_eyeDistance = 4;
    m_focalDistance = 60;
    m_cameraType = RV_CAMERA_MONO;

}

int RVStereoCamera::cameraType() const
{
    return m_cameraType;
}

void RVStereoCamera::setCameraType(int cameraType)
{
    m_cameraType = cameraType;
}

float RVStereoCamera::eyeDistance() const
{
    return m_eyeDistance;
}

void RVStereoCamera::setEyeDistance(float eyeDistance)
{
    m_eyeDistance = eyeDistance;
}

float RVStereoCamera::focalDistance() const
{
    return m_focalDistance;
}

void RVStereoCamera::setFocalDistance(float focalDistance)
{
    m_focalDistance = focalDistance;
}

QMatrix4x4 RVStereoCamera::viewMatrix(){
    if(m_cameraType == RV_CAMERA_MONO)
        return RVCamera::viewMatrix();
    if(m_cameraType == RV_CAMERA_LEFT)
        return leftViewMatrix();
    if(m_cameraType == RV_CAMERA_RIGHT)
        return rightViewMatrix();
}

QMatrix4x4 RVStereoCamera::leftViewMatrix(){

}
