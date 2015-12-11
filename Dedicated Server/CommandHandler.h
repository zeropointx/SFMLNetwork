#pragma once
#include <string>
#include <vector>
class CommandHandler
{
public:
	CommandHandler();
	~CommandHandler();
	bool running;
private:
	void commandThread();
	void handleCommand(std::vector<std::string> command);
};

