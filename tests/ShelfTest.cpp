#include "gtest/gtest.h"
#include "../Shelf.h"

namespace {

class ShelfTest: public ::testing::Test {

protected:
	
	ShelfTest() {
		shelf_ = new Shelf("HOT", 1.0, 3);
	}
	
	virtual ~ShelfTest() {
		delete shelf_;
	}
	
	virtual void SetUp() {
		shared_ptr<Order> order = make_shared<Order>("000", "first", "HOT", 1.0, 1.0);
		shelf_->Add(order);
		order = make_shared<Order>("111", "second", "HOT", 20.0, 1.0);
		shelf_->Add(order);
		order = make_shared<Order>("222", "third", "HOT", 3.5, 1.0);
		shelf_->Add(order);
	}
	
	virtual void TearDown() {

	}
	
	Shelf* shelf_;
};
 
TEST_F(ShelfTest, GetElementTest) {
	
	EXPECT_EQ(3, shelf_->GetSize());
	shelf_->PrintStatus();
  	EXPECT_EQ("111", shelf_->Get("111")->GetId());
	shelf_->PrintStatus();
	EXPECT_EQ(2, shelf_->GetSize());

}

TEST_F(ShelfTest, MaintainTest) {
	shelf_->PrintStatus();
	sleep(5);
	shelf_->Maintain();
	shelf_->PrintStatus();
	EXPECT_EQ(1, shelf_->GetSize());
}

TEST_F(ShelfTest, FullAddTest) {

	EXPECT_EQ(3, shelf_->GetSize());
	shelf_->PrintStatus();
	shared_ptr<Order> order = make_shared<Order>("333", "fourth", "HOT", 1.0, 1.0);
	shelf_->Add(order);
	shelf_->PrintStatus();
	EXPECT_EQ(nullptr, shelf_->Get("333"));

}
 
}  // namespace
 
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
