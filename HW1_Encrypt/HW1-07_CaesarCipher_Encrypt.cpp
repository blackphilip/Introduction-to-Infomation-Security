#include <string>
#include <iostream>

using namespace std;

int main()
{
    string plaintext, ciphertext;
    int shift = 9;

    while (cin >> plaintext)
    {

        ciphertext = plaintext;
        for (int i = 0; i < plaintext.length(); i++)
        {
            char c = plaintext[i];
            if (isalpha(c))
            {
                plaintext[i] = tolower(c);
                ciphertext[i] = (char)(((int)plaintext[i] - 97 + 9) % 26 + 97);
            }
            else
            {
                ciphertext[i] = c;
            }
        }

        cout << ciphertext << endl;
    }
}
