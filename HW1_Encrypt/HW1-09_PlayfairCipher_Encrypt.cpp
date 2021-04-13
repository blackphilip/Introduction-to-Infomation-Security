#include <string>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool vectorCheck(vector<char> tmp, char input)
{
    for (int i = 0; i < tmp.size(); i++)
    {
        if (tmp[i] == input)
            return false;
    }
    return true;
}

int findIndex(vector<char> tmp, char input)
{
    int index;
    for (int i = 0; i < tmp.size(); i++)
    {
        if (tmp[i] == input)
            index = i;
    }
    return index;
}

int main()
{
    string plaintext, ciphertext, keyText;

    while (cin >> keyText)
    {
        cin >> plaintext;

        vector<char> tmpKey, tmpPlain, tmpCypher;
        ciphertext = "";

        //Key
        for (int i = 0; i < keyText.length(); i++)
        {
            if (isalpha(keyText[i]))
            {
                char charTmp = toupper(keyText[i]);
                if (charTmp == 'J')
                {
                    charTmp = 'I';
                }
                if (vectorCheck(tmpKey, toupper(keyText[i])))
                {
                    tmpKey.push_back(toupper(keyText[i]));
                }
            }
        }

        for (char i = 'A'; i <= 'Z'; i++)
        {
            char charTmp = i;
            if (charTmp == 'J')
            {
                charTmp = 'I';
            }
            if (vectorCheck(tmpKey, charTmp))
            {
                tmpKey.push_back(charTmp);
            }
        }

        //plain
        queue<char> teamTmp;
        for (int i = 0; i < plaintext.length(); i++)
        {
            if (isalpha(plaintext[i]))
            {
                if (teamTmp.empty())
                    teamTmp.push(toupper(plaintext[i]));
                else
                {
                    if (toupper(plaintext[i]) == teamTmp.front())
                    {
                        teamTmp.push('X');
                        i--;
                    }
                    else
                        teamTmp.push(toupper(plaintext[i]));
                }
                if (teamTmp.size() == 2 || i == plaintext.length() - 1)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        tmpPlain.push_back(teamTmp.front());
                        teamTmp.pop();
                        if (teamTmp.empty())
                            break;
                    }
                }
            }
        }

        if (tmpPlain.size() % 2 == 1)
            tmpPlain.push_back('Z');

        //cypher

        for (int i = 0; i < tmpPlain.size(); i += 2)
        {
            queue<char> tmp;
            for (int j = 0; j < 2; j++)
            {
                tmp.push(tmpPlain[i + j]);
            }

            int first = findIndex(tmpKey, tmp.front()), second = findIndex(tmpKey, tmp.back());
            if (first % 5 == second % 5)
            {
                if ((first + 5) >= tmpKey.size())
                    first %= 5;
                else
                    first += 5;
                if ((second + 5) >= tmpKey.size())
                    second %= 5;
                else
                    second += 5;

                tmpCypher.push_back(tmpKey[first]);
                tmpCypher.push_back(tmpKey[second]);
            }
            else if (first / 5 == second / 5)
            {
                if ((first + 1) % 5 == 0)
                    first -= 4;
                else
                    first++;
                if ((second + 1) % 5 == 0)
                    second -= 4;
                else
                    second++;

                tmpCypher.push_back(tmpKey[first]);
                tmpCypher.push_back(tmpKey[second]);
            }
            else
            {
                int ftmp = first, stmp = second;
                if (first % 5 < second % 5)
                {
                    int distance = second % 5 - first % 5;
                    ftmp += distance;
                    stmp -= distance;
                }
                else
                {
                    int distance = first % 5 - second % 5;
                    ftmp -= distance;
                    stmp += distance;
                }
                tmpCypher.push_back(tmpKey[ftmp]);
                tmpCypher.push_back(tmpKey[stmp]);
            }
        }

        for (int i = 0; i < tmpCypher.size(); i++)
            ciphertext += tmpCypher[i];

        cout << ciphertext << endl;
    }
}
