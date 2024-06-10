#ifndef POMODOROTIMER_H
#define POMODOROTIMER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QListWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <QDateTime>

class PomodoroTimer : public QWidget {
    Q_OBJECT

public:
    PomodoroTimer(QWidget *parent = nullptr);

private slots:
    void startTimer();
    void resetTimer();
    void completeTimer();
    void updateTimer();

private:
    static constexpr int WORK_TIME = 25 * 60;
    int timeLeft;
    bool isRunning;
    int elapsedTime;

    QLabel *timerLabel;
    QPushButton *startButton;
    QPushButton *resetButton;
    QPushButton *completeButton;
    QListWidget *completedList;
    QTimer *timer;
};

#endif // POMODOROTIMER_H