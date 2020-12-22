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





QJsonObject *Parser::JsonLoader(const QString &path) {
        QString jsonStr = FileRead(path);

        this->jsonObj = new QJsonObject(JsonParse(jsonStr));

#ifdef  __DEBUG__
        qDebug() << this->jsonObj->take("type");
#endif

        return this->jsonObj;
}





void Parser::InitWidget() {
        this->setWindowTitle(this->jsonObj->value("type").toString());

#ifdef __DEBUG__
        qDebug() << "Title to : " << this->jsonObj->value("type").toString();
#endif

        return ;
}




QComboBox *Parser::ServLoader() {
        /* use smart pointer to do a judgement before alloack */
        // if (!this->comboBoxServ)
        //         qDebug() << "NULL";

        this->comboBoxServ = new QComboBox(this);

        QJsonArray services = this->jsonObj->value("services").toArray();

//        for (auto service : services) {
        for (int i = 0; i < services.size(); i++) {

                QJsonObject item = services[i].toObject();
#ifdef __DEBUG__
                qDebug() << item["description"].toString()
                << " : " << item["properties"];
#endif

                comboBoxServ->addItem(QString::number(i) + " "
                + item["description"].toString());
        }

//        comboBoxServ->setCurrentIndex(0);

        return this->comboBoxServ;
}




QComboBox *Parser::PropLoader() {
        /* use smart pointer to do a judgement before alloack */
        // if (!this->comboBoxServ)
        //         qDebug() << "NULL";

        this->comboBoxProp = new QComboBox(this);
        this->comboBoxProp->move(200, 0);

        QString service = this->comboBoxServ->currentText();

        QJsonArray services = this->jsonObj->value("services").toArray();
//        services


        return this->comboBoxProp;
}


int Parser::BoxReloader() {

        this->comboBoxServ = ServLoader();
        this->comboBoxProp = PropLoader();

        return 0;
}




Parser::Parser(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::Parser)
{
        this->jsonObj = JsonLoader(INSTANCE_PATH);

        BoxReloader();

        InitWidget();

        ui->setupUi(this);
}




Parser::~Parser()
{
        delete jsonObj;

        delete comboBoxServ;
        delete comboBoxProp;

        delete ui;
}

