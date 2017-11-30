#include<iostream>
using namespace std;

template <class Type>
class BinarySearchTree{
private:
    struct BinaryNode{
        Type data;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Type &thedata,BinaryNode *lt,BinaryNode *rt)
            :data(thedata),left(lt),right(rt){}
    };
public: 
    BinarySearchTree(BinaryNode *t=NULL) {root=t;};
    ~BinarySearchTree(){};
    bool find (const Type &x) const;
    void insert (const Type &x);
    void remove(const Type &x);
    
private: 
    BinaryNode *root;
    void insert(const Type &x,BinaryNode *&t);
    void remove(const Type &x,BinaryNode *&t);
    bool find(const Type &x,BinaryNode *t) const;
    void makeEmpty(BinaryNode *&t);
};

template<class Type> 
bool BinarySearchTree<Type> ::find(const Type &x) const{
    return find(x,root);
}

template <class Type> 
bool BinarySearchTree<Type> :: find(const Type &x, BinaryNode *t) const{
    if (t==NULL)
        return false;
    else if (x<t->data)
        return find (x,t->left);
    else if (x>t->data)
        return find (x,t->right);
    else return true;
}

template <class Type> 
void BinarySearchTree <Type> :: insert(const Type &x){
    insert (x,root);
}

template <class Type> 
void BinarySearchTree<Type> :: insert(const Type &x,BinaryNode *&t){
    if (t==NULL) 
        t=new BinaryNode(x,NULL,NULL);
    else if (x<t->data)
        insert(x,t->left);
    else if (x>t->data)
        insert (x,t->right);

}

template <class Type> 
void BinarySearchTree<Type> ::remove(const Type &x){
    remove(x,root);
}

template <class Type> 
void BinarySearchTree<Type> ::remove(const Type &x,BinaryNode *&t){
    if (t==NULL) return;
    if (x<t->data) remove (x,t->left);
    if (x>t->data) remove (x,t->right);
    if (x==t->data) {
        if(t->left!=NULL & t->right!=NULL){
            BinaryNode *tmp=t->right; //Choose an adjacent node in MidPost, here right.
            while (tmp->left!=NULL) tmp=tmp->left;//Find a node which has no left node. (Minimun in right branch)
            t->data=tmp->data;
            remove (t->data,t->right);// Then, just two cases remains to be done: (a)The node is a leaf itself . (b) The node only has a leaf.
        }
        else { //Dispose two cases.
            BinaryNode *old_node=t;
            t= (t->left!=NULL)? t->left:t->right;
            delete old_node;
            /* */
        }
    }
}

int main(){
    int a[]={10,8,6,21,87,56,4,0,11,3,22,7,5,34,1,2,9};
    BinarySearchTree <int> tree;
    for (int i=0;i<17;++i)
        tree.insert(a[i]);
    cout<<endl;
    cout<<"find 2 is"<<(tree.find(2)?"true":"false")<<endl;
    tree.remove(3);
    cout<<"3"<<(tree.find(3)?"exists":"doesnt exist")<<endl;
    return 0;
}