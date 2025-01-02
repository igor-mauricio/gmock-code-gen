# Welcome to the gmock-code-gen wiki!

## Quick Start

1. Install gmock-code-gen package

```bash
go install github.com/igor-mauricio/gmock-code-gen@latest
```

1. Run the generate command with either the path to the root folder of the source files or the path to the source file that contains the class to be mocked.

```bash
gmock-code-gen <path/to/the/root/folder>
```


## How it works


### Expected source file structure

Each header file should contain one or more classes to be mocked. It will generate mocks for files that contains classes with at least one pure virtual method.
For google mock to work, the interface to be mocked *must* have a virtual destructor.

##### myClass.h
```cpp
// Imports

class MyClass {
public:
    virtual ~MyClass() = default;
    virtual void myMethod() = 0;
    virtual int myMethodWithReturn() = 0;
    virtual void myMethodWithArgs(int arg1, int arg2) = 0;
    virtual int myMethodWithArgsAndReturn(int arg1, int arg2) = 0;
};

```

### Expected generated output

##### myClassMocks.h

```cpp
#include <myClass.h>
#include <gmock/gmock.h>

class MyClassMock : public MyClass {
public:
    MOCK_METHOD(void, myMethod, (), (override));
    MOCK_METHOD(int, myMethodWithReturn, (), (override));
    MOCK_METHOD(void, myMethodWithArgs, (int arg1, int arg2), (override));
    MOCK_METHOD(int, myMethodWithArgsAndReturn, (int arg1, int arg2), (override));
};

```

### Expected project structure

a project structure like this:

```
src
├── main.cpp
├── myClass.h
├── noInterfaces.h
└── foo
    ├── foo.cpp
    └── foo.h

```
with the command `gmock-code-gen src`
will generate the following files:
```
src
├── main.cpp
├── myClass.h
├── myClassMocks.h
├── noInterfaces.h
└── foo
    ├── foo.cpp
    ├── foo.h
    └── fooMocks.h
```

The imports of the Mock files will follow the same structure as the source files, relative to the root folder:
##### myClassMocks.h
```cpp
#include <myClass.h>
```

##### fooMocks.h
```cpp
#include <foo/foo.h>
```


### Namespace support

If a class is inside a namespace, the generated mock will also be inside the same namespace.

##### foo/foo.h
```cpp
//imports
namespace foo {
    class Foo {
    public:
        virtual ~Foo() = default;
        virtual void fooMethod() = 0;
    };
}
```

##### foo/fooMocks.h
```cpp
#include <foo/foo.h>
#include <gmock/gmock.h>

namespace foo { 
    class FooMock : public Foo {
    public:
        MOCK_METHOD(void, fooMethod, (), (override));
        
    };
}
```

### uninstall

```bash
rm -f $(which gmock-code-gen)
```
