#pragma once
#include <memory>
#include <stack>

template <class T>
class ObjectPool
{
private:
    struct External_Deleter {
        explicit External_Deleter(std::weak_ptr<ObjectPool<T>* > pool)
            : pool_(pool) {}

        void operator()(T* ptr) {
            if (auto pool_ptr = pool_.lock()) {
                try {
                    (*pool_ptr.get())->add(std::unique_ptr<T>{ptr});
                    return;
                }
                catch (...) {}
            }
            std::default_delete<T>{}(ptr);
        }
    private:
        std::weak_ptr<ObjectPool<T>* > pool_;
    };

public:
    using ptr_type = std::unique_ptr<T, External_Deleter >;

    ObjectPool() : this_ptr_(new ObjectPool<T>* (this)) {}
    virtual ~ObjectPool() {}

    void put(std::unique_ptr<T> t) {
        pool_.push(std::move(t));
    }

    ptr_type get() {
        assert(!pool_.empty());
        ptr_type tmp(pool_.top().release(),
            External_Deleter{ std::weak_ptr<ObjectPool<T>*>{this_ptr_} });
        pool_.pop();
        return std::move(tmp);
    }

    bool empty() const {
        return pool_.empty();
    }

    size_t size() const {
        return pool_.size();
    }

private:
    std::shared_ptr<ObjectPool<T>* > this_ptr_;
    std::stack<std::unique_ptr<T> > pool_;
};