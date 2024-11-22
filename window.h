#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "compte.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QCheckBox;
class QPushButton;
QT_END_NAMESPACE

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);

private slots:
    void toggleIDField(bool checked);
    void togglePasswordField(bool checked);
    void onConnectButtonClicked();
    void openCrediterPage();
    void openDebiterPage();
    void openTransfertPage();
    void openInfosPage();

private:
    QLineEdit *idLineEdit;
    QLineEdit *passwordLineEdit;
    QCheckBox *showIDCheckBox;
    QCheckBox *showPasswordCheckBox;
    QPushButton *connectButton;


    Compte *compteActif; // Le compte actif une fois connecté
    Compte *compteActif1;

    bool connectToDatabase();
    // Fonction pour mettre à jour les informations d'un client
    bool updateClientInformation(int clientId, const QString& newName, double newBalance);
};

#endif
