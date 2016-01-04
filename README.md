## Google's Protobuf Usage

### Preparation
1. Download [protobuf-2.6.1.tar.gz](https://github.com/google/protobuf/releases/download/v2.6.1/protobuf-2.6.1.tar.gz) and [protoc-2.6.1-win32.zip](https://github.com/google/protobuf/releases/download/v2.6.1/protoc-2.6.1-win32.zip), unzip them. The `protoc.exe` in `protoc-2.6.1-win32.zip` is the compiler, and `protobuf-2.6.1.tar.gz` contains all the source files.
2. Compile `protobuf-2.6.1.tar.gz` using VS2013 with the solution file provided in `./vsprojects/`. Then you will get three key `.lib` files, `libprotobuf.lib`, `libprotobuf-lite.lib` and `libprotoc.lib`, which is necessary for all protobuf project.

### Create an example
1. Create a `proto` file using text editing tools, the content is like following code
```protobuf
// file lm.helloworld.proto
package lm; // corresponding to namespace in C/C++
message helloworld // corresponding to class in C/C++
{ 
	required int32     id = 1;  // ID 
	required string    str = 2;  // str 
	optional int32     opt = 3;  //optional field 
}
```
2. Using `protoc.exe` to compile it, with command
```bash
set SRC_DIR=./
set DST_DIR=./
protoc -I=%SRC_DIR% --cpp_out=%DST_DIR% %SRC_DIR%/lm.helloworld.proto
```
Then you will get two files, `lm.helloworld.pb.h` and `lm.helloworld.pb.cc`.

3. Create a cpp file with `main()` function, like this
```cpp
#include "lm.helloworld.pb.h"
#include <fstream>
#include <iostream>

using namespace std;

void ListMsg(const lm::helloworld & msg)
{
	cout << msg.id() << endl;
	cout << msg.str() << endl;
}

int writer()
{
	lm::helloworld msg1;
	msg1.set_id(101);
	msg1.set_str("hello");
	fstream output("./log.txt", ios::out | ios::trunc | ios::binary);
	if (!msg1.SerializeToOstream(&output))
	{
		cerr << "Failed to write msg." << endl;
		return -1;
	}
	return 0;
}

int reader()
{
	lm::helloworld msg1;
	fstream input("./log.txt", ios::in | ios::binary);
	if (!msg1.ParseFromIstream(&input))
	{
		cerr << "Failed to parse address book." << endl;
		return -1;
	}
	ListMsg(msg1);
	return 0;
}

int main(void)
{
	writer();
	reader();
}
```
4. Create a solution with the following `CMakeLists.txt`, configure it and generate the solution. Finally build the solution and get the result.
```cmake
cmake_minimum_required(VERSION 2.9)
set(TARGET_BUILD_PLATFORM x64)
include_directories(./libs/protobuf/include)
project(proto-test)
file(GLOB SOURCES
    src/*.*
)
add_executable(proto-test ${SOURCES})
target_link_libraries(proto-test 
	debug ${CMAKE_CURRENT_SOURCE_DIR}/libs/protobuf/lib/${TARGET_BUILD_PLATFORM}/debug/*.lib
	optimized ${CMAKE_CURRENT_SOURCE_DIR}/libs/protobuf/lib/${TARGET_BUILD_PLATFORM}/release/*.lib
)
```
