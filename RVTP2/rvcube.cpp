#include "rvcube.h"

RVCube::RVCube() : RVBody()
{
    m_VSFileName = ":/shaders/VS_simple.vsh";
    m_FSFileName = ":/shaders/FS_simple.fsh";
}

void RVCube::initializeBuffer()
{
    //Définition de 4 points
    QVector3D A(0, 0, 1);
    QVector3D B(1, 0, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(0, 1, 1);
    QVector3D E(0, 0, 0);
    QVector3D F(1, 0, 0);
    QVector3D G(1, 1, 0);
    QVector3D H(0, 1, 0);

    //Définition de 4 couleurs
    QVector3D rouge(1, 0, 0);
    QVector3D magenta(1, 0, 1);
    QVector3D bleu(0, 0, 1);
    QVector3D blanc(1, 1, 1);
    QVector3D vert(0, 1, 0);
    QVector3D cyan(0, 1, 1);

    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D,
        D, C, G, H,
        B, F, G, C,
        F, E, H, G,
        A, D, H, E,
        A, E, F, B,
        rouge, rouge, rouge, rouge, bleu, bleu, bleu, bleu, cyan, cyan, cyan, cyan,
        magenta, magenta, magenta, magenta, blanc, blanc, blanc, blanc, vert, vert , vert , vert
    };


    //Lien du VBO avec le contexte de rendu OpenG
    m_vbo.bind();
    //Allocation des données dans le VBO
    m_vbo.allocate(vertexData, sizeof (vertexData));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    m_vbo.release();

//    uint indexData[] = {
//        0, 1, 2,
//        0, 2, 3,
//        0, 3, 1,
//        2, 1, 3
//    };


    //Lien du VBO avec le contexte de rendu OpenG
    m_ibo.bind();
    //Allocation des données dans le VBO
//    m_ibo.allocate(indexData, sizeof (indexData));
    m_ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    m_ibo.release();
}


void RVCube::initializeVAO()
{
    //Initialisation du VA
    m_vao.bind();
    m_vbo.bind();

    //Définition des attributs
    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    m_program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*24, 3);
    m_program.enableAttributeArray("rv_Color");

    //Libération
    m_vao.release();
    m_program.release();
}


void RVCube::draw()
{
    glEnable(GL_DEPTH_TEST);

    if(m_wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if(!m_culling)
        glDisable(GL_CULL_FACE);
    else
        glEnable(GL_CULL_FACE);


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

    //Commande de rendu (indexé)
    //glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);

    for(int i=0; i<6;  i++){
        glDrawArrays(GL_TRIANGLE_FAN , i*4, 4);
    }

    m_vao.release();
    m_program.release();
}


QMatrix4x4 RVCube::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(-0.5f, -0.5f, -0.5f);
    return RVBody::modelMatrix() * model;
}
