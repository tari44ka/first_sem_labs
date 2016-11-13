/*
2.1. Пользователь вводит относительный путь до некоторого файла/каталога. Построить поддерево от него вниз. 
2.2. На каждом уровене дерева каталогов найти максимальный по размеру (размер каталога - есть сумма его составляющих)
*/
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <vector>

#define OS Ubuntu
#if OS == Ubuntu
#define FILE_SEP "/"
#elif
#define FILE_SEP "\"
#endif

using std::vector;
// struct for element information
struct TreeElement
{
    char* path;
    long size;
};


long recursive_solution(vector<TreeElement> &elements, char* path, int level);
void klp_print(char* path, char* name);

void first_problem(char* path)
{
    struct stat buf;
    stat(path, &buf);
    if (buf.st_mode & S_IFDIR)
    {
        klp_print(path, "");
    }
    else
    {
        printf("This is not directory\n");
    }
}

void klp_print(char* path, char* name)
{
    printf("%s\n", name);
    struct stat buf;
    stat(path, &buf);
    if (buf.st_mode & S_IFDIR)
    {
        DIR *dir = opendir(path);
        struct dirent *ent;
        while ((ent = readdir (dir)) != NULL) {
                if (ent->d_name[0] != '.')
                {
                    char *str = (char*) malloc((strlen(path) + strlen(ent->d_name) + 2) * sizeof(char) );
                    strcpy(str, path);
                    str[strlen(path)] = '\0';
                    strcat(str, FILE_SEP);
                    strcat(str, ent->d_name);

                    char* name_str = (char*)malloc((strlen(name) + strlen(ent->d_name) + 2)*sizeof(char));
                    strcpy(name_str, name);
                    name_str[strlen(path)] = '\0';
                    strcat(name_str, FILE_SEP);
                    strcat(name_str, ent->d_name);
                    klp_print(str, name_str);
                    free(str);
                    free(name_str);
                }
        }
        closedir (dir);
    }


}
void second_problem(char* path)
{
    vector<TreeElement> elements;
    TreeElement nothing;
    nothing.path = (char*) malloc(1 * sizeof(char));
    strcpy(nothing.path ,"");
    nothing.size = 0;
    elements.push_back(nothing);
    recursive_solution(elements, path, 0);
    for (int i = 0; i < elements.size(); ++i)
    {
        printf("%d - %s (%d)\n", i, elements[i].path, elements[i].size);
    }
}

long recursive_solution(vector<TreeElement> &elements, char* path, int level)
{
    if (elements.size() <= level)
    {
        TreeElement nothing;
        nothing.path = (char*) malloc(1 * sizeof(char));
        strcpy(nothing.path ,"");
        nothing.size = 0;
        elements.push_back(nothing);
    }
    long size = 0;
    struct stat buf;
    stat(path, &buf);
    if (buf.st_mode & S_IFDIR)
    {
        DIR *dir = opendir(path);
        struct dirent *ent;
        while ((ent = readdir (dir)) != NULL) {
                if (ent->d_name[0] != '.')
                {
                    char *str = (char*) malloc((strlen(path) + strlen(ent->d_name)) * sizeof(char) + 3);
                    strcpy(str, path);
                    str[strlen(path)] = '\0';
                    strcat(str, FILE_SEP);
                    strcat(str, ent->d_name);
                    size += recursive_solution(elements, str, level+1);
                    free(str);
                }
        }
        closedir (dir);
    }
    else
    {
        size = buf.st_size;
    }

    if (elements[level].size < size)
    {
        elements[level].size = size;
        free( elements[level].path);
        elements[level].path = new char[strlen(path) + 1];
        strcpy(elements[level].path, path);
    }
    return size;
}



int main(int argc, char* argv[])
{
    if (argc < 1)
    {
        printf("You have to enter path");
        return 0;
    }
    printf("Please, choose number of question: \n");
    printf(" 1 - create tree from catalog\n");
    printf(" 2 - find max object on each tree-level\n");
    printf(" Remember your path: %s\n", argv[1]);
    int question;
    scanf("%d", &question);

    switch(question)
    {
        case 1:
        {
            first_problem(argv[1]);
            break;
        }
        case 2:
        {
            second_problem(argv[1]);
            break;
        }
        default:
            printf("invalid operation number");
    }


    return 0;
}


