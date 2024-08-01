cmake_minimum_required(VERSION 3.10)

project(mosquitto_clients)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Configura le directory di inclusione e le directory delle librerie
include_directories(${GTK3_INCLUDE_DIRS} /usr/include/mosquitto)
link_directories(${GTK3_LIBRARY_DIRS} /usr/lib/x86_64-linux-gnu)

add_definitions(${GTK3_CFLAGS_OTHER})

# Definisci i sorgenti condivisi
set(shared_src client_shared.c client_shared.h client_props.c)

if (WITH_SRV)
	add_definitions("-DWITH_SRV")
endif (WITH_SRV)

set(CLIENT_INC 
    ${mosquitto_SOURCE_DIR} 
    ${mosquitto_SOURCE_DIR}/include
    ${STDBOOL_H_PATH} 
    ${STDINT_H_PATH} 
    ${PTHREAD_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR})

set(CLIENT_DIR ${mosquitto_BINARY_DIR}/lib)

if (CJSON_FOUND)
	add_definitions("-DWITH_CJSON")
	set(CLIENT_DIR "${CLIENT_DIR};${CJSON_DIR}")
	set(CLIENT_INC "${CLIENT_INC};${CJSON_INCLUDE_DIRS}")
endif()

include_directories(${CLIENT_INC})
link_directories(${CLIENT_DIR})

# Aggiungi gli eseguibili
add_executable(mosquitto_pub pub_client.c pub_shared.c ${shared_src})
add_executable(mosquitto_sub sub_client.c sub_client_output.c ${shared_src})
add_executable(mosquitto_rr rr_client.c pub_shared.c sub_client_output.c ${shared_src})

# Configura il linking delle librerie
if (CJSON_FOUND)
	target_link_libraries(mosquitto_pub ${CJSON_LIBRARIES})
	target_link_libraries(mosquitto_sub ${CJSON_LIBRARIES})
	target_link_libraries(mosquitto_rr ${CJSON_LIBRARIES})
endif()

if (WITH_STATIC_LIBRARIES)
	target_link_libraries(mosquitto_pub mosquitto_static)
	target_link_libraries(mosquitto_sub mosquitto_static)
	target_link_libraries(mosquitto_rr mosquitto_static)
else()
	target_link_libraries(mosquitto_pub mosquitto ${GTK3_LIBRARIES})
	target_link_libraries(mosquitto_sub mosquitto ${GTK3_LIBRARIES})
	target_link_libraries(mosquitto_rr mosquitto)
endif()

if (QNX)
    target_link_libraries(mosquitto_pub socket)
    target_link_libraries(mosquitto_sub socket)
    target_link_libraries(mosquitto_rr socket)
endif()

# Aggiungi il supporto per GTK+ agli eseguibili
target_link_libraries(mosquitto_pub ${GTK3_LIBRARIES})
target_link_libraries(mosquitto_sub ${GTK3_LIBRARIES})

# Installa i target
install(TARGETS mosquitto_pub RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install(TARGETS mosquitto_sub RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install(TARGETS mosquitto_rr RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

