```
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:

    int preindex = 0;

    int get_index( vector<int> &in , int data ) {
        for( int i = 0 ; i < in.size() ; i++ ) {
            if( data == in[i]) {
                return i;
            }
        }
        return -1;
    }

    void _build( TreeNode ** root, vector<int> &pre,  vector<int> &in, int start, int end ) {
        
        if( start > end ) {
            (*root) = NULL;
            return;
        }
        
        int rootdata = pre[preindex++];
        
        (*root) = new TreeNode(rootdata);
        
        int index = get_index(in,rootdata);
        _build(&((*root)->left),pre,in,start,index-1);
        _build(&((*root)->right),pre,in,index+1, end);
        
        
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        
        TreeNode *root;
        _build(&root,preorder,inorder,0,inorder.size()-1);
        return root;
        
    }
};
```
