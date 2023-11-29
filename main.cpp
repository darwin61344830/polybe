#include <QCoreApplication>

#include <iostream>
#include <QString>
#include <QMap>
#include <QTextStream>

QMap<QChar, QString> createPolybeGridWithKey(const QString& key) {
    QMap<QChar, QString> polybeGrid;
    QString alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString keyUpperCase = key.toUpper();
    int row = 1;
    int col = 1;

    for (QChar letter : keyUpperCase) {
        if (letter.isLetter() && !polybeGrid.contains(letter)) {
            polybeGrid[letter] = QString::number(row) + QString::number(col);
            col++;
            if (col > 5) {
                col = 1;
                row++;
            }
        }
    }

    for (QChar letter : alphabet) {
        if (!polybeGrid.contains(letter)) {
            polybeGrid[letter] = QString::number(row) + QString::number(col);
            col++;
            if (col > 5) {
                col = 1;
                row++;
            }
        }
    }

    return polybeGrid;
}

QString polybeEncrypt(const QString& message, const QMap<QChar, QString>& polybeGrid) {
    QString encryptedMessage;

    for (QChar letter : message) {
        if (letter.isLetter()) {
            QChar base = letter.isUpper() ? 'A' : 'a';
            encryptedMessage += polybeGrid.value(letter.toUpper(), "") + " ";
        } else if (letter == ' ') {

            encryptedMessage += "0";
        }
    }

    return encryptedMessage.trimmed();
}


QString polybeDecrypt(const QString& encryptedMessage, const QMap<QChar, QString>& polybeGrid) {
    QString decryptedMessage;
    QStringList pairs = encryptedMessage.split(' ', QString::SkipEmptyParts);

    for (const QString& pair : pairs) {
        if (pair == "0") {

            decryptedMessage += " ";
        } else {
            for (auto it = polybeGrid.begin(); it != polybeGrid.end(); ++it) {
                if (it.value() == pair) {
                    decryptedMessage += it.key();
                    break;
                }
            }
        }
    }

    return decryptedMessage;
}



int main() {
    int choix;
    QString key;

    do {
        do {
            std::cout << "1- Chiffrement\n2- Dechiffrement\n3- Retour\n";
            std::cout << "Entrez votre choix : ";
            std::cin >> choix;
        } while (choix < 1 || choix > 3);

        if (choix == 1) {
            QTextStream inputStream(stdin);
            std::cout << "Entrez le message a chiffrer : ";
            QString messageToEncrypt = inputStream.readLine();

            std::cout << "Entrez la cle de chiffrement : ";
            inputStream >> key;

            QMap<QChar, QString> polybeGrid = createPolybeGridWithKey(key);

            QString encryptedMessage = polybeEncrypt(messageToEncrypt, polybeGrid);
            std::cout << "Message chiffre : " << encryptedMessage.toStdString() << std::endl << std::endl;

        } else if (choix == 2) {
            QTextStream inputStream(stdin);
            std::cout << "Entrez le message a déchiffrer : ";
            QString messageToDecrypt = inputStream.readLine();

            std::cout << "Entrez la cle de chiffrement : ";
            inputStream >> key;

            QMap<QChar, QString> polybeGrid = createPolybeGridWithKey(key);

            QString decryptedMessage = polybeDecrypt(messageToDecrypt, polybeGrid);
            std::cout << "Message déchiffre : " << decryptedMessage.toStdString() << std::endl << std::endl;
        }

    } while (choix != 3);

    return 0;
}

