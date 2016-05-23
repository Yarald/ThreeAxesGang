#include "controlpanel.h"
#include "ui_controlpanel.h"

#include <QSerialPort>
#include <QMediaPlayer>
#include <QTimer>

ControlPanel::ControlPanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);

    // Settings for main window.
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    // Settings for COM port.
    serial.setPortName(this->COM);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    // Multimedia
    player = new QMediaPlayer(this);
    // Timer
    this->timer = new QTimer(this);
}

ControlPanel::~ControlPanel()
{
    serial.write("p*");
    serial.close();
    delete ui;
}

void ControlPanel::on_systemOnButton_clicked()
{
    ui->statusLabel->setText(QString("Opening port to %1...").arg(this->COM));
    serial.open(QIODevice::ReadWrite);
    ui->statusLabel->setText(QString("Port opened to %1.").arg(this->COM));
}

void ControlPanel::on_switchL1_clicked()
{
    serial.write("q*");
    ui->statusLabel->setText("Lamp 1 is turned on.");
}

void ControlPanel::on_switchL2_clicked()
{
    serial.write("w*");
    ui->statusLabel->setText("Lamp 2 is turned on.");
}

void ControlPanel::on_switchL3_clicked()
{
    serial.write("e*");
    ui->statusLabel->setText("Lamp 3 is turned on.");
}

void ControlPanel::on_switchL4_clicked()
{
    serial.write("r*");
    ui->statusLabel->setText("Lamp 4 is turned on.");
}

void ControlPanel::on_switchL5_clicked()
{
    serial.write("t*");
    ui->statusLabel->setText("Lamp 5 is turned on.");
}

void ControlPanel::on_switchL6_clicked()
{
    serial.write("y*");
    ui->statusLabel->setText("Lamp 6 is turned on.");
}

void ControlPanel::on_switchL7_clicked()
{
    serial.write("u*");
    ui->statusLabel->setText("Lamp 7 is turned on.");
}

void ControlPanel::on_switchL8_clicked()
{
    serial.write("i*");
    ui->statusLabel->setText("Lamp 8 is turned on.");
}

void ControlPanel::on_changeClrL1_clicked()
{
    serial.write("a*");
    ui->statusLabel->setText("Lamp 1 changed his color.");
}

void ControlPanel::on_changeClrL2_clicked()
{
    serial.write("s*");
    ui->statusLabel->setText("Lamp 2 changed his color.");
}

void ControlPanel::on_changeClrL3_clicked()
{
    serial.write("d*");
    ui->statusLabel->setText("Lamp 3 changed his color.");
}

void ControlPanel::on_changeClrL4_clicked()
{
    serial.write("f*");
    ui->statusLabel->setText("Lamp 4 changed his color.");
}

void ControlPanel::on_changeClrL5_clicked()
{
    serial.write("g*");
    ui->statusLabel->setText("Lamp 5 changed his color.");
}

void ControlPanel::on_changeClrL6_clicked()
{
    serial.write("h*");
    ui->statusLabel->setText("Lamp 6 changed his color.");
}

void ControlPanel::on_changeClrL7_clicked()
{
    serial.write("j*");
    ui->statusLabel->setText("Lamp 7 changed his color.");
}

void ControlPanel::on_changeClrL8_clicked()
{
    serial.write("k*");
    ui->statusLabel->setText("Lamp 8 changed his color.");
}

void ControlPanel::on_colorsAllButton_clicked()
{
    serial.write("o*");
    ui->statusLabel->setText("All colors changed.");
}

void ControlPanel::on_switchAllButton_clicked()
{
    serial.write("p*");
    ui->statusLabel->setText("All lamps are switched.");
}

void ControlPanel::on_pingPongButton_clicked()
{
    serial.write("zz*");
    ui->statusLabel->setText("Ping pong animation!");
}

void ControlPanel::on_newYearButton_clicked()
{
    serial.write("zx*");
    ui->statusLabel->setText("New year animation!");
}

void ControlPanel::on_chaserButton_clicked()
{
    serial.write("zc*");
    ui->statusLabel->setText("Chaser animation!");
}

void ControlPanel::on_sorcererButton_clicked()
{
    QString temp = "Song was turned on.\n";
    // Load the file
    player->setMedia(QUrl::fromLocalFile("sorcerer.mp3"));
    player->play();
    ui->statusLabel->setText(player->errorString());

    temp.append("X-Ray Dog - Sorcerer (remix) animation!");
    serial.write("zb*");
    ui->statusLabel->setText(temp);
}

void ControlPanel::on_flickeringButton_clicked()
{
    serial.write("zv*");
    ui->statusLabel->setText("Flickering animation!");
}

void ControlPanel::on_btght_slider_valueChanged(int value)
{
    char myInt = '0' + value;
    char toWrite[3] = {myInt, '*', '\n'};
    serial.write(toWrite);
    QString statusLabelText = QString("Brightness value level %1.").arg(QString::number(value));
    this->ui->statusLabel->setText(statusLabelText);
}

void ControlPanel::helper(int h, int m, int s, QString context)
{
    this->ui->statusLabel->setText(QString("%1 on %2-%3-%4")
                                   .arg(context)
                                   .arg(QString::number(h))
                                   .arg(QString::number(m))
                                   .arg(QString::number(s))
                                   );
}

void ControlPanel::on_submitTimer_button_clicked()
{
    int hours = this->ui->timer_timeEdit->time().hour();
    int minutes = this->ui->timer_timeEdit->time().minute();
    int seconds = this->ui->timer_timeEdit->time().second();

    QString timerActionText = this->ui->timer_comboBox->currentText();
    QTime now = QDateTime::currentDateTime().time();
    QTime timeOfTheAction = QTime(hours, minutes, seconds);

    if (timerActionText == "Close program")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(close()));
        helper(hours, minutes, seconds, "System will be closed");
    }
    else if (timerActionText == "Turn On 1")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_switchL1_clicked()));
        helper(hours, minutes, seconds, "First lamp will be switched");
    }
    else if (timerActionText == "Turn On 2")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_switchL2_clicked()));
        helper(hours, minutes, seconds, "Second lamp will be switched");
    }
    else if (timerActionText == "Turn On 3")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_switchL3_clicked()));
        helper(hours, minutes, seconds, "Third lamp will be switched");
    }
    else if (timerActionText == "Turn On 4")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_switchL4_clicked()));
        helper(hours, minutes, seconds, "Fourth lamp will be switched");
    }
    else if (timerActionText == "Turn On 5")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_switchL5_clicked()));
        helper(hours, minutes, seconds, "Fifth lamp will be switched");
    }
    else if (timerActionText == "Turn On 6")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_switchL6_clicked()));
        helper(hours, minutes, seconds, "Sixth lamp will be switched");
    }
    else if (timerActionText == "Turn On 7")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_switchL7_clicked()));
        helper(hours, minutes, seconds, "Seventh lamp will be switched");
    }
    else if (timerActionText == "Turn On 8")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_switchL8_clicked()));
        helper(hours, minutes, seconds, "Eigth lamp will be switched");
    }
    else if (timerActionText == "Change color 1")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_changeClrL1_clicked()));
        helper(hours, minutes, seconds, "First lamp will change color");
    }
    else if (timerActionText == "Change color 2")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_changeClrL2_clicked()));
        helper(hours, minutes, seconds, "Second lamp will change color");
    }
    else if (timerActionText == "Change color 3")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_changeClrL3_clicked()));
        helper(hours, minutes, seconds, "Third lamp will change color");
    }
    else if (timerActionText == "Change color 4")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_changeClrL4_clicked()));
        helper(hours, minutes, seconds, "Fourth lamp will change color");
    }
    else if (timerActionText == "Change color 5")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_changeClrL5_clicked()));
        helper(hours, minutes, seconds, "Fifth lamp will change color");
    }
    else if (timerActionText == "Change color 6")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_changeClrL6_clicked()));
        helper(hours, minutes, seconds, "Sixth lamp will change color");
    }
    else if (timerActionText == "Change color 7")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_changeClrL7_clicked()));
        helper(hours, minutes, seconds, "Seventh lamp will change color");
    }
    else if (timerActionText == "Change color 8")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_changeClrL8_clicked()));
        helper(hours, minutes, seconds, "Eigth lamp will change color");
    }
    else if (timerActionText == "Switch All")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_switchAllButton_clicked()));
        helper(hours, minutes, seconds, "All lamps will be switched");
    }
    else if (timerActionText == "Change color all")
    {
        timer->singleShot(now.secsTo(timeOfTheAction) * 1000, this, SLOT(on_colorsAllButton_clicked()));
        helper(hours, minutes, seconds, "All lamps will change color");
    }
    else
    {
        this->ui->statusLabel->setText("WTF JUST HAPPENED?!?!??! REPORT MAXIM GONCHAR PLS");
    }
}
