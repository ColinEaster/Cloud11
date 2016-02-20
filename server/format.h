#ifndef FORMAT_H
#define FORMAT_H

template<typename T, typename = void>
struct Format {
    static int formatSize(const T *source);
    static void formatRead(char *&source, T *dest);
    static void formatWrite(char *&dest, const T *source);
};

#endif // FORMAT_H
