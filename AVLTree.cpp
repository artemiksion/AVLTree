#include <iostream>

struct NodeOfAVLTree
{
	NodeOfAVLTree* left;
	NodeOfAVLTree* right;
	int key;
	char height;
	NodeOfAVLTree(int info)
	{
		left = NULL;
		right = NULL;
		height = 1;
		key = info;
	}
};

int max_of(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

void balance_of_height(NodeOfAVLTree*& a)
{
	if ((a->left != NULL) && (a->right != NULL))
	{
		a->height = max_of(a->left->height, a->right->height) + 1;
		return;
	}
	if ((a->left == NULL) && (a->right == NULL) && (a->height != 1))
	{
		a->height = 1;
		return;
	}
	if ((a->left != NULL) || (a->right != NULL))
	{
		if (a->left == NULL)
		{
			a->height = a->right->height + 1;
			return;
		}
		if (a->right == NULL)
		{
			a->height = a->left->height + 1;
			return;
		}
	}
}

void BigLeftTurn(NodeOfAVLTree*& a)
{
	NodeOfAVLTree* b = a->right;
	NodeOfAVLTree* c = b->left;
	a->right = c->left;
	b->left = c->right;
	c->left = a;
	c->right = b;
	balance_of_height(b);
	balance_of_height(a);
	a = c;
	balance_of_height(a);
}

void BigRightTurn(NodeOfAVLTree*& a)
{
	NodeOfAVLTree* b = a->left;
	NodeOfAVLTree* c = b->right;
	a->left = c->right;
	b->right = c->left;
	c->left = b;
	c->right = a;
	balance_of_height(b);
	balance_of_height(a);
	a = c;
	balance_of_height(a);
}

void SmallRightTurn(NodeOfAVLTree*& a)
{
	NodeOfAVLTree* b = a->left;
	a->left = b->right;
	b->right = a;
	balance_of_height(a);
	a = b;
	balance_of_height(a);
}

void SmallLeftTurn(NodeOfAVLTree*& a)
{
	NodeOfAVLTree* b = a->right;
	a->right = b->left;
	b->left = a;
	balance_of_height(a);
	a = b;
	balance_of_height(a);
}

void balance(NodeOfAVLTree* &a)
{
	if (a != NULL)
	{
		balance_of_height(a);
		if (a->height >= 3)
		{
			if ((a->right == NULL) || (a->left == NULL))
			{
				if (a->right == NULL)
				{
					if (a->left->right == NULL)
						SmallRightTurn(a);
					else
						BigRightTurn(a);
				}
				if (a->left == NULL)
				{
					if (a->right->left == NULL)
						SmallLeftTurn(a);
					else
						BigLeftTurn(a);
				}
			}
			else
			{
				if (((a->right->height - a->left->height) == 2) && (a->right->left->height > a->right->right->height))
				    BigLeftTurn(a);
				if (((a->left->height - a->right->height) == 2) && (a->left->right->height > a->left->left->height))
					BigRightTurn(a);
				if (((a->left->height - a->right->height) == 2) && (a->left->right->height <= a->left->left->height))
					SmallRightTurn(a);
				if (((a->right->height - a->left->height) == 2) && (a->right->left->height <= a->right->right->height))
					SmallLeftTurn(a);
			}
		}
	}
}

void goright(NodeOfAVLTree*& a, int& info)
{
	if (a->right != NULL)
	{
		goright(a->right, info);
		if (a->left != NULL)
			balance(a);
	}
	else
	{
		info = a->key;
		if (a->left != NULL)
		{
			NodeOfAVLTree* b = a->left;
			delete a;
			a = b;
		}
		else
		{
			delete a;
			a = NULL;
		}
	}
}

void goleft(NodeOfAVLTree*& a, int& info)
{
	if (a->left != NULL)
	{
		goleft(a->left, info);
		if (a->right != NULL)
			balance(a);
	}
	else
	{
		info = a->key;
		if (a->right != NULL)
		{
			NodeOfAVLTree* b = a->right;
			delete a;
			a = b;
		}
		else
		{
			delete a;
			a = NULL;
		}
	}
}

void find_similar_value_and_delete(NodeOfAVLTree*& a, int& info)
{
	if ((a->left != NULL) && (a->right != NULL))
	{
		if (a->left->height > a->right->height)
			goright(a->left, info);
		else
			goleft(a->right, info);
		a->key = info;
	}
	else
	{
		if ((a->left == NULL) && (a->right == NULL))
		{
			delete a;
			a = NULL;
		}
		else
		{
			if (a->left == NULL)
			{
				NodeOfAVLTree* b = a->right;
				delete a;
				a = b;
			}
			else
			{
				NodeOfAVLTree* b = a->left;
				delete a;
				a = b;
			}
		}
	}
	balance(a);
}

void push_element(NodeOfAVLTree*& a, const int info)
{
	if (a == NULL)
	{
		a = new NodeOfAVLTree(info);
		return;
	}
	else
	{
		if (a->key > info)
		{
			if (a->left != NULL)
				push_element(a->left, info);
			else
			{
				a->left = new NodeOfAVLTree(info);
			}
		}
		if (a->key < info)
		{
			if (a->right != NULL)
				push_element(a->right, info);
			else
			{
				a->right = new NodeOfAVLTree(info);
			}
		}
		balance(a);
	}
}

void pop_element(NodeOfAVLTree*& a, int info)
{
	if (a != NULL)
	{
		if (a->key != info)
		{
			if (info > a->key)
				pop_element(a->right, info);
			else
				pop_element(a->left, info);
			balance(a);
		}
		else
		{
			find_similar_value_and_delete(a, info);
		}
	}
	else
	{
		std::cout << "Cann't delete this element" << std::endl;
		system("pause");
	}
}

void show_AVL_from_smaller_to_bigger(NodeOfAVLTree*& a)
{
	if (a->left != NULL)
		show_AVL_from_smaller_to_bigger(a->left);
	std::cout << a->key << std::endl;
	if (a->right != NULL)
		show_AVL_from_smaller_to_bigger(a->right);
}

void delete_AVLtree(NodeOfAVLTree*& a)
{
	if (a->left != NULL)
		delete_AVLtree(a->left);
	if (a->right != NULL)
		delete_AVLtree(a->right);
	delete a;
	a = NULL;
}

void go_deep(NodeOfAVLTree* a,int i)
{
	if (i == 0)
	{
		if (a == NULL)
		{
			std::cout << "| |";
		}
		else
			std::cout << "|" << a->key << "|";
	}
	else
	{
		if (a != NULL)
		{
			go_deep(a->left, i - 1);
			go_deep(a->right, i - 1);
		}
		else
		{
			go_deep(a, i - 1);
			go_deep(a, i - 1);
		}
	}
}

void show_AVLtree_like_tree(NodeOfAVLTree*& a)
{
	for (int i = 0; i < a->height; i++)
	{
		go_deep(a, i);
		std::cout << std::endl;
	}
}

void show_AVL_from_bigger_to_smaller(NodeOfAVLTree*& a)
{
	if (a->right != NULL)
		show_AVL_from_bigger_to_smaller(a->right);
	std::cout << a->key << std::endl;
	if (a->left != NULL)
		show_AVL_from_bigger_to_smaller(a->left);
}

int CorrectInput()
{
	int number;
	while (true)
	{
		std::cin >> number;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
	return number;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	NodeOfAVLTree* TopNodeOfTree = NULL;
	int choice;
	while (true)
	{
		std::cout << "Choose action wich tree:" << std::endl;
		std::cout << "1.Add element" << std::endl;
		std::cout << "2.Delete element" << std::endl;
		std::cout << "3.Show elements from smaller to bigger" << std::endl;
		std::cout << "4.Show elements from bigger to smaller" << std::endl;
		std::cout << "5.Show elements as tree" << std::endl;
		std::cout << "6.Delete all elements" << std::endl;
		std::cout << "7.Exit" << std::endl;
		choice = CorrectInput();
		if (choice == 1)
		{
			try
			{
				std::cout << "Input number: ";
				int number;
				number = CorrectInput();
				push_element(TopNodeOfTree, number);
			}
			catch (std::bad_alloc)
			{
				std::cout << "Error of memory allocation" << std::endl;
				system("pause");
			}
		}
		if (choice == 2)
		{
			std::cout << "Input element, wich you want to delete: ";
			int number;
			number = CorrectInput();
			pop_element(TopNodeOfTree, number);
		}
		if (choice == 3)
		{
			if (TopNodeOfTree == NULL)
				std::cout << "Tree is empty" << std::endl;
			else
				show_AVL_from_smaller_to_bigger(TopNodeOfTree);
			system("pause");
		}
		if (choice == 4)
		{
			if (TopNodeOfTree == NULL)
				std::cout << "Tree is empty" << std::endl;
			else
				show_AVL_from_bigger_to_smaller(TopNodeOfTree);
			system("pause");
		}
		if (choice == 5)
		{
			if (TopNodeOfTree == NULL)
				std::cout << "Tree is empty" << std::endl;
			else
			    show_AVLtree_like_tree(TopNodeOfTree);
			system("pause");
		}
		if (choice == 6)
		{
			if (TopNodeOfTree != NULL)
			{
				delete_AVLtree(TopNodeOfTree);
			}
			else
			{
				std::cout << "Tree is empty" << std::endl;
				system("pause");
			}
		}
		if (choice == 7)
		{
			if (TopNodeOfTree != NULL)
				delete_AVLtree(TopNodeOfTree);
			break;
		}
		system("cls");
	}
	return 0;
} 
