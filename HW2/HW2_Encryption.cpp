#include <string>
#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

/*
Main Encryption
  PlainText 64bits
  InitialPermutation
  L0  R0 32bits
  L1=R0  R1=L0 XOR FeistalFunc(R0)
  ...
  Ln=Rn-1 Rn=Ln-1 XOR FeistalFunc(Rn-1)
  ...
  L16=R15  R16=L15 XOR FeistalFunc(R15)
  FinalPermutation
  CipherText
/*

/*
FeistalFunc
  R_input 32bits
  Exp32to48(R_input) XOR SubKey
  S-Box correspond
  P_func
  return 32bits
*/

/*
SubKey
  Key 64bits
  PC-1 get L0 R0 28bits
               L0 R0 
  shift_left_1 L1 R1 -> PC-2 ->SubKey1
  shift_left_1 L2 R2 -> PC-2 ->SubKey2
  shift_left_2 L3 R3 -> PC-2 ->SubKey3
  shift_left_2 L4 R4 -> PC-2 ->SubKey4
  shift_left_2 L5 R5 -> PC-2 ->SubKey5
  shift_left_2 L6 R6 -> PC-2 ->SubKey6
  shift_left_2 L7 R7 -> PC-2 ->SubKey7
  shift_left_2 L8 R8 -> PC-2 ->SubKey8
  shift_left_1 L9 R9 -> PC-2 ->SubKey9
  shift_left_2 L10 R10 -> PC-2 ->SubKey10
  shift_left_2 L11 R11 -> PC-2 ->SubKey11
  shift_left_2 L12 R12 -> PC-2 ->SubKey12
  shift_left_2 L13 R13 -> PC-2 ->SubKey13
  shift_left_2 L14 R14 -> PC-2 ->SubKey14
  shift_left_2 L15 R15 -> PC-2 ->SubKey15
  shift_left_1 L16 R16 -> PC-2 ->SubKey16 
*/

class DES_Encryption
{
public:
  DES_Encryption(string, string);
  string keys[16];
  string cyphertext = "";

private:
  string keyRaw;
  string plaintextRaw;
  void GenerateKey(string);
  string Shift(string, int);
  void DES();
  string XOR(string, string);
  int Bin2Dec(string);
};
string Dec2Bin(int);
DES_Encryption::DES_Encryption(string keyInput, string plaintext)
{
  keyRaw = keyInput;
  plaintextRaw = plaintext;
  GenerateKey(keyRaw);
  DES();
}
void DES_Encryption::GenerateKey(string input)
{
  //pc-1 get 28bits
  int pc1[56] = {
      57, 49, 41, 33, 25, 17, 9,
      1, 58, 50, 42, 34, 26, 18,
      10, 2, 59, 51, 43, 35, 27,
      19, 11, 3, 60, 52, 44, 36,
      63, 55, 47, 39, 31, 23, 15,
      7, 62, 54, 46, 38, 30, 22,
      14, 6, 61, 53, 45, 37, 29,
      21, 13, 5, 28, 20, 12, 4};

  string pc1Result = "";

  for (int i = 0; i < 56; i++)
  {
    pc1Result += input[pc1[i] - 1];
  }
  //cout << pc1Result << endl;
  string C = pc1Result.substr(0, 28);
  string D = pc1Result.substr(28, 28);

  //key generate
  for (int i = 1; i <= 16; i++)
  {
    if (i == 1 || i == 2 || i == 9 || i == 16)
    {
      //shift=1
      C = Shift(C, 1);
      D = Shift(D, 1);
    }
    else
    {
      //shift=2
      C = Shift(C, 2);
      D = Shift(D, 2);
    }
    //cout<<C<<endl<<D<<endl<<endl;
    string CDCombined = C + D;
    string tempKey = "";
    //pc2 to 48bits
    int pc2[48] = {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32};

    for (int i = 0; i < 48; i++)
    {
      tempKey += CDCombined[pc2[i] - 1];
    }
    keys[i - 1] = tempKey;
  }
}
string DES_Encryption::Shift(string input, int num)
{
  string shifted = "";
  string temp = input;
  switch (num)
  {
  case 1:
    for (int i = 1; i < 28; i++)
    {
      shifted += temp[i];
    }
    shifted += temp[0];
    temp = shifted;
    break;
  case 2:
    for (int i = 0; i < 2; i++)
    {
      for (int j = 1; j < 28; j++)
      {
        shifted += temp[j];
      }
      shifted += temp[0];
      temp = shifted;
      shifted = "";
    }
    break;
  }
  return temp;
}

void DES_Encryption::DES()
{
  // Initial Permutation
  string plainTemp = "";
  int IP[64] = {
      58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7};

  for (int i = 0; i < 64; i++)
    plainTemp += plaintextRaw[IP[i] - 1];

  string L = plainTemp.substr(0, 32);
  string R = plainTemp.substr(32, 32);

  //Iterative
  for (int i = 0; i < 16; i++)
  {
    //Feistal Function
    int exp[48] = {
        32, 1, 2, 3, 4, 5, 4, 5,
        6, 7, 8, 9, 8, 9, 10, 11,
        12, 13, 12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21, 20, 21,
        22, 23, 24, 25, 24, 25, 26, 27,
        28, 29, 28, 29, 30, 31, 32, 1};

    string REX = "";
    for (int j = 0; j < 48; j++)
      REX += R[exp[j] - 1];

    string xorREX = XOR(REX, keys[i]);
    string RResult = "";

    for (int j = 0; j < 8; j++)
    {

      string rowTemp = xorREX.substr(j * 6, 1) + xorREX.substr(j * 6 + 5, 1);
      int row = Bin2Dec(rowTemp);
      string colTemp = xorREX.substr(j * 6 + 1, 4);
      int col = Bin2Dec(colTemp);

      int val = 0;
      int sbox[8][4][16] =
          {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
            0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
            4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
            15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
           {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
            3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
            0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
            13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
           {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
            13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
            13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
            1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
           {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
            13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
            10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
            3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
           {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
            14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
            4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
            11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
           {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
            10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
            9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
            4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
           {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
            13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
            1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
            6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
           {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
            1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
            7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
            2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

      val = sbox[j][row][col];

      //int val = substition_boxes[i][row][col];
      RResult += Dec2Bin(val);
    }

    string afterPBox = "";
    int PBox[32] = {
        16, 7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9,
        19, 13, 30, 6, 22, 11, 4, 25};

    for (int j = 0; j < 32; j++)
      afterPBox += RResult[PBox[j] - 1];

    xorREX = XOR(afterPBox, L);

    L = xorREX;
    if (i < 15)
    {
      string temp = R;
      R = xorREX;
      L = temp;
    }
  }

  string finalText = L + R;

  int FP[64] = {
      40, 8, 48, 16, 56, 24, 64, 32,
      39, 7, 47, 15, 55, 23, 63, 31,
      38, 6, 46, 14, 54, 22, 62, 30,
      37, 5, 45, 13, 53, 21, 61, 29,
      36, 4, 44, 12, 52, 20, 60, 28,
      35, 3, 43, 11, 51, 19, 59, 27,
      34, 2, 42, 10, 50, 18, 58, 26,
      33, 1, 41, 9, 49, 17, 57, 25};

  for (int i = 0; i < 64; i++)
    cyphertext += finalText[FP[i] - 1];
}
string DES_Encryption::XOR(string a, string b)
{
  string result = "";
  int size = b.size();
  for (int i = 0; i < size; i++)
  {
    if (a[i] != b[i])
      result += "1";
    else
      result += "0";
  }
  return result;
}
string Dec2Bin(int decimal)
{
  string binary;
  while (decimal != 0)
  {
    binary = (decimal % 2 == 0 ? "0" : "1") + binary;
    decimal = decimal / 2;
  }
  while (binary.length() < 4)
    binary = "0" + binary;

  return binary;
}
int DES_Encryption::Bin2Dec(string binary)
{
  int decimal = 0;
  int counter = 0;
  int size = binary.length();
  for (int i = size - 1; i >= 0; i--)
  {
    if (binary[i] == '1')
      decimal += pow(2, counter);

    counter++;
  }
  return decimal;
}
string Bin2Hex(string str)
{
  string strTemp = "";
  for (int k = 0; k < 16; k++)
  {
    string st = str.substr(k * 4, 4);
    if (st == "0000")
      st = "0";
    else if (st == "0001")
      st = "1";
    else if (st == "0010")
      st = "2";
    else if (st == "0011")
      st = "3";
    else if (st == "0100")
      st = "4";
    else if (st == "0101")
      st = "5";
    else if (st == "0110")
      st = "6";
    else if (st == "0111")
      st = "7";
    else if (st == "1000")
      st = "8";
    else if (st == "1001")
      st = "9";
    else if (st == "1010")
      st = "a";
    else if (st == "1011")
      st = "b";
    else if (st == "1100")
      st = "c";
    else if (st == "1101")
      st = "d";
    else if (st == "1110")
      st = "e";
    else if (st == "1111")
      st = "f";

    strTemp += st;
  }
  return strTemp;
}

int main()
{
  string keyIn;

  while (getline(cin, keyIn))
  {
    //Key transform
    unsigned long long keyTemp;
    keyTemp = stoull(keyIn, 0, 16);
    bitset<64> k2b(keyTemp);
    string keyString = k2b.to_string();

    //PlainText transform
    string plaintext;
    getline(cin, plaintext);
    if (plaintext.size() % 8 != 0)
    {
      for (int i = 8 - plaintext.size() % 8; i >= 1; i--)
        plaintext += " ";
    }

    //vector<string> plaintexts;

    if (plaintext.size() / 8 != 1)
    {
      string result = "";
      for (int i = 0; i < plaintext.size() / 8; i++)
      {
        string temp;
        temp = plaintext.substr(i * 8, 8);
        //plaintexts.push_back(temp);
        string plainString;
        unsigned long long plainTemp;
        stringstream ss;
        for (const auto &item : temp)
          ss << hex << int(item);

        plainString = ss.str();
        plainTemp = stoull(plainString, 0, 16);
        bitset<64> p2b(plainTemp);
        string inputString = p2b.to_string();
        DES_Encryption des(keyString, inputString);

        result += Bin2Hex(des.cyphertext);
      }
      cout << result << endl;
    }
    else
    {
      string plainString;
      unsigned long long plainTemp;
      stringstream ss;
      for (const auto &item : plaintext)
        ss << hex << int(item);

      plainString = ss.str();
      plainTemp = stoull(plainString, 0, 16);
      bitset<64> p2b(plainTemp);
      string inputString = p2b.to_string();
      DES_Encryption des(keyString, inputString);

      string result = Bin2Hex(des.cyphertext);
      cout << result << endl;
    }
  }
}
