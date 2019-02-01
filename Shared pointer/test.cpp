#include "pch.h"
#include "Shared.h"

TEST(Constructors, Basic) {
  SharedPTR<int> p(new int(10));
  SharedPTR<int> p_copy(p);
  EXPECT_EQ(*p, *p_copy);
  SharedPTR<int> p_copy2(new int(20));
  EXPECT_TRUE(*p != *p_copy2);
  p_copy2 = p;
  EXPECT_EQ(*p_copy2, *p);
}

TEST(Constructors, MoveSemantics) {
	SharedPTR<int> p(new int(10));
	SharedPTR<int> p_copy(p);
	SharedPTR<int> moved(static_cast<SharedPTR<int>&&>(p));
	EXPECT_FALSE((p));
	EXPECT_EQ(*moved, *p_copy);
}

TEST(Constructors, Empty) {
	SharedPTR<int> empty(nullptr);
	SharedPTR<int> p(new int(90));
	empty = p;
	EXPECT_EQ(*p, *empty);
	SharedPTR<int> empty2(nullptr);
	SharedPTR<int> empty2copy(empty2);
	EXPECT_EQ(empty2, empty2copy);
}

TEST(Constructors, AssignmentToObj) {
	int * obj = new int(900);
	SharedPTR<int> p(nullptr);
	p = obj;
	EXPECT_EQ(*p, *obj);
}
