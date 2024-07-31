#include <iostream>

class ArrayList {
private:
    int capacity;
    int length;
    int* array;

public:
    ArrayList(int initCapacity) {
        capacity = initCapacity;
        length = 0;
        array = new int[capacity];
    }

    int Get(int index) {
        return array[index];
    }

    void Set(int index, int val) {
        array[index] = val;
    }

    void Pushback(int val) {
        if (length == capacity) {
            Resize();
        }
        array[length] = val;
        ++length;
    }

    int Popback() {
        --length;
        return array[length + 1];
    }

    void Resize() {
        capacity *= 2;
        int* newArray = new int[capacity];
        for (int i = 0; i < length; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }

    int GetSize() {
        return length;
    }

    int GetCapacity() {
        return capacity;
    }

    void PrintList() {
        for (int i = 0; i < length; ++i) {
            std::cout << i << ": " << array[i] << std::endl;
        }
    }

    void Delete() {
        delete[] array;
    }
};

class RingBuffer {
    int* array;
    int length;
    int capacity;
    int head;
    int tail;

    void AddToEmpty(int val) {
        array[0] = val;
        ++length;
    }

public:
    RingBuffer(int initCapacity) {
        if (initCapacity <= 1) {
            initCapacity = 2;
        }
        capacity = initCapacity;
        length = 0;
        head = 0;
        tail = 0;
        array = new int[capacity];
    }

    int Get(int index) {
        return array[(head + index) % capacity - 1];
    }

    void Push(int val) {
        if (length == capacity) {
            Resize();
        }

        if (length == 0) {
            AddToEmpty(val);
        }
        else {
            tail = (tail + 1) % (capacity - 1);
            array[tail] = val;
            ++length;
        }
    }

    void PushHead(int val) {
        if (length == capacity) {
            Resize();
        }

        if (length == 0) {
            AddToEmpty(val);
        }
        else {
            if (head == 0) {
                head = length - 1;
                array[head] = val;
            }
            else {
                --head;
                array[head] = val;
            }
            ++length;
        }
    }

    void Pop() {
        if (length == 0) {
            return;
        }

        array[tail] = 0;

        if (tail == 0) {
            tail = length - 1;
        }
        else {
            --tail;
        }

        --length;
    }

    void PopHead() {
        if (length == 0) {
            return;
        }

        array[head] = 0;
        if (head == capacity - 1) {
            head = 0;
        }
        else {
            ++head;
        }
        --length;
    }

    void Resize() {
        int* tempArr = new int[capacity * 2];
        for (int i = 0; i < length; ++i) {
            tempArr[i] = array[(head + i) % (capacity - 1)];
        }
        head = 0;
        tail = length - 1;
        capacity *= 2;
    }
};


int main(int argc, const char* argv[]) {

    ArrayList* arr = new ArrayList(5);

    arr->Pushback(10);
    arr->Pushback(5);
    arr->Pushback(2);
    arr->Pushback(20);
    arr->Pushback(15);

    arr->PrintList();

    arr->Delete();

    return 0;
}