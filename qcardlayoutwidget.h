#ifndef QCARDLAYOUTWIDGET_H
#define QCARDLAYOUTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QPushButton>

class QCardLayoutWidget:public QWidget
{
    Q_OBJECT
public:

     QCardLayoutWidget();
    ~QCardLayoutWidget();
private:
    QLabel *m_pLabel;
    QPushButton *m_pButton;
    QTextBrowser *m_pTextBrowser;

    void resizeEvent(QResizeEvent *event);
};

#endif // QCARDLAYOUTWIDGET_H
