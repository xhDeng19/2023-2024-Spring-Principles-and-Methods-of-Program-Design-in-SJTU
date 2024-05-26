#include <iostream>
#include <cctype> // Use tolower function

using namespace std;

const int MAX_WORDS = 999; // Maximum number of words in the given sentence

/*
* Transform the string allwords and each string in words[] into lower case
* stored in wordsLower[].
*/
void strLower(string (&words)[MAX_WORDS], string (&wordsLower)[MAX_WORDS],
              int wordsLen, string & allwords)
{
    string word = "";
    for (int i = 0; i < wordsLen; i++)
    {
        for (int j = 0; j < int(words[i].length()); j++)
        {
            word += tolower(words[i][j]);
        }
        wordsLower[i] = word;
        word = "";
    }

    for (int i = 0; i < int(allwords.length()); i++)
    {
        allwords[i] = tolower(allwords[i]);
    }
}

/*
* Separate all the words in a string sentence into a string array words[].
*/
void toWords(string sentence, string (&words)[MAX_WORDS], string & allWords, int & wordsLen)
{
    int i = 0;
    size_t posBegin = 0, posEnd = sentence.find(" ");

    while(posEnd != string::npos)
    {
        words[i] = sentence.substr(posBegin, posEnd - posBegin);

        allWords += words[i];
        i++;
        posBegin = posEnd + 1;
        posEnd = sentence.find(" ", posBegin);
    }

    words[i] = sentence.substr(posBegin);
    allWords += words[i];
    wordsLen = i + 1;
}

/*
* Determine whether a given string is a palindrome.
*/
bool isPalindrome(string str)
{
    int sLen = str.length();
    int mid = sLen / 2;

    for (int i = 0; i <= mid; i++)
    {
        if (str[i] != str[sLen - i - 1])
            return false;
    }
    return true;
}

/*
* Delete all the palindrome word in a given sentence.
* Remain one blank space between each words.
*/
void delPalindrome(string (&words)[MAX_WORDS], string (&wordsLower)[MAX_WORDS], int wordsLen)
{
    for (int i = 0; i < wordsLen; i++)
    {
        if (isPalindrome(wordsLower[i]))
            words[i] = "";
    }

    for (int i = 0; i < wordsLen - 1; i++)
    {
        if (words[i] != "")
            cout << words[i] << " ";
    }
    cout << words[wordsLen - 1];
}


/*
* This program is focused on palindrome sentences and words.
* It will output "No!" if the input is a palindrome sentence.
* It will delete all the palindrome word in the input sentence and output.
*/
int main()
{
    string sentence, words[MAX_WORDS], wordsLower[MAX_WORDS], allWords = "";
    int wordsLen;
    getline(cin, sentence);

    toWords(sentence, words, allWords, wordsLen);
    strLower(words, wordsLower, wordsLen, allWords);

    if (isPalindrome(allWords))
        cout << "No!" << endl;
    else
        delPalindrome(words, wordsLower, wordsLen);

    return 0;
}
