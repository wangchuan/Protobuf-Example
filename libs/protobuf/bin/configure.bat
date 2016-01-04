set SRC_DIR=./
set DST_DIR=../
protoc -I=%SRC_DIR% --cpp_out=%DST_DIR% %SRC_DIR%/lm.helloworld.proto
