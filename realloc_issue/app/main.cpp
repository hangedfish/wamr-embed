#include <fstream>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <thread>
#include <mutex>
#include <cstdint>
#include <unistd.h>
#include <wasm_export.h>

static void init_wamr(){
    static std::once_flag flag{};
    std::call_once(flag, [](){
        RuntimeInitArgs init_args{};
        init_args.mem_alloc_type = Alloc_With_Allocator;
        init_args.mem_alloc_option.allocator.free_func = (void*) ::free;
        init_args.mem_alloc_option.allocator.malloc_func = (void*) ::malloc;
        init_args.mem_alloc_option.allocator.realloc_func = (void*) ::realloc;
        init_args.max_thread_num = 4;
        wasm_runtime_full_init(&init_args);
    });
}

auto main(int argc, char* argv[]) -> int {
    std::ifstream script_file("script.wasm", std::ios::binary);
    if (!script_file.is_open()) {
        std::cout << "fail to open script.wasm" << std::endl;
        return -1;
    }
    std::vector<char> script_data((std::istreambuf_iterator<char>(script_file)),std::istreambuf_iterator<char>());
    script_file.close();

    uint32_t stack_size = 2*1024*1024;
    uint32_t heap_size = 32*1024*1024;

    init_wamr();
    std::array<char, 128> errmsg{};
    auto module = wasm_runtime_load((uint8_t*)script_data.data(), script_data.size(), errmsg.data(), errmsg.size());
    if (module == nullptr) {
        std::cout << errmsg.data() << std::endl;
        return 1;
    }

    auto module_inst = wasm_runtime_instantiate(module, stack_size, heap_size, errmsg.data(), errmsg.size());
    if (module_inst == nullptr) {
        std::cout << errmsg.data() << std::endl;
        return 2;
    }

    auto main_exec_env = wasm_runtime_create_exec_env(module_inst, stack_size);
    if (main_exec_env == nullptr) {
        std::cout << wasm_runtime_get_exception(module_inst) << std::endl;
        return 3;
    }

    auto func = wasm_runtime_lookup_function(module_inst, "test", nullptr);
    if (nullptr == func) {
        std::cout << "fail to lookup funcion" << std::endl;
        return 4;
    }
    bool ok = wasm_runtime_call_wasm(main_exec_env, func, 0, nullptr);
    if (!ok) {
        std::cout << wasm_runtime_get_exception(module_inst) << std::endl;
        return 5;
    }
    
    wasm_runtime_deinstantiate(module_inst);
    wasm_runtime_unload(module);

    std::cout << "done" << std::endl;
    return 0;
}