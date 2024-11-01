project(level1)

include_directories(../deps/include)
# Specify LIB_PATH in Terminal
link_libraries("${LIB_PATH}/libncursesw.a"
        "${LIB_PATH}/libncursesw.dll.a"
        "${LIB_PATH}/libpanelw.a"
        "${LIB_PATH}/libpanelw.dll.a"
        "${LIB_PATH}/libformw.a"
        "${LIB_PATH}/libformw.dll.a"
        "${LIB_PATH}/libmenuw.a")
add_executable(p01_running_letter p01_running_letter/main.c)

add_executable(p02_is_prime p02_is_prime/main.c)

add_executable(p03_all_primes p03_all_primes/main.c)

add_executable(p04_goldbach p04_goldbach/main.c)

add_executable(p05_encrypt_decrypt p05_encrypt_decrypt/main.c)

add_executable(p06_hanoi p06_hanoi/main.c)

add_executable(p07_maze p07_maze/main.c)

add_executable(p08_push_boxes p08_push_boxes/main.c)

add_executable(p09_linked_list p09_linked_list/main.c)

add_executable(p10_warehouse p10_warehouse/main.c
        p10_warehouse/item.h
        p10_warehouse/item.c
        p10_warehouse/ui.h
        p10_warehouse/ui.c
)