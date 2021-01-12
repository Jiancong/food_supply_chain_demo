#include "gtest/gtest.h"
//#include "../CircularBuffer.h"
#include "../Shelves.h"

namespace {

class ShelvesTest: public ::testing::Test {

	protected:
	
	ShelvesTest() {
		shelves_ = new Shelves(2, 2, 2, 2);
	}
	
	virtual ~ShelvesTest() {
		delete shelves_;
	}
	
	virtual void SetUp() {
	}
	
	virtual void TearDown() {
	}
	
	Shelves* shelves_;
};
 
TEST_F(ShelvesTest, AddOrderSingleOverflowTest) {

	shared_ptr<Order> order = make_shared<Order>("000", "first", "HOT", 1.0, 1.0);
	shelves_->AddOrder(order);
	order = make_shared<Order>("001", "first", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);
	shelves_->PrintStatus();

	EXPECT_EQ(2, shelves_->GetShelf("HOT")->GetSize());
}

TEST_F(ShelvesTest, RemoveOrderTest) {
	shared_ptr<Order> order = make_shared<Order>("000", "first", "HOT", 1.0, 1.0);
	shelves_->AddOrder(order);
	shelves_->Remove("000");
	shelves_->PrintStatus();
	EXPECT_EQ(0, shelves_->GetShelf("HOT")->GetSize());
}

TEST_F(ShelvesTest, AddOrderOverflowTest) {

	shared_ptr<Order> order = make_shared<Order>("000", "first", "HOT", 1.0, 1.0);
	shelves_->AddOrder(order);
	order = make_shared<Order>("001", "first", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);

	shelves_->PrintStatus();

	EXPECT_EQ(2, shelves_->GetShelf("HOT")->GetSize());

	order = make_shared<Order>("002", "second", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);
	order = make_shared<Order>("003", "second", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);

	shelves_->PrintStatus();

	EXPECT_EQ(2, shelves_->GetShelf("OVERFLOW")->GetSize());

	order = make_shared<Order>("004", "third", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);
	order = make_shared<Order>("005", "third", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);

	shelves_->PrintStatus();

	order = make_shared<Order>("006", "forth", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);
	order = make_shared<Order>("007", "forth", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);
	shelves_->PrintStatus();

	EXPECT_EQ(2, shelves_->GetShelf("COLD")->GetSize());
	EXPECT_EQ(2, shelves_->GetShelf("FROZEN")->GetSize());
}

TEST_F(ShelvesTest, AddOrderOverflowDiscardTest) {

	shared_ptr<Order> order = make_shared<Order>("000", "first", "HOT", 1.0, 1.0);
	shelves_->AddOrder(order);
	order = make_shared<Order>("001", "first", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);

	shelves_->PrintStatus();

	EXPECT_EQ(2, shelves_->GetShelf("HOT")->GetSize());

	order = make_shared<Order>("002", "second", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);
	order = make_shared<Order>("003", "second", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);

	shelves_->PrintStatus();

	EXPECT_EQ(2, shelves_->GetShelf("OVERFLOW")->GetSize());

	order = make_shared<Order>("004", "third", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);
	order = make_shared<Order>("005", "third", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);

	shelves_->PrintStatus();

	order = make_shared<Order>("006", "forth", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);
	order = make_shared<Order>("007", "forth", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);

	shelves_->PrintStatus();

	order = make_shared<Order>("008", "forth", "HOT", 20.0, 1.0);
	shelves_->AddOrder(order);

	shelves_->PrintStatus();

	EXPECT_EQ("008", shelves_->GetShelf("OVERFLOW")->Get("008")->GetId());
}

}  // namespace
 
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
