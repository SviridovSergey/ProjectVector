#pragma once

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <iostream>

template<typename T>
class my_vector {
private:
    T* arr;
    size_t _size;
    size_t _capacity;

public:
    // Итераторы
    using iterator = T*;
    using const_iterator = const T*;

    // Конструктор по умолчанию
    my_vector()
        : arr(nullptr), _size(0), _capacity(0) {
    }

    // Конструктор с заданным размером
    explicit my_vector(size_t size)
        : _size(size), _capacity(size) {
        arr = static_cast<T*>(::operator new(_capacity * sizeof(T)));
        for (size_t i = 0; i < _size; ++i) {
            new (&arr[i]) T();
        }
    }

    // Конструктор копирования
    my_vector(const my_vector& other)
        : _size(other._size), _capacity(other._capacity) {
        arr = static_cast<T*>(::operator new(_capacity * sizeof(T)));
        for (size_t i = 0; i < _size; ++i) {
            new (&arr[i]) T(other.arr[i]);
        }
    }

    // Конструктор перемещения
    my_vector(my_vector&& other) noexcept
        : arr(other.arr), _size(other._size), _capacity(other._capacity) {
        other.arr = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    // Деструктор
    ~my_vector() {
        clear();
        ::operator delete(arr);
    }

    // Оператор присваивания копированием
    my_vector& operator=(const my_vector& other) {
        if (this != &other) {
            my_vector temp(other);
            swap(temp);
        }
        return *this;
    }

    // Оператор присваивания перемещением
    my_vector& operator=(my_vector&& other) noexcept {
        if (this != &other) {
            clear();
            ::operator delete(arr);

            arr = other.arr;
            _size = other._size;
            _capacity = other._capacity;

            other.arr = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    // Доступ к элементам
    T& operator[](size_t index) {
        return arr[index];
    }

    const T& operator[](size_t index) const {
        return arr[index];
    }

    T& at(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    const T& at(size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    // Размеры
    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }
    bool empty() const { return _size == 0; }

    // Управление памятью
    void reserve(size_t new_capacity) {
        if (new_capacity <= _capacity) return;

        T* new_arr = static_cast<T*>(::operator new(new_capacity * sizeof(T)));
        for (size_t i = 0; i < _size; ++i) {
            new (&new_arr[i]) T(std::move(arr[i]));
            arr[i].~T();
        }

        ::operator delete(arr);
        arr = new_arr;
        _capacity = new_capacity;
    }

    void resize(size_t new_size) {
        if (new_size > _capacity) {
            reserve(new_size);
        }

        while (_size < new_size) {
            new (&arr[_size++]) T();
        }

        while (_size > new_size) {
            arr[--_size].~T();
        }
    }

    void push_back(const T& value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        new (&arr[_size++]) T(value);
    }

    void pop_back() {
        if (_size > 0) {
            arr[--_size].~T();
        }
    }

    void clear() {
        for (size_t i = 0; i < _size; ++i) {
            arr[i].~T();
        }
        _size = 0;
    }

    T* data() { return arr; }
    const T* data() const { return arr; }

    // Итераторы
    iterator begin() { return arr; }
    iterator end() { return arr + _size; }

    const_iterator begin() const { return arr; }
    const_iterator end() const { return arr + _size; }

    const_iterator cbegin() const { return arr; }
    const_iterator cend() const { return arr + _size; }

private:
    void swap(my_vector& other) noexcept {
        std::swap(arr, other.arr);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }
};