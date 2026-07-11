#include "FileSystem.h"
#include <iostream>

FileSystem::FileSystem(int capacity)
    : capacity(capacity), node_count(0), next_number(1), mount_point(nullptr) {
    node_table = new FSNode*[capacity];
    for (int i = 0; i < capacity; i++) node_table[i] = nullptr;
    root = allocNode(FSNodeType::DIRECTORY);
    if (root) root->incrementLinkCount();
}

FileSystem::~FileSystem() {
    for (int i = 0; i < capacity; i++) {
        if (node_table[i]) delete node_table[i];
    }
    delete[] node_table;
}

FSNode* FileSystem::allocNode(FSNodeType type, const char* content) {
    if (node_count >= capacity) return nullptr;
    for (int i = 0; i < capacity; i++) {
        if (node_table[i] == nullptr) {
            FSNode* newNode = new FSNode(next_number++, type, content);
            node_table[i] = newNode;
            node_count++;
            return newNode;
        }
    }
    return nullptr;
}

bool FileSystem::freeNode(int node_id) {
    for (int i = 0; i < capacity; i++) {
        if (node_table[i] && node_table[i]->getNodeId() == node_id) {
            if (node_table[i]->getLinkCount() == 0 && node_table[i]->getOpenCount() == 0) {
                delete node_table[i];
                node_table[i] = nullptr;
                node_count--;
                return true;
            }
            return false;
        }
    }
    return false;
}

bool FileSystem::mount(FSNode* mountpoint) {
    if (!mountpoint || mount_point != nullptr || mountpoint->getType() != FSNodeType::DIRECTORY || mountpoint->getMountedFs() != nullptr) {
        return false;
    }
    this->mount_point = mountpoint;
    mountpoint->setMountedFs(this);
    return true;
}

bool FileSystem::unmount() {
    if (!mount_point) return false;
    mount_point->setMountedFs(nullptr);
    mount_point = nullptr;
    return true;
}

FSNode* FileSystem::getMountPoint() const { return mount_point; }

FSNode* FileSystem::getNode(int node_id) const {
    for (int i = 0; i < capacity; i++) {
        if (node_table[i] && node_table[i]->getNodeId() == node_id) return node_table[i];
    }
    return nullptr;
}

FSNode* FileSystem::getRoot() const { return root; }

void FileSystem::listAll() const {
    for (int i = 0; i < capacity; i++) {
        if (node_table[i]) node_table[i]->printInfo();
    }
}