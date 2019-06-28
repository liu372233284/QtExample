#ifndef PAINTFOUTWIDGET_H
#define PAINTFOUTWIDGET_H
#include <QWidget>

class PaintFoutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintFoutWidget(QWidget *parent = 0);
    ~PaintFoutWidget();
private:
   void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // PAINTFOUTWIDGET_H
