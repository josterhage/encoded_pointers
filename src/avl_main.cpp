#include "AVL_Tree.hpp"

#include <iostream>
#include <string>

int main(void)
{
	AVL_TreeNodePointer<int,int> rootP = new AVL_TreeNode<int,int>(1, 15);
	
	std::cout << "rootP->key() = " << rootP->key() << '\n';
	std::cout << "rootP->value() = " << rootP->value() << '\n';
	std::cout << "rootP.bf() = " << rootP.bf() << '\n';

	rootP.bf(-1);
	balance_factor_t bf = rootP.bf();
	std::cout << "rootP.bf() = " << bf << '\n';

	AVL_TreeNode<int,int>* tp = rootP;

	std::cout << "tp->key() = " << tp->key() << '\n';
	std::cout << "tp->value() = " << tp->value() << '\n';

	std::string truth = tp == rootP ? "true" : "false";
	std::cout << "tp == rootP : " << truth << '\n';
	int *x = new int(0);
	truth = tp == (void *)x ? "true" : "false";
	std::cout << "tp == x : " << truth << '\n';

	AVL_TreeNodePointer<int, int> nullP;
	
	if (nullP) {
		std::cout << "nullP evaluates true\n";
	} else {
		std::cout << "nullP evaluates false\n";
	}
	
	if (!nullP) {
		std::cout << "!nullP evaluates true\n";
	} else {
		std::cout << "!nullP evaluates false\n";
	}

	if (nullptr == nullP) {
		std::cout << "nullptr == nullP\n";
	}

	if (nullP == tp) {
		std::cout << "error!\n";
	}
}