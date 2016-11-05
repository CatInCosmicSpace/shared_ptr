#include "shared_ptr.h"
#include <catch.hpp>

SCENARIO("SP: default ctor", "[ctor]") {
	shared_ptr<size_t> sp;

	REQUIRE(sp.get() == nullptr);
	REQUIRE(sp.unique() == false);
	REQUIRE(sp.use_count() == 0);
}

SCENARIO("SP: params ctor", "[params ctor]") {
	shared_ptr<size_t> sp(new size_t[10]);

	REQUIRE(sp.get() != nullptr);
	REQUIRE(sp.use_count() == 1);
	REQUIRE(sp.unique());
}

SCENARIO("SP: copy ctor", "[copy ctor]") {
	shared_ptr<size_t> f_sp(new size_t[10]);
	auto s_sp = f_sp;

	REQUIRE(s_sp.get() != nullptr);
	REQUIRE(s_sp.use_count() == 2);
	REQUIRE(s_sp.unique() == false);
}

SCENARIO("SP: copy ctor {}", "[copy ctor {}]") {
	shared_ptr<size_t> f_sp(new size_t[10]);
	auto s_sp{f_sp};

	REQUIRE(s_sp.get() != nullptr);
	REQUIRE(s_sp.use_count() == 2);
	REQUIRE(s_sp.unique() == false);
}

SCENARIO("SP: move ctor", "[move ctor]") {
	auto sp = std::move(make_shared<size_t>(10));

	REQUIRE(sp.get() != nullptr);
	REQUIRE(sp.use_count() == 1);
	REQUIRE(sp.unique());
}

SCENARIO("SP: copy operator =", "copy operator =") {
	shared_ptr<size_t> f_sp(new size_t[10]);
	auto s_sp = f_sp;

	REQUIRE(f_sp.get() != nullptr);
	REQUIRE(f_sp.use_count() == 2);
	REQUIRE(f_sp.unique() == false);

	REQUIRE(s_sp.get() != nullptr);
	REQUIRE(s_sp.use_count() == 2);
	REQUIRE(s_sp.unique() == false);
}

SCENARIO("SP: move operator =", "move operator =") {
	shared_ptr<size_t> f_sp(new size_t[10]);
	auto s_sp = std::move(f_sp);

	REQUIRE(f_sp.get() == nullptr);
	REQUIRE(f_sp.use_count() == 0);
	REQUIRE(f_sp.unique() == false);

	REQUIRE(s_sp.get() != nullptr);
	REQUIRE(s_sp.use_count() == 1);
	REQUIRE(s_sp.unique() == true);
}

SCENARIO("SP: reset one", "[reset one]") {
	shared_ptr<size_t> sp(new size_t[10]);
	sp.reset();
	REQUIRE(sp.get() == nullptr);
	REQUIRE(sp.use_count() == 0);
	REQUIRE(sp.unique() == false);
}

SCENARIO("SP: reset two", "[reset two]") {
	shared_ptr<size_t> f_sp(new size_t[10]);
	auto s_sp = f_sp;
	f_sp.reset();

	REQUIRE(s_sp.get() != nullptr);
	REQUIRE(s_sp.use_count() == 1);
	REQUIRE(s_sp.unique() == true);
}

SCENARIO("SP: get", "[get]") {
	size_t * ptr = new size_t[10];
	shared_ptr<size_t> sp(ptr);

	REQUIRE(ptr == sp.get());
}

SCENARIO("SP: use_count", "[use_count]") {
	size_t * ptr = new size_t[10];
	shared_ptr<size_t> f_sp(ptr);

	REQUIRE(f_sp.use_count() == 1);

	shared_ptr<size_t> s_sp(f_sp);

	REQUIRE(f_sp.use_count() == 2);
	REQUIRE(s_sp.use_count() == 2);

	shared_ptr<size_t> t_sp(s_sp);

	REQUIRE(f_sp.use_count() == 3);
	REQUIRE(s_sp.use_count() == 3);
	REQUIRE(t_sp.use_count() == 3);
}

SCENARIO("SP: unique", "[unique]") {
	size_t * ptr = new size_t[10];
	shared_ptr<size_t> f_sp(ptr);

	REQUIRE(f_sp.unique());

	shared_ptr<size_t> s_sp(f_sp);

	REQUIRE(f_sp.unique() == false);
}

SCENARIO("SP: swap", "[swap]") {
	size_t * f_ptr = new size_t[10];
	size_t * s_ptr = new size_t[10];

	shared_ptr<size_t> f_sp(f_ptr);
	shared_ptr<size_t> s_sp(s_ptr);
	s_sp.swap(f_sp);

	REQUIRE(f_sp.get() == s_ptr);
	REQUIRE(s_sp.get() == f_ptr);
	REQUIRE(f_sp.unique());
	REQUIRE(s_sp.unique());
	REQUIRE(f_sp.use_count() == 1);
	REQUIRE(s_sp.use_count() == 1);
}

SCENARIO("SP: operator *", "operator *") {
	class Foo {
	public:
		bool test() {
			return x;
		}
		bool x = true;
	};
	Foo * pFoo = new Foo[10];
	shared_ptr<Foo> sp(pFoo);

	REQUIRE((*sp).test());
}

SCENARIO("SP: operator ->", "operator ->") {
	class Foo {
	public:
		bool test() {
			return x;
		}
		bool x = true;
	};
	Foo * pFoo = new Foo[10];
	shared_ptr<Foo> sp(pFoo);
	
	REQUIRE(sp->test());
}

SCENARIO("SP: operator * throw", "operator * throw") {
	class Foo {
	public:
		bool test() {
			return x;
		}
		bool x = true;
	};
	Foo * pFoo = nullptr;
	shared_ptr<Foo> sp(pFoo);

	bool test_b = false;
	try {
		(*sp).test();
	}
	catch (std::range_error &e) {
		test_b = true;
	}
	REQUIRE(test_b);
}

SCENARIO("SP: operator -> throw", "operator -> throw") {
	class Foo {
	public:
		bool test() {
			return x;
		}
		bool x = true;
	};
	Foo * pFoo = nullptr;
	shared_ptr<Foo> sp(pFoo);

	bool test_b = false;
	try {
		sp->test();
	}
	catch (std::range_error &e) {
		test_b = true;
	}
	REQUIRE(test_b);
}
