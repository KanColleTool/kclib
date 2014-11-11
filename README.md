kclib
=====

This is, basically, all the copypaste and boilerplate that has been in the [KCT](https://github.com/KanColleTool) programs since the very beginning, split out into a neat, portable little library.

This is how it should have been done from the start, but at the start, we used `qmake`, which is absolutely awful with libraries. Better late than never.

The existing classes (`KCTranslator`, `KVTranslator`, `[KCTranslator]`, etc) will be refactored into wrappers around shared library functionality, both to maintain interface compatibility, and because `kclib` very intentionally does not have a networking layer - this is instead up to the program.
