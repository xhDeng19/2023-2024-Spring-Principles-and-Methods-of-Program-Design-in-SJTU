#include <iostream>
using namespace std;

// global variables
int regexp_len = 0, text_len = 0;

// function prototypes
bool match(char *regexp, char *text);
bool matchstart(char *regexp, char *text);
bool matchstar(int c, char *regexp, char *text);


/*
* match : 检查text中是否存在子串匹配regexp描述的格式
*/
bool match(char *regexp, char *text)
{
    if(regexp[0] == '^')
    {
        regexp++;
        return matchstart(regexp, text);
    }

    while(text[0] != '\0')
    {
        if(matchstart(regexp, text))
            return true;

        text++;
    }

    return false;
}

/*
* matchstart : 检查text的开头子串是否匹配regexp
*/
bool matchstart(char *regexp, char *text)
{
    char c;

    if(regexp[0] == '$')
    {
        return (text[0] == '\0');
    }

    if(regexp[0] == '\0')
        return true;
    else if(text[0] == '\0' && regexp[1] == '*' && regexp[2] == '\0')
        return true;
    else if(text[0] == '\0')
        return false;

    if(regexp[1] == '*')
    {
        c = regexp[0];
        regexp = regexp + 2;
        return matchstar(c, regexp, text);
    }


    if(regexp[0] == '.')
    {
        regexp++;
        text++;

        return matchstart(regexp, text);
    }

    if(regexp[0] != text[0])
        return false;
    else
    {
        regexp++;
        text++;

        return matchstart(regexp, text);
    }
}

/*
* matchstar : 检查text的开头子串是否匹配表达式 c*regexp
*/
bool matchstar(int c, char *regexp, char *text)
{

    if(c == '.')
    {
        while(text[0] != '\0')
        {
            if(matchstart(regexp, text))
                return true;

            text++;
        }
    }

    while(text[0] == c)
        text++;

    return matchstart(regexp, text);
}

/*
* This program uses Regular Expression to find a certain substring in a given string.
*/
int main(){
    char reg_exp[22];
    int num;
    cin >> reg_exp;
    cin >> num;

    char text[num][1000];
    bool ans[num];

    for(int i = 0; i < num; i++)
    {
        cin >> text[i];
        ans[i] = match(reg_exp, text[i]);
    }

    for(int i = 0; i < num; i++)
    {
        if(ans[i])
            cout << "matched" << endl;
        else
            cout << "unmatched" << endl;
    }

    return 0;
}
