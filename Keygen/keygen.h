#ifndef KEYGEN_H
#define KEYGEN_H
#include <QString>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QObject>
#include <QApplication>
#include <string>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
class keygen
{
public:
    keygen(QString serial);
    void blowfishencode(char *input, int length);
    void initialize64();
    QString hexdigest();
    void MD5();
    void reverseString();
    void lowerOrUpperCase();
    void methodfloatchar();
    void concatenate();
    void UpperCase();
private:
    QChar m_bytReverseIndex[256];
    char m_bytIndex[64];
    std::string buffer;
    std::string buffer_temp;

    const char k_bytEqualSign = 61;
    const char k_bytMask1 = 3;
    const char k_bytMask2 = 15;
    const char k_bytMask3 = 63;
    const char k_bytMask4 = 192;
    const char k_bytMask5 = 240;
    const char k_bytMask6 = 252;
    const char k_bytShift2 = 4;
    const char k_bytShift4 = 16;
    const char k_bytShift6 = 64;
    const unsigned long k_lMaxBytesPerLine = 152;

    const std::string serial_machine = "MUExQi01OTBELURBMTctQzQxOQ==";
};

QString serial_generate(const QString &input);
#endif // KEYGEN_H
