# common libraries
## Why?
- I have worked on many projects where they had their custom logging, exceptions, thread handling,  ... everything with MACRO hell (hundreds/thousands of macros) => I want to know, why they choose this approach and how it was created.
- I wanna see how it can be done with newest standards
- I need practice
- My codebase need some simple error handling ...

## How
- Using experimental c++20
- Using unit tests
- Avoiding macros as long as it takes
- Using KIFS (hopefully)
- Use different approach to different problems

## What
- Code is written by CLion, some files are only CLion specific
- Default enviroment is Linux Mint
- Code will be static libraries
- Unit test will be done by google tests - see https://github.com/google/googletest
- Custom exceptions
- Custom loggers for
    - single thread
    - multithread (**TODO**)
    - multiprocess (**TODO**)
- Template version (**TODO**)
- Version for std::wstring  (**TODO**)

## Warning
- This is **experiment**, feel free to comment or expand - just **do not use it** in your production code
- I am trying to understand this stuff
- Some stuff might not work outside of CLion - do not know that editor enough (yet)
