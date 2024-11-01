#include <algorithm>
#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>

#define MAXSIZE 4 * 1024 * 1024
#define MAXNUMBEROFFILE 512
#define MAX_FILENAME_LENGTH 128
#define PASSWORD_LENGTH 64

void errExit(char *message);

class DirectoryEntry
{
private:
    char filename[MAX_FILENAME_LENGTH];
    char parent[MAX_FILENAME_LENGTH];
    time_t creation_time;
    time_t last_modification;
    int size;
    int first_block;
    int directory;
    int exist;
    char owner_permissions[2];
    char password[PASSWORD_LENGTH];

public:
    DirectoryEntry(char filename[], char parent[], time_t creation_time, time_t last_modification, int size, int first_block, int directory, const char owner_permissions[], const char password[]);
    DirectoryEntry();
    friend std::ostream &operator<<(std::ostream &os, const DirectoryEntry &entry)
    {
        os << "Filename: " << entry.filename << "\nParent: " << entry.parent << "\nCreation Time: " << std::ctime(&entry.creation_time) << "Last Modification: " << std::ctime(&entry.last_modification) << "Size: " << entry.size << ", First Block: " << entry.first_block << ", Directory: " << entry.directory << ", Exist: " << entry.exist << ", Owner Permissions: " << entry.owner_permissions << ", Password: " << entry.password;
        return os;
    }
    char *getFilename()
    {
        return filename;
    }
    void setFilename(const char *newFilename)
    {
        strcpy(filename, newFilename);
    }
    const char *getParent() const
    {
        return parent;
    }
    void setParent(const char *newParent)
    {
        strcpy(parent, newParent);
    }
    time_t getCreationTime() const
    {
        return creation_time;
    }
    void setCreationTime(time_t newCreationTime)
    {
        creation_time = newCreationTime;
    }
    time_t getLastModification() const
    {
        return last_modification;
    }
    void setLastModification(time_t newLastModification)
    {
        last_modification = newLastModification;
    }
    int getSize() const
    {
        return size;
    }
    void setSize(int newSize)
    {
        size = newSize;
    }
    int getFirstBlock() const
    {
        return first_block;
    }
    void setFirstBlock(int newFirstBlock)
    {
        first_block = newFirstBlock;
    }
    int getDirectory() const
    {
        return directory;
    }
    void setDirectory(int newDirectory)
    {
        directory = newDirectory;
    }
    int getExist() const
    {
        return exist;
    }
    void setExist(int newExist)
    {
        exist = newExist;
    }
    const char *getOwnerPermissions() const
    {
        return owner_permissions;
    }
    void setOwnerPermissions(const char *newOwnerPermissions)
    {
        strcpy(owner_permissions, newOwnerPermissions);
    }
    const char *getPassword() const
    {
        return password;
    }
    void setPassword(const char *newPassword)
    {
        strcpy(password, newPassword);
    }
};

class SuperBlock
{
private:
    int block_size;
    int number_of_blocks;
    int free_blocks;
    int fat_blocks;
    int directory_blocks;

public:
    SuperBlock(int block_size, int number_of_blocks, int free_blocks, int fat_blocks, int directory_blocks);
    SuperBlock();
    int getBlockSize() const
    {
        return block_size;
    }

    int getNumberOfBlocks() const
    {
        return number_of_blocks;
    }

    int getFreeBlocks() const
    {
        return free_blocks;
    }

    int getFatBlocks() const
    {
        return fat_blocks;
    }

    int getDirectoryBlocks() const
    {
        return directory_blocks;
    }

    void setBlockSize(int size)
    {
        block_size = size;
    }

    void setNumberOfBlocks(int number)
    {
        number_of_blocks = number;
    }

    void setFreeBlocks(int free)
    {
        free_blocks = free;
    }

    void setFatBlocks(int fat)
    {
        fat_blocks = fat;
    }

    void setDirectoryBlocks(int directory)
    {
        directory_blocks = directory;
    }
};

DirectoryEntry::DirectoryEntry(char filename[], char parent[], time_t creation_time, time_t last_modification, int size, int first_block, int directory, const char owner_permissions[], const char password[])
{
    strcpy(this->filename, filename);
    strcpy(this->parent, parent);
    this->creation_time = creation_time;
    this->last_modification = last_modification;
    this->size = size;
    this->first_block = first_block;
    this->directory = directory;
    this->exist = 1;
    strcpy(this->owner_permissions, owner_permissions);
    strcpy(this->password, password);
}

DirectoryEntry::DirectoryEntry() {}

SuperBlock::SuperBlock(int block_size, int number_of_blocks, int free_blocks, int fat_blocks, int directory_blocks)
{
    this->block_size = block_size;
    this->number_of_blocks = number_of_blocks;
    this->free_blocks = free_blocks;
    this->fat_blocks = fat_blocks;
    this->directory_blocks = directory_blocks;
}
SuperBlock::SuperBlock() {}

class FileSystem
{
private:
    char filename[100];
    int directoryEntriesChanged;
    int fatTableChanged;
    int freeTableChanged;
    DirectoryEntry *findDirectoryEntry(DirectoryEntry directoryEntries[], int size, const char *parent, const char *child)
    {
        for (int i = 0; i < size; ++i)
        {
            if (
                strcmp(directoryEntries[i].getParent(), parent) == 0 &&
                strcmp(directoryEntries[i].getFilename(), child) == 0)
            {
                return &directoryEntries[i];
            }
        }
        return nullptr;
    }

public:
    FileSystem();
    FileSystem(char *filename);

    const char *getFilename() const
    {
        return filename;
    }

    int getDirectoryEntriesChanged() const
    {
        return directoryEntriesChanged;
    }

    int getFatTableChanged() const
    {
        return fatTableChanged;
    }

    int getFreeTableChanged() const
    {
        return freeTableChanged;
    }

    void setFilename(const char *newFilename)
    {
        strncpy(filename, newFilename, sizeof(filename));
        filename[sizeof(filename) - 1] = '\0';
    }

    void setDirectoryEntriesChanged(int newValue)
    {
        directoryEntriesChanged = newValue;
    }

    void setFatTableChanged(int newValue)
    {
        fatTableChanged = newValue;
    }

    void setFreeTableChanged(int newValue)
    {
        freeTableChanged = newValue;
    }
    void dir(char *, char *, DirectoryEntry[]);
    void mkdir(char *, char *, DirectoryEntry[]);
    void rmdir(char *, char *, char *, SuperBlock, DirectoryEntry[], int[], int[]);
    void write(char *, char *, char *, char *, SuperBlock, DirectoryEntry[], int[], int[]);
    void del(char *, char *, char *, SuperBlock, DirectoryEntry[], int[], int[]);
    void read(char *parent, char *child, char *filename, char *password, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], int free_table[]);
    void dumpe2fs(SuperBlock, int[], int[], DirectoryEntry[]);
    int isParent(char *, char *, DirectoryEntry[]);
    int isExist(char **, int, DirectoryEntry[]);
    int entryType(char *, char *, DirectoryEntry[]);
    char **splitPath(char *, int *);
    void chmod(char *, char *, DirectoryEntry[], const char *);
    void addpw(char *, char *, DirectoryEntry[], const char *);
};
FileSystem::FileSystem()
{
    int directoryEntriesChanged = 0;
    int fatTableChanged = 0;
    int freeTableChanged = 0;
}
FileSystem::FileSystem(char *filename)
{
    strcpy(this->filename, filename);
    int directoryEntriesChanged = 0;
    int fatTableChanged = 0;
    int freeTableChanged = 0;
}
void FileSystem::dir(char *parent, char *child, DirectoryEntry directoryEntries[])
{
    int fileType = entryType(parent, child, directoryEntries);
    if (fileType == 0)
    {
        std::cout << child;
    }
    else
    {
        int number_of_files = 0;
        for (int i = 0; i < MAXNUMBEROFFILE; i++)
        {
            if (strcmp(directoryEntries[i].getParent(), child) == 0)
            {
                std::cout << directoryEntries[i].getFilename() << "\t";
                number_of_files++;
            }
        }
        if (number_of_files > 0)
            std::cout << "\n";
    }
}

void FileSystem::mkdir(char *parent, char *child, DirectoryEntry directoryEntries[])
{
    int fileType = entryType(parent, child, directoryEntries);
    if (fileType == -1)
    {
        for (int i = 0; i < MAXNUMBEROFFILE; i++)
        {
            if (directoryEntries[i].getExist() != 999)
            {
                time_t current_time = time(0);
                char owner_permissions[3] = "RW";
                char password[128] = "";

                directoryEntries[i].setFilename(child);
                directoryEntries[i].setParent(parent);
                directoryEntries[i].setCreationTime(current_time);
                directoryEntries[i].setLastModification(current_time);
                directoryEntries[i].setDirectory(1);
                directoryEntries[i].setSize(0);
                directoryEntries[i].setOwnerPermissions(owner_permissions);
                directoryEntries[i].setPassword(password);
                directoryEntriesChanged = 1;
                directoryEntries[i].setExist(999);
                return;
            }
        }
    }
    else if (fileType == 0)
    {
    }
    else if (fileType == 1)
    {
        std::cout << "CANNOT CREATE DIRECTORY \"" << child << "\": IT EXISTS!\n";
    }
}

void FileSystem::rmdir(char *parent, char *child, char *password, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], int free_table[])
{
    int fileType = entryType(parent, child, directoryEntries);
    if (fileType == 0)
    {
        std::cout << "FAILED TO REMOVE \"" << child << "\": NOT A DIRECTORY!\n";
    }
    else if (fileType == -1)
    {
        std::cout << "FAILED TO REMOVE \"" << child << ": NO SUCH FILE OR DIRECTORY!\n";
    }
    else
    {
        for (int i = 0; i < MAXNUMBEROFFILE; i++)
        {
            if (strcmp(directoryEntries[i].getParent(), child) == 0)
            {
                if (directoryEntries[i].getDirectory() == 1)
                {
                    rmdir(child, directoryEntries[i].getFilename(), password, superBlock, directoryEntries, fat_table, free_table);
                }
                else
                {
                    del(child, directoryEntries[i].getFilename(), password, superBlock, directoryEntries, fat_table, free_table);
                }
            }
            if (strcmp(directoryEntries[i].getFilename(), child) == 0)
            {
                directoryEntries[i].setFilename("");
                directoryEntries[i].setParent("");
                directoryEntries[i].setLastModification(0);
                directoryEntries[i].setDirectory(0);
                directoryEntries[i].setSize(0);
                directoryEntriesChanged = 1;
                directoryEntries[i].setExist(0);
                break;
            }
        }
        freeTableChanged = 1;
        fatTableChanged = 1;
    }
}
void FileSystem::write(char *parent, char *child, char *filename, char *password, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], int free_table[])
{
    int fileType = entryType(parent, child, directoryEntries);
    if (fileType == 1)
    {
        std::cout << child << " is a directory" << std::endl;
    }
    else
    {
        if (fileType == 0)
        {
            int index = -1;
            for (int i = 0; i < MAXNUMBEROFFILE; i++)
            {
                if (directoryEntries[i].getExist() == 999 &&
                    strcmp(directoryEntries[i].getParent(), parent) == 0 &&
                    strcmp(directoryEntries[i].getFilename(), child) == 0)
                {
                    index = i;
                    break;
                }
            }

            if (index == -1)
            {
                std::cerr << "ERROR: FILE \"" << child << "\" NOT FOUND FOR DELETION!\n";
                return;
            }
            if (strcmp(directoryEntries[index].getPassword(), "") != 0)
            {
                if (password == nullptr || strcmp(directoryEntries[index].getPassword(), password) != 0)
                {
                    std::cout << "ERROR: INCORRECT PASSWORD FOR FILE \"" << child << "\"!\n";
                    return;
                }
            }

            del(parent, child, password, superBlock, directoryEntries, fat_table, free_table);
        }

        FILE *file = fopen(filename, "rb");
        if (file == NULL)
        {
            perror("fopen");
            exit(-1);
        }

        fseek(file, 0, SEEK_END);

        int size = ftell(file);

        rewind(file);

        int file_blocks = (size / superBlock.getBlockSize()) + 1;

        char **fileArray = (char **)malloc(file_blocks * sizeof(char *));

        for (int i = 0; i < file_blocks; i++)
        {
            fileArray[i] = (char *)malloc(superBlock.getBlockSize() * sizeof(char));
            fread(fileArray[i], sizeof(char), superBlock.getBlockSize(), file);
        }

        int counter = 0;

        FILE *fptr = fopen(getFilename(), "rb+");
        if (fptr == NULL)
        {
            perror("fopen");
            exit(-1);
        }
        int next = -1;
        for (int i = 0; i < superBlock.getNumberOfBlocks() && counter < file_blocks; i++)
        {
            if (free_table[i] == 1)
            {
                fat_table[i] = next;
                free_table[i] = 0;
                next = i;
                fseek(fptr, sizeof(SuperBlock) + i * superBlock.getBlockSize(), SEEK_SET);
                fwrite(fileArray[file_blocks - counter - 1], sizeof(char), superBlock.getBlockSize(), fptr);
                rewind(fptr);
                counter++;
            }
        }

        if (counter != file_blocks)
        {
            std::cout << "Some parts of the file is not written to" << child << ". Memory is full." << std::endl;
        }

        fclose(file);
        fclose(fptr);

        for (int i = 0; i < MAXNUMBEROFFILE; i++)
        {
            if (directoryEntries[i].getExist() != 999)
            {
                time_t current_time = time(0);
                char owner_permissions[3] = "RW";

                directoryEntries[i].setFilename(child);
                directoryEntries[i].setParent(parent);
                directoryEntries[i].setCreationTime(current_time);
                directoryEntries[i].setLastModification(current_time);
                directoryEntries[i].setDirectory(0);
                directoryEntries[i].setSize(size);
                directoryEntries[i].setFirstBlock(next);
                directoryEntries[i].setOwnerPermissions(owner_permissions);
                directoryEntries[i].setPassword(password ? password : "");
                directoryEntries[i].setExist(999);
                std::cout << "File \"" << filename << "\" written successfully to file \"" << child << "\" under directory \"" << parent << "\"\n";
                break;
            }
        }

        freeTableChanged = 1;
        fatTableChanged = 1;
        directoryEntriesChanged = 1;
    }
}

void FileSystem::read(char *parent, char *child, char *filename, char *password, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], int free_table[])
{
    int fileType = entryType(parent, child, directoryEntries);
    if (fileType == 1)
    {
        std::cout << child << " is a directory" << std::endl;
    }
    else if (fileType == -1)
    {
        std::cout << child << " No such file or directory" << std::endl;
    }
    else
    {
        int index = -1;
        for (int i = 0; i < MAXNUMBEROFFILE; i++)
        {
            if (directoryEntries[i].getExist() == 999 &&
                strcmp(directoryEntries[i].getParent(), parent) == 0 &&
                strcmp(directoryEntries[i].getFilename(), child) == 0)
            {
                index = i;
                break;
            }
        }
        if (strchr(directoryEntries[index].getOwnerPermissions(), 'R') == NULL)
        {
            std::cout << "ERROR: Read permission is denied for file \"" << child << "\"!\n";
            return;
        }

        if (strcmp(directoryEntries[index].getPassword(), "") != 0)
        {
            if (password == nullptr || strcmp(directoryEntries[index].getPassword(), password) != 0)
            {
                std::cout << "ERROR: Incorrect password\"" << child << "\"!\n";
                return;
            }
        }
        FILE *file = fopen(filename, "w");
        FILE *fptr = fopen(getFilename(), "rb+");
        for (int i = 0; i < MAXNUMBEROFFILE; i++)
        {
            if (strcmp(directoryEntries[i].getFilename(), child) == 0 && strcmp(directoryEntries[i].getParent(), parent) == 0)
            {
                int start = directoryEntries[i].getFirstBlock();

                while (start != -1)
                {
                    char buffer[superBlock.getBlockSize()];
                    fseek(fptr, sizeof(SuperBlock) + start * superBlock.getBlockSize(), SEEK_SET);
                    fread(buffer, sizeof(char), superBlock.getBlockSize(), fptr);
                    rewind(fptr);
                    fwrite(buffer, sizeof(char), strlen(buffer), file);
                    memset(buffer, 0, sizeof(buffer));
                    start = fat_table[start];
                }
                break;
            }
        }
        fclose(file);
        fclose(fptr);
    }
}

void FileSystem::del(char *parent, char *child, char *password, SuperBlock superBlock, DirectoryEntry directoryEntries[], int fat_table[], int free_table[])
{
    int fileType = entryType(parent, child, directoryEntries);
    if (fileType == 1)
    {
        std::cout << "\"" << child << "\": IS A DIRECTORY!\n";
    }
    else if (fileType == -1)
    {
        std::cout << "\"" << child << "\": NO SUCH FILE OR DIR!\n";
    }
    else
    {
        for (int i = 0; i < MAXNUMBEROFFILE; i++)
        {
            if (strcmp(directoryEntries[i].getFilename(), child) == 0 && strcmp(directoryEntries[i].getParent(), parent) == 0)
            {
                if (strcmp(directoryEntries[i].getPassword(), "") != 0)
                {
                    if ((password == nullptr))
                    {
                        std::cout << "ERROR: INCORRECT PASSWORD FOR FILE \"" << child << "\"!\n";
                        return;
                    }
                    if (strcmp(directoryEntries[i].getPassword(), password) != 0)
                    {
                        std::cout << "ERROR: INCORRECT PASSWORD FOR FILE \"" << child << "\"!\n";
                        return;
                    }
                }
                int current = directoryEntries[i].getFirstBlock();
                int next;
                do
                {
                    next = fat_table[current];
                    free_table[current] = 1;
                    fat_table[current] = -1;
                    current = next;

                } while (current != -1);
                directoryEntries[i].setFilename("");
                directoryEntries[i].setParent("");
                directoryEntries[i].setLastModification(0);
                directoryEntries[i].setDirectory(0);
                directoryEntries[i].setSize(0);
                directoryEntries[i].setExist(0);
                break;
            }
        }
        freeTableChanged = 1;
        fatTableChanged = 1;
        directoryEntriesChanged = 1;
    }
}

void FileSystem::dumpe2fs(SuperBlock superBlock, int free_table[], int fat_table[], DirectoryEntry directoryEntries[])
{
    std::cout << "BLOCK SIZE: " << superBlock.getBlockSize() << "\nNUMBER OF BLOCKS: " << superBlock.getNumberOfBlocks() << "\n";
    int free_blocks_counter = 0, file_counter = 0, directory_counter = 0;
    for (int i = 0; i < superBlock.getNumberOfBlocks(); i++)
    {
        free_blocks_counter += free_table[i];
    }
    std::cout << "FREE BLOCKS NUMBER: " << free_blocks_counter << "\n";

    for (int i = 0; i < MAXNUMBEROFFILE; i++)
    {
        if (directoryEntries[i].getExist() == 999)
        {
            if (directoryEntries[i].getDirectory() == 1)
            {
                directory_counter++;
            }
            else
            {
                file_counter++;
            }
        }
    }
    std::cout << "NUMBER OF DIRECTORIES: " << directory_counter << "\n";
    std::cout << "NUMBER OF FILES: " << file_counter << "\n";

    for (int i = 0; i < MAXNUMBEROFFILE; i++)
    {
        if (directoryEntries[i].getExist() == 999 && directoryEntries[i].getDirectory() == 0)
        {
            std::cout << directoryEntries[i] << std::endl;
        }
    }
}

char **FileSystem::splitPath(char *path, int *number_of_elements)
{
    char **splittedPath = (char **)malloc(100 * sizeof(char *));

    splittedPath[0] = strdup("NOPARENT");

    splittedPath[1] = strdup("/");

    char *token = strtok(path, "/");

    for (int i = 2; i < 100 && token != NULL; i++)
    {
        splittedPath[i] = token;
        token = strtok(NULL, "/");
        (*number_of_elements)++;
    }
    return splittedPath;
}

int FileSystem::entryType(char *parent, char *child, DirectoryEntry directoryEntries[])
{
    for (int i = 0; i < MAXNUMBEROFFILE; i++)
    {
        if (strcmp(directoryEntries[i].getFilename(), child) == 0 && strcmp(directoryEntries[i].getParent(), parent) == 0)
        {
            return directoryEntries[i].getDirectory();
        }
    }
    return -1;
}

int FileSystem::isParent(char *parent, char *child, DirectoryEntry directoryEntries[])
{
    for (int i = 0; i < MAXNUMBEROFFILE; i++)
    {
        if (strcmp(directoryEntries[i].getParent(), parent) == 0)
        {
            if (strcmp(directoryEntries[i].getFilename(), child) == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

int FileSystem::isExist(char **splittedPath, int until, DirectoryEntry directoryEntries[])
{
    for (int i = 1; i < until; i++)
    {

        if (!isParent(splittedPath[i], splittedPath[i + 1], directoryEntries))
        {
            std::cout << "NO SUCH FILE OR DIR!\n";
            return 0;
        }
    }
    return 1;
}

void FileSystem::chmod(char *parent, char *child, DirectoryEntry directoryEntries[], const char *permissions)
{
    DirectoryEntry *entry = findDirectoryEntry(directoryEntries, MAXNUMBEROFFILE, parent, child);
    if (entry != nullptr)
    {
        std::string currentPermissions(entry->getOwnerPermissions());

        if (permissions[0] == '+')
        {

            if (strchr(permissions, 'r') && currentPermissions.find('R') == std::string::npos)
            {
                currentPermissions += 'R';
            }
            if (strchr(permissions, 'w') && currentPermissions.find('W') == std::string::npos)
            {
                currentPermissions += 'W';
            }
        }
        else if (permissions[0] == '-')
        {

            if (strchr(permissions, 'r'))
            {
                currentPermissions.erase(std::remove(currentPermissions.begin(), currentPermissions.end(), 'R'), currentPermissions.end());
            }
            if (strchr(permissions, 'w'))
            {
                currentPermissions.erase(std::remove(currentPermissions.begin(), currentPermissions.end(), 'W'), currentPermissions.end());
            }
        }

        entry->setOwnerPermissions(currentPermissions.c_str());
        directoryEntriesChanged = 1;
    }
    else
    {
        std::cerr << "Error: DirectoryEntry not found." << std::endl;
    }
}

void FileSystem::addpw(char *parent, char *child, DirectoryEntry directoryEntries[], const char *password)
{
    DirectoryEntry *entry = findDirectoryEntry(directoryEntries, MAXNUMBEROFFILE, parent, child);
    if (entry != nullptr)
    {
        entry->setPassword(password);
        directoryEntriesChanged = 1;
    }
    else
    {
        std::cerr << "Error: DirectoryEntry not found." << std::endl;
    }
}
int getArrayLength(char **array)
{
    int length = 0;
    while (array[length] != nullptr)
    {
        ++length;
    }
    return length;
}
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Insufficient number of elements...\n";
        exit(-1);
    }

    FileSystem fileSystem(argv[1]);

    char *operation = argv[2];

    char **paths = &argv[3];

    std::ifstream file(fileSystem.getFilename(), std::ios::binary);

    SuperBlock superBlock;

    file.read(reinterpret_cast<char *>(&superBlock), sizeof(SuperBlock));

    int free_table[superBlock.getNumberOfBlocks()];

    file.read(reinterpret_cast<char *>(&free_table), sizeof(int) * superBlock.getNumberOfBlocks());

    int fat_table[superBlock.getNumberOfBlocks()];

    file.read(reinterpret_cast<char *>(&fat_table), sizeof(int) * superBlock.getNumberOfBlocks());

    std::streamoff offset = sizeof(SuperBlock) +
                            (superBlock.getFatBlocks() + superBlock.getFreeBlocks()) * superBlock.getBlockSize();

    file.seekg(offset, std::ios::beg);

    DirectoryEntry directoryEntries[MAXNUMBEROFFILE];

    file.read(reinterpret_cast<char *>(directoryEntries), sizeof(DirectoryEntry) * MAXNUMBEROFFILE);

    file.close();

    int number_of_elements = 2;

    char **splittedPath;
    if (argc > 3)
        splittedPath = fileSystem.splitPath(paths[0], &number_of_elements);

    if (strncmp(operation, "dir", 3) == 0)
    {
        if (!fileSystem.isExist(splittedPath, number_of_elements - 1, directoryEntries))
        {
            return -1;
        }
        fileSystem.dir(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], directoryEntries);
    }
    else if (strncmp(operation, "mkdir", 5) == 0)
    {
        if (number_of_elements < 1)
        {
            std::cout << "Insufficient path\n";
            return -1;
        }
        if (!fileSystem.isExist(splittedPath, number_of_elements - 2, directoryEntries))
        {
            return -1;
        }
        fileSystem.mkdir(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], directoryEntries);
    }
    else if (strcmp(operation, "rmdir") == 0)
    {
        if (!fileSystem.isExist(splittedPath, number_of_elements - 1, directoryEntries))
        {
            return -1;
        }
        if (getArrayLength(paths) < 3)
        {
            fileSystem.rmdir(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], nullptr, superBlock, directoryEntries, fat_table, free_table);
        }
        else
        {
            fileSystem.rmdir(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], paths[2], superBlock, directoryEntries, fat_table, free_table);
        }
    }
    else if (strcmp(operation, "write") == 0)
    {
        if (!fileSystem.isExist(splittedPath, number_of_elements - 3, directoryEntries))
        {
            return -1;
        }
        if (getArrayLength(paths) < 3)
        {
            fileSystem.write(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], paths[1], nullptr, superBlock, directoryEntries, fat_table, free_table);
        }
        else
        {
            fileSystem.write(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], paths[1], paths[2], superBlock, directoryEntries, fat_table, free_table);
        }
    }
    else if (strcmp(operation, "del") == 0)
    {
        if (!fileSystem.isExist(splittedPath, number_of_elements - 1, directoryEntries))
        {
            return -1;
        }
        if (getArrayLength(paths) < 3)
        {
            fileSystem.del(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], nullptr, superBlock, directoryEntries, fat_table, free_table);
        }
        else
        {
            fileSystem.del(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], paths[2], superBlock, directoryEntries, fat_table, free_table);
        }
    }
    else if (strcmp(operation, "read") == 0)
    {
        if (!fileSystem.isExist(splittedPath, number_of_elements - 1, directoryEntries))
        {
            return -1;
        }
        if (getArrayLength(paths) < 3)
        {
            fileSystem.read(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], paths[1], nullptr, superBlock, directoryEntries, fat_table, free_table);
        }
        else
        {
            fileSystem.read(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], paths[1], paths[2], superBlock, directoryEntries, fat_table, free_table);
        }
    }
    else if (strcmp(operation, "dumpe2fs") == 0)
    {
        fileSystem.dumpe2fs(superBlock, free_table, fat_table, directoryEntries);
    }
    else if (strcmp(operation, "chmod") == 0)
    {
        fileSystem.chmod(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], directoryEntries, argv[4]);
    }
    else if (strcmp(operation, "addpw") == 0)
    {
        fileSystem.addpw(splittedPath[number_of_elements - 2], splittedPath[number_of_elements - 1], directoryEntries, argv[4]);
    }
    else
    {
        std::cout << "\"" << operation << "\": NOT A VALID COMMAND" << std::endl;
    }

    std::ofstream file2(fileSystem.getFilename(), std::ios::in | std::ios::out | std::ios::binary);
    if (fileSystem.getDirectoryEntriesChanged() == 1)
    {
        file2.seekp(0, std::ios::beg);

        size_t offset = sizeof(SuperBlock) + (superBlock.getFatBlocks() + superBlock.getFreeBlocks()) * superBlock.getBlockSize();
        file2.seekp(offset, std::ios::beg);

        file2.write(reinterpret_cast<const char *>(directoryEntries), sizeof(DirectoryEntry) * MAXNUMBEROFFILE);
    }
    if (fileSystem.getFatTableChanged() == 1)
    {
        file2.seekp(0, std::ios::beg);

        file2.seekp(sizeof(SuperBlock) + (superBlock.getBlockSize() * superBlock.getFreeBlocks()), std::ios::beg);

        for (int i = 0; i < superBlock.getNumberOfBlocks(); i++)
        {
            file2.write(reinterpret_cast<char *>(&fat_table[i]), sizeof(int));
        }
    }
    if (fileSystem.getFreeTableChanged() == 1)
    {
        file2.seekp(0, std::ios::beg);

        file2.seekp(sizeof(SuperBlock), std::ios::beg);

        for (int i = 0; i < superBlock.getNumberOfBlocks(); i++)
        {
            file2.write(reinterpret_cast<char *>(&free_table[i]), sizeof(int));
        }
    }

    file2.close();

    return 0;
}