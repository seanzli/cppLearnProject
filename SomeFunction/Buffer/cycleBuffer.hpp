#include <memory>

namespace CycleBuffer {

    ///TODO: try read write lock, in case multi-thread;
class cycleBuffer {
public:
    cycleBuffer(const size_t size = 1024) : m_size(size){
        m_buffer = static_cast<uint8_t*> (operator new(size * sizeof(uint8_t)));
        m_tail = m_buffer + m_size;
    }

    ~cycleBuffer() {
        if (m_buffer)
            delete m_buffer;
        m_buffer = nullptr;
    }

    uint8_t *getBufferHeader() {return m_buffer;}

    void write(uint8_t* ptr, const size_t size) {
        if (size > m_size)
            return;
        auto rest = restSize();
        if (rest >= size) {
            memcpy(m_write, ptr, size);
            m_write = m_write + size;
        } else {
            memcpy(m_write, ptr, rest);
            memcpy(m_buffer, ptr + rest, size - rest);
            m_write = m_buffer + size - rest;
        }
        return;
    }

    void read(uint8_t* reader, uint8_t* ptr) {
        if (reader < m_write) {
            memcpy(ptr, reader, m_write - reader);
        } else {
            memcpy(ptr, reader, m_tail - reader);
            memcpy(ptr + (m_tail - reader), m_buffer, m_write - m_buffer);
        }
        reader = m_write;
        return;
    }

private:
    size_t m_size;
    uint8_t* m_buffer;
    uint8_t* m_tail;
    uint8_t* m_write;
private:
    size_t restSize() const {
        return m_tail - m_write;
    }

    size_t readSize(uint8_t* ptr) const {
        if (ptr < m_write)
            return m_write - ptr;
        else
            return (m_write - m_buffer) + (m_tail - ptr);
    }
};

}