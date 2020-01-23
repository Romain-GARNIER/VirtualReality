#ifndef RVBODY_H
#define RVBODY_H

#include "rvcamera.h"

#include <QString>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QMessageBox>

class RVBody : public QOpenGLFunctions
{
public:
    RVBody();
    virtual ~RVBody();

    virtual void draw() = 0;
    virtual QMatrix4x4 modelMatrix();

    void initialize();
    void initializeShader();
    virtual void initializeBuffer() = 0;
    virtual void initializeVAO() = 0;
    void translate(QVector3D position);
    QQuaternion orientation() const;
    void rotate(float angle, QVector3D axis);

    // accesseurs et mutateurs .....


    void setOrientation(const QQuaternion &orientation);
    void setOrientation(float yaw, float pitch, float roll);

    QString VSFileName() const;
    void setVSFileName(const QString &VSFileName);

    QString FSFileName() const;
    void setFSFileName(const QString &FSFileName);

    QOpenGLBuffer vbo() const;
    void setVbo(const QOpenGLBuffer &vbo);

    QOpenGLBuffer ibo() const;
    void setIbo(const QOpenGLBuffer &ibo);

    QOpenGLVertexArrayObject vao() const;
    void setVao(const QOpenGLVertexArrayObject &vao);

    QOpenGLShaderProgram program() const;
    void setProgram(const QOpenGLShaderProgram &program);

    int numVertices() const;
    void setNumVertices(int numVertices);

    int numTriangles() const;
    void setNumTriangles(int numTriangles);

    int numIndices() const;
    void setNumIndices(int numIndices);

    RVCamera *camera() const;
    void setCamera(RVCamera *camera);

    QVector3D position() const;
    void setPosition(const QVector3D &position);

protected:
    QString m_VSFileName;               //! : nom du fichier qui contient le vertex shader
    QString m_FSFileName;               //! : nom du fichier qui contient le fragment shader
    QOpenGLBuffer m_vbo;                //! : vertex buffer qui stocke les sommets du maillage
    QOpenGLBuffer m_ibo;                //! : index buffer (optionnel) qui stocke les index à utiliser pour le rendu
    QOpenGLVertexArrayObject m_vao;     //! : vertex array object (obligatoire)
    QOpenGLShaderProgram m_program;     //! : shader program (obligatoire)

    QVector3D m_position;               //! : position de l'objet dans la scène
    QQuaternion m_orientation;          //! : attitude de l'objet dans la scène

    int m_numVertices;                  //! : nombre de sommets de l'objet (lecture seule)
    int m_numTriangles;                 //! : nombre de triangles de l'objet (lecture seule)
    int m_numIndices;                   //! : nombre d'index (0 si on n'utilise pas l'ibo)

    RVCamera *m_camera;                 //! : pointeur sur la caméra utilisée pour le rendu.
};

#endif // RVBODY_H
