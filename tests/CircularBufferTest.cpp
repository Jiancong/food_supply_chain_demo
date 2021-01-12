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
		cb_ = new CircularBuffer(15);
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
		shared_ptr<Order> order = make_shared<Order>("xxx", "second", "hot", 1.0, 1.0);
		cb_->Put(order);
		order = make_shared<Order>("abcd", "first", "hot", 20.0, 1.0);
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
	
  	EXPECT_EQ("abcd", cb_->Get("abcd")->GetId());
}

TEST_F(CircularBufferTest, RemoveAndMaintainTest) {
	sleep(5);
	cb_->Maintain(2.0);
	cb_->PrintStatus();
	EXPECT_EQ(1, cb_->Size());
}
 
}  // namespace
 
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
