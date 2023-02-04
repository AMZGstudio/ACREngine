#pragma once

#include <set>
#include <string>
#include <fstream>
#include <format>

class Leaderboard
{
private:
	const std::string path = "leaderboard.txt";
	Space board;

	struct SortPair
	{
		bool operator()(const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2) const
		{
			return p1.second > p2.second;
		}
	};

public:
	std::multiset<std::pair<std::string, int>, SortPair> leaderboard;

	Leaderboard(Space leaderboardSpace)
	{
		board = leaderboardSpace;
	}

	void draw()
	{
		drawText(Centered, board.startY - 10, "Leaderboard:", Pzim, White);
		int y = 0;

		if (leaderboard.size() == 0)
		{
			spDrawText(Centered, y+5, board, "There is nothing here!", Pzim, White);
			return;
		}

		for (auto& item : leaderboard)
		{
			std::string strScore = std::format("{}", item.second);

			spDrawText(0, y, board, std::string(item.first).c_str(), Pzim, White);
			spDrawText(spWidth(board) - txtWidth(strScore.c_str(), Pzim), y, board, strScore.c_str(), Pzim, White);
			y += 8;
		}
	}
	void loadLeaderboard()
	{
		leaderboard.clear();
		std::ifstream infile(path);

		std::string name;
		int score;

		while (infile >> name >> score)
			leaderboard.insert(std::pair<std::string, int>(name, score));
	}
	void saveLeaderboard()
	{
		std::ofstream outfile(path);

		for (auto item : leaderboard)
			outfile << item.first << " " << item.second << "\n";

		outfile.close();
	}
};

