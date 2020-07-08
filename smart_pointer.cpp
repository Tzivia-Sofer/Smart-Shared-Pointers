#include "smart_pointer.h"

template <typename T, typename S>
bool operator == (const SharedPtr<T>  &shp1, const SharedPtr<S> &shp2)
{
        return shp1.getPtr() == shp2.getPtr();
}

template <typename T ,typename S>
bool operator != (const SharedPtr<T> &shp1, const SharedPtr<S> &shp2)
{
    return !(shp1 == shp2);
}