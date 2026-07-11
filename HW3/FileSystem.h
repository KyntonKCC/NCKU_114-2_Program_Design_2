#pragma once
#include "FSNode.h"

class FileSystem {
   private:
    FSNode** node_table;
    int capacity;
    int node_count;
    int next_number;
    FSNode* root;
    FSNode* mount_point;

   public:
    // [TODO 1]
    //
    // Steps:
    // 1. Allocate an array of FSNode* of size capacity, store in node_table
    //    Initialize every slot to nullptr
    // 2. Call allocFSNode() to create root
    //    - update root pointer
    //    - update link_count
    FileSystem(int capacity = 16);
    
    // [TODO 1]
    ~FileSystem();

    // [TODO 1]
    //
    // Steps:
    // 1. Find the first nullptr slot in node_table
    //    If table full -> Return nullptr
    // 2. new FSNode()
    //    Store in the found slot
    //    next_number++, node_count++
    // 3. Return the node
    FSNode* allocNode(FSNodeType type, const char* content = "");
    // [TODO 4]
    bool freeNode(int node_id);

    // [TODO 5]
    bool mount(FSNode* mountpoint);
    // [TODO 5]
    bool unmount();
    // [TODO 5]
    FSNode* getMountPoint() const;

    // [TODO 2]
    FSNode* getNode(int node_id) const;
    // [TODO 1]
    FSNode* getRoot() const;

    void listAll() const;
};
