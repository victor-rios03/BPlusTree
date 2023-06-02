// -------------------------------------------------------------------------------------------------------------------------------------------
// METODOS PUBLICOS --------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
BPlusTree<T,Order>::BPlusTree() : root(NULL), queue(NULL){}

// -------------------------------------------------------------------------------------------------------------------------------------------
template <typename T, int Order>
BPlusTree<T,Order>::~BPlusTree(){
    clear();
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
BPlusTree<T,Order>::BPlusTree(const BPlusTree<T,Order> &bPT) : root(NULL), queue(NULL){
    *this = bPT;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
BPlusTree<T,Order> & BPlusTree<T,Order>::operator=(const BPlusTree<T,Order> &bPT){
    if(this == &bPT) return *this;
    clear();
    copyTree(bPT.root);
    return *this;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
void BPlusTree<T,Order>::insert(T value){
    root = insert(root, value, value);
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
void BPlusTree<T,Order>::remove(T value){
    root = remove(root, value);
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
bool BPlusTree<T,Order>::find(T value){
	return find(root, value) != NULL;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
bool BPlusTree<T,Order>::empty() const{
    return root == NULL;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
void BPlusTree<T,Order>::clear(){
    if(root != NULL)destroyTreeNodes(root);
    root = NULL;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
void BPlusTree<T,Order>::print(){
    printTree(root);
}
// -------------------------------------------------------------------------------------------------------------------------------------------
// METODOS PRIVADOS --------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
typename BPlusTree<T,Order>::Node * BPlusTree<T,Order>::insert(BPlusTree<T,Order>::Node * root, T key, T value){
    Record * tPointer = NULL;
    Node * leaf = NULL;
    /**> Checks if the key is already in the tree */
    tPointer = find(root, key);
    if(tPointer != NULL){
        /**> If the key already exists in the tree, update the value and return the tree */
        tPointer -> value = value;
        return root;
    }
    /**> If the key do not exist in the tree, creates a new Record to save the new value */
    tPointer = new Record(value);

    /**> If the tree does not exist yet, start a new tree */
    if(root == NULL){
        Node *nRoot = makeLeaf();
        nRoot -> keys[0] = key;
        nRoot -> pointers[0] = tPointer;
        nRoot -> pointers[Order-1] = NULL;
        nRoot -> parent = NULL;
        nRoot -> size++;
        return nRoot;
    }

    /**> Find the optimal leaf to put the new value */
    leaf = findLeaf(root, key);

    /**> Checks if the leaf has space to add the new element (key and value) */
    if(leaf -> size < Order - 1){
        leaf = insertIntoLeaf(leaf, key, tPointer);
        return root;
    }

    /**> If the leaf does not have enough space, it is sent to separate the node to later add */
    return insertIntoLeafAfterSplitting(root, leaf, key, tPointer);
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template<typename T, int Order>
typename BPlusTree<T, Order>::Node *BPlusTree<T, Order>::remove(BPlusTree::Node *root, T key){
    Node * leaf = NULL;
    Record * tPointer = NULL;
    /**> Finds the record associated to the key and the leaf where the key is included */
    tPointer = find(root, key);

    /**> If the key is found in the leaf delete it */
    if (tPointer != NULL && leaf != NULL) {
        root = removeEntry(root, leaf, key, tPointer);
        delete tPointer;
    }
    return root;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
typename BPlusTree<T,Order>::Record * BPlusTree<T,Order>::find(BPlusTree<T,Order>::Node * root, T key) {
    /**> Checks if the tree is null */
    if(root == NULL){
        return NULL;
    }

    /**> Finds the leaf holds the range of keys that would include the desired key */
    Node * leaf = findLeaf(root, key);

    /**> In this loop search if the value is in the keys */
    int i;
	for(i = 0; i < leaf -> size; ++i) if(leaf -> keys[i] == key) break; /**> Stops in the index of the key ; otherwise reach the limit */

    /**> If the index reaches the limit it means that does not found the value */
	if (i == leaf -> size) return NULL;
	else return (Record *)leaf -> pointers[i];
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
void BPlusTree<T,Order>::printTree(BPlusTree<T,Order>::Node * const root){
	if(root == NULL){
		std::cout << "Empty tree" << std::endl;
		return;
	}

    Node * n = NULL;          /**> Auxiliar node. Helps to print the tree */
	int i, rank, newRank= 0;  /**> Auxliar variables. Helps to print the levels */
	/**> Auxliar Queue (starts with the root) */
	queue = NULL;
	enqueue(root);
	while(queue != NULL){
		n = dequeue();
		if(n -> parent != NULL && n == n -> parent -> pointers[0]){
			newRank = pathToRoot(root, n);
			if(newRank != rank){
				rank = newRank;
				std::cout << std::endl;
			}
		}
		for(i = 0; i < n -> size; ++i) std::cout << n -> keys[i] << " ";
		/**> If the node have childrens, enqueue all of his childs */
		if(!n -> leaf)
			for(i = 0; i <= n -> size; ++i)
				enqueue((Node*)n -> pointers[i]);
		std::cout << "| ";
	}
	std::cout << std::endl;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
typename BPlusTree<T,Order>::Node * BPlusTree<T,Order>::insertIntoNode(BPlusTree<T,Order>::Node * root, BPlusTree<T,Order>::Node * parent, int leftIndex, T key, BPlusTree<T,Order>::Node * right){
    int i;
    /**> This loop makes space to the new node */
	for(i = parent -> size; i > leftIndex; --i){
		parent -> pointers[i + 1] = parent -> pointers[i];
		parent -> keys[i] = parent -> keys[i-1];
	}
	/**> Insert the new value */
	parent -> pointers[leftIndex+1] = right;
	parent -> keys[leftIndex] = key;
	parent -> size++;
	return root;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
typename BPlusTree<T,Order>::Node * BPlusTree<T,Order>::insertIntoLeaf(BPlusTree<T,Order>::Node * leaf, T key, BPlusTree<T,Order>::Record * pointer){
    int i, insertionPoint = 0;
    /** Finds the position to insert the new value (key and pointer) */
	while(insertionPoint < leaf -> size && leaf -> keys[insertionPoint] < key) insertionPoint++;

    /** Loop through the elements to make room for the new value */
	for(i = leaf -> size; i > insertionPoint; --i){
		leaf -> keys[i] = leaf -> keys[i - 1];
		leaf -> pointers[i] = leaf -> pointers[i - 1];
	}

	/** Insert the new value in his place */
	leaf -> keys[insertionPoint] = key;
	leaf -> pointers[insertionPoint] = pointer;
	leaf -> size++;
	return leaf;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template<typename T, int Order>
typename BPlusTree<T,Order>::Node * BPlusTree<T,Order>::insertIntoParent(BPlusTree<T,Order>::Node * root, BPlusTree<T,Order>::Node * left, T key, BPlusTree<T,Order>::Node * right){
	Node * parent = left -> parent; /**> Copy the father of the brother */

	/**> If no parent exists, one is created */
	if(parent == NULL){
        Node * nRoot = new Node();
        nRoot -> keys[0] = key;
        nRoot -> pointers[0] = left;
        nRoot -> pointers[1] = right;
        nRoot -> size++;
        nRoot -> parent = NULL;
        left -> parent = nRoot;
        right -> parent = nRoot;
        return nRoot;
	}

	/**> Find the parent's pointer to the left node */
	int leftIndex = getLeftIndex(parent, left);

    /**> If the new key fits into the node, add it */
	if(parent -> size < Order - 1) return insertIntoNode(root, parent, leftIndex, key, right);

    /**> If the new key does not fits into the node, add it after splitting */
	return insertIntoNodeAfterSplitting(root, parent, leftIndex, key, right);
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
typename BPlusTree<T,Order>::Node * BPlusTree<T,Order>::insertIntoNodeAfterSplitting(BPlusTree<T,Order>::Node * root, BPlusTree<T,Order>::Node * parent, int leftIndex, T key, BPlusTree<T,Order>::Node * right){
    /**> First create a temporary set of keys and pointers
	     to hold everything in order, including
	     the new key and pointer, inserted in their
	     correct places.
         Then create a new node and copy half of the
	     keys and pointers to the old node and
	     the other half to the new */
    void ** tempPointers = new void*[Order+1];
    T * tempKeys = new T[Order];

	int i, j;
	/**> Copies the actual values in the temp variables */
	for (i = 0, j = 0; i < parent -> size + 1; ++i, ++j){
		if(j == leftIndex + 1) j++;
		tempPointers[j] = parent -> pointers[i];
	}
	for (i = 0, j = 0; i < parent -> size; ++i, ++j){
		if(j == leftIndex) j++;
		tempKeys[j] = parent -> keys[i];
	}
    /**> Insert the new values in the temp variables */
	tempPointers[leftIndex+1] = right;
	tempKeys[leftIndex] = key;

	/**> Create the new node and copy
	     half the keys and pointers to the
	     old and half to the new */
	int split = cut(Order); /**> Determine the correct index to split the node */
	Node * newNode = new Node();
	parent -> size = 0;
	for(i = 0; i < split - 1; ++i){
		parent -> pointers[i] = tempPointers[i];
		parent -> keys[i] = tempKeys[i];
		parent -> size++;
	}
	parent -> pointers[i] = tempPointers[i];
	T kPrime = tempKeys[split-1];
	for(++i, j = 0; i < Order; ++i, ++j){
		newNode -> pointers[j] = tempPointers[i];
		newNode -> keys[j] = tempKeys[i];
		newNode -> size++;
	}
	newNode -> pointers[j] = tempPointers[i];

	delete [] tempPointers;
	delete [] tempKeys;

	newNode -> parent = parent -> parent;
	Node * child;
	for (i = 0; i <= newNode -> size; ++i){
		child = (Node*)newNode -> pointers[i];
		child -> parent = newNode;
	}

	/* Insert a new key into the parent of the two
	 * nodes resulting from the split, with
	 * the old node to the left and the new to the right.
	 */
	return insertIntoParent(root, parent, kPrime, newNode);
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
typename BPlusTree<T,Order>::Node * BPlusTree<T,Order>::insertIntoLeafAfterSplitting(BPlusTree<T,Order>::Node * root, BPlusTree<T,Order>::Node * leaf, T key, BPlusTree<T,Order>::Record * pointer){
	/**> First create a temporary set of keys and pointers
	     to hold everything in order, including
	     the new key and pointer, inserted in their
	     correct places.
	     Then create a new node and copy half of the
	     keys and pointers to the old node and
	     the other half to the new */

	T * tempKeys = new T[Order];
	void ** tempPointers = new void*[Order];

    /**>  Determine the index of the new value in the leaf */
	int insertionIndex = 0;
	while(insertionIndex < Order - 1 && leaf -> keys[insertionIndex] < key) insertionIndex++;

    /**> Copies the actual values in the temp variables */
    int i, j;
	for (i = 0, j = 0; i < leaf -> size; ++i, ++j){
		if(j == insertionIndex) ++j;
		tempKeys[j] = leaf -> keys[i];
		tempPointers[j] = leaf -> pointers[i];
	}
	/**> Insert the new values in the temp variables */
	tempKeys[insertionIndex] = key;
	tempPointers[insertionIndex] = pointer;

	leaf -> size = 0;

	int split = cut(Order - 1); /**> Determine the correct index to split the node */

	/**> Create the new node and copy
         half the keys and pointers to the
	     old and half to the new */
    Node * newLeaf = makeLeaf();
	for(i = 0; i < split; ++i){
		leaf -> pointers[i] = tempPointers[i];
		leaf -> keys[i] = tempKeys[i];
		leaf -> size++;
	}

	for (i = split, j = 0; i < Order; i++, j++) {
		newLeaf -> pointers[j] = tempPointers[i];
		newLeaf -> keys[j] = tempKeys[i];
		newLeaf -> size++;
	}

    delete[] tempPointers;
    delete[] tempKeys;

    /**> Connects the new leaf with the right leaf*/
	newLeaf -> pointers[Order-1] = leaf -> pointers[Order-1];
	leaf -> pointers[Order-1] = newLeaf;

    /**> Loop through all children to leave them empty */
	for(i = leaf -> size; i < Order - 1; ++i) leaf -> pointers[i] = NULL;
	for(i = newLeaf -> size; i < Order - 1; i++) newLeaf -> pointers[i] = NULL;

    /**> Recursively update values up the tree */
	newLeaf -> parent = leaf -> parent;
	T newKey = newLeaf -> keys[0];
	return insertIntoParent(root, leaf, newKey, newLeaf);
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
typename BPlusTree<T, Order>::Node * BPlusTree<T, Order>::removeEntry(BPlusTree::Node * root, BPlusTree::Node *n, T key, void * pointer){
    n = removeEntryFromNode(n, key, pointer);

    /**> If the entry to remove is the root, the tree need to adjust */
    if(n == root) return adjustRoot(root);

    /**> Determines the minimum number of keys that the sheet must have after deleting the entry */
    int minKeys = n -> leaf ? cut(Order - 1) : cut(Order) - 1;

    /**> If the node complies(number of keys), no further changes are needed */
    if(n -> size >= minKeys) return root;

    /**> If the node does not complies, it need to readjust */
    int neighborIndex = getNeighborIndex(n);
    int kPrimeIndex = neighborIndex == -1 /** = no neighbor */ ? 0 : neighborIndex;

    T kPrime = n -> parent -> keys[kPrimeIndex];
    Node * neighbor = neighborIndex == -1 ? (Node*)n -> parent -> pointers[1]: (Node*)n -> parent -> pointers[neighborIndex];
    int capacity = n -> leaf ? Order : Order - 1; /**> Determines the capacity of the node */

    /**> If nodes can be coalesce, they are coalesce, if not they are redistributed */
    if(neighbor -> size + n -> size < capacity) return coalesceNodes(root, n, neighbor, neighborIndex, kPrime);
    else return redistributeNodes(root, n, neighbor, neighborIndex, kPrimeIndex, kPrime);
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
typename BPlusTree<T,Order>::Node * BPlusTree<T,Order>::removeEntryFromNode(BPlusTree<T,Order>::Node * n, T key, void * pointer){
	/**> Remove the key and shift other keys accordingly */
	int i = 0;
	while(n -> keys[i] != key) ++i;
	for (++i; i < n->size; ++i) n -> keys[i-1] = n -> keys[i];

	/**> Remove the pointer and shift other pointers accordingly.
	     First determine number of pointers */
	int numPointers = n -> leaf ? n -> size : n -> size + 1;

	i = 0;
	while (n -> pointers[i] != pointer) ++i;
	for (++i; i < numPointers; ++i) n -> pointers[i-1] = n -> pointers[i];
	n -> size--; /**> One key fewer */

	/**> Set the other pointers to NULL for tidiness.
	     A leaf uses the last pointer to point to the next leaf */
	if(n->leaf)
		for (i = n -> size; i < Order - 1; ++i)
			n -> pointers[i] = NULL;
	else
		for(i = n -> size + 1; i < Order; ++i)
			n -> pointers[i] = NULL;
	return n;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
void BPlusTree<T,Order>::destroyTreeNodes(Node * root){
	int i;
	/**> If the root is a leaf, destroy the pointers;
	     Otherwise call recursively to destroy the children of the node */
	if(root -> leaf)
		for (i = 0; i < root -> size; ++i)
			delete (Node*) root -> pointers[i];
	else
		for (i = 0; i < root -> size + 1; ++i)
			destroyTreeNodes((Node*)root -> pointers[i]);
    /**> Delete the variables */
	delete [] root -> pointers;
	delete [] root -> keys;
	delete root;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
typename BPlusTree<T,Order>::Node * BPlusTree<T,Order>::findLeaf(BPlusTree<T,Order>::Node * const root, T key){
    /**> Checks if the root where it will search is null */
    if(root == NULL) return root;
    /**> Iterates through the keys of the node to find the child
         where the key is presumed to be. It continues in this way
         until it meets the leaf of the tree (Where the range of values
         encloses the value sought) */
	int i = 0;
	Node * auxNode = root;
	while(!auxNode -> leaf){
		i = 0;
		while(i < auxNode -> size){
			if(key >= auxNode -> keys[i]) i++;
			else break;
		}
		auxNode = (Node *)auxNode -> pointers[i];
	}
	return auxNode;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
typename BPlusTree<T,Order>::Node * BPlusTree<T,Order>::makeLeaf(){
    Node * leaf = new Node();
	leaf -> leaf = true;
	return leaf;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template<typename T, int Order>
typename BPlusTree<T, Order>::Node *BPlusTree<T, Order>::adjustRoot(BPlusTree::Node *root){

    /**> nonempty root.
	     Key and pointer have already been deleted,
	     so nothing to be done */
    if (root -> size > 0) return root;

    /**> Empty root.
         If it has a child, promote
         the first (only) child
         as the new root */
    Node * newRoot;
    if (!(root -> leaf)){
        newRoot = (Node*)root -> pointers[0];
        newRoot -> parent = NULL;
    }
    else newRoot = NULL;

    delete[] root -> keys;
    delete[] root -> pointers;
    delete[] root;
    return newRoot;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template<typename T, int Order>
typename BPlusTree<T, Order>::Node *
BPlusTree<T, Order>::coalesceNodes(BPlusTree::Node *root, BPlusTree::Node *n, BPlusTree::Node *neighbor, int neighborIndex, T kPrime){
    int i, j, nEnd;
    Node *tmp;
    if(neighborIndex == -1){
        /**> Make a swap between n and neighbor */
        tmp = n;
        n = neighbor;
        neighbor = tmp;
    }

    int neighborInsertionIndex = neighbor -> size;
    if(!n -> leaf){
        /**> Insert the new key in the neighbor node */
        neighbor -> keys[neighborInsertionIndex] = kPrime;
        neighbor -> size++;

        nEnd = n -> size;

        /** Copies the values(keys and pointers) */
        for (i = neighborInsertionIndex + 1, j = 0; j < nEnd; ++i, ++j){
            neighbor -> keys[i] = n -> keys[j];
            neighbor -> pointers[i] = n -> pointers[j];
            neighbor -> size++;
            n -> size--;
        }

        neighbor -> pointers[i] = n -> pointers[j];

        for(i = 0; i < neighbor -> size + 1; ++i){
            tmp = (Node *) neighbor -> pointers[i];
            tmp -> parent = neighbor;
        }
    }
    else{
        /** Copies the values(keys and pointers) */
        for (i = neighborInsertionIndex, j = 0; j < n->size; ++i, ++j) {
            neighbor->keys[i] = n->keys[j];
            neighbor->pointers[i] = n->pointers[j];
            neighbor->size++;
        }
        neighbor->pointers[Order - 1] = n->pointers[Order - 1];
    }

    /** Removes the duplicate value */
    root = removeEntry(root, n->parent, kPrime, n);

    delete[] n->keys;
    delete[] n->pointers;
    delete[] n;

    return root;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template<typename T, int Order>
typename BPlusTree<T, Order>::Node * BPlusTree<T, Order>::redistributeNodes(BPlusTree::Node *root, BPlusTree::Node *n, BPlusTree::Node *neighbor,int neighborIndex, int kPrimeIndex, T kPrime){
    int i;
    Node *tmp;

    if(neighborIndex != -1){
        if(!n -> leaf)
            /**> If the node is not a leaf, traverse the last pointer one position to the right */
            n -> pointers[n->size+1] = n -> pointers[n -> size];
        /**> This loop loops through all the elements to the right
            Leaving a space at the beginning */
        for(i = n -> size; i > 0; --i){
            n -> keys[i] = n -> keys[i-1];
            n -> pointers[i] = n -> pointers[i - 1];
        }
        /**> Performs the joins between neighbors depending on whether it is a leaf node or not */
        if(!n -> leaf){
            n -> pointers[0] = neighbor -> pointers[neighbor->size];
            tmp = (Node *) n -> pointers[0];
            tmp->parent = n;
            neighbor -> pointers[neighbor->size] = NULL;
            n -> keys[0] = kPrime;
            n -> parent -> keys[kPrimeIndex] = neighbor -> keys[neighbor->size - 1];
        }
        else{
            n -> pointers[0] = neighbor -> pointers[neighbor->size - 1];
            neighbor -> pointers[neighbor->size - 1] = NULL;
            n -> keys[0] = neighbor -> keys[neighbor->size - 1];
            n -> parent -> keys[kPrimeIndex] = n -> keys[0];
        }
    }
    else{
        if(n -> leaf){
            /**> Copy the first key from the neighbor in the last position of the node */
            n -> keys[n->size] = neighbor -> keys[0];
            /**> Copy the first pointer from the neighbor in the penultimate position of the node */
            n -> pointers[n->size] = neighbor -> pointers[0];
            /**> Copy the second key from the neighbor in the most optimal position of the parent node */
            n -> parent -> keys[kPrimeIndex] = neighbor -> keys[1];
        }
        else{
            /**> Put the key in the last position */
            n -> keys[n->size] = kPrime;
            /**> Copy the first pointer from the neighbor in the last position of the node */
            n -> pointers[n->size+1] = neighbor -> pointers[0];
            tmp = (Node *) n -> pointers[n->size+1];
            tmp -> parent = n;
            /**> Copy the first key from the neighbor in the most optimal position of the parent node */
            n -> parent -> keys[kPrimeIndex] = neighbor->keys[0];
        }
        for(i = 0; i < neighbor -> size - 1; ++i){
            /**> Update the values */
            neighbor -> keys[i] = neighbor -> keys[i + 1];
            neighbor -> pointers[i] = neighbor -> pointers[i + 1];
        }
        if(!n -> leaf) neighbor -> pointers[i] = neighbor -> pointers[i + 1];
    }
    n -> size++;
    neighbor -> size--;
    return root;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template<typename T, int Order>
int BPlusTree<T, Order>::getNeighborIndex(BPlusTree::Node *n){
    /**> Search for the index of the neighbor */
    for(int i = 0; i <= n -> parent -> size; ++i)
        if(n -> parent -> pointers[i] == n)
            return i - 1;
    return -1;  /** -1 = has no neighbors */
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
int BPlusTree<T,Order>::getLeftIndex(BPlusTree<T,Order>::Node * parent, BPlusTree<T,Order>::Node * left) const{
    int leftIndex = 0;
	while(leftIndex <= parent -> size && parent -> pointers[leftIndex] != left) leftIndex++;
	return leftIndex;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
int BPlusTree<T,Order>::cut(int length) const{
	if (length % 2 == 0) return length/2;
	else return length/2 + 1;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
int BPlusTree<T,Order>::pathToRoot(BPlusTree<T,Order>::Node * const root, BPlusTree<T,Order>::Node * child){
    /**> From a child it rises towards its parents, until it reaches the root and thus determines the height */
	int length = 0;
	Node * c = child;
	for(length = 0; c != root; length++) c = c -> parent;
	return length;
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
void BPlusTree<T,Order>::copyTree(BPlusTree<T,Order>::Node * root){
    if(root != NULL){
        if(root -> leaf)
            for(int i = 0; i < root -> size; ++i)
                insert(root -> keys[i]);
    else
        for(int i = 0; i < root -> size + 1; ++i)
            copyTree((Node*)root -> pointers[i]);
    }
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
void BPlusTree<T,Order>::enqueue(BPlusTree<T,Order>::Node * newNode){
	Node * c;
	if (queue == NULL) {
		queue = newNode;
		queue -> next = NULL;
	}
	else{
		c = queue;
		while(c -> next != NULL) {
			c = c->next;
		}
		c -> next = newNode;
		newNode -> next = NULL;
	}
}
// -------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, int Order>
typename BPlusTree<T,Order>::Node * BPlusTree<T,Order>::dequeue(){
	Node * n = queue;
	queue = queue -> next;
	n -> next = NULL;
	return n;
}
