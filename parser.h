#ifndef PARSER_H
#define PARSER_H

#include <QWidget>

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
        Ui::Parser *ui;
};
#endif // PARSER_H
