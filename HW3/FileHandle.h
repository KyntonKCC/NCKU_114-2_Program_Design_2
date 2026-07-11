#pragma once
#include "FSNode.h"

class FileHandle {
   private:
    FSNode* node;
    bool is_open;
    int offset;

   public:
    // [TODO 3]
    FileHandle(FSNode* node);
    // [TODO 3]
    ~FileHandle();

    // [TODO 3]
    void open(FSNode* node);
    // [TODO 3]
    void close();

    void seek(int pos);
    int tell() const;
    bool isOpen() const;
    const char* read() const;
    void write(const char* data);
    void printInfo() const;
};
