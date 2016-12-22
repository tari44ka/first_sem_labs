#include <iostream>
#include <regex.h>

#define DATE_PATTERN "[1-9]\.[1-9]|[10,11,12]\.[1-9]\d{3}"
void findDate()
{
    regex_t dateRegex;
    int error = regcomp (&dateRegex, DATE_PATTERN, dateRegex);
    if (error != 0) {
        std::cout << "error in create regex" << std::endl;
            char buff[512];
            regerror(error, &dateRegex, buff, sizeof(buff));
            std::cout << buff;
    }
    regmatch_t matcher;

    do{
        char string[100];
        fgets(string, 100, stdin);

        error = regexec (&dateRegex, string, 0, &matcher, 0);
        if (error == 0)
        {

        } else {
            char buff[512];
            std::cout << "error in match" << std::endl;
            regerror(error, &dateRegex, buff, sizeof(buff));
            std::cout << errbuf << std::endl;
        }
    }while (command != 0);
}
int main()
{
    /*
    // создать регулярное выражение
    int regcomp (regex_t *restrict preg, const char *restrict pattern, REG_ICASE);
    // применить регулярное выражение к строке
    int regexec (const regex_t *restrict preg, const char *restrict string, size_t nmatch, regmatch_t pmatch [restrict], int eflags);
    // очистить память после использования регулярного выражения
    void regfree (regex_t *preg);
    // соознать ошибки
    size_t regerror (int errcode, const regex_t *restrict preg, char *restrict errbuf, size_t errbuf_size);
*/

    return 0;
}
