/**
 * C++ Memory Management Demonstration
 * Demonstrates: Manual allocation, RAII, smart pointers, common errors
 */

#include <iostream>
#include <memory>
#include <vector>
#include <cstring>

using namespace std;

class DataBuffer
{
private:
    int *data;
    size_t size;
    string name;
    static int instanceCount;

public:
    // Constructor - manual allocation
    DataBuffer(const string &bufferName, size_t bufferSize)
        : size(bufferSize), name(bufferName)
    {
        data = new int[size];
        instanceCount++;
        cout << "✓ Creating '" << name << "' with " << size
             << " elements (Instance #" << instanceCount << ")" << endl;
        cout << "  Memory at: " << static_cast<void *>(data) << endl;
    }

    // Destructor - manual cleanup
    ~DataBuffer()
    {
        instanceCount--;
        cout << "  ✗ Destroying '" << name
             << "' (Remaining: " << instanceCount << ")" << endl;
        delete[] data;
    }

    // Copy constructor (deep copy)
    DataBuffer(const DataBuffer &other)
        : size(other.size), name(other.name + "_copy")
    {
        data = new int[size];
        memcpy(data, other.data, size * sizeof(int));
        instanceCount++;
        cout << "  ✓ Copy: " << name << endl;
    }

    // Move constructor (C++11)
    DataBuffer(DataBuffer &&other) noexcept
        : data(other.data), size(other.size), name(move(other.name))
    {
        other.data = nullptr;
        other.size = 0;
        cout << "  ✓ Move: " << name << endl;
    }

    void fillWithValues(int start)
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] = start + i;
        }
        cout << "  ✓ Filled '" << name << "'" << endl;
    }

    void displayInfo() const
    {
        cout << "  Buffer '" << name << "' has " << size << " elements" << endl;
        cout << "  Memory at: " << static_cast<void *>(data) << endl;
    }

    int getSum() const
    {
        int sum = 0;
        for (size_t i = 0; i < size; i++)
        {
            sum += data[i];
        }
        return sum;
    }
};

int DataBuffer::instanceCount = 0;

// ═══════════════════════════════════════════════════
// BAD PRACTICES (Commented out to prevent crashes)
// ═══════════════════════════════════════════════════

void demonstrateMemoryLeak()
{
    cout << "\n--- DEMO 1: Memory Leak (BAD) ---" << endl;

    int *leaked = new int[1000];
    cout << "  ⚠ Allocated 1000 ints at: " << static_cast<void *>(leaked) << endl;
    cout << "  ⚠ Never freed - MEMORY LEAK!" << endl;

    // Should do: delete[] leaked;
}

void demonstrateDanglingPointer()
{
    cout << "\n--- DEMO 2: Dangling Pointer (BAD) ---" << endl;

    int *ptr = new int(42);
    cout << "  Allocated int at: " << static_cast<void *>(ptr) << endl;
    cout << "  Value: " << *ptr << endl;

    delete ptr;
    cout << "  ✓ Freed memory" << endl;

    // ptr is now dangling!
    cout << "  ⚠ ptr is now dangling - DO NOT ACCESS" << endl;
    // cout << *ptr;  // ❌ UNDEFINED BEHAVIOR

    ptr = nullptr; // Good practice
    cout << "  ✓ Set to nullptr" << endl;
}

void demonstrateDoubleDelete()
{
    cout << "\n--- DEMO 3: Double Delete (BAD) ---" << endl;

    int *ptr = new int(100);
    cout << "  Allocated at: " << static_cast<void *>(ptr) << endl;

    delete ptr;
    cout << "  ✓ First delete OK" << endl;

    // delete ptr;  // ❌ CRASH - Double delete!
    cout << "  ⚠ Second delete would CRASH" << endl;
}

// ═══════════════════════════════════════════════════
// GOOD PRACTICES
// ═══════════════════════════════════════════════════

void demonstrateRAII()
{
    cout << "\n--- DEMO 4: RAII (Stack Allocation) ---" << endl;

    {
        DataBuffer stackBuffer("StackBuffer", 20);
        stackBuffer.fillWithValues(10);
        cout << "  Inside scope" << endl;
    } // Automatically destroyed

    cout << "  ✓ Exited scope - auto cleanup" << endl;
}

void demonstrateSmartPointers()
{
    cout << "\n--- DEMO 5: Smart Pointers (GOOD) ---" << endl;

    // unique_ptr - exclusive ownership
    cout << "\n  Using unique_ptr:" << endl;
    {
        unique_ptr<DataBuffer> uniqueBuffer =
            make_unique<DataBuffer>("UniqueBuffer", 50);
        uniqueBuffer->fillWithValues(1);
        uniqueBuffer->displayInfo();
    } // Automatically deleted
    cout << "  ✓ unique_ptr auto cleaned" << endl;

    // shared_ptr - shared ownership
    cout << "\n  Using shared_ptr:" << endl;
    {
        shared_ptr<DataBuffer> sharedBuffer1 =
            make_shared<DataBuffer>("SharedBuffer", 30);
        cout << "  Ref count: " << sharedBuffer1.use_count() << endl;

        {
            shared_ptr<DataBuffer> sharedBuffer2 = sharedBuffer1;
            cout << "  Ref count: " << sharedBuffer1.use_count() << endl;
        }

        cout << "  Ref count: " << sharedBuffer1.use_count() << endl;
    } // Deleted when last shared_ptr goes away
    cout << "  ✓ shared_ptr auto cleaned" << endl;
}

void demonstrateCopyVsMove()
{
    cout << "\n--- DEMO 6: Copy vs Move ---" << endl;

    {
        DataBuffer original("Original", 10);
        original.fillWithValues(1);

        DataBuffer copied = original;      // Copy
        DataBuffer moved = move(original); // Move

        cout << "  After move, original.data = nullptr" << endl;
    }
}

void demonstrateVector()
{
    cout << "\n--- DEMO 7: STL Vector (RAII) ---" << endl;

    {
        vector<int> vec(1000000); // Stack-allocated vector object
        cout << "  Created vector with 1M elements" << endl;
        cout << "  Vector manages heap memory automatically" << endl;
    } // Vector automatically cleans up

    cout << "  ✓ Vector auto cleaned" << endl;
}

// ═══════════════════════════════════════════════════
// Main
// ═══════════════════════════════════════════════════

int main()
{
    cout << "═══════════════════════════════════════════════" << endl;
    cout << "C++: Manual Memory Management Demo" << endl;
    cout << "═══════════════════════════════════════════════" << endl;

    // Manual allocation and deallocation
    cout << "\n--- Manual Heap Management ---" << endl;
    DataBuffer *heapBuffer = new DataBuffer("HeapBuffer", 100);
    heapBuffer->fillWithValues(1);
    heapBuffer->displayInfo();
    delete heapBuffer; // Must manually delete

    // RAII with stack
    demonstrateRAII();

    // Smart pointers (modern C++)
    demonstrateSmartPointers();

    // Copy vs Move semantics
    demonstrateCopyVsMove();

    // STL containers
    demonstrateVector();

    // Common errors (safely demonstrated)
    demonstrateMemoryLeak();
    demonstrateDanglingPointer();
    demonstrateDoubleDelete();

    cout << "\n═══════════════════════════════════════════════" << endl;
    cout << "Demo Complete" << endl;
    cout << "Use Valgrind to detect leaks!" << endl;
    cout << "═══════════════════════════════════════════════" << endl;

    return 0;
}