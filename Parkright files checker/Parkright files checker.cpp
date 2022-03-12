#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

std::string del(std::string p);
std::string Parseini(std::string param, std::string temp);
void CreateFolders(std::string path);
void CreateFiles(std::string path, std::string PathToMakeTxt);
void CopyFiles(std::string PathToCopy, std::string PathToPR, std::string PathToTxt);


int main()
{
    setlocale(LC_ALL, "Russian");

    // загружаем инишник
    std::ifstream inifile("pr_check.ini");

    //если нет файла, то создаем инишник и закрываем прогу 
    if (!inifile.is_open())
    {
        std::cout << "ini файл не найден" << std::endl;
        std::cout << "Файл создан в папке с прогой" << std::endl;
        inifile.close();
        system("pause");
        return -1;
    }

    std::string PRDir = "PRDir";
    std::string DirToCopy = "DirToCopy";
    std::string FolderTxt = "FolderTxt";
    std::string temp;

    //парсим инишник и присваиваем всем переменным значения
    while (std::getline(inifile, temp))
    {   
        if (PRDir == "PRDir") 
        {
            PRDir = Parseini(PRDir, temp);
        }
        if (DirToCopy == "DirToCopy")
        {
            DirToCopy = Parseini(DirToCopy, temp);
        }  
        if (FolderTxt == "FolderTxt")
        {
            FolderTxt = Parseini(FolderTxt, temp);
        }
    }
    

    //выбираем что надо сделать
    int action;
    std::cout << "1. Создать список папки со списком файлов, рядом с этой прогой (в ini должен быть заполнен PRDir). " << std::endl;
    std::cout << "2. Скопировать файлы в папки, которые прописаны в txt файле (Копировать будем в DirToCopy)" << std::endl;

    std::cin >> action;

    if (action == 1)
    {
        CreateFiles(PRDir, FolderTxt);
    }
    else if (action == 2)
    {   
        CreateFolders(DirToCopy);
        CopyFiles(DirToCopy, PRDir, FolderTxt);
    }
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

std::string Parseini(std::string param, std::string temp)
{   
    std::string tempo = "";
    int i;
    for (i = 0; i < temp.length(); i++)
    {
        if (temp[i] != '=')
        {
            tempo += temp[i];

        }
        else
        {
            i++;
            break;
        }
    }

    if (param == tempo)
    {   
        param = "";
        for (; i < temp.length(); i++)
        {   
            param += temp[i];
        }
    }

    return param;
}

void CreateFolders(std::string path)
{
    while (true)
    {
        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directories(path);
            std::filesystem::create_directories(path + "//Bin");
            std::filesystem::create_directories(path + "//Data");
            std::filesystem::create_directories(path + "//LocKeys");
            std::filesystem::create_directories(path + "//LocKeys//Russian");
            std::filesystem::create_directories(path + "//LocKeys//English");
            break;
        }
        else std::filesystem::remove_all(path);
    }
}

void CreateFiles(std::string path,std::string PathToMakeTxt)
{

    std::string temp;
    std::string RemovePathTemp;
    
  
    //создаем для Bin

    std::ofstream binTemp("C://BinTemp.txt");
    std::ofstream bin(PathToMakeTxt + "//Bin.txt");

    for (auto& p : std::filesystem::directory_iterator(path + "\\Bin"))
    {
        binTemp << p << std::endl;
    }

    binTemp.close();
    std::ifstream ReadBinTemp("C://BinTemp.txt");

    while (std::getline(ReadBinTemp, temp))
    {
        temp = del(temp);
        bin << temp << std::endl;
    }

    ReadBinTemp.close();

    //создаем для Data

    std::ofstream DataTemp("C://DataTemp.txt");
    std::ofstream Data(PathToMakeTxt + "//Data.txt");

    for (auto& p : std::filesystem::directory_iterator(path + "\\Data"))
    {
        DataTemp << p << std::endl;
    }

    DataTemp.close();

    std::ifstream ReadDataTemp("C://DataTemp.txt");

    while (std::getline(ReadDataTemp, temp))
    {
        temp = del(temp);
        Data << temp << std::endl;
    }

    ReadDataTemp.close();

    //Russian Local

    std::ofstream RussianTemp("C://RussianTemp.txt");
    std::ofstream Russian(PathToMakeTxt + "//Russian.txt");

    for (auto& p : std::filesystem::directory_iterator(path + "\\LocKeys\\Russian"))
    {
        RussianTemp << p << std::endl;
    }

    RussianTemp.close();
    std::ifstream ReadRussianTemp("C://RussianTemp.txt");

    while (std::getline(ReadRussianTemp, temp))
    {
        temp = del(temp);
        Russian << temp << std::endl;
    }

    ReadRussianTemp.close();


    //English Local

    std::ofstream EnglishTemp("C://EnglishTemp.txt");
    std::ofstream English(PathToMakeTxt + "//English.txt");

    for (auto& p : std::filesystem::directory_iterator(path + "\\LocKeys\\English"))
    {
        EnglishTemp << p << std::endl;
    }

    EnglishTemp.close();
    std::ifstream ReadEnglishTemp("C://EnglishTemp.txt");

    while (std::getline(ReadEnglishTemp, temp))
    {
        temp = del(temp);
        English << temp << std::endl;
    }

    ReadEnglishTemp.close();

    remove("C://BinTemp.txt");
    remove("C://DataTemp.txt");
    remove("C://RussianTemp.txt");
    remove("C://EnglishTemp.txt");

}

void CopyFiles(std::string PathToCopy, std::string PathToPR, std::string PathToTxt)
{   
    //Копируем bin
    std::string CopyPR, CopyTo, FileName;
    std::ifstream BinTxt(PathToTxt + "\\Bin.txt");

    while (std::getline(BinTxt, FileName))
    {   

            CopyPR = PathToPR + "\\Bin\\";
            for (int i = 0; i < FileName.length(); i++)
            {
                CopyPR += FileName[i];
            }
            CopyTo = PathToCopy + "\\Bin\\" + FileName;
            std::filesystem::copy_file(CopyPR, CopyTo);


    }

    

}
