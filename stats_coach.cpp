#include "stats_coach.h"
#include "ui_stats_coach.h"

STATS_Coach::STATS_Coach(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::STATS_Coach)
{
    ui->setupUi(this);
}

STATS_Coach::~STATS_Coach()
{
    delete ui;
}
