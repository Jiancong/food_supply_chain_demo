#include "gtest/gtest.h"
//#include "../CircularBuffer.h"
#include "../Shelf.h"

namespace {

class ShelfTest: public ::testing::Test {
	protected:
	
	ShelfTest() {
		shelf_ = new Shelf("HOT", 2.0, 15);
	}
	
	virtual ~ShelfTest() {
		delete shelf_;
	}
	
	virtual void SetUp() {
		shared_ptr<Order> order = make_shared<Order>("xxx", "second", "HOT", 1.0, 1.0);
		shelf_->Add(order);
		order = make_shared<Order>("abcd", "first", "HOT", 20.0, 1.0);
		shelf_->Add(order);
	
	}
	
	virtual void TearDown() {
	}
	
	Shelf* shelf_;
};
 
TEST_F(ShelfTest, GetElementTest) {
	
	EXPECT_EQ(2, shelf_->GetSize());
  	EXPECT_EQ("abcd", shelf_->Get("abcd")->GetId());
	EXPECT_EQ(1, shelf_->GetSize());
}

TEST_F(ShelfTest, MaintainTest) {
	sleep(3);
	shelf_->Maintain();
	shelf_->PrintStatus();
	EXPECT_EQ(1, shelf_->GetSize());
}
 
}  // namespace
 
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
