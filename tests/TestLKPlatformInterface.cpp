#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <LKPlatformInterface.h>

class TestBaseImpl : public LKPlatformInterface<TestBaseImpl>
{
public:
	virtual ~TestBaseImpl() {};
	
	virtual int returnSomething() { return 0; };
	
protected:
	TestBaseImpl() {};
};

class TestHighPrioImpl : public TestBaseImpl
{
public:
	TestHighPrioImpl() {};
	virtual ~TestHighPrioImpl() {};
	
	virtual int returnSomething() override { return 1; };
};
REGISTER_IMPL(TestBaseImpl, TestHighPrioImpl, 100);

class TestLowPrioImpl : public TestBaseImpl
{
public:
	TestLowPrioImpl() {};
	virtual ~TestLowPrioImpl() {};
	
	virtual int returnSomething() override { return -1; };
};
REGISTER_IMPL(TestBaseImpl, TestLowPrioImpl, 0);



TEST_CASE("Can instantiate a concrete implementation")
{
	TestBaseImpl *impl = TestBaseImpl::create();
	REQUIRE(impl->returnSomething() == 1);
}
