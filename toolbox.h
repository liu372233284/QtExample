#ifndef TOOLBOX_H
#define TOOLBOX_H
#include <QToolBox>
#include <QString>
#include <QStringList>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QDebug>
class QWidget;

class ToolBox : public QToolBox
{
    Q_OBJECT
public:
    ToolBox(QWidget *parent = 0 ):QToolBox(parent){
        initUI();
        connect(this,SIGNAL(currentChanged(int)),this,SLOT(onCurrentChanged(int)));
    }


private slots:
     void onCurrentChanged(int index){
       QString text =  itemText(index);
       qDebug()<<text;
     }

private:
    void initUI(){
        struct User{
            bool isVip;//是否VIP
            QString strName;
            QString strIcon;
            QString strDesc;
        }user[3][5]=
        {
            {
                {true, QStringLiteral("香香公主"), ":/Images/1", QStringLiteral("金庸笔下的第一美女")},
                {true, QStringLiteral("小龙女"), ":/Images/2", QStringLiteral("玉女心经")},
                {true, QStringLiteral("王语嫣"), ":/Images/3", QStringLiteral("熟读各派武学秘笈")},
                {false, QStringLiteral("赵敏"), ":/Images/4", QStringLiteral("大元第一美人")},
                {false, QStringLiteral("周芷若"), ":/Images/5", QStringLiteral("光复汉家河山，光大峨嵋")}
            },
            {
                {true, QStringLiteral("萧峰"), ":/Images/6", QStringLiteral("丐帮帮主 - 智勇双全、胆略过人、豪迈飒爽")},
                {true, QStringLiteral("令狐冲"), ":/Images/8", QStringLiteral("独孤九剑")},
                {true, QStringLiteral("杨过"), ":/Images/9", QStringLiteral("黯然销魂掌")},
                {false, QStringLiteral("郭靖"), ":/Images/7", QStringLiteral("降龙十八掌")},
                {false, QStringLiteral("胡一刀"), ":/Images/10", QStringLiteral("辽东大侠")}
            },
            {
                {true, QStringLiteral("金轮法王"), ":/Images/11", QStringLiteral("龙象般若功")},
                {true, QStringLiteral("丁春秋"), ":/Images/13", QStringLiteral("星宿老仙，法力无边")},
                {false, QStringLiteral("裘千仞"), ":/Images/12", QStringLiteral("铁掌水上飘")},
                {false, QStringLiteral("成昆"), ":/Images/14", QStringLiteral("混元霹雳手")},
                {false, QStringLiteral("李莫愁"), ":/Images/15", QStringLiteral("冰魄银针，杀人如麻")}
            }
        };

        QStringList groupList ;
        groupList<<"大美女"<<"大英雄"<<"大恶人";

        for(int i = 0;i < sizeof(user)/sizeof(user[0]); i++)
        {
            QGroupBox *groupBox = new QGroupBox(this);
            QVBoxLayout *layout = new QVBoxLayout(groupBox);

            for(int j = 0;j < sizeof(user[0])/sizeof(user[i][0]);++j){
                QWidget *item = initWidget(user[i][j].isVip,user[i][j].strName,user[i][j].strIcon,user[i][j].strDesc);
                layout->addWidget(item);
            }
            layout->addStretch();
            layout->setSpacing(10);
            layout->setContentsMargins(10,10,10,10);

            addItem(groupBox,groupList.at(i));
        }
    }
    QWidget* initWidget(bool isVip,const QString &strName,const QString &strIcon,const QString &strDesc=""){
        QWidget *pWidget = new QWidget(this);
        QLabel *pNameLabel = new QLabel(this);
        QLabel *pDescLabel = new QLabel(this);
        QLabel *pPixMapLabel = new QLabel(this);

        QPixmap pixmap(strIcon);
        pixmap.scaled(30,30,Qt::KeepAspectRatio);
        pPixMapLabel->setPixmap(pixmap);
        pNameLabel->setText(strName);
        pDescLabel->setText(strDesc);
        pPixMapLabel->resize(30,30);



        pNameLabel->setStyleSheet(QString("color:%1;").arg(isVip?"rgb(240,30,40)":"green"));
        pDescLabel->setStyleSheet("color:dark;");

        QVBoxLayout *vlayout = new QVBoxLayout();
        vlayout->addStretch();
        vlayout->addWidget(pNameLabel);
        vlayout->addWidget(pDescLabel);
        vlayout->addStretch();
        vlayout->setSpacing(5);
        vlayout->setContentsMargins(0,0,0,0);

        QHBoxLayout *hlayout = new QHBoxLayout();
        hlayout->addWidget(pPixMapLabel);
        hlayout->addLayout(vlayout);
        hlayout->addStretch();
        hlayout->setContentsMargins(0,0,0,0);

        pWidget->setLayout(hlayout);
        return pWidget;
    }
};


#endif // TOOLBOX_H
