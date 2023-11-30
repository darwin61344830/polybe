#include <QCoreApplication>

#include <iostream>
#include <QString>
#include <QTextStream>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 1;
}

QString affineEncrypt(const QString& message, int a, int b, int m) {
    QString encryptedMessage;

    for (QChar letter : message) {
        if (letter.isLetter()) {
            int base = letter.isUpper() ? 'A' : 'a';
            char encryptedChar = ((a * (letter.toLatin1() - base) + b) % m) + base;
            encryptedMessage += encryptedChar;
        } else if (letter == ' ') {

            encryptedMessage += ' ';
        }
    }

    return encryptedMessage;
}

QString affineDecrypt(const QString& encryptedMessage, int a, int b, int m) {
    int aInverse = modInverse(a, m);
    QString decryptedMessage;

    for (QChar letter : encryptedMessage) {
        if (letter.isLetter()) {
            int base = letter.isUpper() ? 'A' : 'a';
            char decryptedChar = ((aInverse * (letter.toLatin1() - base - b + m)) % m) + base;
            decryptedMessage += decryptedChar;
        } else if (letter == ' ') {

            decryptedMessage += ' ';
        }
    }

    return decryptedMessage;
}
bool areCoprime(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a == 1;
}
int main() {

    int choix;
    QTextStream inputStream(stdin);
    std::cout << "Entrez le message a chiffrer : ";
    QString messageToEncrypt = inputStream.readLine();

    int a, b, m;

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

            do {
                std::cout << "Entrez la valeur de a (doit etre premier avec 26) : ";
                std::cin >> a;
            } while (!areCoprime(a, 26));

            std::cout << "Entrez le decalage : ";
            std::cin >> b;

            m = 26;


            QString encryptedMessage = affineEncrypt(messageToEncrypt, a, b, m);
            std::cout << "Message chiffre : " << encryptedMessage.toStdString() << std::endl;

        } else if (choix == 2) {
            QTextStream inputStream(stdin);
            std::cout << "Entrez le message a déchiffrer : ";
            QString messageToDecrypt = inputStream.readLine();

            do {
                std::cout << "Entrez la valeur de a (doit etre premier avec 26) : ";
                std::cin >> a;
            } while (!areCoprime(a, 26));

            std::cout << "Entrez le decalage : ";
            std::cin >> b;

            m = 26;
            QString decryptedMessage = affineDecrypt(encryptedMessage, a, b, m);
            std::cout << "Message déchiffre'' : " << decryptedMessage.toStdString() << std::endl;

        }

    } while (choix != 3);
















    return 0;
}
