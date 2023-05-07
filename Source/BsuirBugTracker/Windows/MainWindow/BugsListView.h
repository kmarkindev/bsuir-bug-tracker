#pragma once

#include <functional>
#include "BsuirBugTracker/Windows/Controls/Controls.h"
#include "BsuirBugTracker/Storage/Bug.h"

class BugsListView : public ListView<Bug>
{
public:

	BugsListView() = default;

	BugsListView(const BugsListView&) = delete;

	BugsListView(BugsListView&& Other) noexcept = default;

	BugsListView& operator = (const BugsListView&) = delete;

	BugsListView& operator = (BugsListView&& Other) noexcept = default;

	void SetSelectEventCallback(std::function<void(int SelectedIndex, Bug* BugPtr)> NewCallback);

	int AddItem(int InsertIndex, Bug* ItemPtr) override;

protected:

	void BeginLifetime() override;

	// do not allow to change list view layout
	using ListView<Bug>::AddColumn;
	using ListView<Bug>::RemoveColumn;
	using ListView<Bug>::SetItemText;

	void HandleWMNotify(LPNMHDR NotifyInfo, WPARAM WParam, LPARAM LParam) override;

private:

	std::function<void(int SelectedIndex, Bug* BugPtr)> Callback;

};
