#include "TreeTable.h"

bool TreeTable::IsFull() const {
    try {
        PTreeNode node = new TreeNode;
    }
    catch(const char*) {
        return true;
    }
    return false;
}

PDataValue TreeTable::FindRecord(Key key){
    PTreeNode pNode = _pRoot;
    _ppRef = &pNode;
    _efficiency = 0;
    while (pNode != nullptr) {
        _efficiency++;
        if (pNode->_key == key){
            break;
        }
        if (pNode->_key < key){
            _ppRef = &pNode->_right;
        }
        if (pNode->_key > key){
            _ppRef = &pNode->_left;
        }
        pNode = *_ppRef;
    }
    return pNode ? nullptr: pNode->_data;
}

void TreeTable::InsRecord(Key key, PDataValue data){
    if (IsFull()){
        throw "No memory";
    }
    if (FindRecord(key) != nullptr) {
        throw "duplicate";
    }
    _dataCount++;
    *_ppRef = new TreeNode(key, data);
}

Key TreeTable::GetKey() const {
    if (_pCurrent == nullptr){
        return "";
    }
    return _pCurrent->_key;
}
PDataValue TreeTable::GetValue() const {
    if (_pCurrent == nullptr){
        return nullptr;
    }
    return _pCurrent->_data;
}

void TreeTable::DelRecotd(Key key){
    if (FindRecord(key) == nullptr){
        throw "No element";
    }
    PTreeNode pNode = *_ppRef;
    if (pNode->_right == nullptr){
        *_ppRef = pNode->_left;
    }
    else{
        if (pNode->_left == nullptr){
            *_ppRef = pNode->_right;
        }
        else{
            PTreeNode pn = pNode->_left;
            PTreeNode* ppr = &(pNode->_left) ;
            while(pn->_right != nullptr){
                ppr = &(pn->_right);
                pn = *ppr;
            }
            pNode->_key = pn->_key;
            pNode->_data = pn->_data;
            pNode = pn;
            *ppr = pn->_left;
        }

    }
    delete(pNode);
}

bool TreeTable::Reset(){
    PTreeNode pNode = _pCurrent = _pRoot;
    while (!_stack.empty())
    {
        _stack.pop();
    }

    _currPos = 0;
    while (pNode != nullptr)
    {
        _stack.push(pNode);
        _pCurrent = pNode;
        pNode = pNode->GetLeft();
    }
    
    return IsTabEnded();
}
bool TreeTable::IsTabEnded() const{
    return _currPos >= _dataCount;
}
bool TreeTable::GoNext(){
    if (!IsTabEnded() && _pCurrent != nullptr){
        _pCurrent = _pCurrent->GetRight();
        PTreeNode pNode = _pCurrent;
        _stack.pop();
        while (pNode != nullptr)
        {
            _stack.push(pNode);
            _pCurrent = pNode;
            pNode = pNode->GetLeft();
        }
        if (_pCurrent == nullptr && !_stack.empty()){
            _pCurrent == _stack.top();
        }
        _currPos++;
    }
    return IsTabEnded();
}

void TreeTable::DeleteTreeTable(PTreeNode node){
    if (node != nullptr){
        DeleteTreeTable(node->GetLeft());
        DeleteTreeTable(node->GetRight());
        delete node;
    }

}

void TreeTable::Draw(){
    std::cout << "From left to right tree table" << std::endl;
    DrawTreeTable(_pRoot, 0);
}

void TreeTable::DrawTreeTable(PTreeNode root, size_t lvl){
    if (root != nullptr){
        DrawTreeTable(root->GetRight(), lvl + 1);
        for (size_t i = 0; i < lvl * 2; i++){
            std::cout << " " << std::endl;
        }
        root->Print(std::cout);
        std::cout<<std::endl;
        DrawTreeTable(root->GetLeft(), lvl+1);
    }
}

void  TreeTable::PrintTreeTable(std::ostream &stream, PTreeNode root){
    if (root != nullptr){
        PrintTreeTable(stream, root->GetRight());
        root->Print(stream);
        std::cout << std::endl;
        PrintTreeTable(stream, root->GetLeft());
    }
}

void TreeTable::PutValues(PTreeNode node,size_t lvl){
    if (node != nullptr && _pos  < 20){
        PutValues(node->GetLeft(), lvl + 1);
        _s[_pos] = node->GetKey();
        _cap[_pos] = lvl;
        _pos++;
        PutValues(node->GetRight(), lvl + 1);
    }
}

void TreeTable::Show(){
    size_t maxl = 0, i, j, k, pn;
    _pos = 0;
    PutValues(_pRoot, 0);
    for (i = 0; i < _pos; i++){
        if (maxl < _cap[i]){
            maxl = _cap[i];
        }

    }
    std::cout << "TREE TABLE" << std::endl;
    for (i = 0; i < maxl + 1; i++){
        pn = 0;
        for (j = 0; j <  _pos; j++){
            if (_cap[j] == i){
                for ( k = 0; k < 2 * (j - pn); k++){
                    std::cout << " ";
                }
                std::cout << _s[k];
                pn = j + 1;
            }
        }
        std::cout << std::endl;
    }
}
