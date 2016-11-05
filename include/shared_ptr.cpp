#include "shared_ptr.h"

#ifndef SPTR_CPP
#define SPTR_CPP

template<typename T> /*noexcept*/
shared_ptr<T>::shared_ptr() noexcept :
	pointer_(nullptr), 
	counter_(nullptr) {
}

template<typename T> /*noexcept*/
shared_ptr<T>::shared_ptr(T * ptr) noexcept :
	pointer_(ptr),
	counter_(new size_t(1)) {
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr & r) :
	shared_ptr(r.pointer_) {
	counter_ = r.counter_;
	(*counter_)++;
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr && r) :
	pointer_(std::move(r.pointer_)),
	counter_(std::move(r.counter_)) {
	r.pointer_ = nullptr;
	r.counter_ = nullptr;
}

template<typename T>
auto shared_ptr<T>::operator =(const shared_ptr & r) -> shared_ptr & {
	if (this != &r) {
		(shared_ptr<T>(r)).swap(this);
	}
	return *this;
}

template<typename T>
auto shared_ptr<T>::operator =(shared_ptr && r) -> shared_ptr & {
	if (this != &r) {
		swap(r);
	}
	return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
	destroy();
}

template<typename T> /*noexcept*/
auto shared_ptr<T>::reset() noexcept -> void {
	destroy();
	pointer_ = nullptr;
	counter_ = nullptr;
}

template<typename T> /*noexcept*/
auto shared_ptr<T>::swap(shared_ptr & r) noexcept -> void {
	std::swap(pointer_, r.pointer_);
	std::swap(counter_, r.counter_);
}

template<typename T> /*noexcept*/
auto shared_ptr<T>::get() const noexcept -> T * {
	return pointer_;
}

template<typename T> /*noexcept*/
inline auto shared_ptr<T>::use_count() const noexcept -> size_t {
	return (counter_ != nullptr ? *counter_ : 0);
}

template<typename T> /*noexcept*/
auto shared_ptr<T>::unique() const noexcept -> bool {
	return (use_count() == 1);
}

template<typename T> /*noexcept*/
auto shared_ptr<T>::operator*() const noexcept -> T & {
	return *pointer_;
}

template<typename T> /*noexcept*/
auto shared_ptr<T>::operator->() const noexcept -> T * {
	return pointer_;
}

template<typename T> /*noexcept*/
shared_ptr<T>::operator bool() const noexcept {
	return (pointer_ != nullptr);
}

template<typename T>
auto shared_ptr<T>::destroy() -> void {
	if (counter_ != nullptr && (*counter_)-- == 0) {
		delete pointer_;
	}
}

template<class T, class ...Args>
shared_ptr<T> make_shared(Args && ...args) {
	return shared_ptr<T>(new T(std::forward<Args>(args)...));
}
#endif