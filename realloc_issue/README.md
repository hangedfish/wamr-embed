# `realloc` issue

build

```
$ cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug; cmake --build build
$ cd build
$ ./app/app
holder=0x10428
buf=0x0 

ASSERTION FAILED: _ret == 0, at file /Users/admin/wasm-embed/wamr/wasm-micro-runtime/core/shared/mem-alloc/ems/ems_alloc.c, line 595
[1]    27098 abort      ./app/app
```

backtrace at ems_alloc.c:595
```
Console is in 'commands' mode, prefix expressions with '?'.
Launching: /Users/admin/wasm-embed/build/realloc_issue/app/app
Launched process 27269
bt
* thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 2.1
  * frame #0: 0x0000000100009c78 app`gc_realloc_vo(vheap=0x0000000100404080, ptr=0x0000000101000000, size=1256) at ems_alloc.c:595:13
    frame #1: 0x000000010000ba74 app`mem_allocator_realloc(allocator=0x0000000100404080, ptr=0x0000000101000000, size=1256) at mem_alloc.c:49:12
    frame #2: 0x0000000100050f24 app`wasm_module_realloc(module_inst=0x0000000100304540, ptr=0, size=1256, p_native_addr=0x0000000000000000) at wasm_runtime.c:1920:16
    frame #3: 0x00000001000298e8 app`wasm_runtime_module_realloc(module_inst=0x0000000100304540, ptr=0, size=1256, p_native_addr=0x0000000000000000) at wasm_runtime_common.c:1914:16
    frame #4: 0x000000010000f5dc app`realloc_wrapper(exec_env=0x0000000108008000, ptr=0, new_size=1256) at libc_builtin_wrapper.c:676:12
    frame #5: 0x000000010002db5c app`call_func at invokeNative_aarch64.s:71
    frame #6: 0x0000000100039fa4 app`wasm_interp_call_func_native(module_inst=<unavailable>, exec_env=<unavailable>, cur_func=<unavailable>, prev_frame=<unavailable>) at wasm_interp_fast.c:881:15
    frame #7: 0x000000010003938c app`wasm_interp_call_func_bytecode(module=0x0000000100304540, exec_env=0x0000000108008000, cur_func=0x0000600003704060, prev_frame=0x0000000108008138) at wasm_interp_fast.c:3666:17
    frame #8: 0x0000000100039a30 app`wasm_interp_call_wasm(module_inst=0x0000000100304540, exec_env=0x0000000108008000, function=0x0000600003704090, argc=0, argv=0x0000000000000000) at wasm_interp_fast.c:3840:9
    frame #9: 0x00000001000508ac app`wasm_call_function(exec_env=0x0000000108008000, function=0x0000600003704090, argc=0, argv=0x0000000000000000) at wasm_runtime.c:1717:5
    frame #10: 0x0000000100028b0c app`wasm_runtime_call_wasm(exec_env=0x0000000108008000, function=0x0000600003704090, argc=0, argv=0x0000000000000000) at wasm_runtime_common.c:1418:15
    frame #11: 0x0000000100004bf0 app`main(argc=1, argv=0x000000016fdff300) at main.cpp:63:15
    frame #12: 0x00000001000a1088 dyld`start + 516
```

