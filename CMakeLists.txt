cmake_minimum_required(VERSION 3.15)
project(gqrx_cpp_scanner)

set(CMAKE_CXX_STANDARD 14)

add_executable(gqrx_cpp_scanner main.cpp Connector.cpp Connector.h ConnectorException.h GqrxManager.cpp GqrxManager.h GqrxManager.cpp GqrxManager.h GqrxManagerException.h)
