#include<bits/stdc++.h>

using namespace std;

class BSTNode{
    public:
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode() : data(0), left(nullptr), right(nullptr) {}
    BSTNode(int data) : data(data), left(nullptr), right(nullptr) {}
    BSTNode(int data, BSTNode* left, BSTNode* right): data(data), left(left), right(right) {}

    ~BSTNode(){
        delete left;
        delete right;
    }
};

// create BST from sorted input array
BSTNode* createBST(vector<int>& arr, int s, int e){
    if(s>e){
        return nullptr;
    }
    int mid = (s+e)/2;
    int rootdata = arr[mid];
    BSTNode* root = new BSTNode(rootdata);
    root->left = createBST(arr, s, mid-1);
    root->right = createBST(arr, mid+1, e);

    return root;
}

BSTNode* searchBST(BSTNode* root, int val){

    // 1. Recursive approach
    if(root == nullptr)return nullptr;
    if(root->data == val) return root;

    if(root->data < val){
        return searchBST(root->right, val);
    }
    else if (root->data > val)
    {
        return searchBST(root->left, val);
    }
    return nullptr;

    // 2. Iterative Approach
    // while (root != nullptr)
    // {
    //     if(root->data ==val)return root;
    //     if(root->data <val){
    //         root = root->right;
    //     }else if(root->data >val){
    //         root= root->left;
    //     }
    // }
    // return nullptr;
}

// min key in BST
int minBST(BSTNode* root){
    if(root == nullptr)return -1;
    while(root->left){
        root=root->left;
    }
    return root->data;
}

// max key in BST
int maxBST(BSTNode* root){
    if(root==nullptr)return -1;
    while(root->right){
        root=root->right;
    }
    return root->data;
}

// range sum in BST
int rangeSumBST(BSTNode* root, int low, int high){
    if(root==nullptr)return 0;
    int sum =0;

    if(root->data >= low && root->data <= high){
        sum += root->data;
    }
    if(root->data<low){
        sum+= rangeSumBST(root->right, low, high);
    }else if(root->data>high){
        sum+= rangeSumBST(root->right, low, high);
    }else{
        sum+= rangeSumBST(root->left, low, high)+ rangeSumBST(root->right, low,high);
    }

    return sum;
}

// check if BT is BST
bool isBST(BSTNode* root, long long minV= -1e10, long long maxV = 1e10){
    if(root==nullptr)return true;

    bool left = isBST(root->left, minV, root->data);
    bool right = isBST(root->right, root->data, maxV);

    if(left && right && root->data >minV && root->data<maxV) 
        return true;
    else 
        return false;
}

// level order
vector<vector<int>> levelOrderTraversal(BSTNode* root){
    vector<vector<int> > v;
        if(root==nullptr){
            return v;
        }
        vector<int> tmp;   /// tmp is storing result of current level
        
        queue<BSTNode*> q;
        q.push(root);
        q.push(nullptr);

    while(!q.empty()){
        BSTNode* f = q.front();
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

int main(){

    vector<int> array {1,2,3,4,5,6,7};
    int n = array.size();
    BSTNode* root = createBST(array,0,n-1);

    vector<vector<int>> v = levelOrderTraversal(root);
        cout<<"BST - Level Order Traversal\n";
        for(int i=0; i<v.size(); i++){
            for(auto it = v[i].begin(); it != v[i].end(); it++){
                cout<<*it<<" ";
            }
            cout<<endl;
        }

    cout<<"\nValue contained in node returned by search is: "<<searchBST(root,4)->data<<endl;

    cout<<"\nMin value in BST: "<<minBST(root)<<endl;
    cout<<"\nMax value in BST: "<<maxBST(root)<<endl;

    cout<<"\nSum within range [3,7] is: "<<rangeSumBST(root,3,7)<<endl;

    bool flag = isBST(root);
    if(flag == true) {cout<<"BT is BST\n"; }
    else cout<<"\nBT is not BST\n";

}