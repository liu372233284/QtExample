#ifndef ICONSIZESPINBOX_H
#define ICONSIZESPINBOX_H
#include "QWidget"
#include <QSpinBox>
#include <QRegExp>
class IconSizeSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    IconSizeSpinBox(QWidget *parent = 0):QSpinBox(parent){}


protected:
    QString textFromValue(int val) const{
        return QString("%1 x %1").arg(val);
    }

    int valueFromText(const QString &text) const{
        QRegExp regExp("(\\d+)(\\s*[xx]\\s*\\d+)?");
        if (regExp.exactMatch(text)){
            return regExp.cap(1).toInt();
        }else{
            return 0;
        }
    }
};

#endif // ICONSIZESPINBOX_H
