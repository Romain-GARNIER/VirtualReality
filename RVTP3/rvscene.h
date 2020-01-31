#ifndef RVSCENE_H
#define RVSCENE_H

#include <QList>

#include "rvbody.h"

class RVScene : public QList<RVBody*>
{
public:
    RVScene();
    void setCamera(RVCamera* camera);
    void translate(QVector3D vec);
    void rotate(float, QVector3D);
    void draw();

protected:
    RVCamera* m_camera;
};

#endif // RVSCENE_H
