#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

std::string del(std::string p);
std::string Parseini(std::string param, std::string temp);
void CreateFolders(std::string path);
void CreateFiles(std::string path, std::string PathToMakeTxt);
void CopyFiles(std::string PathToCopy, std::string PathToPR, std::string PathToTxt);
void CopyFiles(std::string PathToCopy, std::string PathToPR, std::string PathToTxt, int a);


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
        std::ofstream WriteIni("pr_check.ini");
        WriteIni << "PRDir=C:\\Program Files\\Recognition Technologies\\ParkRight 3.8" << std::endl;
        WriteIni << "DirToCopy=C:\\PR\\new" << std::endl;
        WriteIni << "FolderTxt=C:\\PR\\txt" << std::endl;
        WriteIni << "SVNDir=C:\\SNV" << std::endl;
        WriteIni << "SVNCopyDir=C:\\PR\\Svn" << std::endl;

        system("pause");
        return -1;
    }

    std::string PRDir = "PRDir";
    std::string DirToCopy = "DirToCopy";
    std::string FolderTxt = "FolderTxt";
    std::string SVNDir = "SVNDir";
    std::string SVNCopyDir = "SVNCopyDir";
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
        if (SVNDir == "SVNDir")
        {
            SVNDir = Parseini(SVNDir, temp);
        }
        if (SVNCopyDir == "SVNCopyDir")
        {
            SVNCopyDir = Parseini(SVNCopyDir, temp);
        }
    }
    std::cout << "Дирректория ParkRight: " << PRDir << std::endl;
    std::cout << "Дирректория сборки ParkRight: " << DirToCopy << std::endl;
    std::cout << "Дирректория где хранятся txt с именами файлов: " << FolderTxt << std::endl;
    std::cout << "Svn: " << SVNDir << std::endl;
    std::cout << "Дир до файлов из snv: " << SVNCopyDir << std::endl;

    //выбираем что надо сделать
    while (true)
    {
        
        int action;
        std::cout << "0. Для выхода" << std::endl;
        std::cout << "1. Создать список папки со списком файлов, рядом с этой прогой (PRDir - папка с ПР, FolderTxt - папка где создадутся txt). " << std::endl;
        std::cout << "2. Скопировать файлы в папки, которые прописаны в txt файле (DirToCopy)" << std::endl;
        std::cout << "3. Скопировать файлы из хранилища (SVNDir)" << std::endl;

        std::cin >> action;

        system("cls");

        if (action == 1)
        {
            std::cout << "Создали txt со списком файлов" << std::endl;
            CreateFiles(PRDir, FolderTxt);
        }
        else if (action == 2)
        {   
            CreateFolders(DirToCopy);
            std::cout << "Создали папки, если их нет" << std::endl;
            CopyFiles(DirToCopy, PRDir, FolderTxt);
            std::cout << "Копирование завершено" << std::endl;

        }
        else if (action == 3)
        {
            CreateFolders(SVNCopyDir);
            std::cout << "Создали папки, если их нет" << std::endl;
            CopyFiles(SVNCopyDir, SVNDir, FolderTxt,1);


        }
        else if (action == 0)
        {
            break;
        }
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

    for (int i = temp.length() -1 ; i >= 0; i--)
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

    while (true) {
        try {


            while (std::getline(BinTxt, FileName))
            {
                CopyPR = PathToPR + "\\Bin\\" + FileName;
                CopyTo = PathToCopy + "\\Bin\\" + FileName;
                std::filesystem::copy_file(CopyPR, CopyTo);
            }

            BinTxt.close();
            break;
        }
        catch (...)
        {
            std::cout << "Нет файла: " << CopyPR << std::endl;
        }
    }
    
    //Data
    std::ifstream DataTxt(PathToTxt + "\\Data.txt");

    while (true) {
        try {

            while (std::getline(DataTxt, FileName))
            {
                CopyPR = PathToPR + "\\Data\\" + FileName;
                CopyTo = PathToCopy + "\\Data\\" + FileName;
                std::filesystem::copy_file(CopyPR, CopyTo);
            }

            DataTxt.close();

            break;
        }
        catch (...)
        {
            std::cout << "Нет файла: " << CopyPR << std::endl;
        }
    }

    //LocKeys RUS
    std::ifstream RussianTxt(PathToTxt + "\\Russian.txt");

    while (true) {
        try {
            while (std::getline(RussianTxt, FileName))
            {
                CopyPR = PathToPR + "\\LocKeys\\Russian\\" + FileName;
                CopyTo = PathToCopy + "\\LocKeys\\Russian\\" + FileName;
                std::filesystem::copy_file(CopyPR, CopyTo);
            }

            RussianTxt.close();
            break;
        }
        catch (...)
        {
            std::cout << "Нет файла: " << CopyPR << std::endl;
        }
    }

    //LocKeys Eng
    std::ifstream EnglishTxt(PathToTxt + "\\English.txt");

    while (true) {
        try {
            while (std::getline(EnglishTxt, FileName))
            {
                CopyPR = PathToPR + "\\LocKeys\\English\\" + FileName;
                CopyTo = PathToCopy + "\\LocKeys\\English\\" + FileName;
                std::filesystem::copy_file(CopyPR, CopyTo);
            }

            EnglishTxt.close();
            break;
        }
        catch (...)
        {
            std::cout << "Нет файла: " << CopyPR << std::endl;
        }
    }
}

void CopyFiles(std::string PathToCopy, std::string PathToPR, std::string PathToTxt, int a)
{

    //Копируем bin
    std::string CopyPR, CopyTo, FileName;

    std::ifstream BinTxt(PathToTxt + "\\Bin.txt");

    while (true) {
        try {


            while (std::getline(BinTxt, FileName))
            {
                CopyPR = PathToPR + "\\Bin64\\" + FileName;
                CopyTo = PathToCopy + "\\Bin\\" + FileName;
                std::filesystem::copy_file(CopyPR, CopyTo);
            }

            BinTxt.close();
            break;
        }
        catch (...)
        {
            std::cout << "Нет файла: " << CopyPR << std::endl;
        }
    }

    //Data
    std::ifstream DataTxt(PathToTxt + "\\Data.txt");

    while (true) {
        try {

            while (std::getline(DataTxt, FileName))
            {
                CopyPR = PathToPR + "\\Data\\" + FileName;
                CopyTo = PathToCopy + "\\Data\\" + FileName;
                std::filesystem::copy_file(CopyPR, CopyTo);
            }

            DataTxt.close();

            break;
        }
        catch (...)
        {
            std::cout << "Нет файла: " << CopyPR << std::endl;
        }
    }

    //LocKeys RUS
    std::ifstream RussianTxt(PathToTxt + "\\Russian.txt");

    while (true) {
        try {
            while (std::getline(RussianTxt, FileName))
            {
                CopyPR = PathToPR + "\\LocKeys\\Russian\\" + FileName;
                CopyTo = PathToCopy + "\\LocKeys\\Russian\\" + FileName;
                std::filesystem::copy_file(CopyPR, CopyTo);
            }

            RussianTxt.close();
            break;
        }
        catch (...)
        {
            std::cout << "Нет файла: " << CopyPR << std::endl;
        }
    }

    //LocKeys Eng
    std::ifstream EnglishTxt(PathToTxt + "\\English.txt");

    while (true) {
        try {
            while (std::getline(EnglishTxt, FileName))
            {
                CopyPR = PathToPR + "\\LocKeys\\English\\" + FileName;
                CopyTo = PathToCopy + "\\LocKeys\\English\\" + FileName;
                std::filesystem::copy_file(CopyPR, CopyTo);
            }

            EnglishTxt.close();
            break;
        }
        catch (...)
        {
            std::cout << "Нет файла: " << CopyPR << std::endl;
        }
    }
}
