#include "keygen.h"
#define Make_array_plus_one 1

keygen::keygen(QString serial)
{
    std::string test1 = serial.toStdString().c_str();
    char * test = new char[test1.length() - 1];
    strcpy(test, test1.c_str());
    blowfishencode(test, test1.size()); //un metodo del blowfish que lo aplica el name
                                        //concatena con la constante que fue convertida a otra cosa pero que es nuestro serial de maquina
    concatenate();                                    //la constante con que concatena "MUExQi01OTBELURBMTctQzQxOQ==^"
    MD5();
    MD5();
    methodfloatchar();
    MD5();
    reverseString();
    lowerOrUpperCase();
    MD5();
    UpperCase();
}

void keygen::methodfloatchar()
{

   std::vector <char> new_string;

   for(unsigned int i = 0; i < buffer.size(); i++)
   {

      int result = (i+1) + 0x1;
      result *= (i+1);
      int temp_1 = 0x03f340 * (i+1);
      int temp_2 = buffer[i] ^ (i+2);
      int temp_3 = result * (i+2);
      temp_3 += temp_1;
      int temp_4 = temp_3 + temp_2;
      int temp_5 = temp_4 ^ result;
      double temp_6 = (double) temp_5;
      double d_result_sin = std::sin(temp_6);
      double d_result_cos = std::cos(temp_6);
      int temp_7 = 0x20 & (i+1);
      int temp_8 = 0x20 | (i+1);
      int temp_9 = temp_7 | temp_8;
      int temp_10 = temp_9 + temp_6;
      double temp_11 = (double) temp_10;

      std::string d = std::to_string(temp_11);

      if(d.find_first_of('.') != std::string::npos)
      {

         d.erase(d.find_first_of('.'), std::string::npos); //erase the decimal part and that's included the dot '.'
        for (unsigned j = 0; j<d.size(); j++)
        {
            new_string.push_back(d[j]);
        }
      }
   }
   buffer_temp = std::string(new_string.begin(), new_string.end());
   buffer = buffer_temp;
}

void keygen::reverseString()
{
    std::string reverse(buffer.rbegin(), buffer.rend());
    buffer = reverse;
}

void keygen::lowerOrUpperCase()
{
    int mult = 2;
    int add = 0x7e6800;
    int mod = 2;
    for(unsigned int i=0;i < buffer.size(); i++)
    {
       int result = (i+1) * mult;
       result += add;
       result %= i+1;
       result %= mod;

       if (result != 0)
       {
           buffer[i] = toupper(buffer[i]);
       }
       else {
           buffer[i] = tolower(buffer[i]);
       }

    }
}

void keygen::blowfishencode(char *input, int length)
{
    if (strcmp(input, "") == 0)
    {
        buffer = "";
        return;
    }

    if (m_bytReverseIndex[47] != 63)
    {
        initialize64();
    }

    char bytCrLF[4];
    int lCounter = 0;
    unsigned int lWorkspaceCounter;
    int lCompleteLines, lBytesRemaining;
    char * lpWorkSpace,* lpResult;
    int * lpCrLf;
    long UBound = length - 1;
    static std::string result;

    char *bytWorkspace;
    int UBound_bytWorkspace;
    if (UBound < 1024 )
    {
        bytWorkspace = (new char[4096 + Make_array_plus_one]{});
        UBound_bytWorkspace = 4096 + Make_array_plus_one;
    }
    else {
        bytWorkspace = (new char[UBound * 4 + Make_array_plus_one]{});
        UBound_bytWorkspace = UBound * 4 + Make_array_plus_one;
    }

    lWorkspaceCounter = 0x0;

    for (;(lCounter <= (UBound - (UBound % 3 + 3))); lCounter+=3)
    {
        bytWorkspace[lWorkspaceCounter] = m_bytIndex[input[lCounter] / k_bytShift2];
        bytWorkspace[lWorkspaceCounter + 2] = m_bytIndex[((input[lCounter] & k_bytMask1) * k_bytShift4) + (input[lCounter + 1 ] / k_bytShift4)];
        bytWorkspace[lWorkspaceCounter + 4] = m_bytIndex[((input[lCounter + 1] & k_bytMask2) * k_bytShift2) + (input[lCounter + 2] / k_bytShift6)];
        bytWorkspace[lWorkspaceCounter + 6] = m_bytIndex[input[lCounter + 2] & k_bytMask3];
        lWorkspaceCounter = lWorkspaceCounter + 8;
        //if (!(lCounter < (UBound - (UBound % 3 + 3)))) {break;}
    }

    switch (UBound % 3)
    {
        case 0:
            bytWorkspace[lWorkspaceCounter] = m_bytIndex[input[lCounter] / k_bytShift2];
            bytWorkspace[lWorkspaceCounter + 2] = m_bytIndex[(input[lCounter] & k_bytMask1) * k_bytShift4];
            bytWorkspace[lWorkspaceCounter + 4] = k_bytEqualSign;
            bytWorkspace[lWorkspaceCounter + 6] = k_bytEqualSign;
            break;
        case 1:
            bytWorkspace[lWorkspaceCounter] = m_bytIndex[input[lCounter] / k_bytShift2];
            bytWorkspace[lWorkspaceCounter + 2] = m_bytIndex[((input[lCounter] & k_bytMask1) * k_bytShift4) + input[lCounter + 1] / k_bytShift4];
            bytWorkspace[lWorkspaceCounter + 4] = m_bytIndex[(input[lCounter + 1] & k_bytMask2) * k_bytShift2];
            bytWorkspace[lWorkspaceCounter + 6] = k_bytEqualSign;
            break;
        case 2:
            bytWorkspace[lWorkspaceCounter] = m_bytIndex[input[lCounter] / k_bytShift2];
            bytWorkspace[lWorkspaceCounter + 2] = m_bytIndex[((input[lCounter] & k_bytMask1) * k_bytShift4) + ((input[lCounter + 1]) / k_bytShift4)];
            bytWorkspace[lWorkspaceCounter + 4] = m_bytIndex[((input[lCounter + 1] & k_bytMask2) * k_bytShift2) + ((input[lCounter + 2]) / k_bytShift6)];
            bytWorkspace[lWorkspaceCounter + 6] = m_bytIndex[input[lCounter + 2] & k_bytMask3];
            break;
    }

    lWorkspaceCounter = lWorkspaceCounter + 8;
    if(lWorkspaceCounter <= k_lMaxBytesPerLine)
    {
        result.resize(UBound_bytWorkspace);
        result = QString::fromUtf16((ushort *) bytWorkspace).toStdString();
        buffer = result;
    }

    else
    {
        bytCrLF[0] = 13;
        bytCrLF[1] = 0;
        bytCrLF[2] = 10;
        bytCrLF[3] = 0;

        char bytResult[UBound_bytWorkspace];
        lpWorkSpace = reinterpret_cast<char *>(bytWorkspace);
        lpResult = reinterpret_cast<char *>(bytResult);
        lpCrLf = reinterpret_cast<int *>(bytCrLF);
        lCompleteLines = lWorkspaceCounter / k_lMaxBytesPerLine;
        input = NULL;

        for(int lLineCounter = 0;;lLineCounter++)
        {
            memcpy( lpResult,  lpWorkSpace, k_lMaxBytesPerLine);
            lpWorkSpace += k_lMaxBytesPerLine;
            lpResult += k_lMaxBytesPerLine;
            memcpy( lpResult, lpCrLf, 4);
            lpResult += 4;
            if(!(lLineCounter<lCompleteLines)) break;
        }

        lBytesRemaining = lWorkspaceCounter - (lCompleteLines * k_lMaxBytesPerLine);
        if (lBytesRemaining > 0)
        {
            memcpy(lpResult, lpWorkSpace, lBytesRemaining);
        }
            delete [] bytWorkspace;
            buffer = QString::fromUtf16((ushort *) bytResult).toStdString();

    }

}

void keygen::concatenate()
{
   buffer = serial_machine + buffer;
}


void keygen::MD5()
{
    QByteArray bt_buffer_temp(buffer.c_str());
    QString qst_buffer_temp = QCryptographicHash::hash(bt_buffer_temp, QCryptographicHash::Md5).toHex();
    buffer = qst_buffer_temp.toStdString().c_str();
}

QString keygen::hexdigest()
{
    return QString::fromStdString(buffer);
}

void keygen::UpperCase()
{
    std::transform(buffer.begin(), buffer.end(), buffer.begin(), static_cast<int(*)(int)>(std::toupper));
}

QString serial_generate(const QString &serial)
{
    keygen key = keygen(serial);
    return key.hexdigest();
}

void keygen::initialize64()
{
    m_bytIndex[0] = 65; //Asc["A"]
    m_bytIndex[1] = 66;//Asc["B"]
    m_bytIndex[2] = 67; //Asc["C"]
    m_bytIndex[3] = 68; //Asc["D"]
    m_bytIndex[4] = 69; //Asc["E"]
    m_bytIndex[5] = 70; //Asc["F"]
    m_bytIndex[6] = 71; //Asc["G"]
    m_bytIndex[7] = 72; //Asc["H"]
    m_bytIndex[8] = 73; //Asc["I"]
    m_bytIndex[9] = 74; //Asc["J"]
    m_bytIndex[10] = 75; //Asc["K"]
    m_bytIndex[11] = 76;//Asc["L"]
    m_bytIndex[12] = 77; //Asc["M"]
    m_bytIndex[13] = 78; //Asc["N"]
    m_bytIndex[14] = 79; //Asc["O"]
    m_bytIndex[15] = 80; //Asc["P"]
    m_bytIndex[16] = 81; //Asc["Q"]
    m_bytIndex[17] = 82; //Asc["R"]
    m_bytIndex[18] = 83; //Asc["S"]
    m_bytIndex[19] = 84; //Asc["T"]
    m_bytIndex[20] = 85; //Asc["U"]
    m_bytIndex[21] = 86; //Asc["V"]
    m_bytIndex[22] = 87; //Asc["W"]
    m_bytIndex[23] = 88; //Asc["X"]
    m_bytIndex[24] = 89; //Asc["Y"]
    m_bytIndex[25] = 90; //Asc["Z"]
    m_bytIndex[26] = 97; //Asc["a"]
    m_bytIndex[27] = 98; //Asc["b"]
    m_bytIndex[28] = 99; //Asc["c"]
    m_bytIndex[29] = 100; //Asc["d"]
    m_bytIndex[30] = 101; //Asc["e"]
    m_bytIndex[31] = 102; //Asc["f"]
    m_bytIndex[32] = 103; //Asc["g"]
    m_bytIndex[33] = 104; //Asc["h"]
    m_bytIndex[34] = 105; //Asc["i"]
    m_bytIndex[35] = 106; //Asc["j"]
    m_bytIndex[36] = 107; //Asc["k"]
    m_bytIndex[37] = 108; //Asc["l"]
    m_bytIndex[38] = 109; //Asc["m"]
    m_bytIndex[39] = 110; //Asc["n"]
    m_bytIndex[40] = 111; //Asc["o"]
    m_bytIndex[41] = 112; //Asc["p"]
    m_bytIndex[42] = 113; //Asc["q"]
    m_bytIndex[43] = 114; //Asc["r"]
    m_bytIndex[44] = 115; //Asc["s"]
    m_bytIndex[45] = 116; //Asc["t"]
    m_bytIndex[46] = 117; //Asc["u"]
    m_bytIndex[47] = 118; //Asc["v"]
    m_bytIndex[48] = 119; //Asc["w"]
    m_bytIndex[49] = 120; //Asc["x"]
    m_bytIndex[50] = 121; //Asc["y"]
    m_bytIndex[51] = 122; //Asc["z"]
    m_bytIndex[52] = 48; //Asc["0"]
    m_bytIndex[53] = 49; //Asc["1"]
    m_bytIndex[54] = 50; //Asc["2"]
    m_bytIndex[55] = 51; //Asc["3"]
    m_bytIndex[56] = 52; //Asc["4"]
    m_bytIndex[57] = 53; //Asc["5"]
    m_bytIndex[58] = 54; //Asc["6"]
    m_bytIndex[59] = 55; //Asc["7"]
    m_bytIndex[60] = 56; //Asc["8"]
    m_bytIndex[61] = 57; //Asc["9"]
    m_bytIndex[62] = 43; //Asc["+"]
    m_bytIndex[63] = 47; //Asc["/"]
    m_bytReverseIndex[65] = 0; //Asc["A"]
    m_bytReverseIndex[66] = 1; //Asc["B"]
    m_bytReverseIndex[67] = 2; //Asc["C"]
    m_bytReverseIndex[68] = 3; //Asc["D"]
    m_bytReverseIndex[69] = 4; //Asc["E"]
    m_bytReverseIndex[70] = 5; //Asc["F"]
    m_bytReverseIndex[71] = 6; //Asc["G"]
    m_bytReverseIndex[72] = 7; //Asc["H"]
    m_bytReverseIndex[73] = 8; //Asc["I"]
    m_bytReverseIndex[74] = 9; //Asc["J"]
    m_bytReverseIndex[75] = 10; //Asc["K"]
    m_bytReverseIndex[76] = 11; //Asc["L"]
    m_bytReverseIndex[77] = 12; //Asc["M"]
    m_bytReverseIndex[78] = 13; //Asc["N"]
    m_bytReverseIndex[79] = 14; //Asc["O"]
    m_bytReverseIndex[80] = 15; //Asc["P"]
    m_bytReverseIndex[81] = 16; //Asc["Q"]
    m_bytReverseIndex[82] = 17; //Asc["R"]
    m_bytReverseIndex[83] = 18; //Asc["S"]
    m_bytReverseIndex[84] = 19; //Asc["T"]
    m_bytReverseIndex[85] = 20; //Asc["U"]
    m_bytReverseIndex[86] = 21; //Asc["V"]
    m_bytReverseIndex[87] = 22; //Asc["W"]
    m_bytReverseIndex[88] = 23; //Asc["X"]
    m_bytReverseIndex[89] = 24; //Asc["Y"]
    m_bytReverseIndex[90] = 25; //Asc["Z"]
    m_bytReverseIndex[97] = 26; //Asc["a"]
    m_bytReverseIndex[98] = 27; //Asc["b"]
    m_bytReverseIndex[99] = 28; //Asc["c"]
    m_bytReverseIndex[100] = 29; //Asc["d"]
    m_bytReverseIndex[101] = 30; //Asc["e"]
    m_bytReverseIndex[102] = 31; //Asc["f"]
    m_bytReverseIndex[103] = 32; //Asc["g"]
    m_bytReverseIndex[104] = 33; //Asc["h"]
    m_bytReverseIndex[105] = 34; //Asc["i"]
    m_bytReverseIndex[106] = 35; //Asc["j"]
    m_bytReverseIndex[107] = 36; //Asc["k"]
    m_bytReverseIndex[108] = 37; //Asc["l"]
    m_bytReverseIndex[109] = 38; //Asc["m"]
    m_bytReverseIndex[110] = 39; //Asc["n"]
    m_bytReverseIndex[111] = 40; //Asc["o"]
    m_bytReverseIndex[112] = 41; //Asc["p"]
    m_bytReverseIndex[113] = 42; //Asc["q"]
    m_bytReverseIndex[114] = 43; //Asc["r"]
    m_bytReverseIndex[115] = 44; //Asc["s"]
    m_bytReverseIndex[116] = 45; //Asc["t"]
    m_bytReverseIndex[117] = 46; //Asc["u"]
    m_bytReverseIndex[118] = 47; //Asc["v"]
    m_bytReverseIndex[119] = 48; //Asc["w"]
    m_bytReverseIndex[120] = 49; //Asc["x"]
    m_bytReverseIndex[121] = 50; //Asc["y"]
    m_bytReverseIndex[122] = 51; //Asc["z"]
    m_bytReverseIndex[48] = 52; //Asc["0"]
    m_bytReverseIndex[49] = 53; //Asc["1"]
    m_bytReverseIndex[50] = 54; //Asc["2"]
    m_bytReverseIndex[51] = 55; //Asc["3"]
    m_bytReverseIndex[52] = 56; //Asc["4"]
    m_bytReverseIndex[53] = 57; //Asc["5"]
    m_bytReverseIndex[54] = 58; //Asc["6"]
    m_bytReverseIndex[55] = 59; //Asc["7"]
    m_bytReverseIndex[56] = 60; //Asc["8"]
    m_bytReverseIndex[57] = 61; //Asc["9"]
    m_bytReverseIndex[43] = 62; //Asc["+"]
    m_bytReverseIndex[47] = 63; //Asc["/"]

}
