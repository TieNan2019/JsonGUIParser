#include "parser.h"
#include "ui_parser.h"

Parser::Parser(QWidget *parent)
        : QWidget(parent)
        , ui(new Ui::Parser)
{
        ui->setupUi(this);
}

Parser::~Parser()
{
        delete ui;
}

