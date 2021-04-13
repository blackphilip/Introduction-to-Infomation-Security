#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string plaintext, ciphertext;

    int key;
    while (cin >> key)
    {
        cin >> plaintext;
        ciphertext = "";
        bool railFlag = true;
        vector<int> tmp;
        for (int i = 0; i < plaintext.length(); i++)
            tmp.push_back(0);

        for (int i = 0, j = 0; i < plaintext.length(); i++)
        {
            tmp[i] = j;
            if (railFlag)
            {
                j++;
                if (j == key - 1)
                    railFlag = !railFlag;
            }
            else
            {
                j--;
                if (j == 0)
                    railFlag = !railFlag;
            }
        }

        for (int i = 0; i < key; i++)
        {
            for(int j=0;j<plaintext.length();j++)
            {
                if(tmp[j]==i)
                {
                    ciphertext+=plaintext[j];
                }
            }
        }
        cout << ciphertext << endl;
    }
}
