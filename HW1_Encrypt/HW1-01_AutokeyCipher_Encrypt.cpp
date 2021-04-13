#include <string>
#include <iostream>

using namespace std;

int main()
{
    string plaintext, ciphertext, keyText, key;

    while (cin >> key)
    {
        cin >> plaintext;
        string temp=key+plaintext;
        ciphertext = plaintext;
        keyText = plaintext;
        for (int i = 0; i < plaintext.length(); i++)
            keyText[i] = tolower(temp[i]);

        for (int i = 0; i < plaintext.length(); i++)
        {
            char c = plaintext[i];

            plaintext[i] = tolower(c);

            ciphertext[i] = (char)(((int)plaintext[i] - 97 + (int)keyText[i] - 97) % 26 + 97);
        }

        cout << ciphertext << endl;
    }
}
