#include <iostream>
#include <utility>

#ifndef SPTR_HPP
#define SPTR_HPP

template<typename T>
class shared_ptr {
public:
	shared_ptr() noexcept; /*noexcept*/ // TESTED
	explicit shared_ptr(T * ptr) noexcept; /*noexcept*/ // TESTED

	shared_ptr(const shared_ptr& r); // TESTED
	shared_ptr(shared_ptr&& r); // TESTED
	
	auto operator =(const shared_ptr& r) -> shared_ptr &; // TESTED
	auto operator =(shared_ptr&& r) -> shared_ptr&; // TESTED
	
	~shared_ptr();

	auto reset() noexcept -> void; /*noexcept*/ // TESTED
	auto swap(shared_ptr& r) noexcept -> void; /*noexcept*/ // TESTED

	auto get() const noexcept -> T *; /*noexcept*/ // TESTED
	auto use_count() const noexcept -> size_t; /*noexcept*/ // TESTED
	auto unique() const noexcept -> bool; /*noexcept*/ // TESTED

	auto operator*() const noexcept -> T &; /*noexcept*/ // TESTED
	auto operator->() const noexcept -> T *;  /*noexcept*/ // TESTED
	auto operator[](std::ptrdiff_t idx) noexcept -> T&; /*noexcept*/
	explicit operator bool() const noexcept; /*noexcept*/ // TESTED
private:
	T * pointer_;
	size_t * counter_;

	auto destroy() -> void;
};

template <class T, class... Args>
shared_ptr<T> make_shared(Args&& ...args);

#include "shared_ptr.cpp"

#endif

