#ifndef STATS_COACH_H
#define STATS_COACH_H

#include <QDialog>

namespace Ui {
class STATS_Coach;
}

class STATS_Coach : public QDialog
{
    Q_OBJECT

public:
    explicit STATS_Coach(QWidget *parent = nullptr);
    ~STATS_Coach();

private:
    Ui::STATS_Coach *ui;
};

#endif // STATS_COACH_H
