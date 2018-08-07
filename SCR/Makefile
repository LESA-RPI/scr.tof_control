dir = ../
toolchain = x86_64-linux-g++-4.6.3-glibc-2.15
sockets = $(dir)include/3rd_party/socket.cpp/src/
tcp = $(dir)include/3rd_party/SimpleNetwork/src/

main.cpp:
	g++ main.cpp -std=c++11 -g -w -D_GLIBCXX_USE_CXX11_ABI=0 -o tof \
	-I $(dir)include/3rd_party/ \
	-I $(dir)include/iris/sensor-api \
	-I $(dir)include/3rd_party/boost-1_55_0 \
	-L $(dir)lib/$(toolchain)/iris/sensor-api/static \
	-L $(dir)lib/$(toolchain)/3rd_party/boost-1_55_0/static \
	-L /usr/include/x86_64-linux-gnu \
	-l IrmaMatrix \
	-l boost_system-mt \
	-l boost_filesystem-mt \
	-l boost_thread-mt \
	-l boost_regex-mt \
	-l boost_date_time-mt \
	-l boost_chrono-mt \
	-l boost_regex \
	-l dl \
	-l pthread \

# dir = ../
# toolchain = x86_64-linux-g++-4.6.3-glibc-2.15
# sockets = $(dir)/include/3rd_party/SimpleNetwork/src/

# main.cpp:
# 	g++ main.cpp -g -w -D_GLIBCXX_USE_CXX11_ABI=0 -o tof -std=c++11 \
# 	$(sockets)TCPClient.cpp \
# 	$(sockets)TCPServer.cpp \
# 	-I $(dir)include/3rd_party/ \
# 	-I $(dir)include/iris/sensor-api \
# 	-I $(dir)include/3rd_party/boost-1_55_0 \
# 	-I $(dir)include/3rd_party/SimpleNetwork/src \
# 	-L $(dir)lib/$(toolchain)/iris/sensor-api/static \
# 	-L $(dir)lib/$(toolchain)/3rd_party/boost-1_55_0/static \
# 	-L /usr/include/x86_64-linux-gnu \
# 	-l IrmaMatrix \
# 	-l boost_system-mt \
# 	-l boost_filesystem-mt \
# 	-l boost_thread-mt \
# 	-l boost_regex-mt \
# 	-l boost_date_time-mt \
# 	-l boost_chrono-mt \
# 	-l boost_regex \
# 	-l dl \
# 	-l pthread \
