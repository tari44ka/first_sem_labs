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
#include <iostream>

#define OS Ubuntu
#if OS == Ubuntu
#define FILE_SEP "/"
#elif
#define FILE_SEP "\\"
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
        char * empty = new char[1];
        empty[0] = '\0';
        klp_print(path, empty);
        delete [] empty;
    }
    else
    {
        std::cout << "This is not directory" << std::endl;
    }
}

void klp_print(char* path, char* name)
{
    std::cout << name << std::endl;
    struct stat buf;
    stat(path, &buf);
    if (buf.st_mode & S_IFDIR)
    {
        DIR *dir = opendir(path);
	if (dir == NULL)
		return;
        struct dirent *ent;
        while ((ent = readdir (dir)) != NULL) {
                if (ent->d_name[0] != '.')
                {
                    //todo: сделать нормальные имена
                    char *str = new char[strlen(path) + strlen(ent->d_name) + 2];
                    strcpy(str, path);
                    str[strlen(path)] = '\0';
                    strcat(str, FILE_SEP);
                    strcat(str, ent->d_name);

                    char* name_str = new char[strlen(name) + strlen(ent->d_name) + 2];
                    strcpy(name_str, name);
                    name_str[strlen(name)] = '\0';
                    strcat(name_str, FILE_SEP);
                    strcat(name_str, ent->d_name);
                    klp_print(str, name_str);
                    delete [] str;
                    delete [] name_str;
                }
        }
        closedir (dir);
    }


}
void second_problem(char* path)
{
    vector<TreeElement> elements;
    TreeElement nothing;
    nothing.path = new char[1];
    nothing.path[0] = '\0';
    nothing.size = 0;
    elements.push_back(nothing);
    recursive_solution(elements, path, 0);
    for (int i = 0; i < elements.size(); ++i)
    {
        std::cout << "level - " << i;
        std::cout << "  "  << elements[i].path;
        std::cout << " (" << elements[i].size << ")" << std::endl;
    }
}

long recursive_solution(vector<TreeElement> &elements, char* path, int level)
{
    if (elements.size() <= level)
    {
        TreeElement nothing;
        nothing.path = new char[1];
        nothing.path[0] = 0;
        nothing.size = 0;
        elements.push_back(nothing);
    }
    long size = 0;
    struct stat buf;
    stat(path, &buf);
    if (buf.st_mode & S_IFDIR && !( buf.st_mode & S_IFREG))
    {
        DIR *dir = opendir(path);
	if (dir != NULL)
	{
        	struct dirent *ent;
        	while ((ent = readdir (dir)) != NULL) {
        	        if (ent->d_name[0] != '.')
        	        {
        	            char *str = new char[strlen(path) + strlen(ent->d_name) + 2];
        	            strcpy(str, path);
        	            str[strlen(path)] = '\0';
	                    strcat(str, FILE_SEP);
                	    strcat(str, ent->d_name);
                	    size += recursive_solution(elements, str, level+1);
                	    delete [] str;
                	}
        	}
        	closedir (dir);
	}
    }
    else 
    {
        size = buf.st_size;
    }

    if (elements[level].size < size)
    {
        elements[level].size = size;
        delete [] elements[level].path;
        elements[level].path = new char[strlen(path) + 1];
        strcpy(elements[level].path, path);
    }
    return size;
}



int main()
{
    int question;
    do
    {
        std::cout << "Please, enter path" << std::endl;
        char *path = new char[200];
        std::cin >> path;//fgets(path, 200, stdin);
        std::cout << path << std::endl;
        std::cout << "Please, choose number of question: " << std::endl;
        std::cout << " 1 - create tree from catalog" << std::endl;
        std::cout << " 2 - find max object on each tree-level" << std::endl;

        std::cin >> question;

        switch(question)
        {
            case 1:
                first_problem(path);
                break;
            case 2:
                second_problem(path);
                break;
            case 0:
                break;
            default:
                std::cout << "unknown operation number" << std::endl;
        }
    }while (question != 0);

    return 0;
}


