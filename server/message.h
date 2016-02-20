#ifndef MESSAGE_H
#define MESSAGE_H

template<typename T>
class Message {
public:
    virtual ~Message() { }

    T * resolve() { return static_cast<T *>(this); }

    int size() const;
    void write(char *&dest) const;

    using Type = T;
    static T * read(char *&source) { return T::implRead(source); }
};

#endif // MESSAGE_H
