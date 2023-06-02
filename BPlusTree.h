#ifndef BPLUSTREE_H_INCLUDED
#define BPLUSTREE_H_INCLUDED

template <typename T, int Order>
class BPlusTree{
public:
    BPlusTree();
    ~BPlusTree();
    BPlusTree(const BPlusTree &bPT);
    BPlusTree & operator=(const BPlusTree &bPT);
    void insert(T value);
    void remove(T value);
    bool find(T value);
    bool empty() const;
    void clear();
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
    /**
     * @brief Finds a key and returns its value,
     * @param root Root of the tree
     * @param key Key to be found
     * @return Pointer to the value, NULL if not found
     */
    Record * find(Node * root, T key);
    /**
     * @brief Prints the tree per level
     * @param root Root of the tree
     */
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
    /**
     * @brief Returns a pointer to a leaf where the key is located
     * @param root Root of the tree
     * @param key Key to be looked for
     * @return Pointer to the leaf that contains the key, NULL if the leaf is not found
     */
    Node * findLeaf(Node * root, T key);

    /**> Create functions */
    /**
     * @brief Creates a leaf node
     * @return Pointer to leaf node created
     */
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
    /**
     * @brief Calculates de index of where the split should be done
     * @param length Length of the node
     * @return Index of where the cut should be done
     */
    int cut(int length) const;
    /**
     * @brief Returns the height of the node passed
     * @param root Root of the tree
     * @param child Child whose height wants to be calculated
     * @return Height of the subtree
     */
    int pathToRoot(Node * root, Node * child);
    void copyTree(Node *root);


    Node * queue;   /**> The queue is used in the print method */

    /** > Queue functions */
    /**
     * @brief Queues a new node to the queue
     * @param newNode Node to be enqueued
     */
    void enqueue(Node * newNode);
    /**
     * @brief Dequeues a node from the queue
     * @return Pointer to the dequeued node
     */
    Node * dequeue();
};

#include "BPlusTree.tpp"

#endif // BPLUSTREE_H_INCLUDED
