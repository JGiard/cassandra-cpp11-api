/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    status = CxxTest::Main<CxxTest::ErrorPrinter>( tmp, argc, argv );
    return status;
}
bool suite_TestWrapper_init = false;
#include "/home/jg/workspace/cassandra-cpp11-api/src/test/tst_wrapper.h"

static TestWrapper suite_TestWrapper;

static CxxTest::List Tests_TestWrapper = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestWrapper( "/home/jg/workspace/cassandra-cpp11-api/src/test/tst_wrapper.h", 63, "TestWrapper", suite_TestWrapper, Tests_TestWrapper );

static class TestDescription_suite_TestWrapper_test_basic1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestWrapper_test_basic1() : CxxTest::RealTestDescription( Tests_TestWrapper, suiteDescription_TestWrapper, 66, "test_basic1" ) {}
 void runTest() { suite_TestWrapper.test_basic1(); }
} testDescription_suite_TestWrapper_test_basic1;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
