/*
* Binary Serach Tree 二叉搜索树
*/

#include <iostream>
#include <functional>
#include <queue>
using namespace std;

// BST类
template<class T,typename Compare=less<T>>
class BSTreee
{
public:
	BSTreee()
		:root_(nullptr)
	{}

	// 插入操作（非递归实现）
	void n_insert(const T& val)
	{
		if (root_ == nullptr)
		{// 树为空，生成根节点
			root_ = new Node(val);
			return;
		}

		Node* parent = nullptr;  //用于记录父节点的位置
		Node* cur = root_;
		
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{// 元素相同，不插入相同的值,
				return;
			}
			else if (cmp_(cur->data_, val))   // 小于关系
			{
				parent = cur;
				cur = cur->right_;
			}
			else   // 大于关系	//if (cur->data_ > val)
			{
				parent = cur;
				cur = cur->left_;
			}
		}

		// 出来的情况就是cur == nullptr，parent是原始BST的叶子节点
		if (cmp_(val, parent->data_))    // 小于关系
		{
			parent->left_ = new Node(val);;
		}
		else
		{
			parent->right_ = new Node(val);;
		}
	}

	// 删除操作（非递归实现）
	void n_remove(const T& val)
	{
		if (root_ == nullptr)
		{
			return;
		}

		// s搜索待删除节点
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				break;
			}
			else if (cmp_(cur->data_, val))
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				parent = cur;
				cur = cur->left_;
			}
		}

		if (cur == nullptr)
		{
			return; // 未找到待删除节点
		}

		// 处理情况三
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			// 寻找前驱节点
			parent = cur;
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				parent = pre;
				pre = pre->right_;
			}

			cur->data_ = pre->data_;
			cur = pre;  // 让cur指向前驱节点，转化为情况1，2   2的情况可能是左孩子也可能是右孩子
		}

		//cur指向删除节点，parent指向其父节点， 统一处理cur指向的节点，此时属于情况1或者2

		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}

		if (parent == nullptr)
		{
			// 删除的是根节点
			root_ = child;
		}
		else
		{
			// 把带删除孩子节点写入到父节点中
			if (parent->left_ == cur)
			{
				parent->left_ = child;
			}
			else
			{
				parent->right_ = child;
			}
		}
		delete cur;  // 删除当前节点
	}

	// 查找操作
	bool n_query(const T& val)
	{
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{
				return true;
			}
			else if (cmp_(cur->data_, val))
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}
		return false;
	}

	// 递归前序遍历(接口)
	void PreOrder()
	{
		cout << "[递归]前序遍历" << endl;
		PreOrder(root_);
		cout << endl;
	}

	// 递归中序遍历(接口)
	void InOrder()
	{
		cout << "[递归]中序遍历" << endl;
		InOrder(root_);
		cout << endl;
	}

	// 递归后序遍历（接口）
	void PostOrder()
	{
		cout << "[递归]后序遍历" << endl;
		PostOrder(root_);
		cout << endl;
	}

	// 递归层序遍历（接口）
	void levelOrder()
	{
		cout << "[递归]层序遍历" << endl;
		int h = high();   // 树的层数
		for (int i = 0; i < h; ++i)
		{
			levelOrder(root_, i);
		}
		cout << endl;
	}

	// 递归求层数(接口)
	int high()
	{
		return high(root_);
	}

	// 递归求二叉树节点个数（接口）
	int number()
	{
		return number(root_);
	}

	// 层序遍历非递归(接口)
	void n_levelOrder()
	{
		return n_levelOrder(root_);
	}

private:
	// 节点定义
	struct Node
	{
		Node(T data = T())
			:data_(data)
			, left_(nullptr)
			, right_(nullptr)
		{}

		T	data_;		// 数据
		Node* left_;	// 左孩子
		Node* right_;	// 右孩子
	};


	// 递归前序遍历（实现）
	void PreOrder(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " ";		// 访问当前节点
			PreOrder(node->left_);			// 访问左孩子
			PreOrder(node->right_);			// 访问右孩子
		}
	}
	 
	// 递归中序遍历(实现)
	void InOrder(Node* node)
	{
		if (node != nullptr)
		{
			InOrder(node->left_);			// 访问左孩子
			cout << node->data_ << " ";		// 访问当前节点
			InOrder(node->right_);			// 访问右孩子
		}
	}

	// 递归后序遍历(实现)
	void PostOrder(Node* node)
	{
		if (node != nullptr)
		{
			PostOrder(node->left_);			// 访问左孩子
			PostOrder(node->right_);			// 访问右孩子
			cout << node->data_ << " ";		// 访问当前节点
		}
	}
	/*
	* 注意：递归是深度遍历，而层序遍历是广度遍历，需要求出来层数
	*/
	// 递归层序遍历实现
	void levelOrder(Node* node,int h)
	{
		if (node == nullptr)
			return;

		if (h == 0)
		{
			// 递归到当前层
			cout << node->data_ << " ";
			return;
		}
		levelOrder(node->left_, h - 1);
		levelOrder(node->right_, h - 1);
	}

	// 递归求层数(实现)
	int high(Node * node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left = high(node->left_);    //  L
		int right = high(node->right_);  // R

		return left > right ? left + 1 : right + 1;   // V
	}

	// 递归求二叉树节点个数（实现）
	int number(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}

		int left = number(node->left_);   // L
		int right = number(node->right_);  // R

		return left + right + 1;  // V

	}

	// 层序遍历非递归(实现)
	void n_levelOrder(Node* node)
	{
		if (node == nullptr)
			return;
		queue<Node*> queue;
		queue.push(node);
		while (!queue.empty())
		{
			Node* valNode = queue.front();
			queue.pop();              // 队列出队
			cout << valNode->data_ << " ";
			if (valNode->left_ != nullptr)
			{
				queue.push(valNode->left_);
			}
			if (valNode->right_ != nullptr)
			{
				queue.push(valNode->right_);
			}
		}
	}

	Node* root_;			// 指向BST的根节点
	Compare		cmp_;		// 比较对象
};


int main()
{
	int arr[] = { 58,24,67,0,34,62,69,5,41,64,78 };
	BSTreee<int> bst;

	for (int v : arr)
	{
		bst.n_insert(v);
	}

	bst.PreOrder();
	bst.InOrder();
	bst.PostOrder();

	cout << bst.high() << endl;
	cout << bst.number() << endl;
	bst.levelOrder();
	bst.n_levelOrder();

	return 0;
}