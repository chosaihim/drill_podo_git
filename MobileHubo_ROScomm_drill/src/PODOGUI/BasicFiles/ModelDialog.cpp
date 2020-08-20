#include "ModelDialog.h"
#include "ui_ModelDialog.h"


using namespace isnl;


enum JointSequentialNumber_Finger{
    RF_a1 = NO_OF_MOBILE_JOINTS, RF_a2, RF_a3,
    RF_b1, RF_b2, RF_b3,
    RF_c1, RF_c2, RF_c3,
    LF_a1, LF_a2, LF_a3,
    LF_b1, LF_b2, LF_b3,
    LF_c1, LF_c2, LF_c3, NO_OF_MODEL_JOINTS
};

enum BONE_ID{
    B_WST, B_CAMERA,B_WHBASE, B_WHPLATE,
    B_LSP,B_LSR,B_LSY,B_LEB,B_LWY,B_LWP,B_LWFT,B_LHAND,
    B_LF_a1,B_LF_a2,B_LF_a3,B_LF_b1,B_LF_b2,B_LF_b3,B_LF_c1,B_LF_c2,B_LF_c3,
    B_RSP,B_RSR,B_RSY,B_REB,B_RWY,B_RWP,B_RWFT,B_RHAND,
    B_RF_a1,B_RF_a2,B_RF_a3,B_RF_b1,B_RF_b2,B_RF_b3,B_RF_c1,B_RF_c2,B_RF_c3,
    B_RWH, B_LWH, B_BWH,
    NBONE
};
enum COMP_ID{
    JRSP, JRSR, JRSY, JREB, JRWY, JRWP, JRWY2,
    JLSP, JLSL, JLSY, JLEB, JLWY, JLWP, JLWY2,
    JWST,
    JRHAND, JLHAND,
    JRWH, JLWH, JBWH,
    JRF_a1,JRF_a2,JRF_a3,JRF_b1,JRF_b2,JRF_b3,JRF_c1,JRF_c2,JRF_c3,
    JLF_a1,JLF_a2,JLF_a3,JLF_b1,JLF_b2,JLF_b3,JLF_c1,JLF_c2,JLF_c3,
    BTORSO,BCAMERA,BWHBASE, BWHPLATE,
    BLSP,BLSR,BLSY,BLEB,BLWY,BLWP,BLWFT,BLWY2,
    BLF_a1,BLF_a2,BLF_a3,BLF_b1,BLF_b2,BLF_b3,BLF_c1,BLF_c2,BLF_c3,
    BRSP,BRSR,BRSY,BREB,BRWY,BRWP,BRWFT,BRWY2,
    BRF_a1,BRF_a2,BRF_a3,BRF_b1,BRF_b2,BRF_b3,BRF_c1,BRF_c2,BRF_c3,
    BRWH, BLWH, BBWH,
    NCOMP
};
static const char COMP_NAME[NCOMP+1][10] = {
    "JRSP", "JRSR", "JRSY", "JREB", "JRWY", "JRWP", "JHAND",
    "JLSP", "JLSL", "JLSY", "JLEB", "JLWY", "JLWP", "JHAND",
    "JWST",
    "JRHAND", "JLHAND",
    "JRWH", "JLWH", "JBWH",
    "JRF_a1","JRF_a2","JRF_a3","JRF_b1","JRF_b2","JRF_b3","JRF_c1","JRF_c2","JRF_c3",
    "JLF_a1","JLF_a2","JLF_a3","JLF_b1","JLF_b2","JLF_b3","JLF_c1","JLF_c2","JLF_c3",

    "BTORSO","BCAMERA","BWHBASE","BWHPLATE",
    "BLSP","BLSR","BLSY","BLEB","BLWY","BLWP","BLWFT","BLF_a","BLF_b","BLF_c",
    "BRSP","BRSR","BRSY","BREB","BRWY","BRWP","BRWFT","BRF_a","BRF_b","BRF_c",
    "BRWH","BLWH","BBWH",
    "Null"
};

std::string STLPath = "../share/GUI/stl_mobile/";

ModelDialog::ModelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelDialog)
{
    ui->setupUi(this);

    glWidget = new GLWidget(this);

    QScrollArea *glWidgetArea = new QScrollArea;
    glWidgetArea->setWidget(glWidget);
    glWidgetArea->setWidgetResizable(true);
    glWidgetArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    glWidgetArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    glWidgetArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    glWidgetArea->setMinimumSize(50, 50);

    xSlider = createSlider(SIGNAL(xRotationChanged(int)), SLOT(setXRotation(int)));
    ySlider = createSlider(SIGNAL(yRotationChanged(int)), SLOT(setYRotation(int)));
    zSlider = createSlider(SIGNAL(zRotationChanged(int)), SLOT(setZRotation(int)));

    ui->LAYOUT_MODEL->addWidget(glWidgetArea, 0, 0);
    ui->LAYOUT_SLIDER->addWidget(xSlider,0,0);
    ui->LAYOUT_SLIDER->addWidget(ySlider,1,0);
    ui->LAYOUT_SLIDER->addWidget(zSlider,2,0);

    xSlider->setValue(180 * 16);
    ySlider->setValue(180 * 16);
    zSlider->setValue(180 * 16);

    displayTimer = new QTimer(this);
    connect(displayTimer, SIGNAL(timeout()), this, SLOT(DisplayUpdate()));
    displayTimer->start(100);
}

ModelDialog::~ModelDialog()
{
    delete ui;
}


void ModelDialog::DisplayUpdate(){
    if(ui->CB_USE_ENCODER->isChecked()){

        glWidget->model->ref[mRSP+7] = JointEncoder(RSP) * D2Rf;
        glWidget->model->ref[mRSR+7] = JointEncoder(RSR) * D2Rf;
        glWidget->model->ref[mRSY+7] = JointEncoder(RSY) * D2Rf;
        glWidget->model->ref[mREB+7] = JointEncoder(REB) * D2Rf;
        glWidget->model->ref[mRWY+7] = JointEncoder(RWY) * D2Rf;
        glWidget->model->ref[mRWP+7] = JointEncoder(RWP) * D2Rf;
        glWidget->model->ref[mRWY2+7]= JointEncoder(RWY2)* D2Rf;

        glWidget->model->ref[mLSP+7] = JointEncoder(LSP) * D2Rf;
        glWidget->model->ref[mLSR+7] = JointEncoder(LSR) * D2Rf;
        glWidget->model->ref[mLSY+7] = JointEncoder(LSY) * D2Rf;
        glWidget->model->ref[mLEB+7] = JointEncoder(LEB) * D2Rf;
        glWidget->model->ref[mLWY+7] = JointEncoder(LWY) * D2Rf;
        glWidget->model->ref[mLWP+7] = JointEncoder(LWP) * D2Rf;
        glWidget->model->ref[mLWY2+7]= JointEncoder(LWY2)* D2Rf;

        glWidget->model->ref[mWST+7] = JointEncoder(WST) * D2Rf;

        glWidget->model->ref[mRHAND+7] = JointEncoder(RHAND) * D2Rf;
        glWidget->model->ref[mLHAND+7] = JointEncoder(LHAND) * D2Rf;

        glWidget->model->ref[mRWH+7] = JointEncoder(RWH) * D2Rf;
        glWidget->model->ref[mLWH+7] = JointEncoder(LWH) * D2Rf;
        glWidget->model->ref[mBWH+7] = JointEncoder(BWH) * D2Rf;

        glWidget->model->ref[3] = 1.0;
        glWidget->model->ref[4] = 0.0;
        glWidget->model->ref[5] = 0.0;
        glWidget->model->ref[6] = 0.0;

    }else{

        glWidget->model->ref[mRSP+7] = JointReference(RSP) * D2Rf;
        glWidget->model->ref[mRSR+7] = JointReference(RSR) * D2Rf;
        glWidget->model->ref[mRSY+7] = JointReference(RSY) * D2Rf;
        glWidget->model->ref[mREB+7] = JointReference(REB) * D2Rf;
        glWidget->model->ref[mRWY+7] = JointReference(RWY) * D2Rf;
        glWidget->model->ref[mRWP+7] = JointReference(RWP) * D2Rf;
        glWidget->model->ref[mRWY2+7]= JointReference(RWY2)* D2Rf;

        glWidget->model->ref[mLSP+7] = JointReference(LSP) * D2Rf;
        glWidget->model->ref[mLSR+7] = JointReference(LSR) * D2Rf;
        glWidget->model->ref[mLSY+7] = JointReference(LSY) * D2Rf;
        glWidget->model->ref[mLEB+7] = JointReference(LEB) * D2Rf;
        glWidget->model->ref[mLWY+7] = JointReference(LWY) * D2Rf;
        glWidget->model->ref[mLWP+7] = JointReference(LWP) * D2Rf;
        glWidget->model->ref[mLWY2+7]= JointReference(LWY2)* D2Rf;

        glWidget->model->ref[mWST+7] = JointReference(WST) * D2Rf;

        glWidget->model->ref[mRHAND+7]= JointReference(RHAND) * D2Rf;
        glWidget->model->ref[mLHAND+7]= JointReference(LHAND) * D2Rf;

        glWidget->model->ref[mRWH+7] =  JointReference(RWH) * D2Rf;
        glWidget->model->ref[mLWH+7] = -JointReference(LWH) * D2Rf;
        glWidget->model->ref[mBWH+7] = -JointReference(BWH) * D2Rf;

        glWidget->model->ref[3] = 1.0f;
        glWidget->model->ref[4] = 0.0f;
        glWidget->model->ref[5] = 0.0f;
        glWidget->model->ref[6] = 0.0f;
    }

    // Fingers always use encoder
    static float RHAND_ref = 100*D2Rf;
    static float LHAND_ref = 100*D2Rf;
    if(JointReference(RHAND) > 0.1)
    {
        RHAND_ref += 0.1;
    }else if(JointReference(RHAND) < -0.1)
    {
        RHAND_ref -= 0.1;
    }

    if(JointReference(LHAND) > 0.1)
    {
        LHAND_ref += 0.1;
    }else if(JointReference(LHAND) < -0.1)
    {
        LHAND_ref -= 0.1;
    }

    double uplimit = 100.;
    double downlimit = 0.;
    if(RHAND_ref < downlimit*D2Rf)      RHAND_ref = downlimit*D2Rf;
    else if(RHAND_ref > uplimit*D2Rf)   RHAND_ref = uplimit*D2Rf;
    if(LHAND_ref < downlimit*D2Rf)      LHAND_ref = downlimit*D2Rf;
    else if(LHAND_ref > uplimit*D2Rf)   LHAND_ref = uplimit*D2Rf;

    glWidget->model->ref[RF_a1+7] = glWidget->model->ref[RF_a2+7] = glWidget->model->ref[RF_a3+7] =  RHAND_ref;//( 100/36.2)*(36.2-JointReference(RHAND))*D2Rf;
    glWidget->model->ref[RF_b1+7] = glWidget->model->ref[RF_b2+7] = glWidget->model->ref[RF_b3+7] =  RHAND_ref;//( 100/36.2)*(36.2-JointReference(RHAND))*D2Rf;
    glWidget->model->ref[RF_c1+7] = glWidget->model->ref[RF_c2+7] = glWidget->model->ref[RF_c3+7] = -RHAND_ref;//(-100/36.2)*(36.2-JointReference(RHAND))*D2Rf;

    glWidget->model->ref[LF_a1+7] = glWidget->model->ref[LF_a2+7] = glWidget->model->ref[LF_a3+7] =  LHAND_ref;//( 100/36.2)*(36.2-JointReference(LHAND))*D2Rf;
    glWidget->model->ref[LF_b1+7] = glWidget->model->ref[LF_b2+7] = glWidget->model->ref[LF_b3+7] =  LHAND_ref;//( 100/36.2)*(36.2-JointReference(LHAND))*D2Rf;
    glWidget->model->ref[LF_c1+7] = glWidget->model->ref[LF_c2+7] = glWidget->model->ref[LF_c3+7] = -LHAND_ref;//(-100/36.2)*(36.2-JointReference(LHAND))*D2Rf;

    glWidget->floor->setVisible(ui->CB_SHOW_FLOOR->isChecked());
    glWidget->rwforce->setVisible(ui->CB_SHOW_FT->isChecked());
    glWidget->lwforce->setVisible(ui->CB_SHOW_FT->isChecked());

    glWidget->updateGL();
}


QSlider* ModelDialog::createSlider(const char *changedSignal, const char *setterSlot){
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    connect(slider, SIGNAL(valueChanged(int)), glWidget, setterSlot);
    connect(glWidget, changedSignal, slider, SLOT(setValue(int)));
    return slider;
}

void ModelDialog::on_BT_CamFront_clicked(){
    xSlider->setValue(180 * 16);
    ySlider->setValue(180 * 16);
    zSlider->setValue(180 * 16);
}
void ModelDialog::on_BT_CamRight_clicked(){
    xSlider->setValue(180 * 16);
    ySlider->setValue(180 * 16);
    zSlider->setValue(270 * 16);
}
void ModelDialog::on_BT_CamLeft_clicked(){
    xSlider->setValue(180 * 16);
    ySlider->setValue(180 * 16);
    zSlider->setValue( 90 * 16);
}


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;


    floor = new GLGridPlane(0.5f, 0.5f, 20, 20);
    floor->setPosition(isnl::pos(0.f, 0.f, -1.f));

    model = newModel();
    model->ref.resize(NO_OF_MODEL_JOINTS+7);//NO_OF_MOBILE_JOINTS+7);
    model->ref[3] = 1.f;

    //globjs << model;
    globjs << floor;

    rwforce = new GLArrow(0.01f ,0.5f); rwforce->setBaseColor(1, 0, 0);
    lwforce = new GLArrow(0.01f ,0.5f); lwforce->setBaseColor(1, 0, 0);

    globjs << rwforce << lwforce;


}
GLWidget::~GLWidget()
{
    makeCurrent();
}

void GLWidget::setXRotation(int angle){
    normalizeAngle(&angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
    }
}
void GLWidget::setYRotation(int angle){
    normalizeAngle(&angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
    }
}
void GLWidget::setZRotation(int angle){
    normalizeAngle(&angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
    }
}
void GLWidget::initializeGL()
{
    GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor);
    glEnable(GL_DEPTH_TEST);

    globjs.initialize();

    glEnable(GL_NORMALIZE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::paintGL()
{
    GLfloat lightPos0[4] = { 10.0f,-10.0f, 7.0f, 1.0f };
    GLfloat lightPos1[4] = {-10.0f, 10.0f, 7.0f, 1.0f };
    GLfloat lightPos2[4] = {-10.0f,-10.0f, 7.0f, 1.0f };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glPushMatrix();

    glRotated(xRot / 16.0 -180, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0 -180, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0 -180, 0.0, 0.0, 1.0);

    model->render();

    glPushMatrix();

    glRotated(xRot / 16.0 -180, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0 -180, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0 -180, 0.0, 0.0, 1.0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);

    // ft ----
    rwforce->setPosition(model->getPosition(BRWFT)* isnl::pos(-0.05f,0.0f,0.0f));
    lwforce->setPosition(model->getPosition(BLWFT)* isnl::pos(-0.05f,0.0f,0.0f));
    rwforce->setLength(PODO_DATA.CoreSEN.FT[2].Fz/50.0);
    lwforce->setLength(PODO_DATA.CoreSEN.FT[3].Fz/50.0);

    globjs.render();

    glPopMatrix();
    glPopMatrix();

}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.1, +0.1, -0.1, 0.1, 0.1, 60.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -1.0);
    // change camera coord to world coord :
    glRotatef(2.0944*R2Df, -0.5774, -0.5774, -0.5774);
}
void GLWidget::mousePressEvent(QMouseEvent *event){
    lastPos = event->pos();
}
void GLWidget::mouseMoveEvent(QMouseEvent *event){
    currPos = event->pos();
    int dx = currPos.x() - lastPos.x();
    int dy = currPos.y() - lastPos.y();

    if(event->buttons() & Qt::RightButton){
        setYRotation(yRot + 2 * dy);
        setZRotation(zRot + 2 * dx);
    }else if (event->buttons() & Qt::LeftButton){
        glTranslatef(0, dx/500.0, -dy/500.0);
    }
    lastPos = event->pos();
}
void GLWidget::wheelEvent(QWheelEvent *event){
    //if(event->modifiers().testFlag(Qt::ControlModifier)){
        glTranslatef(-event->delta()/1000.0, 0, 0);
    //}
}

void GLWidget::normalizeAngle(int *angle){
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}


// ===========================
// ===========================


HUBOModel* GLWidget::newModel()
{
    Joints joints(NO_OF_MODEL_JOINTS + 3);
    Bones  bones(NBONE);
    Bones tempbone(32);
    std::vector<GLComplex*> objs(1);
    objs[0] = new GLComplex();

    // Upper body joints
    joints[mRSP]   = new RevoluteYJoint("mRSP");
    joints[mRSR]   = new RevoluteXJoint("mRSR");
    joints[mRSY]   = new RevoluteZJoint("mRSY");
    joints[mREB]   = new RevoluteYJoint("mREB");
    joints[mRWY]   = new RevoluteZJoint("mRWY");
    joints[mRWP]   = new RevoluteYJoint("mRWP");
    joints[mRWY2]  = new RevoluteZJoint("mRWY2");

    joints[mLSP]   = new RevoluteYJoint("mLSP");
    joints[mLSR]   = new RevoluteXJoint("mLSR");
    joints[mLSY]   = new RevoluteZJoint("mLSY");
    joints[mLEB]   = new RevoluteYJoint("mLEB");
    joints[mLWY]   = new RevoluteZJoint("mLWY");
    joints[mLWP]   = new RevoluteYJoint("mLWP");
    joints[mLWY2]  = new RevoluteZJoint("mLWY2");

    // Waist, Fingers
    joints[mWST]   = new RevoluteZJoint("mWST");
    joints[mRHAND] = new RevoluteZJoint("mRHAND");
    joints[mLHAND] = new RevoluteZJoint("mLHAND");

    joints[mRWH]   = new RevoluteYJoint("mRWH");
    joints[mLWH]   = new RevoluteYJoint("mLWH");
    joints[mBWH]   = new RevoluteYJoint("mBWH");

    joints[RF_a1]  = new RevoluteYJoint("RF_a1");
    joints[RF_a2]  = new RevoluteYJoint("RF_a2");
    joints[RF_a3]  = new RevoluteYJoint("RF_a3");
    joints[RF_b1]  = new RevoluteYJoint("RF_b1");
    joints[RF_b2]  = new RevoluteYJoint("RF_b2");
    joints[RF_b3]  = new RevoluteYJoint("RF_b3");
    joints[RF_c1]  = new RevoluteYJoint("RF_c1");
    joints[RF_c2]  = new RevoluteYJoint("RF_c2");
    joints[RF_c3]  = new RevoluteYJoint("RF_c3");

    joints[LF_a1]  = new RevoluteYJoint("LF_a1");
    joints[LF_a2]  = new RevoluteYJoint("LF_a2");
    joints[LF_a3]  = new RevoluteYJoint("LF_a3");
    joints[LF_b1]  = new RevoluteYJoint("LF_b1");
    joints[LF_b2]  = new RevoluteYJoint("LF_b2");
    joints[LF_b3]  = new RevoluteYJoint("LF_b3");
    joints[LF_c1]  = new RevoluteYJoint("LF_c1");
    joints[LF_c2]  = new RevoluteYJoint("LF_c2");
    joints[LF_c3]  = new RevoluteYJoint("LF_c3");

    joints[NO_OF_MODEL_JOINTS]   = new RevoluteZJoint("tempRWH");
    joints[NO_OF_MODEL_JOINTS+1] = new RevoluteZJoint("tempLWH");
    joints[NO_OF_MODEL_JOINTS+2] = new RevoluteZJoint("tempBWH");

    ((RevoluteJoint*)joints[mRSR])->setOffset(-15.f*D2Rf);
    ((RevoluteJoint*)joints[mLSR])->setOffset( 15.f*D2Rf);
    ((RevoluteJoint*)joints[mREB])->setOffset(-20.f*D2Rf);
    ((RevoluteJoint*)joints[mLEB])->setOffset(-20.f*D2Rf);
    ((RevoluteJoint*)joints[NO_OF_MODEL_JOINTS])->setOffset(30.0*D2Rf);
    ((RevoluteJoint*)joints[NO_OF_MODEL_JOINTS+1])->setOffset(-30.0*D2Rf);
    ((RevoluteJoint*)joints[NO_OF_MODEL_JOINTS+2])->setOffset(90.0*D2Rf);

    GLObject *body_camera   = newStl(0.0, 0.0, 0.58, STLPath+"ASM_VISION_col.stl");
    GLObject *body_torso    = newStl(0.0, 0.0, 0.0,  STLPath+"Body_TORSO_col.STL");

    //Base
    GLObject *body_whbase   = newStl(0.0, 0.0, 0.0, STLPath+"Body_OMNI_WHEELBASE_col.stl");
    GLObject *body_whplate  = newStl(0.0, 0.0, 0.0, STLPath+"Body_WHBASE_plate_col.STL");
    GLObject *body_rwh      = newStl(0.0, 0.0, 0.0, STLPath+"Body_OMNI_WHEEL_col.stl");
    GLObject *body_lwh      = newStl(0.0, 0.0, 0.0, STLPath+"Body_OMNI_WHEEL_col.stl");
    GLObject *body_bwh      = newStl(0.0, 0.0, 0.0, STLPath+"Body_OMNI_WHEEL_col.stl");

    //LARM
    GLObject *body_lsp	    = newStl(0.0, 0.0, 0.0, STLPath+"Body_LSP_col.STL");
    GLObject *body_lsr      = newStl(0.0, 0.0, 0.0, STLPath+"Body_LSR_col.STL");
    GLObject *body_lsy      = newStl(0.0, 0.0, 0.0, STLPath+"Body_LSY_col.STL");
    GLObject *body_leb      = newStl(0.0, 0.0, 0.0, STLPath+"Body_LEB_col.STL");
    GLObject *body_lwy      = newStl(0.0, 0.0, 0.0, STLPath+"Body_LWY_col.STL");
    GLObject *body_lwp      = newStl(0.0, 0.0, 0.0, STLPath+"Body_LWP_col.STL");
    GLObject *body_lwft     = newStl(0.0, 0.0, 0.0, STLPath+"Body_LWFT_col.STL");
    GLObject *body_lhand    = newStl(0.0, 0.0, 0.0, STLPath+"Body_LF1_col.STL");

    //LFinger
    GLObject *body_LF_a1    = newStl(0.0, 0.0, 0.0, STLPath+"Body_LF2_a1_col.STL");
    GLObject *body_LF_b1    = newStl(0.0, 0.0, 0.0, STLPath+"Body_LF2_b1_col.STL");
    GLObject *body_LF_c1    = newStl(0.0, 0.0, 0.0, STLPath+"Body_LF2_c1_col.STL");

    GLObject *body_LF_a2    = newStl(0.0, 0.0, 0.0, STLPath+"Body_LF2_a2_col.STL");
    GLObject *body_LF_b2    = newStl(0.0, 0.0, 0.0, STLPath+"Body_LF2_b2_col.STL");
    GLObject *body_LF_c2    = newStl(0.0, 0.0, 0.0, STLPath+"Body_LF2_c2_col.STL");

    GLObject *body_LF_a3    = newStl(0.0, 0.0, 0.0, STLPath+"Body_LF2_a3_col.STL");
    GLObject *body_LF_b3    = newStl(0.0, 0.0, 0.0, STLPath+"Body_LF2_b3_col.STL");
    GLObject *body_LF_c3    = newStl(0.0, 0.0, 0.0, STLPath+"Body_LF2_c3_col.STL");

    //RARM
    GLObject *body_rsp	    = newStl(0.0, 0.0, 0.0, STLPath+"Body_RSP_col.STL");
    GLObject *body_rsr      = newStl(0.0, 0.0, 0.0, STLPath+"Body_RSR_col.STL");
    GLObject *body_rsy      = newStl(0.0, 0.0, 0.0, STLPath+"Body_RSY_col.STL");
    GLObject *body_reb      = newStl(0.0, 0.0, 0.0, STLPath+"Body_REB_col.STL");
    GLObject *body_rwy      = newStl(0.0, 0.0, 0.0, STLPath+"Body_RWY_col.STL");
    GLObject *body_rwp      = newStl(0.0, 0.0, 0.0, STLPath+"Body_RWP_col.STL");
    GLObject *body_rwft     = newStl(0.0, 0.0, 0.0, STLPath+"Body_RWFT_col.STL");
    GLObject *body_rhand    = newStl(0.0, 0.0, 0.0, STLPath+"Body_RF1_col.STL");

    //RFinger
    GLObject *body_RF_a1    = newStl(0.0, 0.0, 0.0, STLPath+"Body_RF2_a1_col.STL");
    GLObject *body_RF_b1    = newStl(0.0, 0.0, 0.0, STLPath+"Body_RF2_b1_col.STL");
    GLObject *body_RF_c1    = newStl(0.0, 0.0, 0.0, STLPath+"Body_RF2_c1_col.STL");

    GLObject *body_RF_a2    = newStl(0.0, 0.0, 0.0, STLPath+"Body_RF2_a2_col.STL");
    GLObject *body_RF_b2    = newStl(0.0, 0.0, 0.0, STLPath+"Body_RF2_b2_col.STL");
    GLObject *body_RF_c2    = newStl(0.0, 0.0, 0.0, STLPath+"Body_RF2_c2_col.STL");

    GLObject *body_RF_a3    = newStl(0.0, 0.0, 0.0, STLPath+"Body_RF2_a3_col.STL");
    GLObject *body_RF_b3    = newStl(0.0, 0.0, 0.0, STLPath+"Body_RF2_b3_col.STL");
    GLObject *body_RF_c3    = newStl(0.0, 0.0, 0.0, STLPath+"Body_RF2_c3_col.STL");


    bones[B_WST]     = new Bone(COMP_NAME[BTORSO],  isnl::pos(0.0, 0.0, 0.0), body_torso);
    bones[B_CAMERA]  = new Bone(COMP_NAME[BCAMERA], isnl::pos(0.0, 0.0, 0.0), body_camera);
    bones[B_WHBASE]  = new Bone(COMP_NAME[BWHBASE], isnl::pos(0.0, 0.0, 0.0), body_whbase);
    bones[B_WHPLATE] = new Bone(COMP_NAME[BWHPLATE],isnl::pos(0.0, 0.0, 0.0), body_whplate);

    bones[B_LSP]     = new Bone(COMP_NAME[BLSP],    isnl::pos(0.0, 0.0, 0.0), body_lsp);
    bones[B_LSR]     = new Bone(COMP_NAME[BLSR],    isnl::pos(0.0, 0.0, 0.0), body_lsr);
    bones[B_LSY]     = new Bone(COMP_NAME[BLSY],    isnl::pos(0.0, 0.0, 0.0), body_lsy);
    bones[B_LEB]     = new Bone(COMP_NAME[BLEB],    isnl::pos(0.0, 0.0, 0.0), body_leb);
    bones[B_LWY]     = new Bone(COMP_NAME[BLWY],    isnl::pos(0.0, 0.0, 0.0), body_lwy);
    bones[B_LWP]     = new Bone(COMP_NAME[BLWP],    isnl::pos(0.0, 0.0, 0.0), body_lwp);
    bones[B_LWFT]    = new Bone(COMP_NAME[BLWFT],   isnl::pos(0.0, 0.0, 0.0), body_lwft);
    bones[B_LHAND]   = new Bone(COMP_NAME[BLWY2],   isnl::pos(0.0, 0.0, 0.0), body_lhand);

    bones[B_LF_a1]   = new Bone(COMP_NAME[BLF_a1],  isnl::pos(0.0, 0.0, 0.0), body_LF_a1);
    bones[B_LF_b1]   = new Bone(COMP_NAME[BLF_b1],  isnl::pos(0.0, 0.0, 0.0), body_LF_b1);
    bones[B_LF_c1]   = new Bone(COMP_NAME[BLF_c1],  isnl::pos(0.0, 0.0, 0.0), body_LF_c1);

    bones[B_LF_a2]   = new Bone(COMP_NAME[BLF_a2],  isnl::pos(0.0, 0.0, 0.0), body_LF_a2);
    bones[B_LF_b2]   = new Bone(COMP_NAME[BLF_b2],  isnl::pos(0.0, 0.0, 0.0), body_LF_b2);
    bones[B_LF_c2]   = new Bone(COMP_NAME[BLF_c2],  isnl::pos(0.0, 0.0, 0.0), body_LF_c2);

    bones[B_LF_a3]   = new Bone(COMP_NAME[BLF_a3],  isnl::pos(0.0, 0.0, 0.0), body_LF_a3);
    bones[B_LF_b3]   = new Bone(COMP_NAME[BLF_b3],  isnl::pos(0.0, 0.0, 0.0), body_LF_b3);
    bones[B_LF_c3]   = new Bone(COMP_NAME[BLF_c3],  isnl::pos(0.0, 0.0, 0.0), body_LF_c3);


    bones[B_RSP]     = new Bone(COMP_NAME[BRSP],    isnl::pos(0.0, 0.0, 0.0), body_rsp);
    bones[B_RSR]     = new Bone(COMP_NAME[BRSR],    isnl::pos(0.0, 0.0, 0.0), body_rsr);
    bones[B_RSY]     = new Bone(COMP_NAME[BRSY],    isnl::pos(0.0, 0.0, 0.0), body_rsy);
    bones[B_REB]     = new Bone(COMP_NAME[BREB],    isnl::pos(0.0, 0.0, 0.0), body_reb);
    bones[B_RWY]     = new Bone(COMP_NAME[BRWY],    isnl::pos(0.0, 0.0, 0.0), body_rwy);
    bones[B_RWP]     = new Bone(COMP_NAME[BRWP],    isnl::pos(0.0, 0.0, 0.0), body_rwp);
    bones[B_RWFT]    = new Bone(COMP_NAME[BRWFT],   isnl::pos(0.0, 0.0, 0.0), body_rwft);
    bones[B_RHAND]   = new Bone(COMP_NAME[BRWY2],   isnl::pos(0.0, 0.0, 0.0), body_rhand);

    bones[B_RF_a1]   = new Bone(COMP_NAME[BRF_a1],  isnl::pos(0.0, 0.0, 0.0), body_RF_a1);
    bones[B_RF_b1]   = new Bone(COMP_NAME[BRF_b1],  isnl::pos(0.0, 0.0, 0.0), body_RF_b1);
    bones[B_RF_c1]   = new Bone(COMP_NAME[BRF_c1],  isnl::pos(0.0, 0.0, 0.0), body_RF_c1);

    bones[B_RF_a2]   = new Bone(COMP_NAME[BRF_a2],  isnl::pos(0.0, 0.0, 0.0), body_RF_a2);
    bones[B_RF_b2]   = new Bone(COMP_NAME[BRF_b2],  isnl::pos(0.0, 0.0, 0.0), body_RF_b2);
    bones[B_RF_c2]   = new Bone(COMP_NAME[BRF_c2],  isnl::pos(0.0, 0.0, 0.0), body_RF_c2);

    bones[B_RF_a3]   = new Bone(COMP_NAME[BRF_a3],  isnl::pos(0.0, 0.0, 0.0), body_RF_a3);
    bones[B_RF_b3]   = new Bone(COMP_NAME[BRF_b3],  isnl::pos(0.0, 0.0, 0.0), body_RF_b3);
    bones[B_RF_c3]   = new Bone(COMP_NAME[BRF_c3],  isnl::pos(0.0, 0.0, 0.0), body_RF_c3);

    bones[B_LWH]     = new Bone(COMP_NAME[BLWH],    isnl::pos(0.0, 0.0, 0.0), body_lwh);
    bones[B_RWH]     = new Bone(COMP_NAME[BRWH],    isnl::pos(0.0, 0.0, 0.0), body_rwh);
    bones[B_BWH]     = new Bone(COMP_NAME[BBWH],    isnl::pos(0.0, 0.0, 0.0), body_bwh);


    //tree
    bones[B_WST]->setParent(NULL);
    *bones[B_WST] + bones[B_CAMERA];

    //right arm
    tempbone[14] = new Bone("T_RS",         isnl::pos(0,-0.249,0.456));
    tempbone[15] = new Bone("RS_REB",       isnl::pos(0.035,0,-0.35));
    tempbone[16] = new Bone("REB_RWP",      isnl::pos(-0.035,0,-0.34));
    tempbone[17] = new Bone("RWP_RWFT",     isnl::pos(0,0,-0.0326));
    tempbone[18] = new Bone("RWFT_RHAND",   isnl::pos(0,0,0.0326));

    tempbone[19] = new Bone("RHAND_RF2_a1", isnl::pos(0.02498, -0.023, -0.1471));
    tempbone[20] = new Bone("RF2_a1_a2",    isnl::pos(0.03889, 0.0, -0.0388));
    tempbone[21] = new Bone("RF2_a2_a3",    isnl::pos(0.04, 0.0, 0.0));

    tempbone[22] = new Bone("RHAND_RF2_b1", isnl::pos(0.02498, 0.023, -0.1471));
    tempbone[23] = new Bone("RF2_b1_b2",    isnl::pos(0.03889, 0.0, -0.0388));
    tempbone[24] = new Bone("RF2_b2_b3",    isnl::pos(0.04, 0.0, 0.0));

    tempbone[25] = new Bone("RHAND_RF2_c1", isnl::pos(-0.02502, 0.0, -0.1471));
    tempbone[26] = new Bone("RF2_c1_c2",    isnl::pos(-0.03889, 0.0, -0.0388));
    tempbone[27] = new Bone("RF2_c2_c3",    isnl::pos(-0.04, 0.0, 0.0));

    *bones[B_WST] + tempbone[14]  + joints[mRSP]  + bones[B_RSP] + joints[mRSR] + bones[B_RSR]  + joints[mRSY] + bones[B_RSY]
                  + tempbone[15]  + joints[mREB]  + bones[B_REB]
                  + tempbone[16]  + joints[mRWY]  + bones[B_RWY] + joints[mRWP] + bones[B_RWP]
                  + tempbone[17]  + bones[B_RWFT] + tempbone[18]
                  + joints[mRWY2] + bones[B_RHAND];
    *bones[B_RHAND] + tempbone[19] + joints[RF_a1] + bones[B_RF_a1] + tempbone[20] + joints[RF_a2] + bones[B_RF_a2] + tempbone[21] + joints[RF_a3] ;//+ bones[B_RF_a3];
    *bones[B_RHAND] + tempbone[22] + joints[RF_b1] + bones[B_RF_b1] + tempbone[23] + joints[RF_b2] + bones[B_RF_b2] + tempbone[24] + joints[RF_b3] ;//+ bones[B_RF_b3];
    *bones[B_RHAND] + tempbone[25] + joints[RF_c1] + bones[B_RF_c1] + tempbone[26] + joints[RF_c2] + bones[B_RF_c2] + tempbone[27] + joints[RF_c3] ;//+ bones[B_RF_c3];

    //left arm
    tempbone[0]  = new Bone("T_LS",         isnl::pos(0,0.249,0.456));
    tempbone[1]  = new Bone("LS_LEB",       isnl::pos(0.035,0,-0.35));
    tempbone[2]  = new Bone("LEB_LWP",      isnl::pos(-0.035,0,-0.34));
    tempbone[3]  = new Bone("LWP_LWFT",     isnl::pos(0,0,-0.0326));
    tempbone[4]  = new Bone("LWFT_LHAND",   isnl::pos(0,0,0.0326));

    tempbone[5]  = new Bone("LHAND_LF2_a1", isnl::pos(0.02498, -0.023, -0.1471));
    tempbone[6]  = new Bone("LF2_a1_a2",    isnl::pos(0.03889, 0.0, -0.0388));
    tempbone[7]  = new Bone("LF2_a2_a3",    isnl::pos(0.04, 0.0, 0.0));

    tempbone[8]  = new Bone("LHAND_LF2_b1", isnl::pos(0.02498, 0.023, -0.1471));
    tempbone[9]  = new Bone("LF2_b1_b2",    isnl::pos(0.03889, 0.0, -0.0388));
    tempbone[10] = new Bone("LF2_b2_b3",    isnl::pos(0.04, 0.0, 0.0));

    tempbone[11] = new Bone("LHAND_LF2_c1", isnl::pos(-0.02502, 0.0, -0.1471));
    tempbone[12] = new Bone("LF2_c1_c2",    isnl::pos(-0.03889, 0.0, -0.0388));
    tempbone[13] = new Bone("LF2_c2_c3",    isnl::pos(-0.04, 0.0, 0.0));

    *bones[B_WST] + tempbone[0]   + joints[mLSP]  + bones[B_LSP] + joints[mLSR] + bones[B_LSR]  + joints[mLSY] + bones[B_LSY]
                  + tempbone[1]   + joints[mLEB]  + bones[B_LEB]
                  + tempbone[2]   + joints[mLWY]  + bones[B_LWY] + joints[mLWP] + bones[B_LWP]
                  + tempbone[3]   + bones[B_LWFT] + tempbone[4]
                  + joints[mLWY2] + bones[B_LHAND];
    *bones[B_LHAND] + tempbone[5] + joints[LF_a1] + bones[B_LF_a1] + tempbone[6] + joints[LF_a2] + bones[B_LF_a2] + tempbone[7]  + joints[LF_a3] + bones[B_LF_a3];
    *bones[B_LHAND] + tempbone[8] + joints[LF_b1] + bones[B_LF_b1] + tempbone[9] + joints[LF_b2] + bones[B_LF_b2] + tempbone[10] + joints[LF_b3] + bones[B_LF_b3];
    *bones[B_LHAND] + tempbone[11]+ joints[LF_c1] + bones[B_LF_c1] + tempbone[12]+ joints[LF_c2] + bones[B_LF_c2] + tempbone[13] + joints[LF_c3] + bones[B_LF_c3];

    //Base
    tempbone[28] = new Bone("T_WHBASE",   isnl::pos(0.0, 0.0, -0.478));
    tempbone[29] = new Bone("WHBASE_RWH", isnl::pos(0.17062, -0.29, -0.06));
    tempbone[30] = new Bone("WHBASE_LWH", isnl::pos(0.15704, 0.27, -0.06));
    tempbone[31] = new Bone("WHBASE_BWH", isnl::pos(-0.31, -0.00784, -0.06));
    *bones[B_WST] + joints[mWST] + tempbone[28] + bones[B_WHBASE];
    *bones[B_WHBASE] + tempbone[29] + joints[NO_OF_MODEL_JOINTS]   + joints[mRWH] + bones[B_RWH];
    *bones[B_WHBASE] + tempbone[30] + joints[NO_OF_MODEL_JOINTS+1] + joints[mLWH] + bones[B_LWH];
    *bones[B_WHBASE] + tempbone[31] + joints[NO_OF_MODEL_JOINTS+2] + joints[mBWH] + bones[B_BWH];

    return new HUBOModel(bones, joints, objs);
}
