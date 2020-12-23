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

#ifdef  __DEBUG__onst
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
        QJsonArray services = this->jsonObj->value("services").toArray();

        for (auto service : services) {
                QJsonObject item = service.toObject();
#ifdef __DEBUG__
                qDebug() << item["description"].toString()
                << " : " << item["properties"];
#endif

                comboBoxServ->addItem(QString::number(item["iid"].toInt())
                + "-" + item["description"].toString());
        }

        comboBoxServ->setCurrentIndex(2);

        return this->comboBoxServ;
}



QJsonObject Parser::GetProp() {
        QString service = this->comboBoxServ->currentText();
        int servID = service.split('-')[0].toInt();

        QJsonArray props = this->jsonObj->value("services").toArray();
        for (auto item : props) {
                QJsonObject prop = item.toObject();

#ifdef __DEBUG__
                qDebug() << prop["description"] << Qt::endl;
                qDebug() << prop["iid"] << Qt::endl;
#endif

                /* iid has to be unique */
                if (servID == prop["iid"].toInt())
                        return prop;

        }

        return QJsonObject();
}


QComboBox *Parser::PropLoader() {
        QJsonObject props = GetProp();
        this->comboBoxProp->addItems(props.keys());

//        this->comboBoxProp->setCurrentIndex(2);

        return this->comboBoxProp;
}



QComboBox *Parser::KeyLoader() {
        if (this->comboBoxIndex->count() == 0)
                return this->comboBoxKey;

        QJsonObject props = GetProp();
        QString serv = this->comboBoxProp->currentText();


        int iid = this->comboBoxIndex->currentText().split('-')[0].toInt();

        QJsonArray items = props[serv].toArray();


        for (auto item : items) {
                QJsonObject obj = item.toObject();
                if (obj["iid"].toInt() == iid) {
                        this->comboBoxKey->addItems(obj.keys());

#ifdef __DEBUG__
                        qDebug() << obj.keys();
#endif
                        return this->comboBoxKey;
                }
        }

        return this->comboBoxKey;
}


QPlainTextEdit *Parser::TextLoader() {
        if (this->comboBoxKey->count() == 0)
                return this->itemContent;

        QJsonObject props = GetProp();
        QString serv = this->comboBoxProp->currentText();

        int iid = this->comboBoxIndex->currentText().split('-')[0].toInt();

        QJsonArray items = props[serv].toArray();

        for (auto item : items) {
                QJsonObject obj = item.toObject();
                if (obj["iid"].toInt() == iid) {

                        QString key = this->comboBoxKey->currentText();
                        QJsonValue value = obj[key];

                        if (value.isArray()) {
                                this->itemContent->setPlainText(QJsonDocument(value.toArray()).toJson());
                        }
                        else if (value.isString()) {
                                this->itemContent->setPlainText(value.toString());
                        }
                        else if (value.isDouble()) {
                                this->itemContent->setPlainText(QString::number(value.toDouble()));
                        }
                        else {
                                QJsonDocument doc = QJsonDocument::fromVariant(value);
                        }
                        return this->itemContent;
                }
        }

        return this->itemContent;
}



QPlainTextEdit *Parser::ShortContent() {
        QJsonObject prop = GetProp();
        QString key = this->comboBoxProp->currentText();

#ifdef __DEBUG__
        qDebug() << prop[key];
#endif

        if (prop[key].isString()) {
                this->itemContent->setPlainText(prop[key].toString());
                this->comboBoxIndex->clear();
                this->comboBoxKey->clear();
        }
        else if (prop[key].isArray()) {


                QJsonArray values = prop[key].toArray();


                for (auto x : values) {
                        QJsonObject obj = x.toObject();
#ifdef __DEBUG__
                        qDebug() << QString::number(obj["iid"].toInt())
                        + '-' + obj["description"].toString();
#endif
                        this->comboBoxIndex->addItem(
                        QString::number(obj["iid"].toInt())
                        + '-' + obj["description"].toString());
                }


        }
        else if (prop[key].isDouble()) {
                this->itemContent->setPlainText(QString::number(prop[key].toDouble()));
                this->comboBoxIndex->clear();
                this->comboBoxIndex->clear();
        }

        this->comboBoxIndex->setCurrentIndex(1);
        KeyLoader();

        return this->itemContent;
}


int Parser::BoxReloader() {

        this->itemContent = new QPlainTextEdit(this);
        this->itemContent->move(0, 40);

        this->comboBoxKey = new QComboBox(this);
        this->comboBoxKey->move(600, 0);
        this->comboBoxKey->resize(180, 30);

        this->comboBoxIndex = new QComboBox(this);
        this->comboBoxIndex->move(400, 0);
        this->comboBoxIndex->resize(180, 30);

        this->comboBoxProp = new QComboBox(this);
        this->comboBoxProp->move(200, 0);
        this->comboBoxProp->resize(180, 30);

        this->comboBoxServ = new QComboBox(this);
        this->comboBoxServ->move(0, 0);
        this->comboBoxServ->resize(180, 30);

        this->comboBoxServ = ServLoader();
        this->comboBoxProp = PropLoader();
        this->ShortContent();


        this->comboBoxKey->setCurrentIndex(5);


        this->TextLoader();

        connect(this->comboBoxKey, SIGNAL(currentIndexChanged(int)), this, SLOT(KeyChanged(int)));
        connect(this->comboBoxIndex, SIGNAL(currentIndexChanged(int)), this, SLOT(IndexChanged(int)));
        connect(this->comboBoxProp, SIGNAL(currentIndexChanged(int)), this, SLOT(PropChanged(int)));
        connect(this->comboBoxServ, SIGNAL(currentIndexChanged(int)), this, SLOT(ServChanged(int)));

        return 0;
}


void Parser::KeyChanged(int idx) {
        this->TextLoader();
}

void Parser::IndexChanged(int idx) {
        this->comboBoxKey->clear();
        this->KeyLoader();
}

void Parser::PropChanged(int idx) {
        this->comboBoxIndex->clear();
        this->ShortContent();
}


void Parser::ServChanged(int idx) {
        this->comboBoxProp->clear();
        this->itemContent->clear();
        this->PropLoader();
}


Parser::Parser(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::Parser)
{
        this->jsonObj = JsonLoader(INSTANCE_PATH);

        InitWidget();

        BoxReloader();

        ui->setupUi(this);
}




Parser::~Parser()
{
        delete jsonObj;

        delete comboBoxServ;
        delete comboBoxProp;
        delete itemContent;
        delete comboBoxIndex;

        delete ui;
}

