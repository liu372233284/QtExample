#include "mainwindow.h"
#include "iconsizespinbox.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QAction>
#include <QLabel>
#include <QValidator>
#include <QGroupBox>
#include <QSpinBox>
#include <QDebug>
#include <QSlider>
#include <QProgressBar>
#include <QDateTimeEdit>
#include <QScrollArea>
#include <QToolBox>
#include "toolbox.h"
#include <QTabWidget>
#include <QSystemTrayIcon>
#include "traymenu.h"
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include "cardlayout.h"
#include "flowlayout.h"
#include "qborderlayout.h"
#include <QTextBrowser>
#include "qcardlayoutwidget.h"
#include <QCheckBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QStackedLayout>
#include <QSpacerItem>
#include "filesystemwatcher.h"
#include <QTimer>
#include <QFileIconProvider>
#include <QListWidget>
#include "paintfoutwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QTabWidget *pTabWidget = new QTabWidget(this);
    ///
    /// QLineEdit
    ///
   {
        QVBoxLayout *pLineEditLayout = new QVBoxLayout();

        QLineEdit *normalText = new QLineEdit(this);
        QLineEdit *noEchoText = new QLineEdit(this);
        QLineEdit *passwordText = new QLineEdit(this);
        QLineEdit *passwordEchoOnEditText = new QLineEdit(this);

        normalText->setPlaceholderText("Normal");
        noEchoText->setPlaceholderText("NoEcho");
        passwordText->setPlaceholderText("Password");
        passwordEchoOnEditText->setPlaceholderText("PasswordEchoOnEdit");

        normalText->setEchoMode(QLineEdit::Normal);
        noEchoText->setEchoMode(QLineEdit::NoEcho);
        passwordText->setEchoMode(QLineEdit::Password);
        passwordEchoOnEditText->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        pLineEditLayout->addWidget(normalText);
        pLineEditLayout->addWidget(noEchoText);
        pLineEditLayout->addWidget(passwordText);
        pLineEditLayout->addWidget(passwordEchoOnEditText);

        pSearchLabel = new QLabel(this);
        pSearchLabel->setText("要搜索的内容是:");
        pSearchEdit = new QLineEdit(this);

        QAction *pActionLeading = new QAction(this);
        pActionLeading->setIcon(QIcon(":/Images/leading"));
        pSearchEdit->addAction(pActionLeading,QLineEdit::LeadingPosition);

        QAction *pActionTrailing = new QAction(this);
        pActionTrailing->setIcon(QIcon(":/Images/trailing"));
        pSearchEdit->addAction(pActionTrailing,QLineEdit::TrailingPosition);
        pSearchEdit->setPlaceholderText("请输入要搜索的内容");

        connect(pActionTrailing,SIGNAL(triggered(bool)),this,SLOT(onSearch(bool)));
        pLineEditLayout->addWidget(pSearchEdit);
        pLineEditLayout->addWidget(pSearchLabel);

        QLineEdit *pIntEdit = new QLineEdit(this);
        QLineEdit *pDoubleEdit = new QLineEdit(this);
        QLineEdit *pValidatorEdit = new QLineEdit(this);

        pIntEdit->setPlaceholderText("校验整形");
        pDoubleEdit->setPlaceholderText("校验双精度");
        pValidatorEdit->setPlaceholderText("校验字符串数字");

        QIntValidator *pIntValidator = new QIntValidator(this);
        pIntValidator->setRange(1,99);

        QDoubleValidator *pDoubleValidator = new QDoubleValidator(this);
        pDoubleValidator->setNotation(QDoubleValidator::StandardNotation);
        pDoubleValidator->setRange(-300,300,2);

        QRegExpValidator *pRegValidator = new QRegExpValidator(this);
        pRegValidator->setRegExp(QRegExp("[A-Za-z0-9]+$"));

        pIntEdit->setValidator(pIntValidator);
        pDoubleEdit->setValidator(pDoubleValidator);
        pValidatorEdit->setValidator(pRegValidator);

        pLineEditLayout->addWidget(pIntEdit);
        pLineEditLayout->addWidget(pDoubleEdit);
        pLineEditLayout->addWidget(pValidatorEdit);

        QLineEdit *pIpLineEdit = new QLineEdit(this);
        QLineEdit *pMacLineEdit = new QLineEdit(this);
        QLineEdit *pDateLineEdit = new QLineEdit(this);
        QLineEdit *pLicenseLineEdit = new QLineEdit(this);

        pIpLineEdit->setInputMask("000.000.000.000;_");
        pMacLineEdit->setInputMask("HH:HH:HH:HH:HH:HH;_");
        pDateLineEdit->setInputMask("0000-00-00");
        pLicenseLineEdit->setInputMask(">AAAA-AAAA-AAAA-AAAA-AAAA;#");

        pLineEditLayout->addWidget(pIpLineEdit);
        pLineEditLayout->addWidget(pMacLineEdit);
        pLineEditLayout->addWidget(pDateLineEdit);
        pLineEditLayout->addWidget(pLicenseLineEdit);
        pLineEditLayout->addStretch();

        QWidget *pLineEditWidget = new QWidget(this);
        pLineEditWidget->setLayout(pLineEditLayout);
        pTabWidget->addTab(pLineEditWidget,"QLineEdit");
    }

    ///
    ///  SpinBox
    ///
    {
        QVBoxLayout *pSpinBoxLayout = new QVBoxLayout();

        QSpinBox *pSpinBox = new QSpinBox(this);

        pSpinBox->setRange(20,200);
        pSpinBox->setSingleStep(10);
        pSpinBox->setSuffix("%");
        pSpinBox->setPrefix("$");
        pSpinBox->setValue(150);
        pSpinBox->setWrapping(true);
        connect(pSpinBox,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                [=](int value){
            qDebug()<<"Value: "<<value;
            qDebug()<<"text: "<<pSpinBox->text();
        });

        connect(pSpinBox,static_cast<void (QSpinBox::*)(const QString &)>(&QSpinBox::valueChanged),
                [=](const QString &text){
            qDebug()<<"text Value: "<<text;
            qDebug()<<"cleanText: "<<pSpinBox->cleanText();
        });
        pSpinBoxLayout->addWidget(pSpinBox);

        QSpinBox *pZoomSpinBox = new QSpinBox(this);
        pZoomSpinBox->setRange(0,1000);
        pZoomSpinBox->setSpecialValueText("Auto");
        pZoomSpinBox->setSingleStep(10);
        pZoomSpinBox->setValue(100);
        pZoomSpinBox->setSuffix("%");

        pSpinBoxLayout->addWidget(pZoomSpinBox);

        pSpinBoxLayout->addWidget(new IconSizeSpinBox(this));

        QDoubleSpinBox *pDoubleSpinBox = new QDoubleSpinBox(this);
        pDoubleSpinBox->setRange(0,20);
        pDoubleSpinBox->setSingleStep(0.005);
        pDoubleSpinBox->setValue(0.010);
        pDoubleSpinBox->setDecimals(3);
        pSpinBoxLayout->addWidget(pDoubleSpinBox);
        pSpinBoxLayout->addStretch();

        QWidget *pSpinBoxWidget = new QWidget(this);
        pSpinBoxWidget->setLayout(pSpinBoxLayout);
        pTabWidget->addTab(pSpinBoxWidget,"QSpinBox");
    }

    ///
    /// QSlider
    ///
   {
        QVBoxLayout *pSliderLayout = new QVBoxLayout();

        QSlider *pSlider = new QSlider(this);
        pSlider->setRange(0,100);
        pSlider->setSingleStep(1);
        pSlider->setValue(1);
        pSlider->setTickInterval(10);
        pSlider->setTickPosition(QSlider::TicksAbove);
        pSlider->setOrientation(Qt::Horizontal);

        QSpinBox *pSpinTmp = new QSpinBox(this);
        pSpinTmp->setRange(0,100);
        pSpinTmp->setSingleStep(1);
        pSpinTmp->setValue(1);

        connect(pSlider,SIGNAL(valueChanged(int)) ,pSpinTmp,SLOT(setValue(int)));
        connect(pSpinTmp,SIGNAL(valueChanged(int)),pSlider,SLOT(setValue(int)));

        pSliderLayout->addWidget(pSlider);
        pSliderLayout->addWidget(pSpinTmp);
        pSliderLayout->addStretch();

        QWidget *pSliderWidget = new QWidget(this);
        pSliderWidget->setLayout(pSliderLayout);
        pTabWidget->addTab(pSliderWidget,"QSlider");
    }

    ///
    /// QProgressBar
    ///
    {
        QVBoxLayout *pProgressBarLayout = new QVBoxLayout();

        QProgressBar *pProgressBar1 = new QProgressBar(this);
        pProgressBar1->setOrientation(Qt::Horizontal);
        pProgressBar1->setRange(0,100);
        pProgressBar1->setValue(50);
        double dProgress = (pProgressBar1->value()-pProgressBar1->minimum())*100/(pProgressBar1->maximum()-pProgressBar1->minimum());
        pProgressBar1->setFormat(QString("我的进度条是:%1%").arg(QString::number(dProgress,'f',2)));
        pProgressBar1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        QProgressBar *pProgressBar2 = new QProgressBar(this);
        pProgressBar2->setOrientation(Qt::Horizontal);
        pProgressBar2->setRange(0,100);
        pProgressBar2->setValue(50);
        pProgressBar2->setInvertedAppearance(true);

        QProgressBar *pProgressBar3 = new QProgressBar(this);
        pProgressBar3->setRange(0,0);
        pProgressBar3->setOrientation(Qt::Horizontal);

        pProgressBarLayout->addWidget(pProgressBar1);
        pProgressBarLayout->addWidget(pProgressBar2);
        pProgressBarLayout->addWidget(pProgressBar3);
        pProgressBarLayout->addStretch();

        QWidget *pProgressBarWidget = new QWidget(this);
        pProgressBarWidget->setLayout(pProgressBarLayout);
        pTabWidget->addTab(pProgressBarWidget,"QProgressBar");
    }

    ///
    /// QDateTimeEdit
    ///
    {
        QVBoxLayout *pDateTimeLayout = new QVBoxLayout();

        QDateTimeEdit *pDateTimeEdit = new QDateTimeEdit(this);
        QDateTimeEdit *pCurrentDateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(),this);
        QDateTimeEdit *pDateEdit = new QDateTimeEdit(QDate::currentDate(),this);
        QDateTimeEdit *pTimeEdit = new QDateTimeEdit(QTime::currentTime(),this);
        pCurrentDateTimeEdit->setMaximumDate(QDate::currentDate().addDays(365));
        pCurrentDateTimeEdit->setMinimumDate(QDate::currentDate().addDays(-365));
        pCurrentDateTimeEdit->setCalendarPopup(true);

        qDebug()<<"当前日期时间:"<<pCurrentDateTimeEdit->dateTime();
        qDebug()<<"当前日期:"<<pCurrentDateTimeEdit->date();
        qDebug()<<"当前时间:"<<pCurrentDateTimeEdit->time();
        qDebug()<<"最大日期时间:"<<pCurrentDateTimeEdit->maximumDateTime();
        qDebug()<<"最大日期:"<<pCurrentDateTimeEdit->maximumDate();
        qDebug()<<"最大时间:"<<pCurrentDateTimeEdit->maximumTime();
        qDebug()<<"最小日期时间:"<<pCurrentDateTimeEdit->minimumDateTime();
        qDebug()<<"最小日期:"<<pCurrentDateTimeEdit->minimumDate();
        qDebug()<<"最小时间:"<<pCurrentDateTimeEdit->time();

        pDateTimeLayout->addWidget(pDateTimeEdit);
        pDateTimeLayout->addWidget(pCurrentDateTimeEdit);
        pDateTimeLayout->addWidget(pDateEdit);
        pDateTimeLayout->addWidget(pTimeEdit);

        QDateTimeEdit *pDateTimeEdit1 = new QDateTimeEdit(this);
        QDateTimeEdit *pCurrentDateTimeEdit1 = new QDateTimeEdit(QDateTime::currentDateTime(),this);
        QDateTimeEdit *pDateEdit1 = new QDateTimeEdit(QDate::currentDate(),this);
        QDateTimeEdit *pTimeEdit1 = new QDateTimeEdit(QTime::currentTime(),this);

        pDateTimeEdit1->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
        pCurrentDateTimeEdit1->setDisplayFormat("yyyy/MM/dd HH/mm/ss");
        pDateEdit1->setDisplayFormat("yyyy.M.d");
        pTimeEdit1->setDisplayFormat("H.mm");

        pDateTimeLayout->addWidget(pDateTimeEdit1);
        pDateTimeLayout->addWidget(pCurrentDateTimeEdit1);
        pDateTimeLayout->addWidget(pDateEdit1);
        pDateTimeLayout->addWidget(pTimeEdit1);

        connect(pDateTimeEdit1,static_cast<void (QDateTimeEdit::*)(const QDateTime &dateTime)> (&QDateTimeEdit::dateTimeChanged),
                [=](const QDateTime &dateTime){
            qDebug()<<"QDateTime"<<dateTime;
        });
        connect(pDateTimeEdit1,static_cast<void (QDateTimeEdit::*)(const QTime &time)> (&QDateTimeEdit::timeChanged),
                [=](const QTime &time){
            qDebug()<<"QTime"<<time;
        });
        connect(pDateTimeEdit1,static_cast<void (QDateTimeEdit::*)(const QDate &date)> (&QDateTimeEdit::dateChanged),
                [=](const QDate &date){
            qDebug()<<"QDate"<<date;
        });
        pDateTimeLayout->addStretch();
        QWidget *pDateTimeEditWidget = new QWidget(this);
        pDateTimeEditWidget->setLayout(pDateTimeLayout);
        pTabWidget->addTab(pDateTimeEditWidget,"QDateTimeEdit");
    }

    ///
    /// QScrollArea
    ///
   {
        QVBoxLayout *pScrollAreaLayout = new QVBoxLayout();
        QLabel *pScrollAreaTitle = new QLabel("QScrollArea",this);
        pScrollAreaTitle->setAlignment(Qt::AlignLeft|Qt::AlignTop);
        pScrollAreaLayout->addWidget(pScrollAreaTitle);

        QLabel *pImageLabel = new QLabel(this);
        pImageLabel->setPixmap(QPixmap(":/Images/head"));

        QScrollArea *pScrollArea = new QScrollArea(this);
        pScrollArea->setBackgroundRole(QPalette::Dark);
        pScrollArea->setWidget(pImageLabel);

        pScrollAreaLayout->addWidget(pScrollArea);

        QLabel *imgLabel = new QLabel(this);
        QPixmap pixmap  =  QPixmap(":/Images/head1");
        pixmap.scaled(200,200,Qt::KeepAspectRatio);
        imgLabel->setPixmap(pixmap);
        imgLabel->setStyleSheet("background:white;");
        imgLabel->setAlignment(Qt::AlignCenter);

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setBackgroundRole(QPalette::Dark);
        scrollArea->setWidget(imgLabel);
        scrollArea->setAlignment(Qt::AlignCenter);
     //   scrollArea->widget()->resize(260,260);
        scrollArea->setWidgetResizable(true);
        pScrollAreaLayout->addWidget(scrollArea);
        pScrollAreaLayout->addStretch();

    //    QWidget *widget = scrollArea->takeWidget();
    //    QLabel *pLabel = qobject_cast<QLabel *>(widget);

        QWidget *pScrollAreaWidget = new QWidget(this);
        pScrollAreaWidget->setLayout(pScrollAreaLayout);
        pTabWidget->addTab(pScrollAreaWidget,"QScrollArea");
    }


    ///
    /// QToolBox
    ///
    {
        QVBoxLayout *pToolBoxLayout = new QVBoxLayout();
        QLabel *pToolBoxTitle = new QLabel("QToolBox",this);
        pToolBoxTitle->setAlignment(Qt::AlignTop|Qt::AlignLeft);
        pToolBoxLayout->addWidget(pToolBoxTitle);

        ToolBox *pToolBox = new ToolBox(this);
        pToolBoxLayout->addWidget(pToolBox);
        pToolBoxLayout->addStretch();

        QWidget *pToolBoxWidget = new QWidget(this);
        pToolBoxWidget->setLayout(pToolBoxLayout);
        pTabWidget->addTab(pToolBoxWidget,"QToolBox");
    }

    ///
    /// QSystemTrayIcon
    ///
    {
        QSystemTrayIcon *pSystemTray = new QSystemTrayIcon(this);
        TrayMenu *pTrayMenu = new TrayMenu(this);
        pSystemTray->setContextMenu(pTrayMenu);
        pSystemTray->setIcon(QIcon(":/Images/10"));
        pSystemTray->setToolTip("我就是托盘");

        pSystemTray->show();

        pSystemTray->showMessage("我是标题","我是内容消息");

        connect(pSystemTray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(onActivated(QSystemTrayIcon::ActivationReason)));


        connect(pTrayMenu,SIGNAL(showWindow()),this,SLOT(onShowWindow()));
    }

    ///
    /// 布局管理器
    ///
    {
        QWidget *layoutWidget = new QWidget();
        QPushButton *oneButton = new QPushButton("One");
        QPushButton *twoButton = new QPushButton("Two");
        QPushButton *threeButton = new QPushButton("Three");
        QPushButton *fourButton = new QPushButton("Four");
        QPushButton *fiveButton = new QPushButton("Five");

        QGridLayout *gridLayout = new QGridLayout();
        gridLayout->addWidget(oneButton,0,0);
        gridLayout->addWidget(twoButton,0,1);
        gridLayout->addWidget(threeButton,1,0,1,2);
        gridLayout->addWidget(fourButton,2,0);
        gridLayout->addWidget(fiveButton,2,1);

        QFormLayout *formLayout = new QFormLayout();
        formLayout->addRow(new QPushButton("One1"),new QLineEdit());
        formLayout->addRow(new QPushButton("Two2"),new QLineEdit());
        formLayout->addRow(new QPushButton("Three3"),new QLineEdit());

        QVBoxLayout *vlayout = new QVBoxLayout();
        vlayout->addLayout(gridLayout);
        vlayout->addLayout(formLayout);
        vlayout->addStretch();
        layoutWidget->setLayout(vlayout);
        pTabWidget->addTab(layoutWidget,"布局管理器");
    }

    ///
    /// 自定义布局CardLayout
    ///
    {
        CardLayout *pCardlayout = new CardLayout();
        pCardlayout->setSpacing(30);

        pCardlayout->addWidget(new QLabel("label1"));
        pCardlayout->addWidget(new QLabel("label2"));
        pCardlayout->addWidget(new QLabel("label3"));

        QWidget *pCardLayoutWidget = new QWidget();
        pCardLayoutWidget->setLayout(pCardlayout);

        pTabWidget->addTab(pCardLayoutWidget,"自定义CardLayout");
    }

    ///
    /// 自定义布局FlowLayout
    ///
    {
        FlowLayout *pFlowLayout = new FlowLayout();
        pFlowLayout->setSpacing(30);

        pFlowLayout->addWidget(new QPushButton("click1"));
        pFlowLayout->addWidget(new QPushButton("click2"));
        pFlowLayout->addWidget(new QPushButton("click3"));
        pFlowLayout->addWidget(new QPushButton("click4"));
        pFlowLayout->addWidget(new QPushButton("click5"));
        pFlowLayout->addWidget(new QPushButton("click6"));
        pFlowLayout->addWidget(new QPushButton("click7"));
        pFlowLayout->addWidget(new QPushButton("click8"));
        pFlowLayout->addWidget(new QPushButton("click9"));
        pFlowLayout->addWidget(new QPushButton("click10"));
        pFlowLayout->addWidget(new QPushButton("click11"));
        pFlowLayout->addWidget(new QPushButton("click12"));

        QWidget *pFlowLayoutWidget = new QWidget();
        pFlowLayoutWidget->setLayout(pFlowLayout);

        pTabWidget->addTab(pFlowLayoutWidget,"自定义FlowLayout");
    }

    ///
    ///自定义边框布局QBorderLayout
    ///
   {
        QBorderLayout *pBorderLayout = new QBorderLayout();
        pBorderLayout->setSpacing(30);

        QTextBrowser *pCentralWidget = new QTextBrowser();
        pCentralWidget->setPlainText("Central Widget");

        pBorderLayout->addWidget(pCentralWidget,QBorderLayout::Center);
        pBorderLayout->addWidget(CreateLabel("north"),QBorderLayout::North);
        pBorderLayout->addWidget(CreateLabel("south"),QBorderLayout::South);
        pBorderLayout->addWidget(CreateLabel("east1"),QBorderLayout::East);
        pBorderLayout->addWidget(CreateLabel("east2"),QBorderLayout::East);
        pBorderLayout->addWidget(CreateLabel("west"),QBorderLayout::West);

        QWidget *pBorderLayoutWidget = new QWidget();
        pBorderLayoutWidget->setLayout(pBorderLayout);

        pTabWidget->addTab(pBorderLayoutWidget,"自定义BorderLayout");
    }

    ///
    ///手动布局
    ///
    {
        QWidget *pCardLayoutWidget1 = new QCardLayoutWidget();
        pTabWidget->addTab(pCardLayoutWidget1,"手动布局");
    }

    ///
    ///QBoxLayout、QHBoxLayout、QVBoxLayout 水平/垂直布局
    ///
    {
        QVBoxLayout *pLayout = new QVBoxLayout();
        {
            QHBoxLayout *pLayout1 = new QHBoxLayout();
            pLayout1->addWidget(new QPushButton("button1"));
            pLayout1->addWidget(new QPushButton("button2"));
            pLayout1->addWidget(new QPushButton("button3"));
            pLayout1->addWidget(new QPushButton("button4"));
            pLayout1->addWidget(new QPushButton("button5"));
            pLayout->addLayout(pLayout1);
        }
        {//设置边距
            QHBoxLayout *pLayout1 = new QHBoxLayout();
            pLayout1->setContentsMargins(10,10,10,10);
            //pLayout1->setMargin();
            pLayout1->addWidget(new QPushButton("button1"));
            pLayout1->addWidget(new QPushButton("button2"));
            pLayout1->addWidget(new QPushButton("button3"));
            pLayout1->addWidget(new QPushButton("button4"));
            pLayout1->addWidget(new QPushButton("button5"));
            pLayout->addLayout(pLayout1);
        }
        {//设置间距
            QHBoxLayout *pLayout1 = new QHBoxLayout();
            pLayout1->setContentsMargins(10,10,10,10);
            pLayout1->setSpacing(20);
            //pLayout1->setMargin();
            pLayout1->addWidget(new QPushButton("button1"));
            pLayout1->addWidget(new QPushButton("button2"));
            pLayout1->addWidget(new QPushButton("button3"));
            pLayout1->addWidget(new QPushButton("button4"));
            pLayout1->addWidget(new QPushButton("button5"));
            pLayout->addLayout(pLayout1);
        }
        {//居右
            QHBoxLayout *pLayout1 = new QHBoxLayout();
            pLayout1->setSpacing(20);
            pLayout1->addStretch();
            pLayout1->addWidget(new QPushButton("button1"));
            pLayout1->addWidget(new QPushButton("button2"));
            pLayout1->addWidget(new QPushButton("button3"));
            pLayout1->addWidget(new QPushButton("button4"));
            pLayout1->addWidget(new QPushButton("button5"));
            pLayout->addLayout(pLayout1);
        }
        {//居左
            QHBoxLayout *pLayout1 = new QHBoxLayout();
            pLayout1->setSpacing(20);
            pLayout1->addWidget(new QPushButton("button1"));
            pLayout1->addWidget(new QPushButton("button2"));
            pLayout1->addWidget(new QPushButton("button3"));
            pLayout1->addWidget(new QPushButton("button4"));
            pLayout1->addWidget(new QPushButton("button5"));
            pLayout1->addStretch();
            pLayout->addLayout(pLayout1);
        }
        {//居中
            QHBoxLayout *pLayout1 = new QHBoxLayout();
            pLayout1->setSpacing(20);
            pLayout1->addStretch();
            pLayout1->addWidget(new QPushButton("button1"));
            pLayout1->addWidget(new QPushButton("button2"));
            pLayout1->addWidget(new QPushButton("button3"));
            pLayout1->addWidget(new QPushButton("button4"));
            pLayout1->addWidget(new QPushButton("button5"));
            pLayout1->addStretch();
            pLayout->addLayout(pLayout1);
        }
        {//匀分
            QHBoxLayout *pLayout1 = new QHBoxLayout();
            pLayout1->setSpacing(20);
            pLayout1->addStretch();
            pLayout1->addWidget(new QPushButton("button1"));
            pLayout1->addStretch();
            pLayout1->addWidget(new QPushButton("button2"));
            pLayout1->addStretch();
            pLayout1->addWidget(new QPushButton("button3"));
            pLayout1->addStretch();
            pLayout1->addWidget(new QPushButton("button4"));
            pLayout1->addStretch();
            pLayout1->addWidget(new QPushButton("button5"));
            pLayout1->addStretch();
            pLayout->addLayout(pLayout1);
        }
        {//设置对齐方式
            QHBoxLayout *pLayout1 = new QHBoxLayout();
            pLayout1->setSpacing(20);
            pLayout1->addStretch();
            pLayout1->addWidget(new QPushButton("button1"),0,Qt::AlignLeft|Qt::AlignTop);
            pLayout1->addWidget(new QPushButton("button2"),0,Qt::AlignLeft|Qt::AlignTop);
            pLayout1->addWidget(new QPushButton("button3"));
            pLayout1->addWidget(new QPushButton("button4"),0,Qt::AlignBottom|Qt::AlignRight);
            pLayout1->addWidget(new QPushButton("button5"),0,Qt::AlignBottom|Qt::AlignRight);
            pLayout1->addStretch();
        }
        {//设置拉伸
            QHBoxLayout *pLayout1 = new QHBoxLayout();
            pLayout1->setSpacing(20);
            pLayout1->addStretch();
            QPushButton *pButton1 = new QPushButton("button1");
            QPushButton *pButton2 = new QPushButton("button2");

            pLayout1->addWidget(pButton1);
            pLayout1->addWidget(pButton2);
            pLayout1->addWidget(new QPushButton("button3"));
            pLayout1->addWidget(new QPushButton("button4"));
            pLayout1->addWidget(new QPushButton("button5"));
            pLayout1->addStretch();
            pLayout1->setStretchFactor(pButton1,1);
            pLayout1->setStretchFactor(pButton2,2);
        }

        QWidget *pBoxLayoutWidget = new QWidget();
        pBoxLayoutWidget->setLayout(pLayout);
        pTabWidget->addTab(pBoxLayoutWidget,"水平/垂直布局");
    }

    ///
    ///QGridLayout 栅栏布局 仿QQ登录页面
    ///
    {
        //创建控件 头像、用户名、密码框、登录按钮等
        QLabel *pImageLabel = new QLabel();
        QLineEdit *pUserLineEdit = new QLineEdit();
        QLineEdit *pPasswordLineEdit = new QLineEdit();
        QCheckBox *pRememberCheckBox = new QCheckBox();
        QCheckBox *pAutoLoginCheckBox = new QCheckBox();
        QPushButton *pLoginButton = new QPushButton();
        QPushButton *pRegisterButton = new QPushButton();
        QPushButton *pForgotButton = new QPushButton();

        pUserLineEdit->setFixedWidth(200);
        pLoginButton->setFixedHeight(30);

        //设置头像
        QPixmap pixmap(":/Images/5");
        pImageLabel->setFixedSize(90,90);
        pImageLabel->setPixmap(pixmap);
        pImageLabel->setScaledContents(true);

        //设置文本
        pUserLineEdit->setPlaceholderText(QStringLiteral("QQ帐号/手机号/邮箱"));
        pPasswordLineEdit->setPlaceholderText(QStringLiteral("密码"));
        pPasswordLineEdit->setEchoMode(QLineEdit::Password);
        pRememberCheckBox->setText(QStringLiteral("记住密码"));
        pAutoLoginCheckBox->setText(QStringLiteral("自动登录"));
        pLoginButton->setText(QStringLiteral("登录"));
        pRegisterButton->setText(QStringLiteral("注册帐号"));
        pForgotButton->setText(QStringLiteral("找回密码"));

        QGridLayout *pLayout = new QGridLayout();

        pLayout->addWidget(pImageLabel,0,0,3,1);
        pLayout->addWidget(pUserLineEdit,0,1,1,2);
        pLayout->addWidget(pRegisterButton,0,4);
        pLayout->addWidget(pPasswordLineEdit,1,1,1,2);
        pLayout->addWidget(pForgotButton,1,4);
        pLayout->addWidget(pRememberCheckBox,2,1,1,1,Qt::AlignLeft|Qt::AlignCenter);
        pLayout->addWidget(pAutoLoginCheckBox,2,2,1,1,Qt::AlignLeft|Qt::AlignCenter);
        pLayout->addWidget(pLoginButton,3,1,1,2);
        pLayout->setHorizontalSpacing(30);
        pLayout->setVerticalSpacing(30);
        pLayout->setContentsMargins(30,30,30,30);

        QWidget *pWidget = new QWidget();
        pWidget->setLayout(pLayout);
        pTabWidget->addTab(pWidget,"QGridLayout栅栏布局");
        pTabWidget->setCurrentWidget(pWidget);

    }

    ///
    ///QFromLayout 表单布局
    ///
    {
        QFormLayout *pLayout = new QFormLayout();

        QLineEdit *pUserLineEdit = new QLineEdit();
        pUserLineEdit->setPlaceholderText(QStringLiteral("用户名"));
        QLineEdit *pPasswordLineEdit = new QLineEdit();
        pPasswordLineEdit->setPlaceholderText(QStringLiteral("密码"));
        QLineEdit *pVerifyLineEdit = new QLineEdit();
        pVerifyLineEdit->setPlaceholderText(QStringLiteral("验证码"));

        pLayout->addRow(new QLabel("用户名:"),pUserLineEdit);
        pLayout->addRow(new QLabel("密码:"),pPasswordLineEdit);
        pLayout->addRow(new QLabel("验证码:"),pVerifyLineEdit);
        pLayout->setSpacing(20);
        pLayout->setContentsMargins(20,20,20,20);
        //pLayout->setRowWrapPolicy(QFormLayout::WrapAllRows); //上下排序
        pLayout->setRowWrapPolicy(QFormLayout::DontWrapRows); //前后结构


        QWidget *pWidget = new QWidget();
        pWidget->setLayout(pLayout);
        pTabWidget->addTab(pWidget,"表单布局(QFormLayout)");
    }

    //
    //QStackedLayout 页面切换布局
    //
    {
        QStackedLayout *pStackedLayout = new QStackedLayout();
        pStackedLayout->addWidget(new QLabel("页面1"));
        pStackedLayout->addWidget(new QLabel("页面2"));
        pStackedLayout->addWidget(new QLabel("页面3"));


        QPushButton *pButton = new QPushButton();
        pButton->setText(QStringLiteral("切换页面"));
        connect(pButton,static_cast<void (QPushButton::*)(bool checked)> (&QPushButton::clicked),
                [=](){
            int nIndex = pStackedLayout->currentIndex();
            ++nIndex;
            if (nIndex >= pStackedLayout->count()){
                nIndex = 0;
            }
            pStackedLayout->setCurrentIndex(nIndex);
        });

        QHBoxLayout *pLayout = new QHBoxLayout();
        pLayout->addWidget(pButton);
        pLayout->addLayout(pStackedLayout);

        QWidget *pWidget = new QWidget();
        pWidget->setLayout(pLayout);
        pTabWidget->addTab(pWidget,"切换布局QStackedLayout");
    }

    ///
    ///QSpacerItem 布局空白区域
    ///
    {
        QHBoxLayout *pLayout = new QHBoxLayout();
        pLayout->addWidget(new QPushButton("button1"));
        pLayout->addSpacing(10);
        pLayout->addWidget(new QPushButton("button2"));
        pLayout->addSpacing(20);
        pLayout->addWidget(new QPushButton("button3"));
        pLayout->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding));//宽度尽可能是缩小放大
        pLayout->addWidget(new QPushButton("button4"));
        pLayout->addSpacerItem(new QSpacerItem(30,30));
        pLayout->addWidget(new QPushButton("button5"));
        pLayout->setSpacing(0);
        pLayout->setMargin(0);

        QWidget *pWidget = new QWidget();
        pWidget->setLayout(pLayout);
        pTabWidget->addTab(pWidget,"布局空白区域");
    }
    ///
    ///监控文件和目录的修改 QFileSystemWatcher
    ///
    FileSystemWatcher::addWatchPath(QString("D:\\QTprojects"));

    ///
    ///QTimer
    ///
    {
        m_pProgressBar = new QProgressBar();
        m_pProgressBar->setRange(0,100);
        m_pProgressBar->setValue(30);

        QPushButton *pStartButton = new QPushButton();
        pStartButton->setText(QStringLiteral("开始"));

        QPushButton *pStopButton = new QPushButton();
        pStopButton->setText(QStringLiteral("停止"));

        m_pTimer = new QTimer();
        m_pTimer->setInterval(1000);

        QVBoxLayout *pLayout = new QVBoxLayout();
        pLayout->addStretch();
        pLayout->addWidget(m_pProgressBar);
        pLayout->addWidget(pStartButton);
        pLayout->addWidget(pStopButton);
        pLayout->addStretch();

        connect(pStartButton,SIGNAL(clicked()),m_pTimer,SLOT(start()));
        connect(pStopButton,SIGNAL(clicked()),m_pTimer,SLOT(stop()));
        connect(m_pTimer,SIGNAL(timeout()),this,SLOT(updateProgress()));

        QWidget *pWidget = new QWidget();
        pWidget->setLayout(pLayout);

        pTabWidget->addTab(pWidget,"QTimer定时器");
    }

    ///
    /// QFileIconProvider提供文件图标
    ///
    {
        QListWidget *pWidget = new QListWidget();
        pWidget->setIconSize(QSize(48,48));
        pWidget->setResizeMode(QListView::Adjust);//设置大小可调节
        pWidget->setMovement(QListView::Static);//设置不可拖拽
        pWidget->setSpacing(10);
        pWidget->setViewMode(QListView::IconMode);
        for(int i = 0; i <= 6; i++){
            QFileIconProvider provider;
            QIcon icon = provider.icon((QFileIconProvider::IconType)i);

            QListWidgetItem *pItem = new QListWidgetItem();
            pItem->setIcon(icon);
            pWidget->addItem(pItem);
        }
        pTabWidget->addTab(pWidget,"QFileIconProvider提供文件图标");
    }

    ///
    ///paint 基本绘制
    ///
    {
        pTabWidget->addTab(new PaintFoutWidget(),"paint基本绘制");
    }

    ///
    /// 主窗口添加tab视图
    ///

    pTabWidget->setCurrentIndex( pTabWidget->count()-1);
    mainLayout->addWidget(pTabWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10,10,10,10);
    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onSearch(bool){

    pSearchLabel->setText(QString("要搜索的内容是:%1").arg(pSearchEdit->text()));
}

void MainWindow::onActivated(QSystemTrayIcon::ActivationReason reason){
    switch(reason){
        case QSystemTrayIcon::Trigger:{
        showNormal();
        raise();
        activateWindow();
        break;
        }
    default :

        break;
   }
}

void MainWindow::onShowWindow(){
    showNormal();
    raise();
    activateWindow();
}

QLabel* MainWindow::CreateLabel(const QString &text){
    QLabel *pLabel = new QLabel(this);
    pLabel->setText(text);
    pLabel->setFrameStyle(QFrame::Box|QFrame::Raised);
    return pLabel;
}

void MainWindow::updateProgress(){
    int nStep = m_pProgressBar->value();
    nStep++;
    if (nStep >= 100){
        m_pTimer->stop();
    }
    m_pProgressBar->setValue(nStep);
}
