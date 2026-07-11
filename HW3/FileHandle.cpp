#include "FileHandle.h"
#include <cstring>
#include <iostream>

FileHandle::FileHandle(FSNode* node) : node(node), is_open(false), offset(0) {
    if (node) open(node);
}

FileHandle::~FileHandle() {
    if (is_open) close();
}

void FileHandle::open(FSNode* node) {
    if (is_open) close();
    this->node = node;
    this->is_open = true;
    this->offset = 0;
    if (this->node) this->node->incrementOpenCount();
}

void FileHandle::close() {
    if (is_open && node) {
        node->decrementOpenCount();
        is_open = false;
    }
}

void FileHandle::seek(int pos) {
    if (pos < 0) pos = 0;
    if (pos > 255) pos = 255;
    offset = pos;
}

int FileHandle::tell() const { return offset; }
bool FileHandle::isOpen() const { return is_open; }

const char* FileHandle::read() const {
    if (!is_open || !node) return "";
    return node->getContent() + offset;
}

void FileHandle::write(const char* data) {
    if (!is_open || !node) return;
    char buf[256];
    memset(buf, 0, 256);
    strncpy(buf, node->getContent(), 255);
    int len = strlen(data);
    for (int i = 0; i < len && (offset + i) < 255; i++) {
        buf[offset + i] = data[i];
    }
    node->setContent(buf);
}

void FileHandle::printInfo() const {
    if (is_open && node)
        std::cout << "[FileHandle] open    -> FSNode #" << node->getNodeId() << "\n";
    else
        std::cout << "[FileHandle] closed\n";
}