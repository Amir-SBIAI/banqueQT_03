#include "window.h"
#include "compte.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>


Window::Window(QWidget *parent)
    : QWidget(parent),
      compteActif(nullptr) // Initialisation du compte actif
{
    QLabel *idLabel = new QLabel(tr("Identifiant:"));
    idLineEdit = new QLineEdit;
    idLineEdit->setPlaceholderText("Entrer votre identifiant");

    QLabel *passwordLabel = new QLabel(tr("Mot de passe:"));
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setPlaceholderText("Entrer votre mot de passe");

    showIDCheckBox = new QCheckBox(tr("Afficher l'identifiant"));
    connect(showIDCheckBox, &QCheckBox::toggled, this, &Window::toggleIDField);

    showPasswordCheckBox = new QCheckBox(tr("Afficher le mot de passe"));
    connect(showPasswordCheckBox, &QCheckBox::toggled, this, &Window::togglePasswordField);

    connectButton = new QPushButton(tr("Se connecter"));
    connect(connectButton, &QPushButton::clicked, this, &Window::onConnectButtonClicked);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(idLabel, 0, 0);
    layout->addWidget(idLineEdit, 0, 1);
    layout->addWidget(showIDCheckBox, 0, 2);
    layout->addWidget(passwordLabel, 1, 0);
    layout->addWidget(passwordLineEdit, 1, 1);
    layout->addWidget(showPasswordCheckBox, 1, 2);
    layout->addWidget(connectButton, 2, 1);

    setLayout(layout);
    setWindowTitle(tr("LA BANQUE DU BOSS AMIR"));
}

void Window::toggleIDField(bool checked) {
    idLineEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::PasswordEchoOnEdit);
}

void Window::togglePasswordField(bool checked) {
    passwordLineEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}

void Window::onConnectButtonClicked() {
    QString id = idLineEdit->text();
    QString password = passwordLineEdit->text();

    // CLIENT
    Client client1("FR1234", "SBIAI", "Amir", "0645687654");
    Client client2("FR5678", "KOCHBATI", "Slim", "0675684212");

    Compte *compte1 = new Compte("FR1234", 5000, client1);
    Compte *compte2 = new Compte("FR5678", 5000, client2);


    // Vérification des identifiants
    if (id == "Amir" && password == "1234") {
        compteActif = compte1;

        QWidget *newWindow = new QWidget;
        newWindow->setWindowTitle("MENU DU COMPTE");
        newWindow->resize(400, 300);

        QVBoxLayout *layout = new QVBoxLayout;

        QPushButton *CrediterButton = new QPushButton(tr("Crediter"));
        QPushButton *DebiterButton = new QPushButton(tr("Debiter"));
        QPushButton *TransfertButton = new QPushButton(tr("Transfert"));
        QPushButton *InfosButton = new QPushButton(tr("Afficher Infos"));
        QPushButton *quitButton = new QPushButton(tr("Quitter"));

        layout->addWidget(CrediterButton);
        layout->addWidget(DebiterButton);
        layout->addWidget(TransfertButton);
        layout->addWidget(InfosButton);
        layout->addWidget(quitButton);

        connect(quitButton, &QPushButton::clicked, newWindow, &QWidget::close);
        connect(CrediterButton, &QPushButton::clicked, this, &Window::openCrediterPage);
        connect(DebiterButton, &QPushButton::clicked, this, &Window::openDebiterPage);
        connect(TransfertButton, &QPushButton::clicked, this, &Window::openTransfertPage);
        connect(InfosButton, &QPushButton::clicked, this, &Window::openInfosPage);

        newWindow->setLayout(layout);
        newWindow->show();
    } else if (id == "Slim" && password == "5678") {
        compteActif = compte2;

        QWidget *newWindow = new QWidget;
        newWindow->setWindowTitle("MENU DU COMPTE");
        newWindow->resize(400, 300);

        QVBoxLayout *layout = new QVBoxLayout;

        QPushButton *CrediterButton = new QPushButton(tr("Crediter"));
        QPushButton *DebiterButton = new QPushButton(tr("Debiter"));
        QPushButton *TransfertButton = new QPushButton(tr("Transfert"));
        QPushButton *InfosButton = new QPushButton(tr("Afficher Infos"));
        QPushButton *quitButton = new QPushButton(tr("Quitter"));

        layout->addWidget(CrediterButton);
        layout->addWidget(DebiterButton);
        layout->addWidget(TransfertButton);
        layout->addWidget(InfosButton);
        layout->addWidget(quitButton);

        connect(quitButton, &QPushButton::clicked, newWindow, &QWidget::close);
        connect(CrediterButton, &QPushButton::clicked, this, &Window::openCrediterPage);
        connect(DebiterButton, &QPushButton::clicked, this, &Window::openDebiterPage);
        connect(TransfertButton, &QPushButton::clicked, this, &Window::openTransfertPage);
        connect(InfosButton, &QPushButton::clicked, this, &Window::openInfosPage);

        newWindow->setLayout(layout);
        newWindow->show();


   } else {
        QMessageBox::warning(this, tr("Erreur de connexion"), tr("Identifiants ou mot de passe incorrects."));
    }
}

void Window::openCrediterPage() {
    // Créer la fenêtre de créditer
    QWidget *creditWindow = new QWidget;
    //QVBoxLayout *layout = new QVBoxLayout;

    //A CORRIGER

    creditWindow->setWindowTitle("CREDITER");
    creditWindow->resize(400, 300);

    // créditer
    QLabel *amountLabel = new QLabel(tr("Entrez le montant à créditer :"));
    QLineEdit *amountLineEdit = new QLineEdit;
    amountLineEdit->setPlaceholderText("Montant");

    // btn créditer
    QPushButton *creditButton = new QPushButton(tr("Créditer"));
    connect(creditButton, &QPushButton::clicked, [this, amountLineEdit]() {
        bool ok;
        double montant = amountLineEdit->text().toDouble(&ok);  // Conversion du texte en double
        if (ok && montant > 0) {
            if (compteActif) {
                  compteActif->Crediter(montant);  // Appeler la méthode de crédit du compte actif

                            // msg confirmation
                     QMessageBox::information(nullptr, tr("Crédit effectué"), tr("Le montant a été crédité avec succès."));
                 }
               } else {
                   // msg erreur
                      QMessageBox::warning(nullptr, tr("Erreur"), tr("Veuillez entrer un montant valide."));
                    }
                });

    // Layout pour la fenêtre de créditer
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(amountLabel);
    layout->addWidget(amountLineEdit);
    layout->addWidget(creditButton);

    creditWindow->setLayout(layout);
    creditWindow->show();
}

void Window::openDebiterPage() {
    // Créer la fenêtre de débiter
    QWidget *debitWindow = new QWidget;
    debitWindow->setWindowTitle("DEBITER");
    debitWindow->resize(400, 300);

    // débiter
    QLabel *amountLabel = new QLabel(tr("Entrez le montant à débiter :"));
    QLineEdit *amountLineEdit = new QLineEdit;
    amountLineEdit->setPlaceholderText("Montant");

    // btn débiter
    QPushButton *debitButton = new QPushButton(tr("Débiter"));
    connect(debitButton, &QPushButton::clicked, [this, amountLineEdit]() {
        bool ok;
        double montant = amountLineEdit->text().toDouble(&ok);
        if (ok && montant > 0) {
            if (compteActif) {
                // Vérification si le montant à débiter est inférieur ou égal au solde
                if (compteActif->getSolde() >= montant) {
                    compteActif->Debiter(montant);  // apl de la fonction débit


                    // msg confirmation
                    QMessageBox::information(nullptr, tr("Débit effectué"), tr("Le montant a été débité avec succès."));
                } else {
                    // Si le solde est insuffisant
                    QMessageBox::warning(nullptr, tr("Erreur"), tr("Solde insuffisant pour effectuer le débit."));
                }
            }
        } else {
            // msg erreur
            QMessageBox::warning(nullptr, tr("Erreur"), tr("Veuillez entrer un montant valide."));
        }
    });

    // Layout pour la fenêtre de débiter
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(amountLabel);
    layout->addWidget(amountLineEdit);
    layout->addWidget(debitButton);

    debitWindow->setLayout(layout);
    debitWindow->show();
}

void Window::openTransfertPage() {

    // Ouvrir la page pour un transfert
    QWidget *transfertWindow = new QWidget;
    transfertWindow->setWindowTitle("TRANSFERT");
    transfertWindow->resize(400, 300);

    //champs de saisie pr le transfert
    QLabel *destinationLabel = new QLabel(tr("Identifiant du destinataire :"));
    QLineEdit *destinationLineEdit = new QLineEdit;
    //montre l'exemple du compte a mettre
    destinationLineEdit->setPlaceholderText("Ex : FR1111");

    QLabel *amountLabel = new QLabel(tr("Montant à transférer :"));
    QLineEdit *amountLineEdit = new QLineEdit;
    //montre l'exemple du montant a mettre
    amountLineEdit->setPlaceholderText("Ex : 500");

    QPushButton *transferButton = new QPushButton(tr("Effectuer le transfert"));

    //mise en page
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(destinationLabel);
    layout->addWidget(destinationLineEdit);
    layout->addWidget(amountLabel);
    layout->addWidget(amountLineEdit);
    layout->addWidget(transferButton);
    transfertWindow->setLayout(layout);

    connect(transferButton, &QPushButton::clicked, [this, destinationLineEdit, amountLineEdit, transfertWindow](){
        QString destinationID = destinationLineEdit->text();
        bool ok;
        double montant = amountLineEdit->text().toDouble(&ok);
//verifie si le montant est valide sinon erreur
        if(!ok && montant <= 0) {
            QMessageBox::warning(transfertWindow, tr("Erreur"), tr("Montant invalide"));
            return;
        }

        Client client1("FR1234", "SBIAI", "Amir", "0645687654");
        Client client2("FR1234", "KOCHBATI", "Slim", "0675684212");
        Compte compte1("FR1234", 5000, client1);
        Compte compte2("FR5678", 3000, client2);

        Compte *compteDestinataire = nullptr;

        if(destinationID == "FR1234") {
            compteDestinataire = &compte1;
        } else if (destinationID == "FR5678") {
                compteDestinataire = &compte2;
            }

        if (!compteDestinataire) {
            QMessageBox::warning(transfertWindow, tr("Erreur"), tr("Compte destinataire introuvable"));
            return;
        }
//verifie solde insuffisant et transfert
        if (compteActif->getSolde() >= montant) {
            compteActif->Debiter(montant);
            compteDestinataire->Crediter(montant);

            QMessageBox::information(transfertWindow, tr("Succès"),
                tr("Transfert de %1 euros effectué avec succès vers %2")
                    .arg(montant)
                    .arg(destinationID));
            //transfertWindow->close();
        } else {
            QMessageBox::warning(transfertWindow, tr("Erreur"), tr("Solde insuffisant"));
        }



    });
    transfertWindow->show();


}

void Window::openInfosPage() {
    // Ouvrir la page d'informations
    QWidget *infosWindow = new QWidget;
    infosWindow->setWindowTitle("INFORMATIONS");
    infosWindow->resize(400, 300);

    if (compteActif) {
        QLabel *infosLabel = new QLabel(tr("Nom: %1\nPrénom: %2\nTéléphone: %3\nSolde: %4")
                                            .arg(QString::fromStdString(compteActif->getProprietaireNom()))
                                            .arg(QString::fromStdString(compteActif->getProprietairePrenom()))
                                            .arg(QString::fromStdString(compteActif->getProprietaireTelephone()))
                                            .arg(QString::number(compteActif->getSolde())));
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(infosLabel);
        infosWindow->setLayout(layout);
    }
    infosWindow->show();
}

bool Window::connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("amir_banque");
    db.setUserName("root");
    db.setPassword("root");

    if (!db.open()) {
        QMessageBox::critical(this, "Erreur de connexion", "Impossible de se connecter à la base de données.");
        return false;
    }
    return true;
}
bool updateClientInformation(int clientId, const QString& newName, double newBalance) {
    QSqlQuery query;
    query.prepare("UPDATE clients SET name = :name, balance = :balance WHERE id = :id");
    query.bindValue(":name", newName);
    query.bindValue(":balance", newBalance);
    query.bindValue(":id", clientId);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour du client : " << query.lastError().text();
        return false;
    }
    return true;
}

