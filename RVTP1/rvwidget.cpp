#include "rvwidget.h"
#include <QMessageBox>

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    m_angleY = 30;
    m_angleX = 30;
    m_timer = new QTimer();
    m_rotate = false;
    m_aspetcRatio = 1.33f;
    m_angleProj = 45;
    m_opacity = 100;
}

RVWidget::~RVWidget()
{
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();
//    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    initializeBuffer();
    initializeShaders();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));

}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
//    glCullFace(GL_BACK);
//    glFrontFace(GL_CCW);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    m_program.bind();
    m_vbo.bind();
    m_ibo.bind();

    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    m_program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*24, 3);
    m_program.enableAttributeArray("rv_Color");

    m_program.setUniformValue("u_opacity",((float) m_opacity)/100);

    QMatrix4x4 model, proj, view, matrix;

    m_aspetcRatio = ((float)width())/((float)height());

    //Définition de la matrice de projetcion
    proj.perspective(m_angleProj, m_aspetcRatio, 0.1f, 100.0f);

    //Définiion de la matrice de vue
    view  = QMatrix4x4();

    //Définition de la matrice de placement
    model.translate(0, 0.0, -3);
    model.translate(0, 0, -2);
    model.rotate(m_angleX,1.0,0.0,0.0);
    model.rotate(m_angleY,0.0,1.0,0.0);
    model.translate(-0.5, -0.5, -0.5);

    //Produit des trois matrices (dans ce sens!)
    matrix = proj * view * model;

    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);

    for(int i=0; i<6;  i++){
        glDrawArrays(GL_TRIANGLE_FAN , i*4, 4);
    }

    m_vbo.release();
    m_program.release();
}

void RVWidget::resizeGL(int w, int h)
{
    //transformation de viewport
    glViewport(0, 0, w, h);
}

void RVWidget::initializeBuffer()
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
        B, C, G, F,
        G, H, E, F,
        A, D, H, E,
        A, B, F, E,
        rouge, rouge, rouge, rouge, bleu, bleu, bleu, bleu, cyan, cyan, cyan, cyan,
        magenta, magenta, magenta, magenta, blanc, blanc, blanc, blanc, vert, vert , vert , vert
    };

    //Initialisation du Vertex Buffer Object
    m_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    //Création du VBO
    m_vbo.create();
    //Lien du VBO avec le contexte de rendu OpenG
    m_vbo.bind();
    //Allocation des données dans le VBO
    m_vbo.allocate(vertexData, sizeof (vertexData));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    m_vbo.release();

    uint indexData[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 1,
        2, 1, 3
    };

    //Initialisation de l'Index Buffer Object
    m_ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    //Création du VBO
    m_ibo.create();
    //Lien du VBO avec le contexte de rendu OpenG
    m_ibo.bind();
    //Allocation des données dans le VBO
    m_ibo.allocate(indexData, sizeof (indexData));
    m_ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    m_ibo.release();

}

void RVWidget::initializeShaders()
{
    bool resultat;
    m_program.create();
    m_program.bind();

    //Vertex Shader
    resultat = m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/VS_simple.vsh");
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(m_program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Fragment Shader
    resultat = m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/FS_simple.fsh");
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

void RVWidget::update(){
    m_angleY += 5;
    QOpenGLWidget::update();
}

void RVWidget::mousePressEvent(QMouseEvent* event){
    m_oldPos = event->pos();
}

void RVWidget::mouseMoveEvent(QMouseEvent* event){
    float dx, dy;

    dx = (event->pos().x() - m_oldPos.x());
    dy = (event->pos().y() - m_oldPos.y());

    dx = dx/width();
    dy = dy/height();

    m_angleX += dy*180;
    m_angleY += dx*180;

    m_oldPos = event->pos();
    QOpenGLWidget::update();
}


void RVWidget::startAnimation(){
    if(!m_rotate){
        // démarrage du timer en ms (50 ms)
        m_timer->start(50);
        m_rotate = true;
    }else{
        m_timer->stop();
        m_rotate = false;
    }
}

void RVWidget::changeFov(int angle){
    m_angleProj = angle;
}

void RVWidget::changeOpacity(int opacity){
    m_opacity = opacity;
}

