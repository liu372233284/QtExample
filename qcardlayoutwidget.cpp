#include "qcardlayoutwidget.h"

QCardLayoutWidget::QCardLayoutWidget()
{
    m_pButton = new QPushButton(this);
    m_pButton->setText("确定");

    m_pLabel = new QLabel(this);
    m_pLabel->setText("某");

    m_pTextBrowser = new QTextBrowser(this);
    m_pTextBrowser->setPlainText("夫苟其挫而不退矣，则小逆之后必有小顺，大逆之后必有大顺。盘根错节之既破，而遂有应刃而解之一日。");
}

QCardLayoutWidget::~QCardLayoutWidget()
{

}

void QCardLayoutWidget::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);

    int nSpacing = 10;
    int nTopMargin = 10;
    int nLeftMargin = 10;
    int nRightMargin = 10;
    int nBottomMargin = 10;

    //
    m_pLabel->setGeometry(QRect(nLeftMargin,nTopMargin,width()-nLeftMargin-nRightMargin,20));

    m_pButton->setFixedSize(75,25);
    m_pButton->move(width()- m_pButton->width()-nRightMargin,height()-nBottomMargin-m_pButton->height());

    m_pTextBrowser->setGeometry(QRect(this->geometry().x()+nLeftMargin,
                                      this->geometry().y()+nTopMargin+m_pLabel->geometry().height()+nSpacing,
                                      width()-nLeftMargin-nRightMargin,
                                      height()-nTopMargin-m_pLabel->height()-2*nSpacing-m_pButton->height()-nBottomMargin));
}
