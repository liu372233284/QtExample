#include "cardlayout.h"

CardLayout::CardLayout(QWidget *parent ):QLayout(parent)
{

}

CardLayout::~CardLayout()
{
    QLayoutItem *item;
    while((item = takeAt(0))){
        delete item;
    }
}

int CardLayout::count()const{
    return list.size();
}

QLayoutItem* CardLayout::itemAt(int idx) const{
    return list.value(idx);
}

QLayoutItem*  CardLayout::takeAt(int idx){
    return idx >= 0 &&idx < list.size()?list.takeAt(idx):0;
}

void CardLayout::addItem(QLayoutItem *item){
    list.append(item);
}

void CardLayout::setGeometry(const QRect &rect){
    QLayout::setGeometry(rect);

    if (list.size() == 0 ){
        return;
    }
    int w = rect.width() - (list.count()-1)*spacing();
    int h = rect.height()- (list.count()-1)*spacing();
    int i = 0;

    while(i < list.count()){
        QLayoutItem *item = list.at(i);
        QRect r(rect.x()+i*spacing(),rect.y()+i*spacing(),w,h);
        item->setGeometry(r);
        ++i;
    }
}

QSize CardLayout::sizeHint()const{
    int n = list.count();
    QSize s(0,0);
    if (n > 0){
        s = QSize(100,70);
    }
    int i = 0 ;
    while(i < n){
        QLayoutItem *o = itemAt(i);
        s = s.expandedTo(o->sizeHint());
        i++;
    }
    return s+n*QSize(spacing(),spacing());
}

QSize CardLayout::minimumSize()const{
    int n = list.count();
    QSize s(0,0);

    int i = 0 ;
    while(i < n){
        QLayoutItem *o = itemAt(i);
        s = s.expandedTo(o->sizeHint());
        i++;
    }
    return s+n*QSize(spacing(),spacing());
}
