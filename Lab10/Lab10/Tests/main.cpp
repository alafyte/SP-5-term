#include "Test.h"

using namespace std;
using namespace Test;

int main()
{

	if (Test1_Create())
		cout << "-- Test #1: success" << endl;
	else
		cout << "-- Test #1: error" << endl;

	if (Test2_Insert())
		cout << "-- Test #2: success" << endl;
	else
		cout << "-- Test #2: error" << endl;

	if (Test3_Get())
		cout << "-- Test #3: success" << endl;
	else
		cout << "-- Test #3: error" << endl;

	if (Test4_Delete())
		cout << "-- Test #4: error" << endl;
	else
		cout << "-- Test #4: success" << endl;

	if (Test5_Close())
		cout << "-- Test #5: success" << endl;
	else
		throw "-- Test #5: error";
}