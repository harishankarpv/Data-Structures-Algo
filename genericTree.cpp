
//GENERIC TREE - No limitation on the number of children for any given TreeNode.
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

template<typename T>
class TreeNode{
    public:
        T data;
        vector< TreeNode<T>* > children;

        TreeNode(T data){
            this->data = data;
        }

        ~TreeNode(){
            for(int i=0; i<children.size(); i++){
                delete children[i];
            }
        }

};

//     1
//     /\
//    2  3

void printTree(TreeNode<int>* root){
    if(root == nullptr)
        return;
    cout<<root->data<<" : ";
    for (int i = 0; i < root->children.size(); i++)
    {
        cout<<root->children[i]->data<<" ";
    }
    cout<<endl;
    for(int i=0; i<root->children.size();i++){
        printTree(root->children[i]);
    }   

}

TreeNode<int>* takeInput(){
    int rootdata {};
    cout<<"enter root data: \n";
    cin>>rootdata;
    TreeNode<int>* root = new TreeNode<int>(rootdata);
    int n {};
    cout<<"enter no of children: \n";
    cin>>n;
    for(int i=1 ;i<=n; i++){
        TreeNode<int>* child = takeInput();
        root->children.push_back(child);
    }
    return root;
}

TreeNode<int>* takeInputLevelWise(){
    int rootdata {};
    cout<<"Enter root data: \n";
    cin>>rootdata;
    TreeNode<int>* root = new TreeNode<int>(rootdata);
    queue<TreeNode<int>*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode<int>* f = q.front();
        q.pop();
        int n {};
        cout<<"Enter no of children of "<<f->data<<"\n";
        cin>>n;
        for(int i=1; i<=n; i++){
            int childData;
            cout<<"Enter data of child TreeNode "<<i<< " of "<<f->data<<endl;
            cin>>childData;
            TreeNode<int>* child = new TreeNode<int>(childData);
            q.push(child);
            f->children.push_back(child);
        }
    }
    return root;

}

void printTreeLevelWise(TreeNode<int>* root){
    queue<TreeNode<int>*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode<int>* f = q.front();
        q.pop();
        cout<<f->data<<" : ";
        for(int i =0; i<f->children.size(); i++){
                cout<<f->children[i]->data<<" ";
        }
        cout<<endl;
        for(int i =0 ;i <f->children.size(); i++){
            q.push(f->children[i]);
        }
    }

}

int countTreeNode(TreeNode<int>* root){
    if(root == nullptr){
        return 0;
    }
    int TreeNodes =1;
    for(int i=0; i<root->children.size();i++){
        TreeNodes += countTreeNode(root->children[i]);
    }
    return TreeNodes;
}

int tree_height(TreeNode<int>* root){
    if(root ==nullptr){
        return 0;
    }
    int max_height =0;
    for(int i=0; i<root->children.size(); i++){
        max_height = max(max_height, tree_height(root->children[i]));
    }
    return max_height +1;
}

void printAtLevelK(TreeNode<int>* root, int k){
    if(root == nullptr)
        return;
    if(k==1){
        cout<<root->data<<"\t";
    }
    for(int i=0;i<root->children.size();i++){
        printAtLevelK(root->children[i],k-1);
    }
    
}

int countLeafTreeNode(TreeNode<int>* root){
    if(root == nullptr){
        return 0;
    }
    if (root->children.size() ==0){
        return 1;
    }
    int leaf_TreeNodes {};
    for(int i=0; i<root->children.size();i++){
        leaf_TreeNodes += countLeafTreeNode(root->children[i]);
    }
    return leaf_TreeNodes;
}

void preOrderTraversal(TreeNode<int>* root){
    if(root== nullptr){
        return;
    }
    cout<<root->data<<" ";
    for(int i=0; i<root->children.size();i++){
        preOrderTraversal(root->children[i]);
    }
}

void postOrderTraversal(TreeNode<int>* root){
    if(root== nullptr){
        return;
    }
    
    for(int i=0; i<root->children.size();i++){
        postOrderTraversal(root->children[i]);
    }
    cout<<root->data<<" ";
}

void deleteTree(TreeNode<int>* root){
    if(root ==nullptr){
        return;
    }
    for(int i=0; i<root->children.size(); i++){
        deleteTree(root->children[i]);
    }
    delete root;
}

int main()
{
    // TreeNode<int>* root = new TreeNode<int>(1);
    // TreeNode<int>* n1 = new TreeNode<int>(2);
    // TreeNode<int>* n2 = new TreeNode<int>(3);

    // root->children.push_back(n1);
    // root->children.push_back(n2);
    cout<<"creating a generic tree\n\n";
    TreeNode<int>* root =takeInputLevelWise(); // 1 3 2 3 4 2 5 6 0 1 7 0 2 8 9 0 0 0 
    // printTree(root);
    cout<<endl;
    cout<<"Printing the generic tree level wise\n";
    printTreeLevelWise(root);
   
    cout<<"Number of TreeNodes :"<<countTreeNode(root)<<"\n";
    
    cout<<"Height of the tree :"<<tree_height(root)<<"\n";
    
    cout<<"Printing TreeNodes at level K. Enter k :\n";
    int k {};
    cin>>k;
    printAtLevelK(root,k);
    cout<<endl;
    cout<< "Number of leaf TreeNodes: "<<countLeafTreeNode(root)<<"\n";
    cout<<"Pre Order Traversal: \n";
    preOrderTraversal(root);
    cout<<"\n Post Order Traversal: \n";
    postOrderTraversal(root);
    cout<<"\ndeleteing the tree \n";
    
    delete root; //calls the destructor which deletes all the children and then deletes the root
    
    return 0;
}

