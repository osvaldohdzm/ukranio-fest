set(COMMON_SRC "PaqueteDatagrama.cpp" "Respuesta.cpp" "SocketDatagrama.cpp" "Solicitud.cpp" "mensaje.h")

add_executable(mainServer mainServer.cpp ${COMMON_SRC})
