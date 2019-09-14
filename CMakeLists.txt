cmake_minimum_required(VERSION 2.8) 					# Проверка версии CMake.
                                                                        # Если версия установленой программы
                                                                        # старее указаной, произайдёт аварийный выход.
include_directories(contib/cpp-httplib)
add_executable(main main.cpp)          					# Создает исполняемый файл с именем main
                                                                        # из исходника main.cpp
