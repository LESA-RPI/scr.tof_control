dir = ../
toolchain = x86_64-linux-g++-4.6.3-glibc-2.15


main.cpp:
	g++ -o tof main.cpp -w -D_GLIBCXX_USE_CXX11_ABI=0 \
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