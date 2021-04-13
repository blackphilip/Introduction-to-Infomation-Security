#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string plaintext, ciphertext, keyText;

    while (getline(cin, keyText))
    {
        getline(cin, plaintext);
        
        vector<char> tmpPlain;
        ciphertext = "";
        for (int i = 0; i < plaintext.length(); i++)
        {
            if (isalpha(plaintext[i]))
                tmpPlain.push_back(plaintext[i]);
        }

        int tableHeight = tmpPlain.size() / keyText.length();
        if (tmpPlain.size() % keyText.length() != 0)
            tableHeight++;

        vector<vector<char>> tmpTable;
        for (int i = 0, k = 0; i < tableHeight; i++)
        {
            vector<char> tmp;
            if (k < plaintext.length())
                for (int j = 0; j < keyText.length(); j++)
                {
                    tmp.push_back(tolower(tmpPlain[k]));
                    
                    k++;
                }
            tmpTable.push_back(tmp);
            
        }

        for (int i = 1; i <= keyText.length(); i++)
        {
            int index = keyText.find((char)(48 + i), 0);
            
            for (int j = 0; j < tmpTable.size(); j++)
            {
                for (int k = 0; k < tmpTable[0].size(); k++)
                {
                    if (k == index && isalpha(tmpTable[j][k]))
                        ciphertext += tmpTable[j][k];
                }
            }
        }

        
        cout << ciphertext << endl;
    }
}
