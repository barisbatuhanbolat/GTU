#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstring>

using namespace std;

const int MAXSIZE = 4 * 1024 * 1024;
const int MAXNUMBEROFFILE = 512;
const int MAX_FILENAME_LENGTH = 128;
const int PASSWORD_LENGTH = 64;

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
    string owner_permissions; // "R" for read, "W" for write, "RW" for both
    string password;          // Password if the file is protected

public:
    DirectoryEntry(const char filename[], const char parent[], time_t creation_time, time_t last_modification, int size, int first_block, int directory, const string &owner_permissions, const string &password)
    {
        strcpy(this->filename, filename);
        strcpy(this->parent, parent);
        this->creation_time = creation_time;
        this->last_modification = last_modification;
        this->size = size;
        this->first_block = first_block;
        this->directory = directory;
        this->exist = 1;
        this->owner_permissions = owner_permissions;
        this->password = password;
    }

    DirectoryEntry() {}

    friend ostream &operator<<(ostream &os, const DirectoryEntry &entry)
    {
        os << "Filename: " << entry.filename << ", Parent: " << entry.parent << ", Creation Time: " << entry.creation_time << ", Last Modification: " << entry.last_modification << ", Size: " << entry.size << ", First Block: " << entry.first_block << ", Directory: " << entry.directory << ", Exist: " << entry.exist << ", Owner Permissions: " << entry.owner_permissions << ", Password: " << entry.password;
        return os;
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
    SuperBlock(int block_size, int number_of_blocks, int free_blocks, int fat_blocks, int directory_blocks)
    {
        this->block_size = block_size;
        this->number_of_blocks = number_of_blocks;
        this->free_blocks = free_blocks;
        this->fat_blocks = fat_blocks;
        this->directory_blocks = directory_blocks;
    }

    SuperBlock() {}

    friend ostream &operator<<(ostream &os, const SuperBlock &superBlock)
    {
        os << "Block Size: " << superBlock.block_size << ", Number of Blocks: " << superBlock.number_of_blocks << ", Free Blocks: " << superBlock.free_blocks << ", FAT Blocks: " << superBlock.fat_blocks << ", Directory Blocks: " << superBlock.directory_blocks;
        return os;
    }
};

void errExit(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Insufficient number of elements..." << endl;
        exit(EXIT_FAILURE);
    }

    int block_size = 1024 * atoi(argv[1]);
    int number_of_blocks = MAXSIZE / block_size;
    int fat_blocks = ((number_of_blocks * sizeof(int)) + block_size - 1) / block_size;
    int directory_blocks = ((MAXNUMBEROFFILE * sizeof(DirectoryEntry)) + block_size - 1) / block_size;
    int free_blocks = ((number_of_blocks * sizeof(int)) + block_size - 1) / block_size;

    const char *filename = argv[2];

    char rootName[MAX_FILENAME_LENGTH] = "/";
    char rootParent[MAX_FILENAME_LENGTH] = "NOPARENT";

    ofstream file(filename, ios::binary);
    if (!file)
    {
        errExit("ofstream");
    }

    SuperBlock superBlock(block_size, number_of_blocks, free_blocks, fat_blocks, directory_blocks);

    time_t current_time = time(nullptr);
    DirectoryEntry rootDir(rootName, rootParent, current_time, current_time, 0, 0, 1, "RW", "");

    file.write(reinterpret_cast<const char *>(&superBlock), sizeof(SuperBlock));

    vector<int> free_table(number_of_blocks, 1);
    for (int i = 0; i < 1 + free_blocks + fat_blocks + directory_blocks; i++)
    {
        free_table[i] = 0;
    }
    file.write(reinterpret_cast<const char *>(&free_table[0]), free_table.size() * sizeof(int));

    vector<int> fat_table(number_of_blocks, -1);
    file.write(reinterpret_cast<const char *>(&fat_table[0]), fat_table.size() * sizeof(int));

    file.write(reinterpret_cast<const char *>(&rootDir), sizeof(DirectoryEntry));

    file.seekp((directory_blocks - 1) * block_size, ios::beg);
    char buffer[block_size];
    for (int i = 0; i < number_of_blocks - fat_blocks - directory_blocks - free_blocks - 1; i++)
    {
        file.write(buffer, sizeof(char) * block_size);
    }

    file.close();

    return 0;
}
