#include "FSNode.h"
#include "FileSystem.h"
#include <cstring>
#include <iostream>

FSNode::FSNode(int node_id, FSNodeType type, const char* content)
    : node_id(node_id), type(type), link_count(0), open_count(0), mounted_fs(nullptr) {
    memset(this->content, 0, sizeof(this->content));
    if (content) {
        strncpy(this->content, content, 255);
    }
    for (int i = 0; i < MAX_DENTRIES; i++) {
        dentry_inums[i] = 0;
        memset(dentry_names[i], 0, sizeof(dentry_names[i]));
    }
}

FSNode::~FSNode() {}

int FSNode::getNodeId() const { return node_id; }
FSNodeType FSNode::getType() const { return type; }
int FSNode::getLinkCount() const { return link_count; }
int FSNode::getOpenCount() const { return open_count; }
const char* FSNode::getContent() const { return content; }
FileSystem* FSNode::getMountedFs() const { return mounted_fs; }

void FSNode::setContent(const char* new_content) {
    if (new_content) {
        strncpy(this->content, new_content, 255);
        this->content[255] = '\0';
    }
}

void FSNode::setMountedFs(FileSystem* fs) { mounted_fs = fs; }
void FSNode::incrementLinkCount() { link_count++; }
void FSNode::decrementLinkCount() { if (link_count > 0) link_count--; }
void FSNode::incrementOpenCount() { open_count++; }
void FSNode::decrementOpenCount() { if (open_count > 0) open_count--; }

bool FSNode::addDentry(const char* name, FSNode* target) {
    if (type != FSNodeType::DIRECTORY || mounted_fs != nullptr || !target) return false;
    for (int i = 0; i < MAX_DENTRIES; i++) {
        if (dentry_inums[i] != 0 && strcmp(dentry_names[i], name) == 0) return false;
    }
    for (int i = 0; i < MAX_DENTRIES; i++) {
        if (dentry_inums[i] == 0) {
            strncpy(dentry_names[i], name, MAX_NAME_LEN);
            dentry_names[i][MAX_NAME_LEN] = '\0';
            dentry_inums[i] = target->getNodeId();
            target->incrementLinkCount();
            return true;
        }
    }
    return false;
}

bool FSNode::removeDentry(const char* name, FileSystem* fs) {
    if (type != FSNodeType::DIRECTORY || mounted_fs != nullptr) return false;
    for (int i = 0; i < MAX_DENTRIES; i++) {
        if (dentry_inums[i] != 0 && strcmp(dentry_names[i], name) == 0) {
            FSNode* target = fs->getNode(dentry_inums[i]);
            if (target) target->decrementLinkCount();
            dentry_inums[i] = 0;
            memset(dentry_names[i], 0, sizeof(dentry_names[i]));
            return true;
        }
    }
    return false;
}

FSNode* FSNode::findDentry(const char* name, FileSystem* fs) const {
    if (type != FSNodeType::DIRECTORY) return nullptr;
    if (mounted_fs != nullptr) return mounted_fs->getRoot()->findDentry(name, mounted_fs);
    for (int i = 0; i < MAX_DENTRIES; i++) {
        if (dentry_inums[i] != 0 && strcmp(dentry_names[i], name) == 0) {
            return fs->getNode(dentry_inums[i]);
        }
    }
    return nullptr;
}

void FSNode::listDentries(FileSystem* fs) const {
    if (type != FSNodeType::DIRECTORY) return;
    if (mounted_fs != nullptr) {
        mounted_fs->getRoot()->listDentries(mounted_fs);
        return;
    }
    std::cout << "List FSNode #" << node_id << " (DIRECTORY):" << "\n";
    for (int i = 0; i < MAX_DENTRIES; i++) {
        if (dentry_inums[i] != 0) {
            FSNode* target = fs->getNode(dentry_inums[i]);
            std::cout << "  \"" << dentry_names[i] << "\" -> FSNode #"
                      << dentry_inums[i] << " ("
                      << (target && target->getType() == FSNodeType::DIRECTORY ? "DIRECTORY" : "FILE")
                      << ")\n";
        }
    }
}

void FSNode::printInfo() const {
    std::cout << "FSNode #" << node_id << " [" << (type == FSNodeType::DIRECTORY ? "DIR" : "FILE") << "]\n";
    std::cout << "- Link Count: " << link_count << "\n";
    std::cout << "- Open Count: " << open_count << "\n";
}