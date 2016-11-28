#include<iostream>
#include<assert.h>
using  namespace std;

template<typename K>
struct TreeNode
{
	K _key;
	TreeNode *_left;
	TreeNode *_right;
	TreeNode(const K& key)
		: _key(key)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<typename K>
class BinaryTree
{
	typedef TreeNode<K> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}

	void Insert(const K& key)
	{
		_Insert(key);
	}

	bool Find(const K& key)
	{
		if (_root == NULL)
			return false;
		else
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
					cur = cur->_left;
				else if (cur->_key < key)
					cur = cur->_right;
				else
					return true;
			}
			return false;
		}
	}

	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

	Node* BinaryTreeToList()
	{
		assert(_root);
		Node *ListHead = NULL;

		_BinaryTreeToList(_root,&ListHead);
		//_BinaryTreeToList(_root, ListHead);
		while (ListHead->_left != NULL)
			ListHead = ListHead->_left;
		return ListHead;
	}
	

	void Display()
	{
		Node*	pListNode =  BinaryTreeToList();
		while (pListNode)
		{
			cout << pListNode->_key << " ";
			pListNode = pListNode->_right;
		}
		cout << endl;
	}
	
protected:
	void _BinaryTreeToList(Node *root,Node** pListHead)
	{
		if (root == NULL)
			return ;
		else
		{
			Node *cur = root;

			if (cur->_left!=NULL)
				_BinaryTreeToList(cur->_left, pListHead);//加一个判断条件的好处是当递归到最后一个节点时没必要在递归，减少了额外的开销
			cur->_left = *pListHead;
			if (*pListHead != NULL)
				(*pListHead)->_right = cur;
			*pListHead = cur;
			if (cur->_right != NULL)
				_BinaryTreeToList(cur->_right, pListHead);

		}
	}
/*
	void _BinaryTreeToList(Node *root, Node*& ListNode)
	{
		if (root == NULL)
			return;
		else
		{
			Node *cur = root;
			
			if (cur->_left != NULL)
				_BinaryTreeToList(cur->_left, ListNode);
			if (cur->_left == NULL)
			{
				if (ListNode == NULL)
				{
					ListNode = cur;
				}	
				else
				{
					cur->_left = ListNode;
					ListNode->_right = cur;
					ListNode = cur;
				}
			}
			else
			{
				cur->_left = ListNode;
				ListNode->_right = cur;
				ListNode = cur;
			}

			if (cur->_right != NULL)
				_BinaryTreeToList(cur->_right,ListNode);		 
		}
	}*/
	void _Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node(key);
			return ;
		}
		else
		{
			if (Find(key))
			{
				return;
			}

			Node* cur = _root;
			Node *parent = NULL;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else 
				{
					 parent = cur;
					 cur = cur->_right;
				}
			}    
			/*
			cur = cur1 ->next :cur 假设为0x0018
			cur = new Node(key) :很明显，此时的cur不再是cur1->next所指向的空间，
			想当然的以为，cur 是cur1的下一个节点，则cur 新开辟的节点就会自然而然的也是下一个节点，它又不是cur1->next节点的引用
			*/

			if (parent->_key < key)
				parent->_right = new Node(key);
			else
				parent->_left = new Node(key);
			
		}
	}

	void _Inorder(Node* root)
	{
		if (root == NULL)
			return;
		else
		{
			Node *cur = root;
			_Inorder(cur->_left);
			cout << cur->_key << " " ;
			_Inorder(cur->_right);

		}
	}

protected:
	Node *_root;
};

 

void TextTreeToList()
{
	int a[] = {15,5,12,7,8,4,10,25,9,3};
	BinaryTree<int> bt;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		bt.Insert(a[i]);
	}
	//	bt.Inorder();
		bt.Display();

}
