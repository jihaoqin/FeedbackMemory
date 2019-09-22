#ifndef ADDDIALOG_H
#define ADDDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

class AddDialog:public QDialog
{
public:
    AddDialog(QWidget* parent = nullptr);
    QLineEdit *nameText;
    QTextEdit *wordText;
private:
    QLabel* nameLabel;
    QLabel* wordLabel;
    QPushButton* okButton;
    QPushButton* cancelButton;
};

#endif // ADDDIALOG_H
