#include <cstddef>
#include <iostream>

// ------------shared ptr----------------------
template <typename T>
class SharedPtr
{
public:
    explicit SharedPtr(T* = NULL);

    template <typename S>
    SharedPtr(const SharedPtr<S>& other);
    ~SharedPtr();

    template <typename S>
    SharedPtr&      operator = (const SharedPtr<S>& other);
    T&              operator* () { return *m_ptr; };
    T*              operator-> () { return m_ptr; };
    operator bool() const;

    T*              getPtr() const { return m_ptr; }
    size_t*         getCount() const { return m_count; }

private:
    void            DeleteMembers();
    T* m_ptr;
    size_t *m_count;
};

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr):m_ptr(ptr), m_count(new size_t(0)){ }

template <typename T>
SharedPtr<T>::operator bool() const
{
    return m_ptr != NULL;
}

template <typename T>
template <typename S>
SharedPtr<T>::SharedPtr(const SharedPtr<S>& other):m_ptr(other.getPtr()),m_count(other.getCount())
{
    m_count ++;
}

template <typename T>
inline void SharedPtr<T>::DeleteMembers()
{
    if (getCount() == 0)
    {
        delete m_ptr;
        delete m_count;
    }
    else
    {
        m_count --;
    }
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    DeleteMembers();
}

template <typename T>
template <typename S>
SharedPtr<T>& SharedPtr<T>::operator = (const SharedPtr<S>& other)
{
    if ((*this).getPtr() != other.getPtr())
    {
        DeleteMembers();
        m_ptr = other.getPtr();
        m_count = other.getCount() + 1;
    }
    return *this;
}

// ------------smart ptr----------------------

template <typename T>
class SmartPtr
{
public:
    SmartPtr();
    ~SmartPtr();

    T&              operator* () { return *m_ptr; };
    T*              operator-> () { return m_ptr; };

private:
    T* m_ptr;
};

template <typename T>
SmartPtr<T>::SmartPtr():m_ptr(new T) {}

template <typename T>
SmartPtr<T>::~SmartPtr()
{
    delete [] m_ptr;
}


// ------------unique ptr----------------------

template <typename T>
class UniquePtr: public SmartPtr<T>
{
public:
    explicit UniquePtr(T*);
private:
    UniquePtr(const UniquePtr&) {}
    UniquePtr& operator = (const UniquePtr&) {}
};

template <typename T>
UniquePtr<T>::UniquePtr(T* ptr):SmartPtr<T>(ptr) {}
