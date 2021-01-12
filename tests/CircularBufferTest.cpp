#include "gtest/gtest.h"
#include "../CircularBuffer.h"

namespace {
// The fixture for testing class Foo.
class CircularBufferTest: public ::testing::Test {
	protected:
	// You can remove any or all of the following functions if its body
	// is empty.
	
	CircularBufferTest() {
	  	// You can do set-up work for each test here.
		cb_ = new CircularBuffer(4);
	}
	
	virtual ~CircularBufferTest() {
	  	// You can do clean-up work that doesn't throw exceptions here.
		delete cb_;
	}
	
	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		shared_ptr<Order> order = make_shared<Order>("000", "first", "hot", 0.1, 1.0);
		cb_->Put(order);
		order = make_shared<Order>("111", "second", "hot", 20.0, 1.0);
		cb_->Put(order);
		order = make_shared<Order>("222", "third", "hot", 10.0, 1.0);
		cb_->Put(order);
	
	}
	
	virtual void TearDown() {
	  	// Code here will be called immediately after each test (right
	  	// before the destructor).
	}
	
	// Objects declared here can be used by all tests in the test case for Foo.
	CircularBuffer* cb_;
};
 
TEST_F(CircularBufferTest, FindElementTest) {
	
  	EXPECT_EQ("111", cb_->Get("111")->GetId());
	EXPECT_EQ(2, cb_->Size());
}

TEST_F(CircularBufferTest, MaintainTest) {
	EXPECT_EQ(false, cb_->Full());
	EXPECT_EQ(3, cb_->Size());

	sleep(2);

	cb_->Maintain(1.0);
	cb_->PrintStatus();
	EXPECT_EQ(2, cb_->Size());
}

TEST_F(CircularBufferTest, OverflowTest) {
	
	shared_ptr<Order> order = make_shared<Order>("444", "fourth", "hot", 0.1, 1.0);
	cb_->Put(order);
	cb_->PrintStatus();
	order = make_shared<Order>("555", "fifth", "hot", 0.1, 1.0);
	cb_->Put(order);
	cb_->PrintStatus();
	EXPECT_EQ("555", cb_->Get("555")->GetId());
	EXPECT_EQ(nullptr, cb_->Get("000"));

}

}  // namespace
 
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
