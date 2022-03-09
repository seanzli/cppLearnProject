
#include <memory>

template<int ObjectSize, int NumObject = 20>
class MemPool {
private:
    const int MemBlockSize;
    const int ItemSize;

    struct FreeNode {
        FreeNode* next;
        char data[ObjectSize];
    };

    struct MemBlock {
        MemBlock* next;
        FreeNode data[NumObject];
    };

    FreeNode* freeNodeHeader;
    MemBlock* memBlockHeader;

public:
    MemPool()
        : ItemSize(ObjectSize + sizeof(FreeNode*))
        , MemBlockSize(sizeof(MemBlock*) + NumObject*(ObjectSize + sizeof (FreeNode*)))
        , freeNodeHeader(nullptr)
        , memBlockHeader(nullptr)
    {}

    ~MemPool() {
        MemBlock* ptr;
        while (memBlockHeader) {
            ptr = memBlockHeader->next;
            delete memBlockHeader;
            memBlockHeader = ptr;
        }
    }

    void* malloc() {
        if (freeNodeHeader == nullptr) {
            MemBlock* newBlock = new MemBlock;
            newBlock->data[0].next = nullptr;
            for (int i = 1; i < NumObject; ++i)
                newBlock->data[i].next = &newBlock->data[i-1];
            freeNodeHeader = &newBlock->data[NumObject - 1];
            newBlock->next = memBlockHeader;
        }
        void* freeNode = freeNodeHeader;
        freeNodeHeader = freeNodeHeader->next;
        return freeNode;
    }
    void free(void* p) {
        FreeNode* pNode = (FreeNode*)p;
        pNode->next = freeNodeHeader;
        freeNodeHeader = pNode;
    }
};