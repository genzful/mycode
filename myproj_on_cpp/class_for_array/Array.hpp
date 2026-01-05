#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream> // for cout cin
#include <stdexcept> // for exceptions

using namespace std; // for std::

namespace ArrayLib {
    
// func for fastsort
template <typename T>
void fastsort(T *array, int start, int end) {
    if (start >= end)
        return;

    T pivot = array[(start + end) / 2];
    int left = start;
    int right = end;

    while (left <= right) {
        while (array[left] < pivot)
            left++;
        while (array[right] > pivot)
            right--;

        if (left <= right) {
            T temp = array[left];
            array[left] = array[right];
            array[right] = temp;
            left++;
            right--;
        }
    }

    fastsort(array, start, right);
    fastsort(array, left, end);
}

// custom class for arrays
template <typename T> class Array {
private:
  T *data;
  int size;

public:
  // constructors
  Array() : data(nullptr), size(0) {}

  // copy from array
  Array(const T *arr, int arrSize) : size(arrSize) {
    if (size > 0) {
      data = new T[size];
      for (int i = 0; i < size; i++) {
        data[i] = arr[i];
      }
    } else {
      data = nullptr;
    }
  }

  // filling for zeros or false
  explicit Array(int arrSize) : size(arrSize) {
    if (size > 0) {
      data = new T[size](); // 0 && false && 0.0 && "0" && '0'
    } else {
      data = nullptr;
    }
  }

  // copy constructor
  Array(const Array &other) : size(other.size) {
    if (size > 0) {
      data = new T[size];
      for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
      }
    } else {
      data = nullptr;
    }
  }

  // operator =
  Array &operator=(const Array &other) {
    if (this != &other) {
      delete[] data;
      size = other.size;
      if (size > 0) {
        data = new T[size];
        for (int i = 0; i < size; i++) {
          data[i] = other.data[i];
        }
      } else {
        data = nullptr;
      }
    }
    return *this;
  }

  // destructors
  ~Array() { delete[] data; }

  // operator []
  T &operator[](int index) {
    if (index < 0 || index >= size) {
      throw out_of_range("Index out of the range");
    }
    return data[index];
  }

  // operator [] with const
  const T &operator[](int index) const {
    if (index < 0 || index >= size) {
      throw out_of_range("Index out of the range");
    }
    return data[index];
  }

  // getter size
  int getSize() const { return size; }

  // sort func for public
  void sort() {
    if (size > 1) {
      fastsort(data, 0, size - 1);
    }
  }

  // prefix increment
  Array &operator++() {
    for (int i = 0; i < size; i++) {
      ++data[i];
    }
    return *this;
  }

  // postfix increment
  Array operator++(int) {
    Array temp(*this);
    ++(*this);
    return temp;
  }

  // prefix decrement
  Array &operator--() {
    for (int i = 0; i < size; i++) {
      --data[i];
    }
    return *this;
  }

  // postfix decrement
  Array operator--(int) {
    Array temp(*this);
    --(*this);
    return temp;
  }

  // operator << (output)
  friend ostream &operator<<(ostream &out, const Array &obj) {
    out << '[';
    for (int i = 0; i < obj.size; i++) {
      out << obj.data[i];
      if (i < obj.size - 1)
        out << " ";
    }
    out << ']';
    return out;
  }

  // operator >> (input)
  friend istream &operator>>(istream &in, Array &obj) {
    for (int i = 0; i < obj.size; i++) {
      in >> obj.data[i];
    }
    return in;
  }

  // operator +
  Array operator+(const Array &other) const {
    if (size != other.size) {
      throw invalid_argument("Arrays must have same size");
    }

    Array result(size);
    for (int i = 0; i < size; i++) {
      result.data[i] = data[i] + other.data[i];
    }
    return result;
  }

  // operator -
  Array operator-(const Array &other) const {
    if (size != other.size) {
      throw invalid_argument("Arrays must have same size");
    }

    Array result(size);
    for (int i = 0; i < size; i++) {
      result.data[i] = data[i] - other.data[i];
    }
    return result;
  }

  // operator ==
  bool operator==(const Array &other) {
    if (other.getSize() == this->size) {
      for (int i = 0; i < size; i++) {
        if (this->data[i] == other.data[i]) {
          continue;
        } else {
          return false;
        }
      }
    } else {
      return false;
    }
    return true;
  }

  // operator !=
  bool operator!=(const Array &other) {
    if (other.getSize() == this->size) {
      for (int i = 0; i < size; i++) {
        if (this->data[i] == other.data[i]) {
          continue;
        } else {
          return true;
        }
      }
    } else {
      return true;
    }
    return false;
  }
};

} // namespace ArrayLib

#endif