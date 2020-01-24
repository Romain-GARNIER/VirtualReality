#include "rvbody.h"

RVBody::~RVBody()
{
    m_program.removeAllShaders();
}

RVBody::RVBody()
    :QOpenGLFunctions(),
      m_vao(), m_program(),
      m_position(), m_orientation()
{
    m_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_vbo.create();
    m_ibo.create();
    m_vao.create();
    m_program.create();

    m_numVertices = 0;
    m_numTriangles = 0;
    m_numIndices = 0;

    m_VSFileName = ":/shaders/VS_simpler.vsh";
    m_FSFileName = ":/shaders/FS_simple.fsh";

    m_opacity = 1;
    m_wireframe = false;
    m_culling  = true;

    m_scale = 1;

    m_globalColor = QVector3D(1, 1, 1);
}

void RVBody::initialize()
{
    initializeShader();
    initializeBuffer();		//à écrire dans la classe fille
    initializeVAO();    	//à écrire dans la classe fille
}

void RVBody::initializeShader()
{
    initializeOpenGLFunctions();

    bool resultat;

    m_program.bind();
    //Vertex Shader
    resultat = m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, m_VSFileName);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(m_program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Fragment Shader
    resultat = m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, m_FSFileName);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Fragment shader");
        msg.setText(m_program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Link
    resultat = m_program.link();
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Link du shader program");
        msg.setText(m_program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Libération
    m_program.release();
}

void RVBody::initializeVAO()
{
    m_vao.bind();
    m_vbo.bind();
    m_ibo.bind();

    //Définition du seul attribut position (la couleur est uniforme avec le VS_simpler)
    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    //Libération
    m_vao.release();
    m_program.release();
}

void RVBody::rotate(float angle, QVector3D axis)
{
    m_orientation =  QQuaternion::fromAxisAndAngle(axis, angle) * m_orientation ;
}

void RVBody::translate(QVector3D position)
{
    m_position += position;
}

void RVBody::setOrientation(float yaw, float pitch, float roll)
{
    m_orientation = QQuaternion::fromEulerAngles(pitch, yaw, roll);
}

QString RVBody::VSFileName() const
{
    return m_VSFileName;
}

void RVBody::setVSFileName(const QString &VSFileName)
{
    m_VSFileName = VSFileName;
}

QString RVBody::FSFileName() const
{
    return m_FSFileName;
}

void RVBody::setFSFileName(const QString &FSFileName)
{
    m_FSFileName = FSFileName;
}

QOpenGLBuffer RVBody::vbo() const
{
    return m_vbo;
}

void RVBody::setVbo(const QOpenGLBuffer &vbo)
{
    m_vbo = vbo;
}

QOpenGLBuffer RVBody::ibo() const
{
    return m_ibo;
}

void RVBody::setIbo(const QOpenGLBuffer &ibo)
{
    m_ibo = ibo;
}

int RVBody::numVertices() const
{
    return m_numVertices;
}

void RVBody::setNumVertices(int numVertices)
{
    m_numVertices = numVertices;
}

int RVBody::numTriangles() const
{
    return m_numTriangles;
}

void RVBody::setNumTriangles(int numTriangles)
{
    m_numTriangles = numTriangles;
}

int RVBody::numIndices() const
{
    return m_numIndices;
}

void RVBody::setNumIndices(int numIndices)
{
    m_numIndices = numIndices;
}

RVCamera *RVBody::camera() const
{
    return m_camera;
}

void RVBody::setCamera(RVCamera *camera)
{
    m_camera = camera;
}


QVector3D RVBody::position() const
{
    return m_position;
}

void RVBody::setPosition(const QVector3D &position)
{
    m_position = position;
}

float RVBody::opacity() const
{
    return m_opacity;
}

void RVBody::setOpacity(float opacity)
{
    m_opacity = opacity;
}

bool RVBody::wireframe() const
{
    return m_wireframe;
}

void RVBody::setWireframe(bool wireframe)
{
    m_wireframe = wireframe;
}

bool RVBody::culling() const
{
    return m_culling;
}

void RVBody::setCulling(bool culling)
{
    m_culling = culling;
}

float RVBody::scale() const
{
    return m_scale;
}

void RVBody::setScale(float scale)
{
    m_scale = scale;
}

QVector3D RVBody::globalColor() const
{
    return m_globalColor;
}

void RVBody::setGlobalColor(const QVector3D &globalColor)
{
    m_globalColor = globalColor;
}

QQuaternion RVBody::orientation() const
{
    return m_orientation;
}

void RVBody::setOrientation(const QQuaternion &orientation)
{
    m_orientation = orientation;
}

QMatrix4x4 RVBody::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(m_position);
    model.rotate(m_orientation);
    model.scale(m_scale);
    return model;
}

