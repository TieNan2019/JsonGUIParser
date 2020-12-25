#ifndef PARSER_H
#define PARSER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QComboBox>

#include <QFile>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>


#include <QDebug>
//#define __DEBUG__





#define INSTANCE_PATH   "/home/whoami/massager.json"


QT_BEGIN_NAMESPACE
namespace Ui { class Parser; }
QT_END_NAMESPACE

class Parser : public QWidget
{
        Q_OBJECT

public:
        Parser(QString path, QWidget *parent = nullptr);
        ~Parser();

private slots:
        void KeyChanged(int );
        void IndexChanged(int );
        void PropChanged(int );
        void ServChanged(int );
        void SaveCmd();
        void ReloadCmd();
        void OKCmd();


private:

        QJsonObject *jsonObj;
        QComboBox *comboBoxServ;
        QComboBox *comboBoxProp;
        QComboBox *comboBoxIndex;
        QComboBox *comboBoxKey;
        QPlainTextEdit *itemContent;
        QLineEdit *jsonPath;
        QPushButton *saveButton;
        QPushButton *reloadButton;
        QPushButton *okButton;

        QString FileRead(const QString&);
        QJsonObject JsonParse(const QString&);
        QJsonObject *JsonLoader(const QString &);

        void InitWidget();

        QJsonObject GetProp();
        QComboBox *ServLoader();
        QComboBox *PropLoader();
        QPlainTextEdit *ShortContent();
        QComboBox *KeyLoader();
        QPlainTextEdit *TextLoader();
        int BoxReloader();

        Ui::Parser *ui;
};
#endif // PARSER_H
