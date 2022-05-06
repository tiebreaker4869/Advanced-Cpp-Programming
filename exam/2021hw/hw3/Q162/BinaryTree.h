#ifdef BINARYTREE_EXPORTS
#define BINARYTREE_API __declspec(dllexport)
#else
#define BINARYTREE_API __declspec(dllimport)
#endif

#include <iostream>

namespace cpp {
	struct BINARYTREE_API TreeNode {
	public:
		int data;
		TreeNode *left, *right;

		TreeNode(void);
		TreeNode(int data);

	private:
		TreeNode(int data, TreeNode *left, TreeNode *right);
	};

	BINARYTREE_API void print_tree(const TreeNode *root);
}