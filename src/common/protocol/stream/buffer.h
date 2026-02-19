#pragma once

#include <cstdlib>

struct buffer {
    void* data;
    size_t size;

    void free() const {
        ::free(this->data);
    }
};
