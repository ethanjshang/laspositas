//
//  main.cpp
//  BinaryTree
//
//  Created by Ethan Shang on 4/25/17.
//  Copyright © 2017 Ethan Shang. All rights reserved.
//

#include <iostream>
using namespace std;
template <typename T>
struct BSTNode
{
    T key;
    BSTNode<T> * left;
    BSTNode<T> * right;
    BSTNode(T key){
        this->key = key;
        left = right = NULL;
    }
    
    bool IsLeaf(){
        return left == NULL && right == NULL;
    }

    bool OnlyHasLeftChild() {
        if(left != NULL && right == NULL)
            return true;
        else
            return false;
    }
    
    bool OnlyHasRightChild()
    {
        if(left == NULL && right != NULL)
            return true;
        else
            return false;
    }
    bool HasTwoChildren(){
        if(left != NULL && right != NULL)
            return true;
        else
            return false;
    }
    
    void SetChildPointer(bool setLeftSide, BSTNode<T> * newValue)
    {
        if (setLeftSide)
            left = newValue;
        else
            right = newValue;
    }
    
    

};



template <typename T>

class BST {
private:
    BSTNode<T> * root;
    BSTNode<T> * FindNode(BSTNode<T> * p, T key)
    {
        
        BSTNode<T> *returnNode = NULL;
        bool recursive = true;
        if (p == NULL){
            return NULL;
        }
        else if (p->key == key){
            returnNode = p;
            recursive = false;
        }
        if (key < p->key and recursive){
            return FindNode(p->left, key);
        }
        else if (key > p->key and recursive){
            return FindNode(p->right, key);
        }

        return returnNode;
    }
    
    void TraverseTree(BSTNode<T> * p)

    {
        if (p != NULL)
        {
            TraverseTree(p->left);
            cout << p->key << " ";
            TraverseTree(p->right);
        }
        
    }
    
    void deleteNode(T key, BSTNode<T> *&nodePtr) // function to find the node to be deleted in the binary tree, gets called from Delete function
    {
        if(key < nodePtr->key) // if key given is less than current key, move left
        {
            deleteNode(key, nodePtr->left);
        }
        else if(key > nodePtr->key) // if key is greater than current key, move right
        {
            deleteNode(key, nodePtr->right);
        }
        
        else // if key matches the current key, proceed to delete node
        {
            makeDeletion(key);
        }
    }
    
    
    void makeDeletion(T item) {
        //Handles case if root is node to be deleted
        if (root->key == item)
        {
            if (root->IsLeaf()) //Checks if only root
            {
                delete root;
                root = NULL;
            }
            else if (root->OnlyHasLeftChild()) //Checks if only left node
            {
                BSTNode<T> * temp = root->left;
                delete root;
                root = temp;
            }
            else if (root->OnlyHasRightChild()) //Checks if only right node
            {
                BSTNode<T> * temp = root->right;
                delete root;
                root = temp;
            }
            else if(root->HasTwoChildren()) //Checks for both nodes
            {
                BSTNode<T> * tLeft = root->left;
                BSTNode<T> * tRight = root->right;
                BSTNode<T> * temp = root->right;
                while(temp->left != NULL)
                {
                    temp = temp->left;
                }
                if(FindParent(root, temp->key)->left->key==temp->key)
                {
                    FindParent(root, temp->key)->left=temp->right;
                }
                else if(FindParent(root, temp->key)->right->key==temp->key)
                {
                    FindParent(root, temp->key)->right=temp->right;
                }
                delete root;
                if(temp == tRight)
                {
                    temp->right = tRight->right;
                }
                else
                {
                    temp->right = tRight;
                }
                temp->left = tLeft;
                root = temp;
            }
            return;
            
        }
        
        BSTNode<T> * parent = FindParent(root, item);
        BSTNode<T> * target = FindNode(parent, item);
        bool targetIsLeftChild = (parent->left == target);
        
        if (target->IsLeaf()) //Similar checks for subtree properties
        {
            parent->SetChildPointer(targetIsLeftChild, NULL);
            delete target;
        }
        else if (target->OnlyHasLeftChild())
        {
            parent->SetChildPointer(targetIsLeftChild, target->left);
            delete target;
        }
        else if (target->OnlyHasRightChild())
        {
            parent->SetChildPointer(targetIsLeftChild, target->right);
            delete target;
        }
        else if(target->HasTwoChildren())
        {
            BSTNode<T> * temp = target->right;
            BSTNode<T> * parentB = FindParent(root, target->key);
            BSTNode<T> * tLeft = target->left;
            BSTNode<T> * tRight = target->right;
            while(temp->left != NULL)
            {
                temp = temp->left;
            }
            if(FindParent(root, temp->key)->left->key==temp->key)
            {
                FindParent(root, temp->key)->left=temp->right; //Continues to find parent until correct one is found
            }
            else if(FindParent(root, temp->key)->right->key==temp->key)
            {
                FindParent(root, temp->key)->right=temp->right;
            }
            
            if(FindParent(root, item)->left->key==item) //"Brings up" left object
            {
                delete target;
                parentB->left= temp;
            }
            else if(FindParent(root, item)->right->key==item) //"Brings up" right object
            {
                delete target;
                parentB->right= temp;
            }
            temp->left = tLeft;
            if(temp == tRight)
            {
                temp->right = tRight->right;
            }
            else
            {
                temp->right = tRight;
            }
        }
        
        
        
    }

    
    void deleteAll_Helper(BSTNode<T> *nodePtr) {
        if (nodePtr)
        {
            deleteAll_Helper(nodePtr->left);
            deleteAll_Helper(nodePtr->right);
            delete nodePtr;
            root = NULL;
        }
    }

    string * myMerge(string A[], int size1, string B[], int size2){
        string *S = new string[size1+size2];
        int iA = 0, iB = 0;
        int iT = 0;
        for (int i = 0; i < size1+size2; i++){
            S[i] = "";
        }
        for (iT = 0; iT < (size1+size2); iT++) {
            if (A[iA] < B[iB]){
                S[iT] = A[iA];
                iA++;
            }
            else if (A[iA] > B[iB]){
                S[iT] = B[iB];
                iB++;
            }
            else if (A[iA] == B[iB]){
                S[iT] = A[iA];
                iT++;
                iA++;
                S[iT] = B[iB];
                iB++;
            }
            if (iA == size1 || iB == size2)
                break;
        }
        iT = iA + iB;
        if (iA< size1){
            for (int i = iA; i<size1;i++, iT++){
                S[iT] = A[i];
            }
        }
        else if (iB<size2){
            for (int i = iB;i<size2;i++,iT++){
                S[iT] = B[i];
            }
        }
        
        return S;
    }
    

    
public:
    BST()
    {
        
        root = NULL;
        
    }
    
    void DeleteAll()
    {
        
        deleteAll_Helper(root);
        
    }
    
    string * merge_sort(string arr[], int n){
        if (n<2){
            return arr;
        }
        int mid = n/2;
        string *T1 = merge_sort(arr,mid);
        string *T2 = merge_sort(arr+mid,n-mid);
        return myMerge(T1,mid,T2,n-mid);
    }
    
    void PrintAll()
    
    {
        cout << endl << "Print all nodes:" << endl;
        if(root != nullptr)
            TraverseTree(root);
        else
            cout << "The tree is empty." << endl;
    }
    
    BSTNode<T> * Find(T key)
    {
        
        return FindNode(root, key);
    }
    
    
    void Insert(T key)
    {
        bool traverse = true;
        BSTNode<T> *node = new BSTNode<T>(key);
        if (root == NULL){
            root = node;
            return;
        }
        BSTNode<T> * ptr = root;
        while (traverse){
            traverse = false;
            if (key < ptr->key and ptr->left != NULL){
                ptr=ptr->left;
                traverse = true;
            }
            else if (key > ptr->key and ptr->right != NULL){
                ptr = ptr->right;
                traverse = true;
            }
        }
        ptr->SetChildPointer((key < ptr->key),node);
    }
    
    
    void Delete(T key) // function that calls helper function  deleteNode
    
    {
        
        cout << endl << endl << "Trying to delete " << key ;
        
        deleteNode(key, root);
        
    }
    
    
    
    void recursiveInsert(string arr[],int start,int end)
    
    {
        int middle =(start+end)/2;
        Insert(arr[middle]);
        // Enter your code here
        if(start <= middle-1)
        {
            recursiveInsert(arr, start, (middle-1));//low
        }
        if(middle+1 <= end)
        {
            recursiveInsert(arr, (middle+1), end);//high
        }
        return;
    }
    
    
    
    void CreateBalancedTree(string arr[], int SIZE)
    
    {
        recursiveInsert(arr, 0, SIZE-1);

    }
    
    BSTNode<T> * FindParent(BSTNode<T> * subtree, T item){
        if (subtree == NULL){
            return NULL;
        }
        if (subtree->left and subtree->left->key == item){
            return subtree;
        }
        if (subtree->right and subtree->right->key == item){
            return subtree;
        }
        if (item < subtree->key){
            return FindParent(subtree->left, item);
        }
        else {
            return FindParent(subtree->right, item);
        }
    }
    
    
};



int main()

{
    /// First Part
    cout << "Part 1:" << endl;
    BST<string> mytree;
    mytree.Insert("E");
    mytree.Insert("C");
    mytree.Insert("A");
    mytree.Insert("B");
    mytree.Insert("F");
    mytree.Insert("D");
    mytree.Insert("J");
    mytree.Insert("I");
    mytree.Insert("H");
    mytree.Insert("G");
    /// "A B C D E F G H I J" should be displayed.
    mytree.PrintAll();
    
    
    
    
    
    if (mytree.Find("I"))
    {
        cout << endl <<  "'I' was found";
        mytree.Delete("I");
    }
    else {
        cout << endl << "Node was not found";
    }

    cout << endl << endl;
    
    /// "A B C D E F G H J" should be displayed.
    
    mytree.PrintAll();
    
    
    
    if (mytree.Find("E"))
        
    {
        cout << endl << "'E' is found.";
        mytree.Delete("E");
        
    }
    
    cout << endl << endl;
    
    /// "A B C D F G H J" should be displayed.
    
    mytree.PrintAll();
    
    
    
    mytree.DeleteAll();
    
    cout << endl << endl;
    
    /// Should display "The tree is empty."
    
    mytree.PrintAll();
    
    
    
    /// Second Part
    
    cout << endl << endl << "Part 2:" << endl;
    
    const int SIZE = 10;
    
    string arrString[SIZE] = {"J","A","G","C","E","D","F","B","H","I"};
    
    string *sortedArr;
    
    
    
    // Use merge sort to sort the array
    
    BST<string> mytree2;
    
    sortedArr = mytree2.merge_sort(arrString, SIZE); // merge sort, sorts the array
    
    /// Display the array to show that it has been sorted
    cout << endl << "Print sorted array: " << endl;
    for (int i=0; i < SIZE; i++)
        
        cout << sortedArr[i] << " ";
    
    cout << endl;

    /// The function CreateBalancedTree() uses insert_recursive() to add nodes to the tree.
    
    cout << "Create a balanced tree"  << endl;
    
    mytree2.CreateBalancedTree(sortedArr, SIZE);
  
    /// Should display "A B C D E F G H I J"
    
    mytree2.PrintAll();
    /// Yes. It is true that we do not have a good way to test if the tree is balanced or not here.
    
    /// The major problem is that the definition of "Balanced Binary Tree" has not been clearly defined.
    
    /// This is good enough for this HW.
    mytree2.DeleteAll();
    /// Should display "The tree is empty."
    mytree2.PrintAll();

    return 0;
    
}
