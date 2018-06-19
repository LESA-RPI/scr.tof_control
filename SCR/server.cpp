class Server {

	public:

		Server(int port);
		std::string listen();
		int get_port();
		void send(const std::string&);

	private:

		int port;
};
