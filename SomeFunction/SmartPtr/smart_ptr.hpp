#ifdef SMART_PTR_
#define SMART_PTR_


namespace TEST_SMART_PTR {
    template<typename T>
    class SmartPtr {
    public:
        SmartPtr() {
            m_buffer = nullptr;
            m_count = new unsigned (0);
        }

        SmartPtr(T* p) {
            m_buffer = p;
            m_count = new unsigned (1);
        }

        SmartPtr(const SmartPtr& rhs) {
            m_buffer = rhs.m_buffer;
            m_count = rhs.m_count;
            ++(*m_count);
        }

        SmartPtr<T>& operator=(const SmartPtr<T>& rhs) {
            m_buffer = rhs.m_buffer;
            m_count = rhs.m_count;
            ++(*m_count);
        }

        ~SmartPtr() {
            --(*m_count);
            if((*m_count) == 0) {
                delete m_buffer;
                delete m_count;
                m_buffer = nullptr;
                m_count = nullptr;
            }
        }

    private:
        T* m_buffer;
        unsigned* m_count;
    };



}


#endif