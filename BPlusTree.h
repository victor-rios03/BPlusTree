#ifndef BPLUSTREE_H_INCLUDED
#define BPLUSTREE_H_INCLUDED

template <typename T, int Order>
class BPlusTree{
public:
    /**
     * @brief Initializes the root and queue of the B+ Tree
     */
    BPlusTree();
    /**
     * @brief Clears the tree
     */
    ~BPlusTree();
    /**
     * @brief Copies a tree to this tree
     * @param bPT Tree to copy values from
     */
    BPlusTree(const BPlusTree &bPT);
    /**
     * @brief Match the values from one tree to this
     * @param bPT Tree to match values from
     * @return This tree with matched values from other tree
     */
    BPlusTree & operator=(const BPlusTree &bPT);
    /**
     * @brief Inserts a key in the tree
     * @param value Value of key to insert
     */
    void insert(T value);
    /**
     * @brief Removes a key in the tree
     * @param value Value of key to remove
     */
    void remove(T value);
    /**
     * @brief Verifies if a key is in the tree
     * @param value Value of key to find
     * @return bool Value that indicates if it was found
     */
    bool find(T value);
    /**
     * @brief Verifies if the tree is empty
     * @return bool Value that indicates if tree is empty
     */
    bool empty() const;
    /**
     * @brief Empties all keys from tree
     */
    void clear();
    /**
     * @brief Prints tree
     */
    void print();
private:
    struct Node{
        void **pointers;    /**> Array of pointers */
        T *keys;            /**> Array of the keys */
        Node *parent;
        bool leaf;
        int size;           /**> Number of keys */
        Node *next;         /**> Variable used for queue */

        Node(){
            pointers = new void*[Order];
            keys = new T[Order - 1];
            parent = NULL;
            leaf = false;
            size = 0;
            next = NULL;
        }
    } * root;

    /**> Key storage */
    struct Record{
        T value;
        explicit Record(T v) : value(v){}
    };
    /**> Basic functions */
    Node * insert(Node * root, T key, T value);

    /**
     * @brief Deletes a key in the tree
     * @param root Root node of the tree
     * @param key Key's value to be deleted
     * @return Tree's root with the deleted node
     */
    Node * remove(Node *root, T key);
    Record * find(Node * root, T key, Node ** leafOut);
    void printTree(Node * root);

    /**> Insert functions */
    Node * insertIntoNode(Node * root, Node * parent, int leftIndex, T key, Node * right);
    Node * insertIntoLeaf(Node * leaf, T key, Record * pointer);
    Node * insertIntoParent(Node * root, Node * left, T key, Node * right);
    Node * insertIntoNodeAfterSplitting(Node * root, Node * parent, int leftIndex, T key, Node * right);
    Node * insertIntoLeafAfterSplitting(Node * root, Node * leaf, T key, Record * pointer);

    /**> Remove functions */

    /**
     * @brief Deletes an entry from the tree.
     * Removes the record and its key from the leaf, and makes all changes
     * to the structure of the tree
     * @param root Root node of the tree
     * @param n Leaf where the entry is
     * @param key Key's value to be deleted
     * @param pointer Used to determine the number of pointers
     * @return Leaf with deleted entry
     */
    Node * removeEntry(Node * root, Node *n, T key, void * pointer);
    Node * removeEntryFromNode(Node * n, T key, void * pointer);
    void destroyTreeNodes(Node * root);

    /**> Find functions */
    Node * findLeaf(Node * root, T key);

    /**> Create functions */
    Node * makeLeaf();

    /**> Auxiliar functions */

    /**
     * @brief Adjusts the root if necessary
     * @param root Root node of the tree
     * @return New root node
     */
    Node * adjustRoot(Node *root);

    /**
     * @brief Merge nodes that is too small with a neighbouring node
     * @param root Root node of the tree
     * @param n Node to search for neighbor
     * @param neighbor Neighbor node
     * @param neighbor_index Index value of the neighbor
     * @param k_prime First key in the leaf node
     * @return Merged node
     */
    Node * coalesceNodes(Node *root, Node *n, Node *neighbor, int neighborIndex, T kPrime);

    /**
     * @brief Redistributes entries between two nodes
     * @param root Root node of the tree
     * @param n Node to search for neighbor
     * @param neighbor Neighbor node
     * @param neighbor_index Index value of the neighbor
     * @param k_prime_index Index value of the first key
     * @param k_prime First key in the leaf node
     * @return Nodes with redistributed entries
     */
    Node * redistributeNodes(Node *root, Node *n, Node *neighbor, int neighborIndex, int kPrimeIndex, T kPrime);

    /**
     * @brief Gets the index of a node's nearest neighbor to the left if it exists, else
     * returns -1
     * @param n Node to search neighbor
     * @return Index of n node's nearest neighbor
     */
    int getNeighborIndex(Node *n);
    int getLeftIndex(Node * parent, Node * left) const;
    int cut(int length) const;
    int pathToRoot(Node * root, Node * child);
    void copyTree(Node *root);


    Node * queue;   /**> The queue is used in the print method */

    /** > Queue functions */
    void enqueue(Node * newNode);
    Node * dequeue();
};

#include "BPlusTree.tpp"

#endif // BPLUSTREE_H_INCLUDED
