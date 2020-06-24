class Solution {
public:

	bool isValidBST(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> TreeNodeStack;
        TreeNode* temp;
        if(root==nullptr) return true;
        TreeNodeStack.push(root);
        while(!TreeNodeStack.empty()){
            temp = TreeNodeStack.top();
            TreeNodeStack.pop();
            if(temp!=nullptr){
                if(temp->right) TreeNodeStack.push(temp->right);
                TreeNodeStack.push(temp);
                TreeNodeStack.push(nullptr);
                if(temp->left) TreeNodeStack.push(temp->left);
            }
            else{
				if(result.size()>=1 && TreeNodeStack.top()->val<=result.back()) {
                    return false;
                }
                
				result.push_back(TreeNodeStack.top()->val);
                TreeNodeStack.pop();
            }
        }
        return true;
    }
};