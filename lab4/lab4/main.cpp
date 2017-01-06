/*
Реализовать следующие регулярные выражения (совпадает строка) :
1. Дата вида 3.11.2016 (1-2.1-2.4)
2. Дата + время (со временем или нет)
3. e-mail
4. имя графического файла gif jpeg jpg png (+ разный регистр)
Выделить из строки
5. html – теги открывающиеся и закрывающиеся
6. список всех ссылок и выделить в ней href, title и текст (делается группами () )
7. поменять два слова с местами
*/

#include <QCoreApplication>
#include <QRegExp>
#include <QStringList>
#include <QDebug>
#include <QString>
#include <QTextStream>
QTextStream cin(stdin);

QString getCheckDataRule()
{
    QString ruleForAll("([0-9]|[1-2][0-8])\\.([1-9]|(1[0-2]))\\.[1-2][0-9]{3}");
    QString ruleFor30("(29|30)\\.([0-1]|[3-9]|(1[0-2]))\\.[1-2][0-9]{3}");
    QString ruleFor31("31\\.(1|3|5|7|8|10|12)\\.[1-2][0-9]{3}");

    QString ruleFor29_02("29\\.2\\.([1-2][0-9](([2468]0)|([02468][48])|([13579][26]))|(1200)|(1600)|(2000)|(2400)|(2800))");

    QString rule = "(" + ruleForAll + ")|(" + ruleFor30 + ")|(" + ruleFor31 + ")|(" + ruleFor29_02 + ")";
    return rule;
}

bool checkDate(QString str)
{
    QRegExp dateRe(getCheckDataRule());
    return dateRe.exactMatch(str);
}

QString getCheckTimeRule()
{
    //"HH:mm::ss"
    return "(([01][0-9])|(2[0-3])):[0-5][0-9]:[0-5][0-9]";
}
bool checkDateTime(QString str)
{
    QString rule = "(" + getCheckDataRule() + ")( +"  + getCheckTimeRule() + ")?";
    QRegExp dateTimeRe(rule);
    return dateTimeRe.exactMatch(str);
}

bool checkEmail(QString str)
{
    QString login ("[A-Za-z]([-+_\\.]?[A-Za-z0-9]){,255}");
    QString domain("[A-Za-z0-9](-?[A-Za-z0-9]){1,62}(.[A-Za-z0-9](-?[A-Za-z0-9]){1,62}){,2}");
    QString rule = login + "@" + domain;
    QRegExp emailRe(rule);
    return emailRe.exactMatch(str);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString inputString = "my string";
    while (!inputString.startsWith("stop"))
    {
        qDebug() << "input your string: ";
        inputString = cin.readLine();
        qDebug() << checkEmail(inputString);
    }
    return 0;
}

