/********************************************************************************
** Form generated from reading ui file 'chatdialog.ui'
**
** Created: Sat Mar 1 16:28:57 2008
**      by: Qt User Interface Compiler version 4.3.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

class Ui_ChatDialog
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QTextEdit *textEdit;
    QListWidget *listWidget;
    QHBoxLayout *hboxLayout1;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QDialog *ChatDialog)
    {
    if (ChatDialog->objectName().isEmpty())
        ChatDialog->setObjectName(QString::fromUtf8("ChatDialog"));
    ChatDialog->resize(513, 349);
    vboxLayout = new QVBoxLayout(ChatDialog);
#ifndef Q_OS_MAC
    vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout->setMargin(9);
#endif
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout->setMargin(0);
#endif
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    textEdit = new QTextEdit(ChatDialog);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setFocusPolicy(Qt::NoFocus);
    textEdit->setReadOnly(true);

    hboxLayout->addWidget(textEdit);

    listWidget = new QListWidget(ChatDialog);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setMaximumSize(QSize(180, 16777215));
    listWidget->setFocusPolicy(Qt::NoFocus);

    hboxLayout->addWidget(listWidget);


    vboxLayout->addLayout(hboxLayout);

    hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout1->setSpacing(6);
#endif
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    label = new QLabel(ChatDialog);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout1->addWidget(label);

    lineEdit = new QLineEdit(ChatDialog);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    hboxLayout1->addWidget(lineEdit);


    vboxLayout->addLayout(hboxLayout1);


    retranslateUi(ChatDialog);

    QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
    ChatDialog->setWindowTitle(QApplication::translate("ChatDialog", "Chat", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("ChatDialog", "Message:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ChatDialog);
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

#endif // UI_CHATDIALOG_H
