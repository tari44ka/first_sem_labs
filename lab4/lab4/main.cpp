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

bool checkFileName(QString str)
{
    //gif jpeg jpg png
    QString name("[^\\/]{1,255}");
    QString ext("(gif|jpeg|jpg|png)");
    QString rule = name + "\\." + ext;
    QRegExp fileNameRe(rule, Qt::CaseInsensitive);
    return fileNameRe.exactMatch(str);
}

void printHtmlTags(QString str)
{
    QRegExp tagRe("<([^>]+)>");
    int lastPos = 0;
    while( ( lastPos = tagRe.indexIn(str, lastPos ) ) != -1 ) {
           qDebug() << lastPos <<  ":" << tagRe.cap( 1 );
           lastPos += tagRe.matchedLength();
    }
}

void printLinks(QString str)
{
    //<a href="URL" title = "не обязательная подсказка">текст ссылки</a>

    QRegExp linkRe("<a(.)* href=\"([^\"]+)\"(.)*>((.)+)</a>");
    QRegExp titleRe("title=\"([^\"]+)\"");
    int lastPos = 0;
    while( ( lastPos = linkRe.indexIn(str, lastPos ) ) != -1 ) {
        QString wholeLink = linkRe.cap(0);
        QString href = linkRe.cap(2);
        QString text = linkRe.cap(4);

        qDebug() << "whole link" << wholeLink;
        qDebug() << "href" << href;

        int titlePos = titleRe.indexIn(str, lastPos);
        if ((titlePos > lastPos) && (titlePos < linkRe.matchedLength()))
        {
            qDebug() << "title" << titleRe.cap(1);
        }
        qDebug() << "text" << text;

        lastPos += linkRe.matchedLength();
    }

}

void changeWords(QString str, QString word1, QString word2)
{
    QRegExp changeRe(word1 +  "(.*)" + word2);
    changeRe.setMinimal(true);
    int lastPos = 0;
    while ((lastPos = changeRe.indexIn(str, lastPos)) != -1)
    {
        qDebug() << changeRe.cap(0);

        QString word = changeRe.cap(1);
        str.replace(lastPos, changeRe.matchedLength(), word2 + word + word1);
        lastPos += changeRe.matchedLength();
    }
    qDebug() << str;
}


void checkDateQuery()
{
    while(true)
    {
        QString string;
        qDebug() << "Please, enter date (if you want exit - enter \'stop\')";
        string = cin.readLine();
        if (0 == string.compare("stop"))
        {
            break;
        }
        if (checkDate(string))
        {
            qDebug() << "this is correct date";
        }
        else
        {
            qDebug() << "this is NOT correct date";
        }
    }
}

void checkDateTimeQuery()
{
    while(true)
    {
        QString string;
        qDebug() << "Please, enter date with or without time (if you want exit - enter \'stop\')";
        string = cin.readLine();
        if (0 == string.compare("stop"))
        {
            break;
        }
        if (checkDateTime(string))
        {
            qDebug() << "this is correct date (with time)";
        }
        else
        {
            qDebug() << "thie is NOT correct date (with time)";
        }
    }
}

void checkEmailQuery()
{
    while(true)
    {
        QString string;
        qDebug() << "Please, enter e-mail (if you want exit - enter \'stop\')";
        string = cin.readLine();
        if (0 == string.compare("stop"))
        {
            break;
        }
        if (checkEmail(string))
        {
            qDebug() << "this is correct e-mail";
        }
        else
        {
            qDebug() << "this is NOT correct e-mail";
        }
    }
}

void checkFileNameQeury()
{
    while(true)
    {
        QString string;
        qDebug() << "Please, enter file name (if you want exit - enter \'stop\')";
        string = cin.readLine();
        if (0 == string.compare("stop"))
        {
            break;
        }
        if (checkFileName(string))
        {
            qDebug() << "this is correct graphic file name";
        }
        else
        {
            qDebug() << "this is NOT correct graphic file name";
        }
    }
}

void findTagsQuery()
{
    while(true)
    {
        QString string;
        qDebug() << "Please, enter html-text (if you want exit - enter \'stop\')";
        string = cin.readLine();
        if (0 == string.compare("stop"))
        {
            break;
        }
        qDebug() << "tags are:";
        printHtmlTags(string);
    }
}

void findLinksQuery()
{
    while(true)
    {
        QString string;
        qDebug() << "Please, enter html-text (if you want exit - enter \'stop\')";
        string = cin.readLine();
        if (0 == string.compare("stop"))
        {
            break;
        }
        qDebug() << "links are: ";
        printLinks(string);
    }
}

void changeWordsQuery()
{
    while(true)
    {
        QString string;
        qDebug() << "Please, enter your string (if you want exit - enter \'stop\')";
        string = cin.readLine();
        if (0 == string.compare("stop"))
        {
            break;
        }
        qDebug() << "Please, enter first word (it must be in the text first)";
        QString word1 = cin.readLine();
        qDebug() << "Please, enter second word (it must be in the text after first word)";
        QString word2 = cin.readLine();
        changeWords(string, word1, word2);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString query;
    qDebug() << "Hello!";
    do
    {
        qDebug() << "Please, choose number of query from list:";
        qDebug() << "1 - check, that your string is a date like d(d).m(m).yyyy";
        qDebug() << "2 - check, thah your string is a date and may be time HH:mm:ss";
        qDebug() << "3 - check, that your string is e-mail";
        qDebug() << "4 - check, that your string is a graphical file with ext png, jpg, gif or jpeg";
        qDebug() << "5 - find all tags in your html";
        qDebug() << "6 - find all links in your html and find href, title and text in them";
        qDebug() << "7 - change two words in your string";
        qDebug() << "if you want to exit - print \'stop\'";

        query = cin.readLine();
        if (0 == query.compare("1"))
        {
            checkDateQuery();
        }else if (0 == query.compare("2"))
        {
            checkDateTimeQuery();
        }
        else if (0 == query.compare("3"))
        {
            checkEmailQuery();
        }
        else if (0 == query.compare("4"))
        {
            checkFileNameQeury();
        }
        else if (0 == query.compare("5"))
        {
            findTagsQuery();
        }
        else if (0 == query.compare("6"))
        {
            findLinksQuery();
        }
        else if (0 == query.compare("7"))
        {
            changeWordsQuery();
        }
    }while (query.compare("stop") != 0);

    return 0;
}

