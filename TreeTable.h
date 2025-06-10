#pragma once
#include "TreeNode.h"
#include "Table.h"
#include <stack>
#include <string>

class TreeTable : public Table
{
protected:
    PTreeNode _pRoot;
    PTreeNode* _ppRef;
    PTreeNode _pCurrent;
    size_t _currPos;
    std::stack<PTreeNode> _stack;
    std::string _s[20];
    size_t _cap[20];
    size_t _pos;
    void  PrintTreeTable(std::ostream &stream, PTreeNode root);
    void DrawTreeTable(PTreeNode root, size_t lvl);
    void DeleteTreeTable(PTreeNode node);
    void PutValues(PTreeNode node,size_t lvl);
public:
    TreeTable() : Table(){
        _currPos = 0;
        _pRoot = nullptr;
        _pCurrent = nullptr;
        _ppRef = nullptr;
    }

    ~TreeTable(){
        DeleteTreeTable(_pRoot);
    }
    bool IsFull() const override;

    bool Reset() override;
    bool IsTabEnded() const override;
    bool GoNext() override;

    Key GetKey() const override;
    PDataValue GetValue() const override;

    PDataValue FindRecord(Key key) override;
    void DelRecotd(Key key) override;
    void InsRecord(Key key, PDataValue value) override;

    friend std::ostream& operator<<(std::ostream& stream, TreeTable& table){
        std::cout << "Table printing" << std::endl;
        table.PrintTreeTable(stream, table._pRoot);
        return stream;
    }
    void Draw();
    void Show();
};


