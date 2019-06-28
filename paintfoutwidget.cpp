#include "paintfoutwidget.h"
#include<QPainter>

PaintFoutWidget::PaintFoutWidget(QWidget *parent) : QWidget(parent)
{

}

PaintFoutWidget::~PaintFoutWidget()
{

}

void PaintFoutWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setPen(QColor(Qt::green));

    QFont font;
    font.setItalic(true);
    font.setFamily("Microsoft YaHei");
    font.setPointSize(50);
    painter.setFont(font);

    painter.drawText(this->rect(),Qt::AlignCenter,"QT5.9");
}
