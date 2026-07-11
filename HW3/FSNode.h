#pragma once
#include "FSNodeType.h"

class FileSystem;

#define MAX_DENTRIES 16
#define MAX_NAME_LEN 14

class FSNode {
   private:
    int node_id;
    FSNodeType type;
    int link_count;
    int open_count;
    char content[256];

    int dentry_inums[MAX_DENTRIES];
    char dentry_names[MAX_DENTRIES][MAX_NAME_LEN + 1];

    FileSystem* mounted_fs;

   public:
    // [TODO 1]
    FSNode(int node_id, FSNodeType type, const char* content = "");
    // [TODO 1]
    ~FSNode();

    // [TODO 1]
    int getNodeId() const;
    // [TODO 1]
    FSNodeType getType() const;
    // [TODO 1]
    int getLinkCount() const;
    // [TODO 1]
    int getOpenCount() const;
    // [TODO 1]
    const char* getContent() const;
    // [TODO 1]
    FileSystem* getMountedFs() const;

    // [TODO 1]
    void setContent(const char* new_content);
    // [TODO 1]
    void setMountedFs(FileSystem* fs);

    // [TODO 1]
    void incrementLinkCount();
    // [TODO 1]
    void decrementLinkCount();
    // [TODO 1]
    void incrementOpenCount();
    // [TODO 1]
    void decrementOpenCount();

    // [TODO 2]
    // [TODO 5]
    bool addDentry(const char* name, FSNode* target);

    // [TODO 4]
    // [TODO 5]
    bool removeDentry(const char* name, FileSystem* fs);

    // [TODO 2]
    // [TODO 5]
    FSNode* findDentry(const char* name, FileSystem* fs) const;

    // [TODO 5]
    void listDentries(FileSystem* fs) const;

    void printInfo() const;
};
