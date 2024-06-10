#include <QApplication>
#include "pomodoro.h"

PomodoroTimer::PomodoroTimer(QWidget *parent)
    : QWidget(parent), timeLeft(WORK_TIME), isRunning(false), elapsedTime(0) {
    setWindowTitle("Pomodoro Timer");
    setFixedSize(300, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    timerLabel = new QLabel("00:00", this);
    timerLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(timerLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    startButton = new QPushButton("Start", this);
    resetButton = new QPushButton("Reset", this);
    completeButton = new QPushButton("Complete", this);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(completeButton);

    mainLayout->addLayout(buttonLayout);

    completedList = new QListWidget(this);
    mainLayout->addWidget(completedList);

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &PomodoroTimer::updateTimer);
    connect(startButton, &QPushButton::clicked, this, &PomodoroTimer::startTimer);
    connect(resetButton, &QPushButton::clicked, this, &PomodoroTimer::resetTimer);
    connect(completeButton, &QPushButton::clicked, this, &PomodoroTimer::completeTimer);

    updateTimer();
}

void PomodoroTimer::startTimer() {
    if (!isRunning) {
        isRunning = true;
        timer->start(1000);
    }
}

void PomodoroTimer::resetTimer() {
    isRunning = false;
    timer->stop();
    timeLeft = WORK_TIME;
    elapsedTime = 0;
    updateTimer();
}

void PomodoroTimer::completeTimer() {
    if (elapsedTime > 0) {
        int mins = elapsedTime / 60;
        int secs = elapsedTime % 60;
        QString timeFormat = QString("%1:%2").arg(mins, 2, 10, QChar('0')).arg(secs, 2, 10, QChar('0'));
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        bool ok;
        QString text = QInputDialog::getText(this, tr("Task Complete"),
            tr("Enter a short message:"), QLineEdit::Normal,
            "", &ok);
        if (ok && !text.isEmpty()) {
            QString logEntry = QString("%1 - %2 - %3").arg(timestamp).arg(timeFormat).arg(text);
            completedList->addItem(logEntry);
        }
        resetTimer();
    }
}

void PomodoroTimer::updateTimer() {
    if (isRunning) {
        if (timeLeft > 0) {
            --timeLeft;
            ++elapsedTime;
        } else {
            isRunning = false;
            timer->stop();
            QMessageBox::information(this, "Pomodoro Timer", "Time's up!");
        }
    }
    int mins = timeLeft / 60;
    int secs = timeLeft % 60;
    QString timeFormat = QString("%1:%2").arg(mins, 2, 10, QChar('0')).arg(secs, 2, 10, QChar('0'));
    timerLabel->setText(timeFormat);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    PomodoroTimer window;
    window.show();

    return app.exec();
}