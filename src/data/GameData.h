//
// Created by Rob on 7/16/2018.
//

#ifndef DGL_GAMEDATA_H
#define DGL_GAMEDATA_H

#include <memory>
#include <iostream>
#include <arpa/inet.h>


struct Vertex3DEx
{
    uint32_t x, y, z, extra;

    Vertex3DEx() :
            x(0), y(0), z(0), extra(0) {}

    Vertex3DEx(uint32_t _x, uint32_t _y, uint32_t _z, uint32_t _extra = 0) :
            x(_x), y(_y), z(_z), extra(_extra) {}

    bool operator==(const Vertex3DEx &other) {
        return ((x == other.x) && (y == other.y) && (z == other.z));
    }

    bool operator!=(const Vertex3DEx &other) { return !(*this == other); }

    void print() const {
        std::cout << "Vertex 3D: [" << "X=" << x << ", Y=" << y << ", Z=" << z << ", Ex=" << extra
                  << "]" << std::endl;
    }
};

typedef std::vector<Vertex3DEx> vertex3d_vec;


class GameData
{
public:
    virtual ~GameData() {}

    virtual char *serializeData() = 0;
    virtual bool deserializeData(const char *data, size_t length) = 0;
    virtual size_t getLength() const = 0;
    friend std::ostream &operator<<(std::ostream &os, const GameData &game_data);

protected:
    virtual void print(std::ostream &os) const {};
};

typedef std::shared_ptr<GameData> game_data_ptr;
typedef std::vector<game_data_ptr> game_data_vec;


template<typename T>
class BasicSingle32 : public GameData
{
    static const size_t DATA_SIZE = 4;

    T data_;

    char serial_data_[DATA_SIZE];

public:
    // Constructor for message receiver.
    BasicSingle32() :
            data_(0) {}

    // Constructor for message sender.
    BasicSingle32(T data) :
            data_(data) {}

    T getData() const { return data_; }
    void setData(T data) { data_ = data; }

    virtual char *serializeData() {
        *(reinterpret_cast<T *>(serial_data_)) = htonl(data_);
        return serial_data_;
    }

    virtual bool deserializeData(const char *data, size_t length) {
        if (length != DATA_SIZE)
            return false;

        data_ = ntohl(*(reinterpret_cast<const uint32_t *>(data)));
        return true;
    }

    virtual size_t getLength() const { return DATA_SIZE; }

protected:
    virtual void print(std::ostream &os) const {
        os << "BasicSingle32: Data=" << data_ << std::endl;
    }
};


template<typename T>
class Matrix3D : public GameData
{
    static const size_t HEADER_SIZE = 12;

    uint32_t width_, depth_, height_;
    uint32_t height_offset_;
    T *buffer_;

    size_t data_len_;
    char *serial_data_;

public:
    // Constructor for message receiver (client).
    Matrix3D() :
            width_(0), depth_(0), height_(0), height_offset_(0), buffer_(nullptr),
            data_len_(0), serial_data_(nullptr) {}

    // Constructor for message sender (server).
    Matrix3D(uint32_t width, uint32_t depth, uint32_t height, T init_value) :
            width_(width), depth_(depth), height_(height), height_offset_(width * depth),
            buffer_(new T[width * depth * height]) {
        data_len_ = HEADER_SIZE + (height_offset_ * height);
        serial_data_ = new char[data_len_];

        T *ptr = buffer_;
        for (uint32_t i = 0; i < height_offset_ * height; ++i)
            *ptr++ = init_value;
    }

    ~Matrix3D() {
        delete[] buffer_;
        delete[] serial_data_;
    }

    uint32_t getWidth() const { return width_; }

    uint32_t getDepth() const { return depth_; }

    uint32_t getHeight() const { return height_; }

    T &at(uint32_t x, uint32_t z, uint32_t y) { return buffer_[index(x, z, y)]; }

    const T &at(uint32_t x, uint32_t z, uint32_t y) const { return buffer_[index(x, z, y)]; }

    T *ptr(uint32_t x, uint32_t z, uint32_t y) { return &buffer_[index(x, z, y)]; }

    const T *ptr(uint32_t x, uint32_t z, uint32_t y) const { return &buffer_[index(x, z, y)]; }

    T &at(const Vertex3DEx &vert) { return at(vert.x, vert.z, vert.y); }

    const T &at(const Vertex3DEx &vert) const { return at(vert.x, vert.z, vert.y); }

    T *ptr(const Vertex3DEx &vert) { return ptr(vert.x, vert.z, vert.y); }

    const T *ptr(const Vertex3DEx &vert) const { return ptr(vert.x, vert.z, vert.y); }

    virtual char *serializeData() {
        *(reinterpret_cast<uint32_t *>(serial_data_)) = htonl(width_);
        *(reinterpret_cast<uint32_t *>(serial_data_ + 4)) = htonl(depth_);
        *(reinterpret_cast<uint32_t *>(serial_data_ + 8)) = htonl(height_);

        memcpy((serial_data_ + HEADER_SIZE), buffer_, (height_offset_ * height_));

        return serial_data_;
    }

    virtual bool deserializeData(const char *data, size_t length) {
        if (length < HEADER_SIZE)
            return false;

        width_ = ntohl(*(reinterpret_cast<const uint32_t *>(data)));
        depth_ = ntohl(*(reinterpret_cast<const uint32_t *>(data + 4)));
        height_ = ntohl(*(reinterpret_cast<const uint32_t *>(data + 8)));

        height_offset_ = width_ * depth_;

        data_len_ = HEADER_SIZE + (height_offset_ * height_);
        if (length != data_len_)
            return false;

        buffer_ = new T[height_offset_ * height_];
        memcpy(buffer_, (data + HEADER_SIZE), (height_offset_ * height_));

        return true;
    }

    virtual size_t getLength() const { return data_len_; }

protected:
    uint32_t index(uint32_t x, uint32_t z, uint32_t y) const {
        return x + (width_ * z) + (height_offset_ * y);
    }

    virtual void print(std::ostream &os) const {
        os << "Matrix3D:" << std::endl <<
           "\tWidth=" << width_ << ", Depth=" << depth_ << ", Height=" << height_ << std::endl;
    }

private:
    // Non-copyable.
    Matrix3D(const Matrix3D &);
    void operator=(const Matrix3D &);
};

typedef Matrix3D<uint32_t> matrix3d_u32;
typedef std::shared_ptr<matrix3d_u32> matrix3d_u32_ptr;


#endif //DGL_GAMEDATA_H
