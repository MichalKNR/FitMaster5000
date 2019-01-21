#include "stats_events_dialog.h"
#include "ui_stats_events_dialog.h"

STATS_Events_dialog::STATS_Events_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::STATS_Events_dialog)
{
    ui->setupUi(this);
}

STATS_Events_dialog::~STATS_Events_dialog()
{
    delete ui;
}
