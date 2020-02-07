#include "rvspecularcube.h"

RVSpecularCube::RVSpecularCube()
    :RVTexCube()
{
    m_VSFileName = ":/shaders/VS_lit_texture_cube.vsh";
    m_FSFileName = ":/shaders/FS_lit_specular_cube.fsh";

}

void RVSpecularCube::setCubeTexture(QString leftImage,
                              QString rightImage,
                              QString frontImage,
                              QString backImage,
                              QString topImage,
                              QString bottomImage)
{
    //Je charge en mémoire les 6 images des 6 faces
    QImage posX = QImage(rightImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negX = QImage(leftImage).convertToFormat(QImage::Format_RGBA8888);
    QImage posY = QImage(topImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negY = QImage(bottomImage).convertToFormat(QImage::Format_RGBA8888);
    QImage posZ = QImage(frontImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negZ = QImage(backImage).convertToFormat(QImage::Format_RGBA8888);

    //Je prépare le format de la texture cubique
    m_texture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    m_texture->create();
    m_texture->setSize(posX.width(), posX.height(), posX.depth());
    m_texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
    m_texture->allocateStorage();

    //Je remplis les données de la texture cuboque
    m_texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX,
                       QOpenGLTexture::RGBA,
                       QOpenGLTexture::UInt8,
                       posX.constBits(),
                       Q_NULLPTR);
    m_texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX,
                       QOpenGLTexture::RGBA,
                       QOpenGLTexture::UInt8,
                       negX.constBits(),
                       Q_NULLPTR);
    m_texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY,
                       QOpenGLTexture::RGBA,
                       QOpenGLTexture::UInt8,
                       posY.constBits(),
                       Q_NULLPTR);
    m_texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY,
                       QOpenGLTexture::RGBA,
                       QOpenGLTexture::UInt8,
                       negY.constBits(),
                       Q_NULLPTR);
    m_texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ,
                       QOpenGLTexture::RGBA,
                       QOpenGLTexture::UInt8,
                       posZ.constBits(),
                       Q_NULLPTR);
    m_texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ,
                       QOpenGLTexture::RGBA,
                       QOpenGLTexture::UInt8,
                       negZ.constBits(),
                       Q_NULLPTR);

    //Quelques réglages sur la texture
    m_texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    //ici on ajoutera aussi ceux du filtrage...
    m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->generateMipMaps();
}

void RVSpecularCube::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (m_wireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (m_culling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    if (m_texture) {
        glEnable(GL_TEXTURE_CUBE_MAP);
        glEnable(GL_TEXTURE1);
        m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        m_texture->bind();
    }
    m_program.bind();
    m_vao.bind();

    m_program.setUniformValue("u_ModelMatrix", this->modelMatrix());
    m_program.setUniformValue("u_ViewMatrix", m_camera->viewMatrix());
    m_program.setUniformValue("u_ProjectionMatrix", m_camera->projectionMatrix());
    m_program.setUniformValue("u_opacity", m_opacity);
    m_program.setUniformValue("u_color", m_globalColor);
    m_program.setUniformValue("texture0", 0);

    m_program.setUniformValue("light_ambient_color", m_light->ambient());
    m_program.setUniformValue("light_diffuse_color", m_light->diffuse());
    m_program.setUniformValue("light_specular_color", m_light->specular());
    m_program.setUniformValue("light_specular_strength", m_specStrength);
    m_program.setUniformValue("light_position", m_light->position());
    m_program.setUniformValue("eye_position", m_camera->position());

    for (int i = 0; i<6; i++)
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);

    m_vao.release();
    m_program.release();

    if (m_texture) {
        m_texture->release();
        glDisable(GL_TEXTURE1);
        glDisable(GL_TEXTURE_CUBE_MAP);
    }
}
