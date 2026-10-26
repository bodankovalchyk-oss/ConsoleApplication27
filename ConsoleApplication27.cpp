#include <iostream>
#include <initializer_list>
#include <string>
using namespace std;

template <typename T>
class Array
{
    T* data;
    int size;

public:
    Array()
    {
        data = nullptr;
        size = 0;
    }

    Array(int n)
    {
        size = n;
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = T();
    }

    Array(initializer_list<T> list)
    {
        size = list.size();
        data = new T[size];
        int i = 0;
        for (T x : list)
        {
            data[i] = x;
            i++;
        }
    }

    Array(const Array& other)
    {
        size = other.size;
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    ~Array()
    {
        delete[] data;
    }

    Array& operator=(const Array& other)
    {
        if (this == &other)
            return *this;
        delete[] data;
        size = other.size;
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
        return *this;
    }

    Array& operator=(initializer_list<T> list)
    {
        delete[] data;
        size = list.size();
        data = new T[size];
        int i = 0;
        for (T x : list)
        {
            data[i] = x;
            i++;
        }
        return *this;
    }

    int GetSize() const
    {
        return size;
    }

    bool IsEmpty() const
    {
        return size == 0;
    }

    T& operator[](int index)
    {
        return data[index];
    }

    const T& operator[](int index) const
    {
        return data[index];
    }

    void Add(T value)
    {
        T* temp = new T[size + 1];
        for (int i = 0; i < size; i++)
            temp[i] = data[i];
        temp[size] = value;
        delete[] data;
        data = temp;
        size++;
    }

    void InsertAt(int index, T value)
    {
        T* temp = new T[size + 1];
        for (int i = 0; i < index; i++)
            temp[i] = data[i];
        temp[index] = value;
        for (int i = index; i < size; i++)
            temp[i + 1] = data[i];
        delete[] data;
        data = temp;
        size++;
    }

    void RemoveAt(int index)
    {
        T* temp = new T[size - 1];
        for (int i = 0; i < index; i++)
            temp[i] = data[i];
        for (int i = index + 1; i < size; i++)
            temp[i - 1] = data[i];
        delete[] data;
        data = temp;
        size--;
    }

    void RemoveAll()
    {
        delete[] data;
        data = nullptr;
        size = 0;
    }

    friend ostream& operator<<(ostream& os, const Array& a)
    {
        os << "{ ";
        for (int i = 0; i < a.size; i++)
            os << a.data[i] << " ";
        os << "}";
        return os;
    }
};

template <typename T>
T Max(const Array<T>& arr)
{
    T max = arr[0];
    for (int i = 1; i < arr.GetSize(); i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

template <typename T>
T Min(const Array<T>& arr)
{
    T min = arr[0];
    for (int i = 1; i < arr.GetSize(); i++)
        if (arr[i] < min)
            min = arr[i];
    return min;
}

template <typename T>
void Sort(Array<T>& arr)
{
    for (int i = 0; i < arr.GetSize() - 1; i++)
        for (int j = 0; j < arr.GetSize() - 1 - i; j++)
            if (arr[j] > arr[j + 1])
            {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

template <typename T>
int BinarySearch(const Array<T>& arr, T value)
{
    int left = 0;
    int right = arr.GetSize() - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (arr[mid] == value)
            return mid;
        else if (arr[mid] < value)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

template <typename T>
int Replace(Array<T>& arr, T oldValue, T newValue)
{
    int count = 0;
    for (int i = 0; i < arr.GetSize(); i++)
        if (arr[i] == oldValue)
        {
            arr[i] = newValue;
            count++;
        }
    return count;
}

int main()
{
    Array<int> a = { 5, 3, 9, 1, 7, 3 };
    cout << "a = " << a << endl;

    cout << "Max = " << Max(a) << endl;
    cout << "Min = " << Min(a) << endl;

    Sort(a);
    cout << "Sorted: " << a << endl;

    cout << "Index of 7: " << BinarySearch(a, 7) << endl;
    cout << "Index of 4: " << BinarySearch(a, 4) << endl;

    int count = Replace(a, 3, 100);
    cout << "Replaced " << count << " times: " << a << endl;

    a = { 10, 20, 30 };
    a.Add(40);
    a.InsertAt(1, 15);
    a.RemoveAt(0);
    cout << "a = " << a << endl;

    Array<double> d = { 2.5, 1.5, 3.5 };
    Sort(d);
    cout << "d = " << d << endl;

    Array<string> s = { "pear", "apple", "orange" };
    Sort(s);
    cout << "s = " << s << endl;

    return 0;
}