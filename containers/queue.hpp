#ifndef D_QUEUE_HPP_
#define D_QUEUE_HPP_ 1

#include <iterator>
#include <memory>
#include <utility>

namespace containers {

    template <class T, class Allocator = std::allocator<T>>
    struct queue {
    private:
        struct element;
    public:
        queue() = default;

        struct forward_iterator {
        public:
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            forward_iterator(element *ptr);

            T& operator* ();
            forward_iterator& operator++ ();
            forward_iterator operator++ (int);

            bool operator== (const forward_iterator& o) const;
            bool operator!= (const forward_iterator& o) const;
        private:
            element* ptr_ = nullptr;

            friend queue;
        };

        forward_iterator begin();
        forward_iterator end();

        void pop();
        void push(const T& value);
        T& top();

        void insert(forward_iterator& it, const T& value);
        void insert_to_num(int pos, const T& value);
        void erase(forward_iterator it);
        void erase_to_num(int pos);
        bool empty() {
            return first == nullptr;
        }
    private:

        using allocator_type = typename Allocator::template rebind<element>::other;

        struct deleter {

            deleter(allocator_type* allocator): allocator_(allocator) {}

            void operator() (element* ptr) {
                if (ptr != nullptr) {
                    std::allocator_traits<allocator_type>::destroy(*allocator_, ptr);
                    allocator_->deallocate(ptr, 1);
                }
            }
        private:
            allocator_type* allocator_;
        };

        using unique_ptr = std::unique_ptr<element, deleter>;

        struct element {
            T value;
            unique_ptr next_element{nullptr, deleter{nullptr}};
            element(const T& value_): value(value_) {}
            forward_iterator next();
        };

        allocator_type allocator_{};
        unique_ptr first{nullptr, deleter{nullptr}};
        element *endl = nullptr;
    };

    template <class T, class Allocator>
    typename queue<T, Allocator>::forward_iterator queue<T, Allocator>::begin() {
        if (first == nullptr) {
            return nullptr;
        }
        return forward_iterator(first.get());
    }

    template <class T, class Allocator>
    typename queue<T, Allocator>::forward_iterator queue<T, Allocator>::end() {
        return forward_iterator(nullptr);
    }

    template <class T, class Allocator>
    void queue<T, Allocator>::insert_to_num(int pos, const T& value) {
        forward_iterator iter = this->begin();
        for (int i = 0; i < pos; ++i) {
            if (i == pos) {
                break;
            }
            ++iter;
        }
        this->insert(iter, value);
    }

    template <class T, class Allocator>
    void queue<T, Allocator>::insert(containers::queue<T, Allocator>::forward_iterator& ptr, const T& value) {
        // element* newptr = this->allocator_.allocate(1);
        // // auto val = std::unique_ptr<element, deleter{&this->allocator_}>(new element{value});
        // // std::unique_ptr<element, deleter{nullptr}> val = std::unique_ptr<element, deleter{nullptr}>(new element{ value });
        // std::allocator_traits<allocator_type>::construct(this->allocator_,value, std::unique_ptr<element, deleter>(nullptr, deleter{&this->allocator_}));
        // unique_ptr = new_node(newptr, deleter{&this->allocator_});

        // forward_iterator it = this->begin();
        // if (ptr == this->begin()) {
        //     val->next_element = std::move(first);
        //     first = std::move(new_node);
        //     return;
        // }
        // while ((it.ptr_ != nullptr) && (it.ptr_->next() != ptr)) {
        //     ++it;
        // }
        // if (it.ptr_ == nullptr) {
        //     throw std::logic_error ("ERROR");
        // }
        // new_node->next_element = std::move(it.ptr_->next_element);
        // it.ptr_->next_element = std::move(new_node);
        



        // element* newptr = this->allocator_.allocate(1);
        // // std::allocator_traits<allocator_type>::construct(this->allocator_,value, std::unique_ptr<element, deleter>(nullptr, deleter{&this->allocator_}));
        // unique_ptr = new_node(newptr, deleter{&this->allocator_});

        // if (it.ptr_ == nullptr) {
        //     throw std::logic_error("iterator went beyond the bounds of the stack");
        // } else if (it.ptr_ == nullptr) {
        //     first = std::unique_ptr<element>(new element(value, nullptr));
        // } else {
        //     new_node->next_element = std::move(it.ptr_->next_element);
        //     it.ptr_->next_element = std::move(new_node);
        // }



        element* NewNode = this->allocator_.allocate(1);
        std::allocator_traits<allocator_type>::construct(this->allocator_, NewNode, value);
        auto val = unique_ptr(NewNode, deleter{&this->allocator_});
        //auto tmp = std::unique_ptr<Node>(new Node{value});
        forward_iterator it = this->begin();
        // while ((i.ptr_ != nullptr) && (i.ptr_->next() != ptr)) {
        //     if (i.ptr_ == nullptr) throw std::logic_error("Out of range\n");
        //     ++i;

        // }
        // if (i.ptr_->next_element == nullptr) {
        //     i.ptr_->next_element = std::move(tmp);
        //     return;
        // }
        // ++i;
        // tmp->next_element = std::move(i.ptr_->next_element);
        // i.ptr_->next_element = std::move(tmp);
        // return;
        if (ptr == this->begin()) {
            val->next_element = std::move(first);
            first = std::move(val);
            return;
        }
        while ((it.ptr_ != nullptr) && (it.ptr_->next() != ptr)) {
            ++it;
        }
        if (it.ptr_ == nullptr) {
            throw std::logic_error ("ERROR");
        }
        val->next_element = std::move(it.ptr_->next_element);
        it.ptr_->next_element = std::move(val);
    }

    template <class T, class Allocator>
    void queue<T, Allocator>::erase_to_num(int pos) {
        pos += 1;
        forward_iterator iter = this->begin();
        for (int i = 1; i <= pos; ++i) {
            if (i == pos) {
                break;
            }
            ++iter;
        }
        this->erase(iter);
    }

    template <class T, class Allocator>
    void queue<T, Allocator>::erase(containers::queue<T, Allocator>::forward_iterator ptr) {
        forward_iterator it = this->begin(), end = this->end();
        if (ptr == end) {
            throw std::logic_error("ERROR");
        }
        if (ptr == it) {
            this->pop();
            return;
        }
        while ((it.ptr_ != nullptr) && (it.ptr_->next() != ptr)) {
            ++it;
        }
        if (it.ptr_ == nullptr) {
            throw std::logic_error("ERROR");
        }
        it.ptr_->next_element = std::move(ptr.ptr_->next_element);
    }

    template <class T, class Allocator>
    void queue<T, Allocator>::pop() {
        if (first == nullptr) {
            throw std::logic_error ("queue is empty");
        }
        auto tmp = std::move(first->next_element);
        first = std::move(tmp);
    }

    template <class T, class Allocator>
    void queue<T, Allocator>::push(const T& value) {
        element* result = this->allocator_.allocate(1);
        std::allocator_traits<allocator_type>::construct(this->allocator_, result, value);
        if (!first) {
            first = unique_ptr(result, deleter{&this->allocator_});
            endl = first.get();
            return;
        }
        endl->next_element = unique_ptr(result, deleter{&this->allocator_});
        endl = endl->next_element.get();
    }

    template <class T, class Allocator>
    T& queue<T, Allocator>::top() {
        if (first == nullptr) {
            throw std::logic_error("queue is empty");
        }
        return first->value;
    }

    template<class T, class Allocator>
    typename queue<T, Allocator>::forward_iterator queue<T, Allocator>::element::next() {
        return forward_iterator(this->next_element.get());
    }

    template<class T, class Allocator>
    queue<T, Allocator>::forward_iterator::forward_iterator(containers::queue<T, Allocator>::element *ptr) {
        ptr_ = ptr;
    }

    template<class T, class Allocator>
    T& queue<T, Allocator>::forward_iterator::operator*() {
        return this->ptr_->value;
    }

    template<class T, class Allocator>
    typename queue<T, Allocator>::forward_iterator& queue<T, Allocator>::forward_iterator::operator++() {
        if (ptr_ == nullptr) throw std::logic_error ("out of queue borders");
        *this = ptr_->next();
        return *this;
    }

    template<class T, class Allocator>
    typename queue<T, Allocator>::forward_iterator queue<T, Allocator>::forward_iterator::operator++(int) {
        forward_iterator old = *this;
        ++*this;
        return old;
    }

    template<class T, class Allocator>
    bool queue<T, Allocator>::forward_iterator::operator==(const forward_iterator& other) const {
        return ptr_ == other.ptr_;
    }

    template<class T, class Allocator>
    bool queue<T, Allocator>::forward_iterator::operator!=(const forward_iterator& other) const {
        return ptr_ != other.ptr_;
    }
}

#endif // D_CONTAINERS_QUEUE_HPP_