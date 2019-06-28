#ifndef TRAYMENU_H
#define TRAYMENU_H

#include <QObject>
#include <QWidget>
#include <QMenu>

class TrayMenu : public QMenu
{
    Q_OBJECT
public:
    TrayMenu(QWidget *parent = 0 ):QMenu(parent){
        initActions();
    }
private:
    QAction *pShowAction;
    QAction *pSettingAction;
    QAction *pHomePageAction;
    QAction *pHelpAction;
    QAction *pAboutAction;
    QAction *pUpgradeAction;
    QAction *pQuitAction;
public:
    void initActions(){
        pShowAction = new QAction(QIcon(":/Images/1"),"显示",this);
        pSettingAction = new QAction(QIcon(":/Images/2"),"设置",this);
        pHomePageAction = new QAction(QIcon(":/Images/3"),"显示首页",this);
        pHelpAction = new QAction(QIcon(":/Images/4"),"帮助信息",this);
        pAboutAction = new QAction(QIcon(":/Images/5"),"关于",this);
        pUpgradeAction = new QAction(QIcon(":/Images/6"),"更新",this);
        pQuitAction = new QAction(QIcon(":/Images/7"),"退出",this);

       addAction(pShowAction);
       addAction(pSettingAction);
       addAction(pHomePageAction);
       addSeparator();
       addAction(pHelpAction);
       addAction(pAboutAction);
       addAction(pUpgradeAction);
       addSeparator();
       addAction(pQuitAction);

       connect(pShowAction,SIGNAL(triggered(bool)),this,SIGNAL(showWindow()));
    }
signals:
    void showWindow();
};

#endif // TRAYMENU_H
