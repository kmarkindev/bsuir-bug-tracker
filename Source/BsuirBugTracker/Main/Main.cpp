#include <Windows.h>
#include <fstream>

#include "BsuirBugTracker/Types/Types.h"
#include "BsuirBugTracker/Storage/Storage.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Storage storage {};

	Bug bug1 { L"123-456-789" };
	Bug bug2 { L"abc-def-chg" };

	bug1.SetUpdatedAt(std::chrono::sys_seconds {std::chrono::sys_days{std::chrono::year_month_day{std::chrono::year{2023}, std::chrono::month{5}, std::chrono::day{4}}}});
	bug2.SetCreatedAt(std::chrono::seconds{25});

	bug2.AddAttachment(Attachment{L"TestFileName.txt"});

	storage.AddBug(std::move(bug1));
	storage.AddBug(std::move(bug2));

	std::ofstream ofstream("output.txt", std::ios::trunc);

	storage.Serialize(ofstream);

	ofstream.close();

	Storage storage2 {};

	std::ifstream ifstream("output.txt");

	storage2.DeSerialize(ifstream);

	return 7788;
}