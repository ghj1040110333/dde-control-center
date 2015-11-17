#include "webcamavatarpanel.h"

WebcamAvatarPanel::WebcamAvatarPanel(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(PANEL_HEIGHT);

    initCameraLayout();

    initStackWidget();

    initCameraView();
    initScaleSlider();
    initControlButton();
    m_layout->addStretch();
}

void WebcamAvatarPanel::turnOnCamera()
{
    m_camera = new QCamera(QCameraInfo::defaultCamera(), this);
    connect(m_camera, SIGNAL(error(QCamera::Error)), this, SLOT(onCameraError(QCamera::Error)));

    if(m_camera){
        m_cameraView->setSource(m_camera);
        m_camera->start();
    }
}

void WebcamAvatarPanel::turnOffCamera()
{
    if (m_camera){
        m_camera->stop();
        m_camera->deleteLater();
        m_camera = NULL;
    }
}

void WebcamAvatarPanel::initCameraLayout()
{
    m_layout = new QVBoxLayout;
    m_layout->setAlignment(Qt::AlignHCenter);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(20);
    m_layout->addSpacing(15);
}

void WebcamAvatarPanel::initCameraView()
{
    m_cameraView = new DCameraView(this);
    m_cameraView->setRound(true);
    m_cameraView->setMirroredHorizontal(true);
    m_cameraView->setFixedSize(CAMERA_VIEW_SIZE, CAMERA_VIEW_SIZE);
    m_cameraView->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);

    m_layout->addWidget(m_cameraView, 0, Qt::AlignHCenter);
}

void WebcamAvatarPanel::initScaleSlider()
{
    QFrame *frame = new QFrame;
    QHBoxLayout *layout = new QHBoxLayout(frame);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    DSlider *slider = new DSlider;
    slider->setPageStep(1);
    slider->setOrientation(Qt::Horizontal);
    slider->setFixedWidth(CAMERA_VIEW_SIZE);
    slider->setRange(10, 20);
    connect(slider, &DSlider::valueChanged, this, &WebcamAvatarPanel::onSliderValueChanged);

    GeneralRemoveButton *decreaseButton = new GeneralRemoveButton;
    decreaseButton->setCheckable(false);
    GeneralAddButton *increaseButton = new GeneralAddButton;
    connect(decreaseButton, &GeneralRemoveButton::clicked, [=]{
        int value = slider->value();
        slider->setValue(value - SLIDER_STEP < slider->minimum() ? value : value - SLIDER_STEP);
    });
    connect(increaseButton, &GeneralAddButton::clicked, [=]{
        int value = slider->value();
        slider->setValue(value + SLIDER_STEP > slider->maximum() ? value : value + SLIDER_STEP);
    });

    layout->addWidget(decreaseButton);
    layout->addWidget(slider);
    layout->addWidget(increaseButton);

    m_layout->addWidget(frame, 0, Qt::AlignHCenter);
}

void WebcamAvatarPanel::initControlButton()
{
    QFrame *frame = new QFrame;
    QHBoxLayout *layout = new QHBoxLayout(frame);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(DUI::BUTTON_MARGIN);

    DTextButton *snapshotButton = new DTextButton(tr("Snapshot"));
    connect(snapshotButton, &DTextButton::clicked, this, &WebcamAvatarPanel::onSnapshot);
    DTextButton *confirmButton = new DTextButton(tr("Confirm"));
    connect(confirmButton, &DTextButton::clicked, this, &WebcamAvatarPanel::onConfirm);

    layout->addStretch(1);
    layout->addWidget(snapshotButton);
    layout->addWidget(confirmButton);
    layout->addSpacing(DUI::HEADER_RIGHT_MARGIN);

    m_layout->addWidget(frame);
}

void WebcamAvatarPanel::initStackWidget()
{
    m_stackWidget = new QStackedWidget;

    QFrame *lFrame = new QFrame;
    QLabel *errorLabel = new QLabel(tr("No camera found."));
    errorLabel->setObjectName("CameraErrorLabel");
    QVBoxLayout *lLayout = new QVBoxLayout(lFrame);
    lLayout->setAlignment(Qt::AlignCenter);
    lLayout->addWidget(errorLabel);
    m_stackWidget->addWidget(lFrame);

    QFrame *frame = new QFrame;
    frame->setLayout(m_layout);
    m_stackWidget->addWidget(frame);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_stackWidget);
    m_stackWidget->setCurrentIndex(1);
}

void WebcamAvatarPanel::onSnapshot()
{
    DTextButton *button = qobject_cast<DTextButton *>(sender());
    if (m_camera->state() == QCamera::ActiveState){
        m_camera->stop();
        button->setText(tr("Again"));
        m_cameraView->setRound(false);  //for save all pixel
        m_captureState = m_cameraView->capture().save(IMAGE_SAVE_PATH);
        m_cameraView->setRound(true);
    }
    else{
        m_camera->start();
        button->setText(tr("Snapshot"));
    }
}

void WebcamAvatarPanel::onConfirm()
{
    if (m_captureState)
        emit selectedAvatar(IMAGE_SAVE_PATH);
}

void WebcamAvatarPanel::onSliderValueChanged(int value)
{
    if (m_cameraView)
        m_cameraView->setScale(value / 10.0);
}

void WebcamAvatarPanel::onCameraError(QCamera::Error)
{
    m_stackWidget->setCurrentIndex(0);
}

