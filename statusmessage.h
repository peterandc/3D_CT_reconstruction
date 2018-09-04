#ifndef STATUSMESSAGE_H
#define STATUSMESSAGE_H
#include <sstream>
#include <QDebug>

class StatusMessage
{
public:
    StatusMessage();
    static QString Format(int slice, int maxSLice)
    {
        //std::stringstream tmp;
         QString str =  "Slice Number  "+ QString::number(slice + 1 , 10) + "/" + QString::number(maxSLice + 1, 10);
        qDebug()<<slice<<" "<<maxSLice<<endl;
        return str;
    }

};

#endif // STATUSMESSAGE_H
