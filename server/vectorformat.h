#ifndef VECTORFORMAT_H
#define VECTORFORMAT_H

#include <vector>

#include "format.h"
#include "formatutils.h"

template<typename T>
struct Format<std::vector<T>> {
    static int formatSize(const std::vector<T> *source);
    static void formatRead(char *&source, std::vector<T> *dest);
    static void formatWrite(char *&dest, const std::vector<T> *source);
};

template<typename T>
int Format<std::vector<T>>::formatSize(const std::vector<T> *source) {
    int vectorLength = source->size();
    int totalSize = 0;
    for (T t : *source) {
        totalSize += Formats::size(&t);
    }
    return Formats::size(&vectorLength) + totalSize;
}

template<typename T>
void Format<std::vector<T>>::formatRead(char *&source, std::vector<T> *dest) {
    int vectorLength = Formats::read<int>(source);
    *dest = std::vector<T>();
    for (int i = 0; i < vectorLength; ++i) {
        dest->push_back(Formats::read<T>(source));
    }
}

template<typename T>
void Format<std::vector<T>>::formatWrite(char *&dest, const std::vector<T> *source) {
    int vectorLength = source->size();
    Formats::write(dest, &vectorLength);
    for (T t : *source) {
        Formats::write(dest, &t);
    }
}

#endif // VECTORFORMAT_H
