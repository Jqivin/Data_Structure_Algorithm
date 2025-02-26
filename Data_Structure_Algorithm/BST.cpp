/*
* Binary Serach Tree ����������
*/

#include <iostream>
#include <functional>
#include <queue>
using namespace std;

// BST��
template<class T,typename Compare=less<T>>
class BSTreee
{
public:
	BSTreee()
		:root_(nullptr)
	{}

	// ����������ǵݹ�ʵ�֣�
	void n_insert(const T& val)
	{
		if (root_ == nullptr)
		{// ��Ϊ�գ����ɸ��ڵ�
			root_ = new Node(val);
			return;
		}

		Node* parent = nullptr;  //���ڼ�¼���ڵ��λ��
		Node* cur = root_;
		
		while (cur != nullptr)
		{
			if (cur->data_ == val)
			{// Ԫ����ͬ����������ͬ��ֵ,
				return;
			}
			else if (cmp_(cur->data_, val))   // С�ڹ�ϵ
			{
				parent = cur;
				cur = cur->right_;
			}
			else   // ���ڹ�ϵ	//if (cur->data_ > val)
			{
				parent = cur;
				cur = cur->left_;
			}
		}

		// �������������cur == nullptr��parent��ԭʼBST��Ҷ�ӽڵ�
		if (cmp_(val, parent->data_))    // С�ڹ�ϵ
		{
			parent->left_ = new Node(val);;
		}
		else
		{
			parent->right_ = new Node(val);;
		}
	}

	// ɾ���������ǵݹ�ʵ�֣�
	void n_remove(const T& val)
	{
		if (root_ == nullptr)
		{
			return;
		}

		// s������ɾ���ڵ�
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
			return; // δ�ҵ���ɾ���ڵ�
		}

		// ���������
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			// Ѱ��ǰ���ڵ�
			parent = cur;
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				parent = pre;
				pre = pre->right_;
			}

			cur->data_ = pre->data_;
			cur = pre;  // ��curָ��ǰ���ڵ㣬ת��Ϊ���1��2   2���������������Ҳ�������Һ���
		}

		//curָ��ɾ���ڵ㣬parentָ���丸�ڵ㣬 ͳһ����curָ��Ľڵ㣬��ʱ�������1����2

		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}

		if (parent == nullptr)
		{
			// ɾ�����Ǹ��ڵ�
			root_ = child;
		}
		else
		{
			// �Ѵ�ɾ�����ӽڵ�д�뵽���ڵ���
			if (parent->left_ == cur)
			{
				parent->left_ = child;
			}
			else
			{
				parent->right_ = child;
			}
		}
		delete cur;  // ɾ����ǰ�ڵ�
	}

	// ���Ҳ���
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

	// �ݹ�ǰ�����(�ӿ�)
	void PreOrder()
	{
		cout << "[�ݹ�]ǰ�����" << endl;
		PreOrder(root_);
		cout << endl;
	}

	// �ݹ��������(�ӿ�)
	void InOrder()
	{
		cout << "[�ݹ�]�������" << endl;
		InOrder(root_);
		cout << endl;
	}

	// �ݹ����������ӿڣ�
	void PostOrder()
	{
		cout << "[�ݹ�]�������" << endl;
		PostOrder(root_);
		cout << endl;
	}

	// �ݹ����������ӿڣ�
	void levelOrder()
	{
		cout << "[�ݹ�]�������" << endl;
		int h = high();   // ���Ĳ���
		for (int i = 0; i < h; ++i)
		{
			levelOrder(root_, i);
		}
		cout << endl;
	}

	// �ݹ������(�ӿ�)
	int high()
	{
		return high(root_);
	}

	// �ݹ���������ڵ�������ӿڣ�
	int number()
	{
		return number(root_);
	}

	// ��������ǵݹ�(�ӿ�)
	void n_levelOrder()
	{
		return n_levelOrder(root_);
	}

private:
	// �ڵ㶨��
	struct Node
	{
		Node(T data = T())
			:data_(data)
			, left_(nullptr)
			, right_(nullptr)
		{}

		T	data_;		// ����
		Node* left_;	// ����
		Node* right_;	// �Һ���
	};


	// �ݹ�ǰ�������ʵ�֣�
	void PreOrder(Node* node)
	{
		if (node != nullptr)
		{
			cout << node->data_ << " ";		// ���ʵ�ǰ�ڵ�
			PreOrder(node->left_);			// ��������
			PreOrder(node->right_);			// �����Һ���
		}
	}
	 
	// �ݹ��������(ʵ��)
	void InOrder(Node* node)
	{
		if (node != nullptr)
		{
			InOrder(node->left_);			// ��������
			cout << node->data_ << " ";		// ���ʵ�ǰ�ڵ�
			InOrder(node->right_);			// �����Һ���
		}
	}

	// �ݹ�������(ʵ��)
	void PostOrder(Node* node)
	{
		if (node != nullptr)
		{
			PostOrder(node->left_);			// ��������
			PostOrder(node->right_);			// �����Һ���
			cout << node->data_ << " ";		// ���ʵ�ǰ�ڵ�
		}
	}
	/*
	* ע�⣺�ݹ�����ȱ���������������ǹ�ȱ�������Ҫ���������
	*/
	// �ݹ�������ʵ��
	void levelOrder(Node* node,int h)
	{
		if (node == nullptr)
			return;

		if (h == 0)
		{
			// �ݹ鵽��ǰ��
			cout << node->data_ << " ";
			return;
		}
		levelOrder(node->left_, h - 1);
		levelOrder(node->right_, h - 1);
	}

	// �ݹ������(ʵ��)
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

	// �ݹ���������ڵ������ʵ�֣�
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

	// ��������ǵݹ�(ʵ��)
	void n_levelOrder(Node* node)
	{
		if (node == nullptr)
			return;
		queue<Node*> queue;
		queue.push(node);
		while (!queue.empty())
		{
			Node* valNode = queue.front();
			queue.pop();              // ���г���
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

	Node* root_;			// ָ��BST�ĸ��ڵ�
	Compare		cmp_;		// �Ƚ϶���
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