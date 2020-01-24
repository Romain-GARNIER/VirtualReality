#include "rvplane.h"

RVPlane::RVPlane()
    : RVBody()
{
    m_FSFileName = ":/shaders/FS_plan.fsh";
    m_longX = 10;
    m_largZ = 10;
    m_globalColor = QVector3D(0,1,0);
}

RVPlane::RVPlane(int longX, int largZ)
    : RVBody()
{
    m_longX = longX;
    m_largZ = largZ;
    m_globalColor = QVector3D(1,0,0);
}
int RVPlane::longX() const
{
    return m_longX;
}

void RVPlane::setLongX(int longX)
{
    m_longX = longX;
}

int RVPlane::largZ() const
{
    return m_largZ;
}

void RVPlane::setLargZ(int largX)
{
    m_largZ = largX;
}


void RVPlane::initializeBuffer()
{
    //Définition de 4 points
    QVector3D A(-m_longX/2, 0, m_largZ/2);
    QVector3D B(m_longX/2, 0, m_largZ/2);
    QVector3D C(m_longX/2, 0, -m_largZ/2);
    QVector3D D(-m_longX/2, 0, -m_largZ/2);

    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D
       };

    //Lien du VBO avec le contexte de rendu OpenG
    m_vbo.bind();
    //Allocation des données dans le VBO
    m_vbo.allocate(vertexData, sizeof (vertexData));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    m_vbo.release();


}

void RVPlane::draw()
{
    glEnable(GL_DEPTH_TEST);

    //permet d'activer la transparance
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


    m_program.bind();
    m_vao.bind();

    //Définition de la variable uniforme
    QMatrix4x4 matrix;
    matrix = m_camera->projectionMatrix() * m_camera->viewMatrix() * this->modelMatrix();
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);

    m_program.setUniformValue("u_opacity",m_opacity);

    m_program.setUniformValue("u_color",m_globalColor);

    glDrawArrays(GL_TRIANGLE_FAN , 0, 4);
//    for(int i=0; i<6;  i++){
        //glDrawArrays(GL_TRIANGLE_FAN , 4, 4);
//    }

    m_vao.release();
    m_program.release();
}
