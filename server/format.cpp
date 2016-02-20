/* Copyright 2015 Colin Easter, Daniel Turchiano, Wah Loon Keng, Aaron Willey, and Nicholas Turney.

    This file is part of Cloud11.

    Cloud11 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Cloud11 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Cloud11.  If not, see <http://www.gnu.org/licenses/>.

    */
#include <cstring>
#include <string>

#include "format.h"
#include "formatutils.h"
#include "messagetype.h"

template<>
int Format<int>::formatSize(const int *) {
    return sizeof(int);
}
template<>
void Format<int>::formatRead(char *&source, int *dest) {
    *dest = *(int *) source;
    source += sizeof(int);
}
template<>
void Format<int>::formatWrite(char *&dest, const int *source) {
    *(int *) dest = *source;
    dest += sizeof(int);
}


template<>
int Format<double>::formatSize(const double *) {
    return sizeof(double);
}
template<>
void Format<double>::formatRead(char *&source, double *dest) {
    *dest = *(double *) source;
    source += sizeof(double);
}
template<>
void Format<double>::formatWrite(char *&dest, const double *source) {
    *(double *) dest = *source;
    dest += sizeof(double);
}


template<>
int Format<std::string>::formatSize(const std::string *source) {
    int stringSize = source->size();
    return Formats::size(&stringSize) + stringSize;
}
template<>
void Format<std::string>::formatRead(char *&source, std::string *dest) {
    int len;
    Formats::read(source, &len);
    *dest = std::string(source, len);
    source += len;
}
template<>
void Format<std::string>::formatWrite(char *&dest, const std::string *source) {
    int len = source->size();
    Formats::write(dest, &len);
    strncpy(dest, source->c_str(), len);
    dest += len;
}

template<>
int Format<MessageType>::formatSize(const MessageType *) {
    return sizeof(MessageType);
}
template<>
void Format<MessageType>::formatRead(char *&source, MessageType *dest) {
    *dest = (MessageType) *(int *) source;
    source += sizeof(MessageType);
}
template<>
void Format<MessageType>::formatWrite(char *&dest, const MessageType *source) {
    *(int *) dest = *(int *) source;
    dest += sizeof(MessageType);
}
