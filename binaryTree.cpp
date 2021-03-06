// every node can have utmost 2 children

#include<bits/stdc++.h>

using namespace std;

template <typename T>
class BTNode{
    public:
    T data;
    BTNode* left;
    BTNode* right;

    BTNode() : data(0), left(nullptr), right(nullptr) {}
    BTNode(T data) : data(data), left(nullptr), right(nullptr) {}
    BTNode(T data, BTNode* left, BTNode* right): data(data), left(left), right(right) {}

    ~BTNode(){
        delete left;
        delete right;
    }
};

void printBTreeRecursive(BTNode<int>* root){
    if(root == nullptr){  //base case
        return; 
    }
    cout<<root->data<< ": ";
    if(root->left){
        cout<<"L"<<root->left->data<<" ";
    }
    if(root->right){
        cout<<"R"<<root->right->data;
    }
    cout<<endl;
    printBTreeRecursive(root->left);
    printBTreeRecursive(root->right);
}

BTNode<int>* takeInput(){
    int rootdata;
    cout<<"Enter root data: \n";
    cin>>rootdata;
    if(rootdata == -1){
        return nullptr;
    }
    BTNode<int>* root = new BTNode<int>(rootdata);
    BTNode<int>* leftchild = takeInput();
    BTNode<int>* rightchild = takeInput();

    root->left = leftchild;
    root->right = rightchild;

    return root;

}

BTNode<int>* takeInputLevelwise(){
    int rootData;
    cout<<"Enter root data"<<endl;
    cin>>rootData;
    BTNode<int>* root = new BTNode<int>(rootData);
    queue<BTNode<int>*> q;
    q.push(root);

    while(!q.empty()){
        BTNode<int>* f = q.front();
        q.pop();

         cout<<"Enter left child of "<<f->data<<endl;
         int leftChildData;
         cin>>leftChildData;
         if(leftChildData != -1){
            BTNode<int>* child = new BTNode<int>(leftChildData);
            q.push(child);
            f->left = child;
         }
         cout<<"Enter right child of "<<f->data<<endl;
         int rightChildData;
         cin>>rightChildData;
         if(rightChildData != -1){
            BTNode<int>* child = new BTNode<int>(rightChildData);
            q.push(child);
            f->right = child;
         }
    }
    return root;
}

void printlevelWise(BTNode<int>* root){
    if(root == nullptr){
        return;
    }
    cout<<root->data<<endl;
    queue< BTNode<int>* > q;
    q.push(root);

    while(!q.empty()){
        BTNode<int>* f = q.front();
        q.pop();

        if(f->left){
            cout<<f->left->data<<endl;
            q.push(f->left);
        }
        if(f->right){
            cout<<f->right->data<<endl;
            q.push(f->right);
        }
    }
}
// level order
vector<vector<int>> levelOrderTraversal(BTNode<int>* root){
    vector<vector<int> > v;
        if(root==nullptr){
            return v;
        }
        vector<int> tmp;   /// storing is storing result of current level
        
        queue<BTNode<int>*> q;
        q.push(root);
        q.push(nullptr);

    while(!q.empty()){
        BTNode<int>* f = q.front();
        q.pop();

        if(f==nullptr){
            // cout<<endl;
            v.push_back(tmp);
            tmp.clear();
            if(!q.empty()){
                q.push(nullptr);
            }

        }else{
            tmp.push_back(f->data);
            if(f->left){
                q.push(f->left);
            }
            if(f->right){
                q.push(f->right);
            }

        }
    }
return v;
}
// count nodes in BT
int countNodes(BTNode<int>* root){
    if(root==nullptr){
        return 0;
    }
    return countNodes(root->left) + countNodes(root->right) +1;
}

//ionrder traversal
void inorder(BTNode<int>* root, vector<int> &ans){
        if(root==nullptr) return;
        
        inorder(root->left,ans);   // left
        ans.push_back(root->data);       // data
        inorder(root->right,ans);   // right
    }
    vector<int> inorderTraversal(BTNode<int>* root) {
        vector<int> ans;
        inorder(root,ans);
        return ans;
    }
// preorder traversal
void preorder(BTNode<int>* root, vector<int> &ans){
    if(root == nullptr){
        return;
    }
    ans.push_back(root->data);
    preorder(root->left, ans);
    preorder(root->right, ans);
    }
    vector<int> preorderTraversal(BTNode<int>* root){
        vector<int> ans;
        preorder(root, ans);
        return ans;
    } 

//post order traversal
void postorder(BTNode<int>* root, vector<int> &ans){
    if(root == nullptr){
        return;
    }
    postorder(root->left, ans);
    postorder(root->right, ans);
    ans.push_back(root->data);
    }
    vector<int> postorderTraversal(BTNode<int>* root){
        vector<int> ans;
        postorder(root, ans);
        return ans;
    } 

// max-depth of BT
int maxdepth(BTNode<int>* root){
    if(root == nullptr) return 0;

    int left_depth = maxdepth(root->left);
    int right_depth = maxdepth(root->right);

    return max(left_depth, right_depth)+1;
}

// check Binary Tree is Symmetric
bool checksymmetry(BTNode<int>* lsub_tree, BTNode<int>* rsub_tree){
    if(lsub_tree==NULL && rsub_tree!=NULL) return false;
        if(lsub_tree!=NULL && rsub_tree==NULL) return false;
        if(lsub_tree==NULL && rsub_tree==NULL) return true;
        
        if(lsub_tree->data != rsub_tree->data) return false;
        
        
        return checksymmetry(lsub_tree->left,rsub_tree->right) &&
               checksymmetry(lsub_tree->right,rsub_tree->left);
}
bool issymmetric(BTNode<int>* root){
    if(root==nullptr) return true;
    return checksymmetry(root->left, root->right);
}
    

int main(){

    // BTNode<int>* root = new BTNode<int>(1);
    // BTNode<int>* n1 = new BTNode<int>(2);
    // BTNode<int>* n2 = new BTNode<int>(3);
    // root->left = n1;
    // root->right =n2;

    // BTNode<int>* root = takeInput();
    BTNode<int>* root = takeInputLevelwise();

    // printBTreeRecursive(root);
    // printlevelWise(root);
    vector<vector<int>> v = levelOrderTraversal(root);
    cout<<"Level Order Traversal\n";
    for(int i=0; i<v.size(); i++){
        for(auto it = v[i].begin(); it != v[i].end(); it++){
            cout<<*it<<" ";
        }
        cout<<endl;
    }
    cout<<"\nNumber of nodes: "<<countNodes(root)<<endl;

    cout<<"\nInorder traversal\n";
    vector<int> inOrder = inorderTraversal(root);
    for(int i=0; i<inOrder.size(); i++){
        cout<<inOrder[i]<<" ";
    }
    

    cout<<"\nPreorder traversal\n";
    vector<int> preOrder = preorderTraversal(root);
    for(int i=0; i<preOrder.size(); i++){
        cout<<preOrder[i]<<" ";
    }
    

    cout<<"\nPostorder traversal\n";
    vector<int> postOrder = postorderTraversal(root);
    for(int i=0; i<postOrder.size(); i++){
        cout<<postOrder[i]<<" ";
    }

    cout<<"\nMax Depth of Binary Tree:"<<maxdepth(root)<<endl;
    cout<<endl;

    bool flag = issymmetric(root);
    if(flag == true){
        cout<<"\nBinart Tree is Symmetric\n";
    }else{
        cout<<"\nBinary Tree is Not Symmetric\n";
    }

    delete root;
    return 0;
}

//3 9 20 -1 -1 15 7 -1 -1 -1 -1