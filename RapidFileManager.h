#ifndef RAPIDFILEMANAGER_H
#define RAPIDFILEMANAGER_H
#include<vector>
#include<memory>
#include<QFile>

class RapidFileManager
{    
public:
    RapidFileManager();

public:

    bool ReadBytesInMainFile();


private:

    std::shared_ptr<std::vector<std::shared_ptr<QFile>>> files;
    std::string_view extisions;

};

#endif // RAPIDFILEMANAGER_H
