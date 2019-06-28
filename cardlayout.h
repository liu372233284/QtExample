#ifndef CARDLAYOUT_H
#define CARDLAYOUT_H

#include <QWidget>
#include <QLayout>
#include <QLayoutItem>

class CardLayout : public QLayout
{
public:
    CardLayout(QWidget *parent = 0);
    ~CardLayout();

    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);
    void setGeometry(const QRect &rect);

    private:
        QList<QLayoutItem*> list;
};

#endif // CARDLAYOUT_H
