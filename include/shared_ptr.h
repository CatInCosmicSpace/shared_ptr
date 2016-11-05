#include <iostream>
#include <utility>
#include <stdexcept>

#ifndef SPTR_HPP
#define SPTR_HPP

template<typename T>
class shared_ptr {
public:
	shared_ptr() noexcept; /*noexcept*/ // TESTED
	explicit shared_ptr(T * ptr); /*strong*/ // TESTED

	shared_ptr(const shared_ptr& r); /*strong*/ // TESTED
	shared_ptr(shared_ptr&& r); /*noexcept*/ // TESTED
	
	auto operator =(const shared_ptr& r) -> shared_ptr &; /*strong*/ // TESTED
	auto operator =(shared_ptr&& r) -> shared_ptr&; /*noexcept*/ // TESTED
	
	~shared_ptr(); /*noexcept*/

	auto reset() noexcept -> void; /*noexcept*/ // TESTED
	auto swap(shared_ptr& r) noexcept -> void; /*noexcept*/ // TESTED

	auto get() const noexcept -> T *; /*noexcept*/ // TESTED
	auto use_count() const noexcept -> size_t; /*noexcept*/ // TESTED
	auto unique() const noexcept -> bool; /*noexcept*/ // TESTED

	auto operator*() const throw(std::range_error) -> T &; /*strong*/ // TESTED
	auto operator->() const throw(std::range_error)-> T *;  /*strong*/ // TESTED
	explicit operator bool() const noexcept; /*noexcept*/ // TESTED
private:
	T * pointer_;
	size_t * counter_;

	auto destroy() -> void; /*strong*/
	auto throw_if_nullptr() const throw(std::range_error) -> void; /*strong*/
};

template <class T, class... Args>
shared_ptr<T> make_shared(Args&& ...args);

#include "shared_ptr.cpp"

#endif