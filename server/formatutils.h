#ifndef FORMATUTILS_H
#define FORMATUTILS_H

#include <cstdlib>

#include "format.h"

class Formats {
public:
    template<typename T>
    static inline int size(const T *sourcet);
    template<typename T, typename U, typename... Rest>
    static inline int size(const T *sourcet, const U *sourceu, const Rest... rest);

    template<typename T>
    static inline void read(char *&source, T *dest);
    template<typename T, typename U, typename... Rest>
    static inline void read(char *&source, T *destt, U *destu, Rest... rest);

    template<typename T>
    static inline T read(char *&source);

    template<typename T>
    static inline void write(char *&dest, const T *source);
    template<typename T, typename U, typename... Rest>
    static inline void write(char *&dest, const T *sourcet, const U *sourceu, const Rest... rest);

    template<typename T, typename... Rest>
    static inline int serialize(char **dest, const T *t, const Rest... rest);
};

template<typename T>
int Formats::size(const T *sourcet) {
    return Format<T>::formatSize(sourcet);
}
template<typename T, typename U, typename... Rest>
int Formats::size(const T *sourcet, const U *sourceu, const Rest... rest) {
    return size(sourcet) + size(sourceu, rest...);
}

template<typename T>
void Formats::read(char *&source, T *dest) {
    Format<T>::formatRead(source, dest);
}
template<typename T, typename U, typename... Rest>
void Formats::read(char *&source, T *destt, U *destu, Rest... rest) {
    read(source, destt);
    read(source, destu, rest...);
}

template<typename T>
T Formats::read(char *&source) {
    T t;
    read(source, &t);
    return t;
}

template<typename T>
void Formats::write(char *&dest, const T *source) {
    Format<T>::formatWrite(dest, source);
}
template<typename T, typename U, typename... Rest>
void Formats::write(char *&dest, const T *sourcet, const U *sourceu, const Rest... rest) {
    write(dest, sourcet);
    write(dest, sourceu, rest...);
}

template<typename T, typename... Rest>
int Formats::serialize(char **dest, const T *source, const Rest... rest) {
    int totalSize = size(source, rest...);
    char *buf = *dest = (char *) malloc(totalSize);
    write(buf, source, rest...);
    return totalSize;
}

#endif // FORMATUTILS_H
