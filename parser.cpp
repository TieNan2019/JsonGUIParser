#include "parser.h"
#include "ui_parser.h"




QString Parser::FileRead(const QString& path) {
#ifdef __DEBUG__
        qDebug() << "Json Path : " << path;
#endif

        QFile jsonFile(path);
        if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
                return "";

        QString jsonStr;
        QTextStream in(&jsonFile);
        while (!in.atEnd()) {
            jsonStr += in.readLine();
        }

#ifdef __DEBUG__
        qDebug() << "Text Read : " << jsonStr;
#endif

        return jsonStr;
}


QJsonObject Parser::JsonParse(const QString& jsonStr) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toLocal8Bit().data());
        QJsonObject jsonObject = jsonDoc.object();

#ifdef __DEBUG__
        for (auto it = jsonObject.begin(); it != jsonObject.end(); it++) {
                qDebug() << it.key() << " : " << it.value();
        }
#endif

        return jsonObject;
}


Parser::Parser(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::Parser)
{
        QString jsonStr = FileRead(INSTANCE_PATH);

        this->jsonObj = JsonParse(jsonStr);

        qDebug() << this->jsonObj["type"];


        ui->setupUi(this);
}

Parser::~Parser()
{
        delete ui;
}

