#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

std::string del(std::string p);
std::string Parseini(std::string param, std::string t);
void CreateFolders();


int main()
{
    setlocale(LC_ALL, "Russian");

    // загружаем инишник
    std::ifstream inifile("pr_check.ini");

    //если нет файла закрываем всё
    if (!inifile.is_open())
    {
        std::cout << "ini файл не найден" << std::endl;
        std::cout << "Файл создан в папке с прогой" << std::endl;
        system("pause");
        return -1;
    }
    std::string PRDir = "PRDir";
    std::string temp;
    while (std::getline(inifile, temp))
    {
        PRDir = Parseini(PRDir,temp);
    }
    

    int action;
    std::cout << "1. Создать список файлов (в ini должен быть заполнен PRDir). Создадутся файлы *.txt со списком файлов" << std::endl;
    std::cout << "2. Скопировать и раскидать файлы, которые в *.txt файлах(скопируется в папку с этой прогой)" << std::endl;

    std::cin >> action;

        if (action == 'y')
        {   
            CreateFolders();
            //CreateListFiles();
            /*while (true)
            {
                if (!std::filesystem::exists("PRFiles")) {
                                           
                    std::string path;
                    // создаем папки с файлами
                    path = "PRFiles";
                    std::filesystem::create_directories(path);
                    path = "PRFiles//Bin";
                    std::filesystem::create_directories(path);
                    //------------------------------------------------------------------------
                    path = "C:\\Program Files\\Recognition Technologies\\ParkRight 3.8\\Bin";
                    std::ofstream tempfile("temp.txt");
                    for (auto& p : std::filesystem::directory_iterator(path))
                    {
                        tempfile << p << std::endl;
                    }
                    //------------------------------------------------------------------------
                    tempfile.close();
                    std::ifstream tempfileOne("temp.txt");
                    std::ofstream binfiles("PRFiles//Bin//Bin.txt");
                    std::string p;
                    while (std::getline(tempfileOne, p))
                    {
                        p = del(p);
                        binfiles << p << std::endl;
                    }
                    tempfileOne.close();
                    std::filesystem::remove("temp.txt");
                    binfiles.close();
                        
                        /*
                    path = "PRFiles";
                    std::filesystem::create_directories(path);
                    path = "PRFiles";
                    std::filesystem::create_directories(path);
                    path = "PRFiles";
                    std::filesystem::create_directories(path);
                    path = "PRFiles";
                    std::filesystem::create_directories(path);

                    std::filesystem::create_directories("PRFiles//Bin");
                    std::ofstream binfiles("PRFiles//Bin//Bin.txt");
                    for (auto& p : std::filesystem::directory_iterator("PRFiles//Bin//Bin.txt"))
                        std::cout << p << std::endl;
                    std::filesystem::create_directories("PRFiles//Data");
                    std::filesystem::create_directories("PRFiles//LocKeys");
                    std::filesystem::create_directories("PRFiles//LocKeys//Russian");
                    std::filesystem::create_directories("PRFiles//LocKeys//English");
                    break;
                }
                else std::filesystem::remove_all("PRFiles");
            }*/
        }
      
   
    /*
    std::ifstream inifile("pr_check.ini");

    while (true)
    {
        if (inifile.is_open())
        {
            std::cout << "ini файл загружен успешно" << std::endl;
            break;
        }
        else std::cout << "ini файл не найден" << std::endl;
             

        std::cout << "Создать ini файл? y/n: ";
        char action;
        std::cin >> action;

        if (action == 'y')
        {
            std::ofstream createinifile("pr_check.ini");
            createinifile << "ParkRightDir= " << std::endl << "CopyDir= ";
            return 0;

        }
    }

    std::string dir, filedir, sourceFile;

    inifile >> dir >> dir >> filedir >> filedir;



    std::filesystem::copy_file(sourceFile, dir, std::filesystem::copy_options::overwrite_existing);

    
    std::string test;
    test = "C:\\1";
    if (!std::filesystem::exists(test)) {
        std::filesystem::create_directories(test);
    }*/
}

std::string del(std::string p)
{
    std::string temp;
    
    for (int i = p.length()-2; i > 0; i--)
    {
        if (p[i] == '\\')
            break;
        temp += p[i];
    }
    
    p = "";

    for (int i = temp.length(); i >= 0; i--)
    {
        p += temp[i];
    }

    return p;
}

std::string Parseini(std::string param, std::string t)
{
    if()
    return std::string();
}

void CreateFolders()
{
    while (true)
    {
        if (!std::filesystem::exists("PRFiles")) {
            std::filesystem::create_directories("PRFiles");
            std::filesystem::create_directories("PRFiles//Bin");
            std::filesystem::create_directories("PRFiles//Data");
            std::filesystem::create_directories("PRFiles//LocKeys");
            std::filesystem::create_directories("PRFiles//LocKeys//Russian");
            std::filesystem::create_directories("PRFiles//LocKeys//English");
            break;
        }
        else std::filesystem::remove_all("PRFiles");
    }
}
