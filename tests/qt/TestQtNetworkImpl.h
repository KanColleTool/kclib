#include <qt/LKQtNetworkImpl.h>
#include <QtTest>

class TestQtNetworkImpl : public QObject
{
	Q_OBJECT
	
public:
	LKQtNetworkImpl impl;
	
	bool success = true;
	int status = 200;
	LKQtNetworkImpl::handler_fn handler = [&](bool success_, int status_, std::vector<char> body_) {
		success = success_;
		status = status_;
	};
	
private slots:
	void initTestCase()
	{
		impl.synchronous = true;
	};
	
	void cleanupTestCase()
	{
		
	};
	
	void getExpect200()
	{
		impl.get("http://httpbin.org/status/200", handler);
		QVERIFY(success == true);
		QVERIFY(status == 200);
	};
	
	void getExpect404()
	{
		impl.get("http://httpbin.org/status/404", handler);
		QVERIFY(success == true);
		QVERIFY(status == 404);
	};
	
	void postExpect200()
	{
		impl.post("http://httpbin.org/status/200", "Lorem ipsum dolor sit amet", handler);
		QVERIFY(success == true);
		QVERIFY(status == 200);
	};
	
	void postExpect404()
	{
		impl.post("http://httpbin.org/status/404", "Lorem ipsum dolor sit amet", handler);
		QVERIFY(success == true);
		QVERIFY(status == 404);
	};
};
