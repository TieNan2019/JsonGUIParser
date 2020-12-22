#ifndef PARSER_H
#define PARSER_H

#include <QWidget>

#include <QFile>

#include <QJsonObject>
#include <QJsonDocument>




#include <QDebug>

#define __DEBUG__


#define INSTANCE_PATH   "/home/whoami/workspace/MIoT/lab/massager.json"


QT_BEGIN_NAMESPACE
namespace Ui { class Parser; }
QT_END_NAMESPACE

class Parser : public QWidget
{
        Q_OBJECT

public:
        Parser(QWidget *parent = nullptr);
        ~Parser();

private:
        QJsonObject jsonObj;

        QString FileRead(const QString&);
        QJsonObject JsonParse(const QString&);

        Ui::Parser *ui;
};
#endif // PARSER_H
