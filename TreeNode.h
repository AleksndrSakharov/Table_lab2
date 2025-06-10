#pragma once
#include "TabRecord.h"

class TreeNode;

using PTreeNode = TreeNode*;

class TreeNode : public TabRecord
{
protected:
   PTreeNode _left;
   PTreeNode _right;

public:
    TreeNode(Key key = "", PDataValue data = nullptr,
    PTreeNode left = nullptr, PTreeNode right = nullptr) : TabRecord(key, data), _right(right), _left(left){    }
    PTreeNode GetLeft() const{
        return _left;
    }
    PTreeNode GetRight() const{
        return _right;
    }   

    virtual PDataValue GetCopy() override{
        PTreeNode a = new TreeNode(_key, _data, nullptr, nullptr);
        return a;
    }

    friend class TreeTable;
    friend class Balance;
};