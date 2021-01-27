/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef __TREE_CLASS__
#define __TREE_CLASS__

//lets implement a basic templated tree
template <class T>
class CIUTreeNode {
public:
	T data;
    CIUTreeNode *left, *right, *parent;

    CIUTreeNode() {
		left = right = parent = NULL;
	};

    CIUTreeNode(T &value) {
		data = value;
	};

    ~CIUTreeNode() {
	};
	
    void operator= (const CIUTreeNode<T> &other) {
		data = other.data;
	};

	bool operator< (T &other) {
		return (data < other);
	};
};

//Our tree will contain the Node defined above
template <class T>
class CIUTree {
public:
    CIUTree() {
		root = NULL;
	};

    ~CIUTree() {
		m_destroy(root);
	};

	//We will define these all as virtuals for inherited trees (like a Huffman Tree and AVL Tree shown later)
	virtual void insert(T &value) {
		m_insert(root,NULL,value);
	};
    virtual CIUTreeNode<T>* search(T &value) {
		return m_search(root,value);
	};
	virtual bool remove(T &value) {
		return m_remove(root,value);
	};
    virtual bool operator< (CIUTree<T> &other) {
		return (root->data < other.first()->data);
	};
    void operator= (CIUTree<T> &other) {
		m_equal(root,other.first());
	};
    CIUTreeNode<T>*& first() {
		return root;
	};


protected:
	//this will be our root node and private functions
    CIUTreeNode<T> *root;
    void m_equal(CIUTreeNode<T>*& node, CIUTreeNode<T>* value) {
		if(value != NULL) {
            node = new CIUTreeNode<T>();
			*node = *value;
			if(value->left != NULL)
				m_equal(node->left, value->left);
			if(value->right != NULL)
				m_equal(node->right, value->right);
		}
	}

    void m_destroy(CIUTreeNode<T>* value) {
		if(value != NULL) {
			m_destroy(value->left);
			m_destroy(value->right);
			delete value;
		}
	};
    void m_insert(CIUTreeNode<T> *&node, CIUTreeNode<T> *parent, T &value) {
		if(node == NULL) {
            node = new CIUTreeNode<T>();
			*node = value;
			node->parent = parent;
		} else if(value < node->data) {
			m_insert(node->left,node,value);
		} else
			m_insert(node->right,node,value);
	};
    void m_insert(CIUTreeNode<T> *&node, CIUTreeNode<T> *parent, CIUTree<T> &tree) {
        CIUTreeNode<T> *value = tree.first();
		if(node == NULL) {
            node = new CIUTreeNode<T>();
			*node = *value;
			node->parent = parent;
		} else if(value->data < node->data) {
			m_insert(node->left,tree);
		} else
			m_insert(node->right,tree);
	};
    CIUTreeNode<T>* m_search(CIUTreeNode<T> *node, T &value) {
		if(node == NULL) 
			return NULL;
		else if(value == node->data)
			return node;
		else if(value < node->data)
			return m_search(node->left,value);
		else
			return m_search(node->right,value);
	};

    bool m_remove(CIUTreeNode<T> *node, T &value) {
		//messy, need to speed this up later
        CIUTreeNode<T> *tmp = m_search(root,value);
		if(tmp == NULL)
			return false;
        CIUTreeNode<T> *parent = tmp->parent;
		//am i the left or right of the parent?
		bool iamleft = false;
		if(parent->left == tmp)
			iamleft = true;
		if(tmp->left != NULL && tmp->right != NULL) {
			if(parent->left == NULL || parent->right == NULL) {
				parent->left = tmp->left;
				parent->right = tmp->right;
			} else {
				if(iamleft)
					parent->left = tmp->left;
				else
					parent->right = tmp->left;
				T data = tmp->right->data;
				delete tmp;
				m_insert(root,NULL,data);
			}
		} else if(tmp->left != NULL) {
			if(iamleft)
				parent->left = tmp->left;
			else
				parent->right = tmp->left;
		} else if(tmp->right != NULL ) {
			if(iamleft)
				parent->left = tmp->right;
			else
				parent->right = tmp->right;
		} else {
			if(iamleft)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		return true;
	};
};

template <class T>
class HuffmanTree : public CIUTree<T> {
public:
	//I have to put this again otherwise the 2nd insert function will overwrite the virtual void
	void insert(T &value) {
		m_insert(root,NULL,value);
	};
	void insert(HuffmanTree<T> &tree) {
		m_insert(root,NULL,tree);
	};
    void insert_left(CIUTree<T> &tree) {
		m_equal(root->left,tree.first());
	}
    void insert_right(CIUTree<T> &tree) {
		m_equal(root->right,tree.first());
	};
};

template <class T>
class AVLTree : public CIUTree<T> {
public:
	//I need to redefine the insert and remove functions so the tree balances
	void insert(T value) {
		m_insert(root,NULL,value);
		m_balance(root,NULL);
	};
	bool remove(T &value) {
		bool ret = m_remove(root,value);
		m_balance(root,NULL);
		return ret;
	};

private:
    void m_balance(CIUTreeNode<T> *&node, CIUTreeNode<T> *parent) {
		//there could be multiple cases since you can insert an entire tree
		//therefore we must check the balance of the entire tree

	}
};

#endif //__TREE_CLASS__
